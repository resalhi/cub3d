/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchfa <abouchfa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:56:11 by ressalhi          #+#    #+#             */
/*   Updated: 2022/11/01 07:21:42 by abouchfa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	get_tex_path(t_game *g)
{
	int	hi;

	g->no_tex = mlx_xpm_file_to_image(g->mlx, g->no_textr, &hi, &hi);
	if (!g->no_tex)
		ft_error("wrong texture path!!\n(north texture)\n");
	g->we_tex = mlx_xpm_file_to_image(g->mlx, g->we_textr, &hi, &hi);
	if (!g->we_tex)
		ft_error("wrong texture path!!\n(west texture)\n");
	g->so_tex = mlx_xpm_file_to_image(g->mlx, g->so_textr, &hi, &hi);
	if (!g->so_tex)
		ft_error("wrong texture path!!\n(south texture)\n");
	g->ea_tex = mlx_xpm_file_to_image(g->mlx, g->ea_textr, &hi, &hi);
	if (!g->ea_tex)
		ft_error("wrong texture path!!\n(east texture)\n");
	g->no_texadr = mlx_get_data_addr(g->no_tex, &g->bpp1, &g->llen1, &g->en1);
	g->so_texadr = mlx_get_data_addr(g->so_tex, &g->bpp2, &g->llen2, &g->en2);
	g->we_texadr = mlx_get_data_addr(g->we_tex, &g->bpp3, &g->llen3, &g->en3);
	g->ea_texadr = mlx_get_data_addr(g->ea_tex, &g->bpp4, &g->llen4, &g->en4);
}

void	ft_init(t_game *game, char *arg)
{
	game->keys = ft_calloc(sizeof(int), 6);
	game->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HIGHT);
	game->addr = mlx_get_data_addr(game->img, &game->bpp,
			&game->llen, &game->en);
	get_tex_path(game);
	get_player_cord(game);
	game->pdx = cos(degtorad(game->pa)) * P_SPEED;
	game->pdy = sin(degtorad(game->pa)) * P_SPEED;
	draw_rays(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
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
	ft_init(game, av[1]);
	mlx_hook(game->mlx_win, 2, 1L << 0, key_hook1, game);
	mlx_hook(game->mlx_win, 3, 1L << 1, key_hook2, game);
	mlx_loop_hook(game->mlx, ft_hook, game);
	mlx_loop(game->mlx);
}


/*todo list :
	Mini map
*/