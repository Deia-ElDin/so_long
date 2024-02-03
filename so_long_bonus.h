/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:49:35 by dehamad           #+#    #+#             */
/*   Updated: 2024/02/03 08:55:59 by dehamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "libft/libft.h"
# include "mlx/mlx.h"

// Constants
# define PX 50
# define FILE_EXTENSION ".ber"
# define ALLOWED_CHARS "10PCEM\n"
# define COUNTERS_CHARS "PCE"
# define MONSTER_CHARS "M><"

// Images
# define WALL_IMG "textures/wall.xpm"
# define GRASS_IMG "textures/grass.xpm"
# define PLAYER_RIGHT_IMG "textures/player_right.xpm"
# define PLAYER_LEFT_IMG "textures/player_left.xpm"
# define MONSTER_RIGHT_IMG "textures/monster_right.xpm"
# define MONSTER_LEFT_IMG "textures/monster_left.xpm"
# define COLLECTABLES_IMG "textures/collectables.xpm"
# define EXIT_IMG "textures/exit.xpm"
# define SWORD_RIGHT_IMG "textures/sword_right.xpm"
# define SWORD_LEFT_IMG "textures/sword_left.xpm"
# define SWORD_DOWN_IMG "textures/sword_down.xpm"
# define SWORD_UP_IMG "textures/sword_up.xpm"
# define RUN1_IMG "textures/run1.xpm"
# define RUN2_IMG "textures/run2.xpm"
# define RUN3_IMG "textures/run3.xpm"
# define RUN4_IMG "textures/run4.xpm"

// Errors
# define INPUTS_ERR "Error\nInvalid inputs, \
kindly provide us only 1 file to work with.\n"
# define NO_FD_ERR "Error\nKindly provide us a file to work with.\n"
# define INVALID_FD_NAME "Error\nInvalid file, kindly check the file name.\n"
# define EMPTY_MAP_ERR "Error\nKindly provide us a map to work with.\n"
# define LARGE_MAP_ERR "Error\nThe map is too large, \
it doesn't make sence dude.\n"
# define FD_ERR "Error\nFailed to read the file you provided.\n"
# define MALLOC_ERR "Error\nFailed to malloc the map array.\n"
# define READ_ERR "Error\nSomething went wrong with the read function, \
kindly try again later.\n"
# define MLX_ERR "Error\nSomething went wrong with mlx lib, kindly try later.\n"
# define LEN_ERR "Error\nEach line of the map \
can't be less than 4 characters.\n"
# define LINES_ERR "Error\nThe map lines can't be of a different length.\n"
# define WALL_ERR "Error\nThe map frame \
must be all one's reprsenting the wall.\n"
# define NO_PLAYER_ERR "Error\nCan't start the game without a player!.\n"
# define MORE_PLAYERS_ERR "Error\nCan't start the game \
with more than 1 player!.\n"
# define NO_EXIT_ERR "Error\nCan't start the game without an exit door!.\n"
# define MORE_EXITS_ERR "Error\nCan't start the game \
with more than 1 exit door!.\n"
# define COLLECTABLES_ERR "Error\nCan't start the game \
without some collectables!.\n"
# define INVALID_CHAR_ERR "Error\nInvalid character.\n"
# define SQR_MAP_ERR "Error\nThe map can't be square.\n"
# define IMG_ERR "Error\nCorrupted image source file.\n"
# define PATH_ERR "Error\nCan't reach either the exit or the collectables.\n"

enum
{
	ON_KEYDOWN = 2,
	ON_DESTROY = 17
};

typedef struct s_position
{
	int		crnt_x;
	int		crnt_y;
	int		next_x;
	int		next_y;
	char	crnt_pos;
	char	next_pos;
}	t_position;

typedef struct s_counters
{
	int	player;
	int	exit;
	int	collectables;
	int	monsters;
	int	steps;
}	t_counters;

typedef struct s_cords
{
	int	x;
	int	y;	
}	t_cords;

typedef struct s_imgs
{
	void	*player_right;
	void	*player_left;
	void	*monster_right;
	void	*monster_left;
	void	*grass;
	void	*wall;
	void	*exit;
	void	*collectable;
	void	*sword_right;
	void	*sword_left;
	void	*sword_down;
	void	*sword_up;
	void	*run1;
	void	*run2;
	void	*run3;
	void	*run4;
	char	player_prev_pos;
}	t_imgs;

typedef struct s_map
{
	char		**arr;
	char		**cpy;
	int			lines;
	int			height;
	int			width;
	int			is_valid;
	t_counters	counters;
	t_cords		cords;
	t_imgs		imgs;
}	t_map;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_map	map;
}	t_vars;

// Map Utils
void	map_read(t_map *map, const char *file);
void	map_parsing(t_map *map);
void	map_draw(t_vars *vars);
int		map_updates(t_vars *vars);

// Parse Utils
void	parse_lineslength(t_map *map, char **arr, int total_lines);
void	parse_chars(t_map *map, char **arr, int total_lines);
void	parse_counters(t_map *map, char **arr);
void	parse_validpath(t_map *map, int x, int y);

// Player Move
int		player_move(int keycode, t_vars *vars);

// Monster Move
int		monster_move(t_vars *vars, int x, int y);

// Updates
void	delete_attack(t_vars *vars, int x, int y);
void	update_steps(t_vars *vars);
void	spirit_animation(t_vars *vars);

// Utils
void	*load_img(t_vars *vars, const char *file_path);
void	draw_img(t_vars *vars, char letter, int x, int y);
void	exit_error(t_map *map, char *err);
int		exit_success(t_vars *vars);
int		update_counters(t_map *map, char letter, int x, int y);

#endif

/*
	t_map	map; VS t_map	*map;

	Direct Struct (t_map):
		Pros:
			Simplicity: Accessing members of the struct is straightforward, 
				using the . operator.
			Memory Allocation: If the struct size is relatively small, 
				allocating it directly on the stack or as part of another 
				struct might be efficient.
		Cons:
			Passing by Value: When passing a struct to a function, 
				it gets passed by value, meaning a copy is made. 
				This might be inefficient for large structs.
			Copying Overhead: Copying structs involves copying all their 
				members, which could be inefficient if the struct is large.
	
	Pointer to Struct (t_map *):
		Pros:
			Dynamic Memory Allocation: If the struct size is large 
				or if you need dynamic memory allocation, using a pointer 
				allows you to allocate memory dynamically using malloc 
				or related functions.
			Passing by Reference: When passing a pointer to a function, 
				you're passing a reference, so modifications made within the 
				function affect the original struct.
		Cons:
			Dereferencing: Accessing members requires dereferencing 
			the pointer using the -> operator, which can be slightly 
			less convenient than the . operator.

	In C, when you define a structure that contains pointers, 
	such as your t_map structure with t_counters *counters;, 
	you need to allocate memory for those pointers before you can use them. 
	Allocating memory dynamically allows you to create space for the data 
	that those pointers will point to.
	
	If you don't allocate memory and attempt to dereference the pointers 
	(i.e., access their members), you may encounter undefined behavior, 
	which could include segmentation faults.

	Why malloc ?
	1) Dynamic Memory Allocation: 
	Memory allocated with malloc is dynamically allocated on the heap, 
	and it persists until explicitly freed with free. 
	This is useful when you need the memory to exist beyond the scope 
	of the current function.

	2) Structure Initialization: 
	When you allocate memory, it ensures that the pointers within the structure 
	are pointing to valid memory locations. This prevents undefined behavior 
	when you later try to access or modify the data through those pointers.
*/
