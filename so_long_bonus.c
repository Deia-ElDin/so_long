/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 14:31:49 by dehamad           #+#    #+#             */
/*   Updated: 2024/02/03 10:58:29 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	init_vars(t_vars *vars)
{
	vars->map.arr = NULL;
	vars->map.cpy = NULL;
	vars->map.imgs.player_prev_pos = 'P';
	vars->map.counters.player = 0;
	vars->map.counters.exit = 0;
	vars->map.counters.collectables = 0;
	vars->map.counters.monsters = 0;
	vars->map.counters.steps = 0;
	vars->map.is_valid = 0;
}

static void	init_imgs(t_vars *vars)
{
	t_imgs	*imgs;

	imgs = &vars->map.imgs;
	imgs->grass = load_img(vars, GRASS_IMG);
	imgs->wall = load_img(vars, WALL_IMG);
	imgs->collectable = load_img(vars, COLLECTABLES_IMG);
	imgs->exit = load_img(vars, EXIT_IMG);
	imgs->player_right = load_img(vars, PLAYER_RIGHT_IMG);
	imgs->player_left = load_img(vars, PLAYER_LEFT_IMG);
	imgs->monster_right = load_img(vars, MONSTER_RIGHT_IMG);
	imgs->monster_left = load_img(vars, MONSTER_LEFT_IMG);
	imgs->sword_right = load_img(vars, SWORD_RIGHT_IMG);
	imgs->sword_left = load_img(vars, SWORD_LEFT_IMG);
	imgs->sword_down = load_img(vars, SWORD_DOWN_IMG);
	imgs->sword_up = load_img(vars, SWORD_UP_IMG);
	imgs->run1 = load_img(vars, RUN1_IMG);
	imgs->run2 = load_img(vars, RUN2_IMG);
	imgs->run3 = load_img(vars, RUN3_IMG);
	imgs->run4 = load_img(vars, RUN4_IMG);
}

static void	start_game(t_vars *vars, const char *file)
{
	t_map	*map;

	map = &vars->map;
	init_vars(vars);
	map_read(map, file);
	map_parsing(map);
	vars->mlx = mlx_init();
	if (!(vars->mlx))
		exit_error(map, MLX_ERR);
	vars->win = mlx_new_window(vars->mlx, map->width, map->height, "so_long");
	if (!(vars->win))
		exit_error(map, MLX_ERR);
	init_imgs(vars);
	map_draw(vars);
	mlx_hook(vars->win, ON_DESTROY, 0, exit_success, vars);
	mlx_hook(vars->win, ON_KEYDOWN, 0, player_move, vars);
	mlx_loop_hook(vars->mlx, map_updates, vars);
	mlx_string_put(vars->mlx, vars->win, 50, map->height - 25,
		0xff00, "Moves:");
	mlx_loop(vars->mlx);
	ft_free(&(vars->map.arr), 'a');
}

int	main(int ac, char **av)
{
	t_vars	vars;

	if (ac == 2)
		start_game(&vars, av[1]);
	else
	{
		if (ac == 1)
			ft_printf(2, "%s", NO_FD_ERR);
		else
			ft_printf(2, "%s", INPUTS_ERR);
		exit(EXIT_FAILURE);
	}
	return (0);
}
