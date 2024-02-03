/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updates_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 03:44:45 by dehamad           #+#    #+#             */
/*   Updated: 2024/02/03 11:09:59 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	delete_attack(t_vars *vars, int x, int y)
{
	if (vars->map.arr[y][x] == 'S')
	{
		vars->map.arr[y][x] = '0';
		draw_img(vars, '0', x, y);
	}
}

void	update_steps(t_vars *vars)
{
	char		*steps;

	if (vars->map.counters.steps)
	{
		steps = ft_itoa(vars->map.counters.steps);
		mlx_string_put(vars->mlx, vars->win, 100, vars->map.height - 25,
			000, "00");
		mlx_string_put(vars->mlx, vars->win, 100, vars->map.height - 25,
			0xff00, steps);
		free(steps);
	}
}

static void	draw_spirit_img(t_vars *vars, void *img, int x, int y)
{
	draw_img(vars, '1', x / PX, y / PX);
	mlx_put_image_to_window(vars->mlx, vars->win, img, x, y);
}

void	spirit_animation(t_vars *vars)
{
	static int	render;
	t_imgs		*imgs;
	int			x;
	int			y;

	imgs = &vars->map.imgs;
	x = 150;
	y = vars->map.height - 50;
	if (render == 1)
		draw_spirit_img(vars, imgs->run1, x, y);
	if (render == 2)
		draw_spirit_img(vars, imgs->run2, x, y);
	if (render == 3)
		draw_spirit_img(vars, imgs->run3, x, y);
	if (render == 4)
	{
		draw_spirit_img(vars, imgs->run4, x, y);
		render = 0;
	}
	++render;
}
