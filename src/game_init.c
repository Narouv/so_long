/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnauke <rnauke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 11:13:32 by rnauke            #+#    #+#             */
/*   Updated: 2026/10/21 11:13:33 by rnauke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static mlx_image_t	*load_img(mlx_t *mlx, char *path)
{
	mlx_texture_t	*tex;
	mlx_image_t		*img;

	tex = mlx_load_png(path);
	if (!tex)
		return (NULL);
	img = mlx_texture_to_image(mlx, tex);
	mlx_delete_texture(tex);
	if (!img)
		return (NULL);
	if (!mlx_resize_image(img, TILE, TILE))
	{
		mlx_delete_image(mlx, img);
		return (NULL);
	}
	return (img);
}

static const char	*load_all(t_game *g)
{
	g->img_floor = load_img(g->mlx, FLOOR_PNG);
	g->img_wall = load_img(g->mlx, WALL_PNG);
	g->img_item = load_img(g->mlx, ITEM_PNG);
	g->img_exit = load_img(g->mlx, EXIT_PNG);
	g->img_player = load_img(g->mlx, PLAYER_PNG);
	if (!g->img_floor || !g->img_wall || !g->img_item
		|| !g->img_exit || !g->img_player)
		return (mlx_strerror(mlx_errno));
	return (NULL);
}

static int	draw_layer(t_game *g, mlx_image_t *img, char *cells)
{
	int	x;
	int	y;

	y = 0;
	while (y < g->map.height)
	{
		x = 0;
		while (x < g->map.width)
		{
			if (ft_strchr(cells, g->map.grid[y][x])
				&& mlx_image_to_window(g->mlx, img, x * TILE, y * TILE) < 0)
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

static const char	*draw_map(t_game *g)
{
	if (!draw_layer(g, g->img_floor, "01CEP")
		|| !draw_layer(g, g->img_wall, "1")
		|| !draw_layer(g, g->img_item, "C")
		|| !draw_layer(g, g->img_exit, "E")
		|| !draw_layer(g, g->img_player, "P"))
		return (mlx_strerror(mlx_errno));
	return (NULL);
}

const char	*game_init(t_game *g)
{
	const char	*err;
	int32_t		w;
	int32_t		h;

	w = g->map.width * TILE;
	h = g->map.height * TILE;
	g->mlx = mlx_init(w, h, "so_long", false);
	if (!g->mlx)
		return (mlx_strerror(mlx_errno));
	err = load_all(g);
	if (!err)
		err = draw_map(g);
	return (err);
}
