/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_move_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 03:50:48 by dehamad           #+#    #+#             */
/*   Updated: 2024/02/03 11:06:03 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	is_validmove(t_vars *vars, int x, int y)
{
	if (vars->map.arr[y][x] == 'P')
		exit_success(vars);
	return (vars->map.arr[y][x] == '0');
}

static void	move(t_vars *vars, char letter, int x, int y)
{
	if (letter == '>')
		draw_img(vars, '0', x - 1, y);
	else
		draw_img(vars, '0', x + 1, y);
	draw_img(vars, letter, x, y);
}

static int	update_pos(t_vars *vars, char letter, int x, int y)
{
	vars->map.arr[y][x] = '0';
	if ((letter == 'M' || letter == '>') && is_validmove(vars, x + 1, y))
		move(vars, '>', ++x, y);
	else
		letter = '<';
	if (letter == '<' && is_validmove(vars, x - 1, y))
		move(vars, '<', --x, y);
	else
		letter = '>';
	vars->map.arr[y][x] = letter;
	return (x);
}

int	monster_move(t_vars *vars, int x, int y)
{
	if (ft_strchr(MONSTER_CHARS, vars->map.arr[y][x]))
		if (update_pos(vars, vars->map.arr[y][x], x, y) > x)
			x++;
	return (x);
}
