/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ressalhi <ressalhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:56:11 by ressalhi          #+#    #+#             */
/*   Updated: 2022/11/05 13:35:55 by ressalhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_rays(t_game *game)
{
	double	x;
	double	y;

	game->r = fixang(game->pa - 30.0);
	game->i = 0;
	while (game->i < WIN_WIDTH)
	{
		x = cos(degtorad(game->r));
		y = sin(degtorad(game->r));
		ft_drawl(game, x, y);
		ft_sprite(game, x*2, y*2);
		game->i++;
		game->r += 60.0 / WIN_WIDTH;
		game->r = fixang(game->r);
	}
}

int	key_hook2(int keycode, t_game *game)
{
	if (keycode == UP)
		game->keys[0] = 0;
	else if (keycode == DOWN)
		game->keys[1] = 0;
	else if (keycode == RIGHT)
		game->keys[2] = 0;
	else if (keycode == LEFT)
		game->keys[3] = 0;
	else if (keycode == ROTATE_RIGHT)
		game->keys[4] = 0;
	else if (keycode == ROTATE_LEFT)
		game->keys[5] = 0;
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
	else if (keycode == ROTATE_RIGHT)
		game->keys[4] = 1;
	else if (keycode == ROTATE_LEFT)
		game->keys[5] = 1;
	else if (keycode == E)
		ft_opendoor(game);
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

char	*get_tex(int i)
{
	char	*s;

	s = ft_strdup("xpms/fire/fire1.xpm");
	s[14] = i + 48;
	return (s);
}

void	get_str_path(t_game *game)
{
	int	i;

	game->spritetex = malloc(sizeof(char *) * 9);
	i = 0;
	while (i < 8)
	{
		game->spritetex[i] = get_tex(i + 1);
		i++;
	}
	game->spritetex[i] = 0;
}
void	get_sprites(t_game *game)
{
	int	i;
	int	hi;

	get_str_path(game);
	game->sprite = malloc(sizeof(void *) * 8);
	game->spriteadr = malloc(sizeof(char *) * 9);
	i = 0;
	while (i < 8)
	{
		game->sprite[i] = mlx_xpm_file_to_image(game->mlx, game->spritetex[i], &hi, &hi);
		i++;
	}
	i = 0;
	while (i < 8)
	{
		game->spriteadr[i] = mlx_get_data_addr(game->sprite[i], &game->bits_per_pixel2[i], &game->line_length2[i], &game->endian2[i]);
		i++;
	}
	game->spriteadr[i] = 0;
}

void	get_img_path(t_game *game)
{
	int	hi;

	game->keys = ft_calloc(sizeof(int), 6);
	game->bits_per_pixel2 = ft_calloc(sizeof(int), 9);
	game->line_length2 = ft_calloc(sizeof(int), 9);
	game->endian2 = ft_calloc(sizeof(int), 9);
	game->speed = 1;
	game->offset = 0;
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HIGHT);
	//game->mini_map = mlx_new_image(game->mlx, 200, 200);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel, &game->line_length, &game->endian);
	get_player_cord(game);
	game->mousex = WIN_WIDTH / 2;
	game->mousey = WIN_HIGHT / 2;
	game->index = 0;
	get_sprites(game);
	game->pdx = cos(degtorad(game->pa)) * (P_SPEED*game->speed);
	game->pdy = sin(degtorad(game->pa)) * (P_SPEED*game->speed);
	game->tex1 = mlx_xpm_file_to_image(game->mlx, "xpms/stone/stone.xpm", &hi, &hi);
	game->tadr1 = mlx_get_data_addr(game->tex1, &game->bits_per_pixel1, &game->line_length1, &game->endian1);
	game->door = mlx_xpm_file_to_image(game->mlx, "xpms/door/door.xpm", &hi, &hi);
	game->dooradr = mlx_get_data_addr(game->door, &game->bits_per_pixel6, &game->line_length6, &game->endian6);
	// game->sprite = mlx_xpm_file_to_image(game->mlx, "xpms/fire/fire1.xpm", &hi, &hi);
	// game->spriteadr = mlx_get_data_addr(game->sprite, &game->bits_per_pixel2, &game->line_length2, &game->endian2);
	game->door2 = mlx_xpm_file_to_image(game->mlx, "xpms/door/door2.xpm", &hi, &hi);
	game->door2adr = mlx_get_data_addr(game->door2, &game->bits_per_pixel8, &game->line_length8, &game->endian8);
	draw_rays(game);
}

void draw_player(t_game *game, int x, int y)
{
	int	xi;
	int	yi;

	yi = 0;
	while (yi < 10)
	{
		xi = 0;
		while (xi < 10)
		{
			//if (dist(115, 115, xi + x, yi + y) <= 10)
				my_mlx_pixel_put(game, xi + x, yi + y, 0xFF0000);
			xi++;
		}
		yi++;
	}
}

void mini_map(t_game *game)
{
	int	l;
	int xi;
	int yi;
	int	x;
	int	y;

	l = 0;
	xi = (game->px / 50)*20 - 120;
	yi = (game->py / 50)*20 - 120;
	if (xi < 0)
		xi = 0;
	if (yi < 0)
		yi = 0;
	while (game->map[l])
		l++;
	y = 0;
	while (y < 220)
	{
		x = 0;
		while (x < 220) 
		{
			if (dist(120, 120, x, y) <= 100)
			{
				if (l > ((y + yi )/ 20) && game->map[((y + yi )/ 20)]
					&& ft_strlen(game->map[((y + yi )/ 20)]) > ((x + xi) / 20)
					&& game->map[((y + yi )/ 20)][((x + xi) / 20)] != '1')
					my_mlx_pixel_put(game, x, y, 0x0A8500);
				else
					my_mlx_pixel_put(game, x, y, 0x808080);
			}
			x++;
		}
		y++;
	}
	draw_player(game, 115, 115);
}

int	ft_hook(t_game *game)
{
	mlx_destroy_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HIGHT);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel, &game->line_length, &game->endian);
	// ft_anime(game);
	if (game->keys[0])
		ft_moveup(game);
	if (game->keys[1])
		ft_movedown(game);
	if (game->keys[2])
		ft_moveright(game);
	if (game->keys[3])
		ft_moveleft(game);
	if (game->keys[4])
		ft_rotateright(game);
	if (game->keys[5])
		ft_rotateleft(game);
	game->index++;
	if (game->index > 14)
		game->index = 0;
	draw_rays(game);
	mini_map(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
	return (0);
}

int		key_hook3(int x, int y, t_game *game)
{
	if ((x > 0 && x < WIN_WIDTH) && (y > 0 && y < WIN_HIGHT))
	{
		if (game->mousex < x)
		{
			game->mousex = x;
			ft_rotateright(game);
		}
		else if (game->mousex > x)
		{
			game->mousex = x;
			ft_rotateleft(game);
		}
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
	mlx_hook(game->mlx_win, 6, 1L << 2, key_hook3, game);
	mlx_loop_hook(game->mlx, ft_hook, game);
	mlx_loop(game->mlx);
}

/*
	todo list:
		problem in getcolor 
*/