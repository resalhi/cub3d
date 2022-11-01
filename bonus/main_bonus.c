/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:56:11 by ressalhi          #+#    #+#             */
/*   Updated: 2022/11/01 08:08:34 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_rays(t_game *game)
{
	double	x, y;

	game->r = fixang(game->pa - 30.0);
	game->i = 0;
	while (game->i < WIN_WIDTH)
	{
		x = cos(degtorad(game->r));
		y = sin(degtorad(game->r));
		ft_drawl(game, x, y);
		game->i++;
		game->r += 60.0 / WIN_WIDTH;
		game->r = fixang(game->r);
	}
	ft_drawc(game, 0);
}

int	key_hook2(int keycode, t_game *game)
{
	int hi;

	if (keycode == UP)
		game->keys[0] = 0;
	else if (keycode == DOWN)
		game->keys[1] = 0;
	else if (keycode == RIGHT)
		game->keys[2] = 0;
	else if (keycode == LEFT)
		game->keys[3] = 0;
	else if (keycode == SPACE)
	{
		game->keys[4] = 0;
		game->hand = mlx_xpm_file_to_image(game->mlx, "xpms/hand/hand1.xpm", &hi, &hi);
	}
	else if (keycode == ROTATE_RIGHT)
		game->keys[5] = 0;
	else if (keycode == ROTATE_LEFT)
		game->keys[6] = 0;
	else if (keycode == 48)
		game->speed = 1;
	return (0);
}

int	key_hook1(int keycode, t_game *game)
{
	if (keycode == 53)
		ft_error("GAME CLOSED\n");
	else if (keycode == UP)
		game->keys[0] = 1;
	else if (keycode == DOWN)
		game->keys[1] = 1;
	else if (keycode == RIGHT)
		game->keys[2] = 1;
	else if (keycode == LEFT)
		game->keys[3] = 1;
	else if (keycode == E)
		ft_opendoor(game);
	else if (keycode == SPACE)
		game->keys[4] = 1;
	else if (keycode == ROTATE_RIGHT)
		game->keys[5] = 1;
	else if (keycode == ROTATE_LEFT)
		game->keys[6] = 1;
	else if (keycode == Q)
		ft_build(game);
	else if (keycode == X)
		ft_destroy(game);
	else if (keycode == 48)
		game->speed = 2;
	return (0);
}

void	get_player_angle(t_game *game, char c)
{
	if (c == 'N')
		game->pa = 270.0;
	else if (c == 'S')
		game->pa = 90.0;
	else if (c == 'W')
		game->pa = 180.0;
	else if (c == 'E')
		game->pa = 0;
}

void	get_player_cord(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S' ||
				game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				game->px = j * 51.5;
				game->py = i * 51.5;
				get_player_angle(game, game->map[i][j]);
				game->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

void	get_img_path(t_game *game)
{
	int	hi;

	game->lineo = malloc(sizeof(float) * WIN_WIDTH);
	game->lineh = malloc(sizeof(float) * WIN_WIDTH);
	game->keys = calloc(sizeof(int), 7);
	game->pix = 10;
	game->offset = 3;
	game->cpa = 3;
	game->barn = 0;
	game->speed = 1;
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HIGHT);
	//game->mini_map = mlx_new_image(game->mlx, 200, 200);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel, &game->line_length, &game->endian);
	get_player_cord(game);
	game->pdx = cos(degtorad(game->pa)) * (P_SPEED*game->speed);
	game->pdy = sin(degtorad(game->pa)) * (P_SPEED*game->speed);
	game->tex1 = mlx_xpm_file_to_image(game->mlx, "xpms/stone/stone.xpm", &hi, &hi);
	game->tadr1 = mlx_get_data_addr(game->tex1, &game->bits_per_pixel1, &game->line_length1, &game->endian1);
	game->sky = mlx_xpm_file_to_image(game->mlx, "xpms/sky/sky5.xpm", &hi, &hi);
	game->skyadr = mlx_get_data_addr(game->sky, &game->bits_per_pixel5, &game->line_length5, &game->endian5);
	game->door = mlx_xpm_file_to_image(game->mlx, "xpms/door/door.xpm", &hi, &hi);
	game->dooradr = mlx_get_data_addr(game->door, &game->bits_per_pixel6, &game->line_length6, &game->endian6);
	game->door2 = mlx_xpm_file_to_image(game->mlx, "xpms/door/door2.xpm", &hi, &hi);
	game->door2adr = mlx_get_data_addr(game->door2, &game->bits_per_pixel8, &game->line_length8, &game->endian8);
	creat_str_bar(game);
	game->bar = mlx_xpm_file_to_image(game->mlx, game->bartex[game->barn], &hi, &hi);
	game->hand = mlx_xpm_file_to_image(game->mlx, "xpms/hand/hand1.xpm", &hi, &hi);
	draw_rays(game);
	// mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
	// mlx_put_image_to_window(game->mlx, game->mlx_win, game->hand, 850, 900);
	// mlx_put_image_to_window(game->mlx, game->mlx_win, game->bar, 170, 920);
}

void mini_map(t_game *game)
{
	int	x;
	int	y;

	y = 20;
	while (y < 200)
	{
		x = 20;
		while (x < 200)
		{
			my_mlx_pixel_put(game, x, y, 0);
			x++;
		}
		y++;
	}
}

int	ft_hook(t_game *game)
{
	mlx_destroy_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HIGHT);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel, &game->line_length, &game->endian);
	if (game->keys[4])
		ft_anime(game);
	if (game->keys[0])
	{
		game->cpa *= -1;
		ft_moveup(game);
	}
	if (game->keys[1])
	{
		game->cpa *= -1;
		ft_movedown(game);
	}
	if (game->keys[2])
		ft_moveright(game);
	if (game->keys[3])
		ft_moveleft(game);
	if (game->keys[5])
		ft_rotateright(game);
	if (game->keys[6])
		ft_rotateleft(game);
	draw_rays(game);
	mini_map(game);
	game->pix+=3;
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->hand, 0+game->cpa, 500);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->bar, 170, 920);
	return (0);
}

int		key_hook3(int keycode, int x, int y, t_game *game)
{
	int hi;
	
	(void)x;
	(void)y;
	if (keycode == 4)
	{
		game->barn++;
		if (game->barn > 8)
			game->barn = 0;
		mlx_destroy_image(game->mlx, game->bar);
		game->bar = mlx_xpm_file_to_image(game->mlx, game->bartex[game->barn], &hi, &hi);
	}
	else if (keycode == 5)
	{
		game->barn--;
		if (game->barn < 0)
			game->barn = 8;
		mlx_destroy_image(game->mlx, game->bar);
		game->bar = mlx_xpm_file_to_image(game->mlx, game->bartex[game->barn], &hi, &hi);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
		ft_error("Error\nWrong Number Of Args\n");
	game = malloc(sizeof(t_game));
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HIGHT, "cub3d");
	game->floor_c = -1;
	game->ceilling_c = -1;
	game->no_textr = NULL;
	game->so_textr = NULL;
	game->we_textr = NULL;
	game->ea_textr = NULL;
	parse(game, av[1]);
	get_img_path(game);
	mlx_hook(game->mlx_win, 2, 1L << 0, key_hook1, game);
	mlx_hook(game->mlx_win, 3, 1L << 1, key_hook2, game);
	mlx_hook(game->mlx_win, 4, 1L << 2, key_hook3, game);
	mlx_loop_hook(game->mlx, ft_hook, game);
	mlx_loop(game->mlx);
}
