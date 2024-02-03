/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 01:42:01 by dehamad           #+#    #+#             */
/*   Updated: 2024/02/03 10:57:35 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	int	height;
	int	width;

	height = map->lines;
	width = ft_strlen(map->arr[0]) - 1;
	if (height == width)
		exit_error(map, SQR_MAP_ERR);
	if (height > 200 || width > 200)
		exit_error(map, LARGE_MAP_ERR);
	map->height = height * PX;
	map->width = width * PX;
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
		map->width = (ft_strlen(map->arr[0]) - 1) * PX;
			-1: To remove the new line at the end of each line.
				&there's must be a new line otherwise it's not a valid map.
			*PX: Because each of our images are a size of 50 x 50 px.
	}
*/
