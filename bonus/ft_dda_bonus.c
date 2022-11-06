/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dda_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ressalhi <ressalhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:13:39 by ressalhi          #+#    #+#             */
/*   Updated: 2022/11/06 23:52:50 by ressalhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_drawline3(t_game *game, float y1, double lineh, float x)
{
	char	*dst;
	int		i;

	i = 0;
	if (lineh > WIN_HIGHT)
		i = (lineh - WIN_HIGHT) / 2;
	while (i < lineh)
	{
		if (y1 >= WIN_HIGHT)
			break ;
		dst = game->tadr1 + (int)(i * (IMG_W1 / lineh)) % IMG_W1 * game->ll1 + (int)(x * IMG_W1 / 50) % IMG_W1 * (game->bpp1 / 8);
		my_mlx_pixel_put(game, game->i, y1, *(unsigned int *)dst);
		y1++;
		i++;
	}
}

void	ft_drawline4(t_game *game, float y1, double lineh, float x)
{
	char	*dst;
	int		i;

	i = 0;
	if (lineh > WIN_HIGHT)
		i = (lineh - WIN_HIGHT) / 2;
	while (i < lineh)
	{
		if (y1 >= WIN_HIGHT)
			break ;
		dst = game->dooradr + (int)(i * (DOOR_W / lineh)) % DOOR_W * game->ll6 + (int)(x * DOOR_W / 50) % DOOR_W * (game->bpp6/ 8);
		if (*(unsigned int *)dst != 0xFF000000)
			my_mlx_pixel_put(game, game->i, y1, *(unsigned int *)dst);
		y1++;
		i++;
	}
}

void	ft_drawline5(t_game *game, float y1, double lineh, float x)
{
	char	*dst;
	int		i;

	i = 0;
	if (lineh > WIN_HIGHT)
		i = (lineh - WIN_HIGHT) / 2;
	while (i < lineh)
	{
		if (y1 >= WIN_HIGHT)
			break ;
		dst = game->spriteadr[game->index/2] + (int)(i * (SPRITE_W / lineh)) % SPRITE_W * game->ll2[game->index/2] + (int)(x * SPRITE_W / 50) % SPRITE_W * (game->bpp2[game->index/2]/ 8);
		if (*(unsigned int *)dst != 0xFF000000)
			my_mlx_pixel_put(game, game->i, y1, *(unsigned int *)dst);
		y1++;
		i++;
	}
}

void	ft_drawf(t_game *game, double lineh, float lineo)
{
	int		j;

	j = (int)(lineh + lineo);
	while (j < WIN_HIGHT)
	{
		my_mlx_pixel_put(game, game->i, j, 0x0A8500);
		j++;
	}
}

void	ft_drawc(t_game *game, float lineo)
{
	int	i;
	
	i = 0;
	while (i < lineo)
	{
		my_mlx_pixel_put(game, game->i, i, 0x0BFBE9);
		i++;
	}
}

void	ft_3dscene(t_game *game, float x, float y, int i)
{
	double	lineh, ch;
	float	lineo;
	double	ca, len;

	ca = fixang(game->pa - game->r);
	len = dist(game->px, game->py, x, y);
	len = len * cos(degtorad(ca));
	lineh = (50*WIN_HIGHT) / len;
	ch = lineh;
	if (lineh > WIN_HIGHT)
		lineh = WIN_HIGHT;
	lineo = (WIN_HIGHT/2.0) - (lineh / 2.0);
	if (i == 1)
		ft_drawline3(game, lineo, ch, x);
	else
		ft_drawline3(game, lineo, ch, y);
	ft_drawf(game, lineh, lineo);
	ft_drawc(game, lineo);
}

void	ft_3dscene2(t_game *game, float x, float y, int i)
{
	double	lineh, ch;
	float	lineo;
	double	ca, len;

	ca = fixang(game->pa - game->r);
	len = dist(game->px, game->py, x, y);
	len = len * cos(degtorad(ca));
	lineh = (50*WIN_HIGHT) / len;
	ch = lineh;
	if (lineh > WIN_HIGHT)
		lineh = WIN_HIGHT;
	lineo = (WIN_HIGHT/2) - (lineh / 2);
	if (i == 1)
		ft_drawline4(game, lineo, ch, x);
	else
		ft_drawline4(game, lineo, ch, y);
	ft_drawf(game, lineh, lineo);
	ft_drawc(game, lineo);
}

void	ft_castray2(t_game *game, double x, double y)
{
	double	x2;
	double	y2;

	x2 = (cos(degtorad(game->r)) * 5);
	y2 = (sin(degtorad(game->r)) * 5);
	while (1)
	{
		if (game->map[(int)y / 50][(int)(x + x2 / 16) / 50] == '1')
		{
			x += x2 / 16;
			ft_3dscene(game, x, y, 0);
			return ;
		}
		else if (game->map[(int)y / 50][(int)(x + x2 / 16) / 50] == '2')
		{
			x += x2 / 16;
			ft_3dscene2(game, x, y, 0);
			return ;
		}
		if (game->map[(int)(y + y2 / 16) / 50][(int)x / 50] == '1')
		{
			y += y2 / 16;
			ft_3dscene(game, x, y, 1);
			return ;
		}
		else if (game->map[(int)(y + y2 / 16) / 50][(int)x / 50] == '2')
		{
			y += y2 / 16;
			ft_3dscene2(game, x, y, 1);
			return ;
		}
		x += x2 / 16;
		y += y2 / 16;
	}
}

void	ft_drawl(t_game *game, double x2, double y2)
{
	double	x;
	double	y;

	x = game->px;
	y = game->py;
	while (1)
	{
		if (game->map[(int)(y) / 50][(int)(x + x2) / 50] != '0' && game->map[(int)(y) / 50][(int)(x + x2) / 50] != '3')
		{
			ft_castray2(game, x, y);
			return ;
		}
		if (game->map[(int)(y + y2) / 50][(int)(x) / 50] != '0' && game->map[(int)(y + y2) / 50][(int)(x) / 50] != '3')
		{
			ft_castray2(game, x, y);
			return ;
		}
		x += x2;
		y += y2;
	}
}
