#include "so_long.h"

static char	*append(char *old, size_t old_len, char *buf, size_t n)
{
	char	*new;

	new = malloc(old_len + n + 1);
	if (!new)
	{
		free(old);
		return (NULL);
	}
	ft_memcpy(new, old, old_len);
	ft_memcpy(new + old_len, buf, n);
	new[old_len + n] = '\0';
	free(old);
	return (new);
}

static char	*read_all(int fd)
{
	char	buf[READ_SIZE];
	char	*all;
	size_t	len;
	ssize_t	n;

	all = malloc(1);
	if (!all)
		return (NULL);
	all[0] = '\0';
	len = 0;
	n = read(fd, buf, READ_SIZE);
	while (n > 0)
	{
		all = append(all, len, buf, n);
		if (!all)
			return (NULL);
		len += n;
		n = read(fd, buf, READ_SIZE);
	}
	if (n < 0)
		free(all);
	if (n < 0)
		return (NULL);
	return (all);
}

static int	count_lines(char *s)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			n++;
		i++;
	}
	if (i > 0 && s[i - 1] != '\n')
		n++;
	return (n);
}

static char	**split_lines(char *s, int lines)
{
	char	**grid;
	int		i;
	int		len;

	grid = ft_calloc(lines + 1, sizeof(char *));
	if (!grid)
		return (NULL);
	i = 0;
	while (i < lines)
	{
		len = 0;
		while (s[len] && s[len] != '\n')
			len++;
		grid[i] = ft_substr(s, 0, len);
		if (!grid[i])
		{
			free_grid(grid);
			return (NULL);
		}
		s += len + 1;
		i++;
	}
	return (grid);
}

const char	*map_read(t_map *map, char *path)
{
	int		fd;
	char	*all;
	int		lines;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return ("Cannot open the map file");
	all = read_all(fd);
	close(fd);
	if (!all)
		return ("Cannot read the map file");
	lines = count_lines(all);
	if (lines > 0)
		map->grid = split_lines(all, lines);
	free(all);
	if (lines == 0)
		return ("The map file is empty");
	if (!map->grid)
		return ("Memory allocation failed");
	map->height = lines;
	map->width = ft_strlen(map->grid[0]);
	return (NULL);
}
