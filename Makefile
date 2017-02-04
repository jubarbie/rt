# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jubarbie <jubarbie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/10/30 16:51:35 by jubarbie          #+#    #+#              #
#    Updated: 2017/02/04 14:37:36 by atoulous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -ILibs/libft -I$(MLX) -ILibs/libv3d -ILibs/libmy_math -ILibs/libmy_mlx -IIncludes #-Wall -Wextra -Werror
SRC =	rt.c			\
		apply_color.c	\
		apply_light.c	\
		modif_color.c	\
		modify_color_for_tex.c	\
		wood.c			\
		marbre.c		\
		noise.c			\
		noise2.c		\
		menu.c			\
		modif_normale.c	\
		color.c			\
		hsv_rgb.c		\
		options.c		\
		error.c			\
		key_event.c		\
		mouse_event.c		\
		mouse_event2.c		\
		render_options.c	\
		env.c			\
		debug.c			\
		parse.c			\
		parse_param.c		\
		parse_obj.c		\
		parse_scene.c		\
		raytracer.c		\
		moves.c			\
		sphere.c		\
		plane.c			\
		cylinder.c		\
		cylinder2.c		\
		cone.c			\
		cone2.c			\
		caps.c			\
		objects.c		\
		add_objects.c		\
		init_opt.c		\
		torus_error.c	\
		torus_normal.c	\
		torus.c			\
		torus2.c			\
		fill_matiere_in_case.c	\
		light_events.c	\
		others_events.c	\
		others_events2.c	\
		save.c			\
		reflection.c			\
		color_filter.c			\

OBJDIR = Objects
VPATH = Sources
OBJS = $(patsubst %,$(OBJDIR)/%,$(SRC:.c=.o))
NAME = rt

VERSION_GET := $(shell sw_vers | grep "ProductVersion:" | tail -c 8 | head -c 5)
SIERRA = 10.12
EL_CAPITAN = 10.11
MLX_S = Libs/libmlx_sierra
MLX_C = Libs/libmlx_el_capitan
MLX = Libs/libmlx_el_capitan
ifeq ($(VERSION_GET), $(SIERRA))
	MLX = $(MLX_S)
else
	MLX = $(MLX_C)
endif

$(NAME): $(OBJS)
	@make -C Libs/libft
	@make -C Libs/libv3d
	@make -C $(MLX)
	@make -C Libs/libmy_math
	@make -C Libs/libmy_mlx
	@$(CC) -LLibs/libft/ -lft -L$(MLX) -lmlx -LLibs/libv3d/ -lv3d -LLibs/libmy_math -lmy_math -LLibs/libmy_mlx -lmy_mlx -framework OpenGL -framework AppKit -framework Opencl -o $@ $^
	@echo "\033[32m[OK]\033[0m rt created"

all: $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@$(CC) -c -o $@ $< $(CFLAGS)

clean:
	@make clean -C Libs/libft
	@make clean -C Libs/libv3d
	@make clean -C Libs/libmy_math
	@make clean -C Libs/libmy_mlx
	@rm -rf $(OBJDIR)
	@echo "\033[32m[OK]\033[0m object files deleted"

.PHONY: fclean

fclean: clean
	@make fclean -C Libs/libft
	@make fclean -C Libs/libv3d
	@make clean -C $(MLX)
	@make fclean -C Libs/libmy_math
	@make fclean -C Libs/libmy_mlx
	@rm -rf $(NAME)
	@echo "\033[32m[OK]\033[0m rt deleted"

run: all
	./rt Scenes/sphere.rt 

run2: all
	./rt Scenes/demo.rt 

test:
	gcc test.c Sources/modif_normale.c $(CFLAGS) 

re: fclean all
