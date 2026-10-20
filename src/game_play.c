#include "so_long.h"

static void	collect(t_game *g, int x, int y)
{
	mlx_image_t	*item;
	size_t		i;

	g->map.grid[y][x] = '0';
	g->map.coll--;
	item = g->img_item;
	i = 0;
	while (i < item->count)
	{
		if (item->instances[i].x == x * TILE
			&& item->instances[i].y == y * TILE)
			item->instances[i].enabled = false;
		i++;
	}
}

static void	print_moves(int moves)
{
	ft_putstr_fd("Moves: ", 1);
	ft_putnbr_fd(moves, 1);
	ft_putchar_fd('\n', 1);
}

static void	move(t_game *g, int dx, int dy)
{
	int	nx;
	int	ny;

	nx = g->map.px + dx;
	ny = g->map.py + dy;
	if (g->map.grid[ny][nx] == '1')
		return ;
	g->map.px = nx;
	g->map.py = ny;
	g->img_player->instances[0].x = nx * TILE;
	g->img_player->instances[0].y = ny * TILE;
	g->moves++;
	print_moves(g->moves);
	if (g->map.grid[ny][nx] == 'C')
		collect(g, nx, ny);
	if (g->map.grid[ny][nx] == 'E' && g->map.coll == 0)
	{
		ft_putstr_fd("You escaped!\n", 1);
		mlx_close_window(g->mlx);
	}
}

void	key_hook(mlx_key_data_t k, void *param)
{
	t_game	*g;

	g = param;
	if (k.action != MLX_PRESS)
		return ;
	if (k.key == MLX_KEY_ESCAPE)
		mlx_close_window(g->mlx);
	else if (k.key == MLX_KEY_W || k.key == MLX_KEY_UP)
		move(g, 0, -1);
	else if (k.key == MLX_KEY_S || k.key == MLX_KEY_DOWN)
		move(g, 0, 1);
	else if (k.key == MLX_KEY_A || k.key == MLX_KEY_LEFT)
		move(g, -1, 0);
	else if (k.key == MLX_KEY_D || k.key == MLX_KEY_RIGHT)
		move(g, 1, 0);
}
