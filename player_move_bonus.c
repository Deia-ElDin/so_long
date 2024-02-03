/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 06:59:26 by dehamad           #+#    #+#             */
/*   Updated: 2024/02/03 10:58:34 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	is_validmove(t_vars *vars, int x, int y)
{
	t_counters	*counters;
	char		next_pos;

	counters = &vars->map.counters;
	next_pos = vars->map.arr[y][x];
	if (next_pos == '1')
		return (0);
	else if (next_pos == 'E' && !counters->collectables && ++counters->steps)
		exit_success(vars);
	else if (next_pos == 'M' || next_pos == '>' || next_pos == '<')
		exit_success(vars);
	return (1);
}

static void	make_amove(t_vars *vars, t_position pos, char letter)
{
	if (pos.next_pos == 'C')
		vars->map.counters.collectables--;
	if (pos.next_pos != 'E')
	{
		vars->map.arr[pos.next_y][pos.next_x] = 'P';
		draw_img(vars, '0', pos.next_x, pos.next_y);
	}
	if (pos.crnt_pos == 'E')
	{
		draw_img(vars, '0', pos.crnt_x, pos.crnt_y);
		draw_img(vars, 'E', pos.crnt_x, pos.crnt_y);
	}
	else
	{
		vars->map.arr[pos.crnt_y][pos.crnt_x] = '0';
		draw_img(vars, '0', pos.crnt_x, pos.crnt_y);
	}
	draw_img(vars, letter, pos.next_x, pos.next_y);
	vars->map.cords.x = pos.next_x;
	vars->map.cords.y = pos.next_y;
}

static void	update_pos(t_vars *vars, char letter, int next_x, int next_y)
{
	t_position	pos;

	pos.crnt_x = vars->map.cords.x;
	pos.crnt_y = vars->map.cords.y;
	pos.next_x = next_x;
	pos.next_y = next_y;
	pos.crnt_pos = vars->map.arr[pos.crnt_y][pos.crnt_x];
	pos.next_pos = vars->map.arr[next_y][next_x];
	make_amove(vars, pos, letter);
	++vars->map.counters.steps;
}

static void	attack(t_vars *vars, void *img, int x, int y)
{
	char	crnt_pos;

	crnt_pos = vars->map.arr[y][x];
	if (crnt_pos == '0' || ft_strchr(MONSTER_CHARS, crnt_pos))
	{
		mlx_put_image_to_window(vars->mlx, vars->win, img, x * PX, y * PX);
		vars->map.arr[y][x] = 'S';
		if (ft_strchr(MONSTER_CHARS, crnt_pos))
		{
			draw_img(vars, '0', x, y);
			vars->map.arr[y][x] = '0';
		}
	}
}

int	player_move(int keycode, t_vars *vars)
{
	t_imgs	*imgs;
	int		x;
	int		y;

	imgs = &vars->map.imgs;
	x = vars->map.cords.x;
	y = vars->map.cords.y;
	if ((keycode == 124 || keycode == 2) && is_validmove(vars, x + 1, y))
		update_pos(vars, 'r', ++x, y);
	else if ((keycode == 123 || keycode == 0) && is_validmove(vars, x - 1, y))
		update_pos(vars, 'l', --x, y);
	else if ((keycode == 125 || keycode == 1) && is_validmove(vars, x, y + 1))
		update_pos(vars, imgs->player_prev_pos, x, ++y);
	else if ((keycode == 126 || keycode == 13) && is_validmove(vars, x, y - 1))
		update_pos(vars, imgs->player_prev_pos, x, --y);
	else if (keycode == 3)
	{
		attack(vars, imgs->sword_right, x + 1, y);
		attack(vars, imgs->sword_left, x - 1, y);
		attack(vars, imgs->sword_up, x, y - 1);
		attack(vars, imgs->sword_down, x, y + 1);
	}
	else if (keycode == 53)
		exit_success(vars);
	return (0);
}

/*
	static void	move(t_vars *vars, t_position pos, char letter)
	{
		the whole problem here is the Exit.
		
		if (pos.next_pos == 'C')
			if we find a collectable we decrement the collectables by 1.
			
		if (pos.next_pos != 'E')
			if exit is our next block:
				1) we should't change that pos on the map to 0.
				2) we shouldn't draw a grass ('0').
		
		if (pos.crnt_pos == 'E')
			if we are standing on the exit:
				1) we should delete the player image by:
					1) draw grass ('0').
					2) draw exit ('E').
				2) we shouldn't set it to 0 since we are move out of this block.
		else if our crnt.pos != 'E'
			1) we set it to zero.
			2) we draw the img ('0').

		Eventually we draw the player img where ever we will step next.
		but we will use either letter ('r' or 'l'), 
		which they are not allowed in our main map,
		still we will use them in the code to indicate either the player,
		is moving right or left and in case he moved up or down,
		we know exactly which img we should use.
	}
*/
