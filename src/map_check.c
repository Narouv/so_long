/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 11:13:39 by rnauke            #+#    #+#             */
/*   Updated: 2026/10/21 11:13:40 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static const char	*check_rect(t_map *m)
{
	int	i;

	i = 0;
	while (i < m->height)
	{
		if ((int)ft_strlen(m->grid[i]) != m->width)
			return ("The map is not rectangular");
		i++;
	}
	return (NULL);
}

static const char	*check_border(t_map *m)
{
	int	i;

	i = 0;
	while (i < m->width)
	{
		if (m->grid[0][i] != '1' || m->grid[m->height - 1][i] != '1')
			return ("The map is not surrounded by walls");
		i++;
	}
	i = 0;
	while (i < m->height)
	{
		if (m->grid[i][0] != '1' || m->grid[i][m->width - 1] != '1')
			return ("The map is not surrounded by walls");
		i++;
	}
	return (NULL);
}

static int	tally(t_map *m, int x, int y)
{
	char	c;

	c = m->grid[y][x];
	if (c == 'P')
	{
		m->players++;
		m->px = x;
		m->py = y;
	}
	else if (c == 'E')
		m->exits++;
	else if (c == 'C')
		m->coll++;
	else if (c != '0' && c != '1')
		return (0);
	return (1);
}

static const char	*check_cells(t_map *m)
{
	int	x;
	int	y;

	y = 0;
	while (y < m->height)
	{
		x = 0;
		while (x < m->width)
		{
			if (!tally(m, x, y))
				return ("The map contains an invalid character");
			x++;
		}
		y++;
	}
	if (m->players != 1)
		return ("The map needs exactly one player (P)");
	if (m->exits != 1)
		return ("The map needs exactly one exit (E)");
	if (m->coll < 1)
		return ("The map needs at least one collectible (C)");
	return (NULL);
}

const char	*map_check(t_map *m)
{
	const char	*err;

	if (m->width < 3 || m->height < 3)
		return ("The map is too small");
	err = check_rect(m);
	if (!err)
		err = check_border(m);
	if (!err)
		err = check_cells(m);
	if (!err)
		err = map_path(m);
	return (err);
}
