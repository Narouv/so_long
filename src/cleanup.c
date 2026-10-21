/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 11:13:27 by rnauke            #+#    #+#             */
/*   Updated: 2026/10/21 11:13:28 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_grid(char **grid)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

void	cleanup(t_game *game)
{
	free_grid(game->map.grid);
	game->map.grid = NULL;
	if (game->mlx)
		mlx_terminate(game->mlx);
	game->mlx = NULL;
}
