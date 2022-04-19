# # **************************************************************************** #
# #                                                                              #
# #                                                         :::      ::::::::    #
# #    Makefile                                           :+:      :+:    :+:    #
# #                                                     +:+ +:+         +:+      #
# #    By: tpierre <tpierre@student.42.fr>            +#+  +:+       +#+         #
# #                                                 +#+#+#+#+#+   +#+            #
# #    Created: 2020/04/03 14:55:53 by tpierre           #+#    #+#              #
# #    Updated: 2020/04/03 16:43:39 by tpierre          ###   ########.fr        #
# #                                                                              #
# # **************************************************************************** #

NAME		= cub3D

SRCS		= ./srcs/main.c ./srcs/ft_display.c ./srcs/ft_error.c\
				./srcs/ft_exit.c ./srcs/ft_free.c ./srcs/ft_read.c\
				./srcs/cub3d_utils.c ./srcs/ft_get_data1.c ./srcs/ft_get_data2.c \
				./srcs/ft_get_data3.c ./srcs/ft_get_map.c ./srcs/ft_init.c ./srcs/ft_event.c\
				./srcs/ft_move.c ./srcs/ft_save.c ./srcs/ft_display_wall.c ./srcs/ft_display_sprite.c

OBJS		= ${SRCS:.c=.o}

CC			= gcc

RM			= rm -f

MLX_FLAGS	= -Lmlx/ -lmlx -lXext -lX11 -lbsd

MATH_FLAGS	= -lm

LIBFT_FLAGS	= -Llibft -lft

CFLAGS		= -Wall -Wextra -Werror

INCLUDES	= -I mlx -I libft

all:		${NAME}

.c.o:
			${CC} ${CFLAGS} ${INCLUDES} ${DEFINES} -c $< -o $@

$(NAME): 	${OBJS} ${OBJS_MLX}
			make -C mlx
			make -C libft
			${CC} ${OBJS} ${OBJS_MLX} ${LIBFT_FLAGS} ${MATH_FLAGS} ${MLX_FLAGS} -o ${NAME}
clean:
			make -C mlx clean
			make -C libft clean
			${RM} ${OBJS} ${OBJS_FULL} ${OBJS_MLX} ${OBJS_TERM}


fclean:		clean
			rm -f libft/libft.a
			${RM} ${NAME}

re:			fclean
			make all

.PHONY:		all clean fclean re
