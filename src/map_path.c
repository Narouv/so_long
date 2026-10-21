/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 11:13:43 by rnauke            #+#    #+#             */
/*   Updated: 2026/10/21 11:13:44 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**dup_grid(t_map *m)
{
	char	**copy;
	int		i;

	copy = ft_calloc(m->height + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < m->height)
	{
		copy[i] = ft_strdup(m->grid[i]);
		if (!copy[i])
		{
			free_grid(copy);
			return (NULL);
		}
		i++;
	}
	return (copy);
}

static void	push(t_flood *f, int x, int y)
{
	char	c;

	c = f->cells[y][x];
	if (c == '1')
		return ;
	if (c == 'C')
		f->coll++;
	if (c == 'E')
		f->exit++;
	f->cells[y][x] = '1';
	f->queue[f->tail] = y * f->width + x;
	f->tail++;
}

static void	spread(t_flood *f)
{
	int	x;
	int	y;

	while (f->head < f->tail)
	{
		x = f->queue[f->head] % f->width;
		y = f->queue[f->head] / f->width;
		f->head++;
		push(f, x + 1, y);
		push(f, x - 1, y);
		push(f, x, y + 1);
		push(f, x, y - 1);
	}
}

const char	*map_path(t_map *m)
{
	t_flood	f;
	int		ok;

	ft_bzero(&f, sizeof(f));
	f.cells = dup_grid(m);
	f.queue = malloc(sizeof(int) * m->width * m->height);
	if (!f.cells || !f.queue)
	{
		free_grid(f.cells);
		free(f.queue);
		return ("Memory allocation failed");
	}
	f.width = m->width;
	push(&f, m->px, m->py);
	spread(&f);
	ok = (f.coll == m->coll && f.exit == 1);
	free_grid(f.cells);
	free(f.queue);
	if (!ok)
		return ("No valid path: the exit or a collectible is unreachable");
	return (NULL);
}
