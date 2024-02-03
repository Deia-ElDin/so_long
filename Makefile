# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/18 19:07:04 by dehamad           #+#    #+#              #
#    Updated: 2024/02/03 10:59:13 by dehamad          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror -Imlx 
AR = ar
MLX_LIB = -Lmlx -lmlx -framework OpenGL -framework AppKit

LIBFT = libft/libft.a
SRCS = so_long.c map_utils.c parse_utils.c player_move.c so_long_utils.c  
BNS = so_long_bonus.c map_utils_bonus.c parse_utils_bonus.c player_move_bonus.c \
	monster_move_bonus.c so_long_utils_bonus.c updates_utils_bonus.c 
OBJS = $(SRCS:.c=.o)
BNS_OBJS = $(BNS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) 
	make -C libft
	make -C mlx 
	${CC} ${CFLAGS} ${LIBFT} ${MLX_LIB} ${OBJS} -o ${NAME}

bonus: ${BNS_OBJS}
	make -C libft
	make -C mlx
	${CC} ${CFLAGS} ${LIBFT} ${MLX_LIB} ${BNS_OBJS} -o ${NAME}_bonus

clean:
	rm -f $(OBJS) $(BOBJS) ${BNS_OBJS}
	make -C libft clean
	make -C mlx clean

fclean: clean
	rm -f $(NAME) ${NAME}_bonus
	make -C libft fclean
	make -C mlx clean

re: fclean all

.PHONY: all bonus clean fclean re
