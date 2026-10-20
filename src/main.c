#include "so_long.h"

static const char	*check_ext(char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".ber", 5) != 0)
		return ("Map file must have the .ber extension");
	return (NULL);
}

static int	print_error(const char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd((char *)msg, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game		game;
	const char	*err;

	if (argc != 2)
		return (print_error("Usage: ./so_long <map.ber>"));
	ft_bzero(&game, sizeof(game));
	err = check_ext(argv[1]);
	if (!err)
		err = map_read(&game.map, argv[1]);
	if (!err)
		err = map_check(&game.map);
	if (!err)
		err = game_init(&game);
	if (err)
	{
		cleanup(&game);
		return (print_error(err));
	}
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_loop(game.mlx);
	cleanup(&game);
	return (0);
}
