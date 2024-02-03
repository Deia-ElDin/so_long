/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:10:28 by dehamad           #+#    #+#             */
/*   Updated: 2024/02/03 10:52:47 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*load_img(t_vars *vars, const char *file_path)
{
	void	*img;
	int		width;
	int		height;

	img = mlx_xpm_file_to_image(vars->mlx, (char *)file_path, &width, &height);
	if (!img)
		exit_error(&vars->map, IMG_ERR);
	return (img);
}

void	draw_img(t_vars *vars, char letter, int x, int y)
{
	t_imgs	*imgs;
	void	*img;

	imgs = &vars->map.imgs;
	if (letter == 'P' || letter == 'r' || letter == 'l')
		imgs->player_prev_pos = letter;
	if (letter == '0')
		img = imgs->grass;
	else if (letter == '1')
		img = imgs->wall;
	else if (letter == 'C')
		img = imgs->collectable;
	else if (letter == 'E')
		img = imgs->exit;
	else if (letter == 'P' || letter == 'r')
		img = imgs->player_right;
	else if (letter == 'l')
		img = imgs->player_left;
	else
		img = NULL;
	if (!img)
		exit_error(&vars->map, IMG_ERR);
	mlx_put_image_to_window(vars->mlx, vars->win, img, x * PX, y * PX);
}

void	exit_error(t_map *map, char *err)
{
	if (map->arr)
		ft_free(&(map->arr), 'a');
	if (map->cpy)
		ft_free(&(map->cpy), 'a');
	ft_printf(2, "%s", err);
	exit(EXIT_FAILURE);
}

int	exit_success(t_vars *vars)
{
	if (vars->map.arr)
		ft_free(&(vars->map.arr), 'a');
	if (vars->map.cpy)
		ft_free(&(vars->map.cpy), 'a');
	mlx_destroy_window(vars->mlx, vars->win);
	exit(EXIT_SUCCESS);
}

int	update_counters(t_map *map, char letter, int x, int y)
{
	if (letter == 'C')
		++map->counters.collectables;
	else if (letter == 'P')
	{
		++map->counters.player;
		map->cords.x = x;
		map->cords.y = y;
	}
	else if (letter == 'E')
		++map->counters.exit;
	return (1);
}

/*
	void	draw_img(t_vars *vars, char letter, int x, int y)
	{
		the only purpose of the letter here is to keep trace of the player,
		particularly if he's moving up or down. 
	}

	EXIT_FAILURE & EXIT_SUCCESS:
		different system use different numbers to represent either of the cases,
		so it's preferable to use the EXIT_FAILURE & EXIT_SUCCESS.
*/
