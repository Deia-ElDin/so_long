/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 01:42:01 by dehamad           #+#    #+#             */
/*   Updated: 2024/02/03 11:06:36 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	map_len(t_map *map, int fd, const char *file)
{
	t_gnl	ret;
	int		len;

	len = (int)ft_strlen(file);
	if ((len - 4) <= 0 || ft_strcmp(FILE_EXTENSION, file + (len - 4)))
		exit_error(map, INVALID_FD_NAME);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit_error(map, FD_ERR);
	len = 0;
	while (fd >= 0)
	{
		ret = ft_get_next_line(fd);
		if (!ret.line)
			break ;
		free(ret.line);
		len++;
	}
	if (!len)
	{
		close(fd);
		exit_error(map, EMPTY_MAP_ERR);
	}
	map->lines = len;
	return ((void)close(fd), len);
}

void	map_read(t_map *map, const char *file)
{
	int		fd;
	int		len;
	t_gnl	ret;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit_error(map, FD_ERR);
	len = map_len(map, fd, file);
	map->arr = (char **)ft_calloc(len + 1, sizeof(char *));
	map->cpy = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!map->arr || !map->cpy)
		exit_error(map, MALLOC_ERR);
	len = 0;
	while (fd >= 0)
	{
		ret = ft_get_next_line(fd);
		if (ret.error)
			return ((void)close(fd), exit_error(map, READ_ERR));
		if (!ret.line)
			break ;
		map->arr[len] = ret.line;
		map->cpy[len] = ft_strdup(ret.line);
		len++;
	}
	close(fd);
}

void	map_parsing(t_map *map)
{
	map->height = (map->lines + 1) * PX;
	map->width = (ft_strlen(map->arr[0]) - 1) * PX;
	if (map->height == map->width)
		exit_error(map, SQR_MAP_ERR);
	parse_lineslength(map, map->arr, map->lines);
	parse_chars(map, map->arr, map->lines);
	parse_counters(map, map->arr);
	parse_validpath(map, map->cords.x, map->cords.y);
	ft_free(&(map->cpy), 'a');
	if (!map->is_valid)
		exit_error(map, PATH_ERR);
}

void	map_draw(t_vars *vars)
{
	char	**arr;
	int		x;
	int		y;

	arr = vars->map.arr;
	y = 0;
	while (arr[y])
	{
		x = 0;
		while (arr[y][x] && arr[y][x] != '\n')
		{
			if (arr[y][x] != '1' && arr[y][x] != '0')
				draw_img(vars, '0', x, y);
			draw_img(vars, arr[y][x], x, y);
			x++;
		}
		y++;
	}
}

int	map_updates(t_vars *vars)
{
	static int	delay;
	int			x;
	int			y;

	y = 1;
	if (delay == 5000)
	{
		update_steps(vars);
		spirit_animation(vars);
		while (vars->map.arr[y])
		{
			x = 1;
			while (vars->map.arr[y][x] && vars->map.arr[y][x] != '\n')
			{
				delete_attack(vars, x, y);
				x = monster_move(vars, x, y);
				x++;
			}
			y++;
		}
		delay = 0;
	}
	delay++;
	return (0);
}

/*
	void	*map_read(t_map *map, const char *file)
	{
		We are using the len && ret multiple times in this fn.
		
		len = ft_strlen(file);
		if ((len - 4) <= 0 || ft_strcmp(FILE_EXTENSION, file + (len - 4)) != 0)
			len - 4:
				.ber = 4 chars.
			ft_strcmp(FILE_EXTENSION, file + (len - 4)) != 0:
				file + (len - 4) shifts the ptr to where the .ber starts.

		len = map_len(map, file);
			to get how many lines in our map so we malloc accordingly.
	}
	
	void	*map_parsing(t_map *map)
	{
		map->height = (map->lines * PX) + 50;
			+50: 
				for writing the player steps.
				
		map->width = (ft_strlen(map->arr[0]) - 1) * PX;
			-1: To remove the new line at the end of each line.
				&there's must be a new line otherwise it's not a valid map.
			*PX: Because each of our images are a size of 50 x 50 px.
	}

	int	map_updates(t_vars *vars)
	{
		if (update_pos(vars, arr[y][x], x, y) > x)
			x++;

		our update_pos fn returns the value of x,
		if the monster moved backward (--x), we are good,
		but if the monster moved forward (++x), 
		we are incrementing the x by 1 after that, so we will always face ('>'), 
		because in update_pos fn we draw 
		('0') at our crnt_pos && ('>') at the next_pos,
		so always our next_pos == ('>'),
		so once we finish the update_pos fn and back to the inner while loop,
		we increment the x by 1 which is the position we moved the monster to,
		so it's always ('>') and therefor our fn will work just fine with the 
		backward movement (against the increment of x), and will move light speed
		with the movement that's the same direction as x.

		to handle this issue, we return the x we moved to from update_pos,
		and if the return value (the new x is > than the old x),
		it means we moved forward, which means our next x is ('>'),
		which means we need to check the one after that so it's x++,
		so we are now at where we draw / moved our monster, 
		then again x++ to check the next pos.
	}
*/
