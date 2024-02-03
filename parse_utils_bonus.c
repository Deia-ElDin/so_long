/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:19:07 by dehamad           #+#    #+#             */
/*   Updated: 2024/02/03 01:09:20 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	parse_lineslength(t_map *map, char **arr, int total_lines)
{
	size_t	ref;
	size_t	len;
	int		index;

	index = 0;
	ref = ft_strlen(arr[index++]);
	if (ref <= 3)
		exit_error(map, LEN_ERR);
	if (total_lines <= 2)
		exit_error(map, LINES_ERR);
	total_lines--;
	while (arr[index])
	{
		len = ft_strlen(arr[index]);
		if (index < total_lines && len != ref)
			exit_error(map, LINES_ERR);
		else if (index == total_lines && ref - len > 1)
			exit_error(map, LINES_ERR);
		index++;
	}
}

void	parse_chars(t_map *map, char **arr, int total_lines)
{
	int		x;
	int		y;
	size_t	len;

	y = 0;
	len = ft_strlen(arr[y]) - 2;
	total_lines--;
	while (arr[y])
	{
		x = 0;
		while (arr[y][x] && arr[y][x] != '\n')
		{
			if (!ft_strchr(ALLOWED_CHARS, arr[y][x]))
				exit_error(map, INVALID_CHAR_ERR);
			if ((!y || y == total_lines) && arr[y][x] != '1')
				exit_error(map, WALL_ERR);
			else if ((!x || x == (int)len) && arr[y][x] != '1')
				exit_error(map, WALL_ERR);
			x++;
		}
		y++;
	}
}

void	parse_counters(t_map *map, char **arr)
{
	int	x;
	int	y;

	y = 0;
	while (arr[y])
	{
		x = 0;
		while (arr[y][x] && arr[y][x] != '\n')
		{
			if (ft_strchr(COUNTERS_CHARS, arr[y][x]))
				update_counters(map, arr[y][x], x, y);
			x++;
		}
		y++;
	}
	if (!map->counters.player)
		exit_error(map, NO_PLAYER_ERR);
	if (map->counters.player > 1)
		exit_error(map, MORE_PLAYERS_ERR);
	if (!map->counters.exit)
		exit_error(map, NO_EXIT_ERR);
	if (map->counters.exit > 1)
		exit_error(map, MORE_EXITS_ERR);
	if (!map->counters.collectables)
		exit_error(map, COLLECTABLES_ERR);
}

static int	is_validpath(t_map *map, int x, int y)
{
	int		i;
	int		j;

	i = 1;
	if (map->cpy[y][x] != '1')
	{
		map->cpy[y][x] = '1';
		while (map->cpy[i] && i < map->lines - 1)
		{
			j = 1;
			while (map->cpy[i][j] && map->cpy[i][j] != '\n')
			{
				if (map->cpy[i][j] == 'E' || map->cpy[i][j] == 'C')
					return (1);
				j++;
			}
			i++;
		}
		map->is_valid = 1;
	}
	return (0);
}

void	parse_validpath(t_map *map, int x, int y)
{
	map->cpy[y][x] = '1';
	if (!map->is_valid && is_validpath(map, x, y - 1))
		parse_validpath(map, x, y - 1);
	if (!map->is_valid && is_validpath(map, x + 1, y))
		parse_validpath(map, x + 1, y);
	if (!map->is_valid && is_validpath(map, x, y + 1))
		parse_validpath(map, x, y + 1);
	if (!map->is_valid && is_validpath(map, x - 1, y))
		parse_validpath(map, x - 1, y);
}

/*
	static void	parse_lineslength(char **arr, int total_lines)
	{
		size_t	ref; 
			that's the refrence length, it's what we will use to compare 
			all the other lines length againt.
		
		if (ref <= 3)
			exit_error(&arr, LINES_ERR, 1) i.e 1P1 || 1E1
			
		if (total_lines <= 2)
			11111
			11111
			
		total_lines--;
			index starts from 0, if total_lines = 3, last index = 2.

		while (arr[index])
		{
			len = ft_strlen(arr[index]);
			if (index < total_lines && len != ref)
				if the len of any line but not the last 
					is different than the ref.
			else if (index == total_lines && ref - len > 1)
				if there's a difference and that diff > 1 
					(might have \n might not).
				if the diff == 0 means there's a \n in the last line.
				if the diff == 1 means there's no \n in the last line.
				both cases are accepetd, and this way we can handle the \n,
				without the need of removing the \n from the whole map.
		}
	}

	void	parse_chars(t_map *map, char **arr, int total_lines)
	{
		Notes:
			1) since we are in this function we are 
				positive that our total_lines >= 3
				which means each line ends with \n, 
				(might / might not) be the case for the last one.
			2) this function works with cords (0, 1, 2, 3, etc).
			
		len = ft_strlen(arr[0]);
			now the len is where the \0 at.
		len = ft_strlen(arr[0]) - 1;
			now the len is where the \n at.
		len = ft_strlen(arr[0]) - 2;
			that's the last char before the \n and \0.

		while (arr[y][x] && arr[y][x] != '\n')
		{
			if ((!y || y == total_lines) && arr[y][x] != '1')
				if first or last rows are not 1's.
			else if ((!x || x == (int)len) && arr[y][x] != '1')
				if first or last char at each row are not 1's.
		}
	}

	static int	is_validpath(t_map *map, int x, int y)
	{
		i is used to represent the y and j used to represent the x.
		
		i = 1;
			because at i = 0 it's a wall.
			
		if (map->cpy[y][x] != '1')
		{
			means we are allowed to move there
			map->cpy[y][x] = '1':
				we set it to 1.
				
			while (map->cpy[i] && i < map->lines - 1)
			{
				i < map->lines - 1:
					to avoid the last line.
				j = 1:
					so we always start from the 2nd index at each line.
				if (map->cpy[i][j] == 'E' || map->cpy[i][j] == 'C')
					if we found E || C we we break out right away 
						returning 1, indicating continuo with the recursive.
				if we didn't find any we continuo looping till we reach the end,
					then we set map->is_valid to 1, that we will help us not to
						create any more recursive function and easily exit the 
						previous ones.
			}
		}
	}

	void	parse_validpath(t_map *map, int x, int y)
	{
		if (!map->is_valid & ...)
			as long as out map->is_valid is 0 we keep on going.
		
		The moving directions:
			- Up.
			- Right.
			- Down.
			- Left.
	}
*/
