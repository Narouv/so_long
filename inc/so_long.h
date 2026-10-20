/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: login <login@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 12:00:00 by login             #+#    #+#             */
/*   Updated: 2026/09/29 12:00:00 by login            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include "MLX42/MLX42.h"

# define TILE 64
# define READ_SIZE 4096

# define FLOOR_PNG "textures/floor.png"
# define WALL_PNG "textures/wall.png"
# define ITEM_PNG "textures/collectible.png"
# define EXIT_PNG "textures/exit.png"
# define PLAYER_PNG "textures/player.png"

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		coll;
	int		players;
	int		exits;
	int		px;
	int		py;
}	t_map;

typedef struct s_flood
{
	char	**cells;
	int		*queue;
	int		head;
	int		tail;
	int		width;
	int		coll;
	int		exit;
}	t_flood;

typedef struct s_game
{
	mlx_t		*mlx;
	t_map		map;
	mlx_image_t	*img_floor;
	mlx_image_t	*img_wall;
	mlx_image_t	*img_item;
	mlx_image_t	*img_exit;
	mlx_image_t	*img_player;
	int			moves;
}	t_game;

const char	*map_read(t_map *map, char *path);
const char	*map_check(t_map *map);
const char	*map_path(t_map *map);
const char	*game_init(t_game *game);
void		key_hook(mlx_key_data_t keydata, void *param);
void		free_grid(char **grid);
void		cleanup(t_game *game);

#endif
