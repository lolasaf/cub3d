# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/03 14:03:23 by wel-safa          #+#    #+#              #
#    Updated: 2025/05/30 01:20:42 by wel-safa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
#--- DIRECTORIES ---
SRCDIR := src
INCDIR := inc
OBJDIR := obj
LIBFTDIR := lib/libft
MINILIBXDIR := lib/minilibx-linux
#--- LIBRARIES ---
LIBFT := $(LIBFTDIR)/libft.a
LIBMLX := $(MINILIBXDIR)/libmlx_Linux.a
#--- SOURCES ---
SRCS := $(addprefix $(SRCDIR)/, cast_ray.c draw_wall.c draw.c \
	exit_game_utils.c exit_game.c find_player.c initialize.c key_flags.c \
	key_hooks.c main.c minimap.c mlx_hooks.c move.c parse_color_tok.c \
	parse_colors.c parse_func.c parse_map_utils.c parse_map.c \
	parse_tandc.c parse_texture_load.c parse_textures.c \
	parse_utils.c parse.c player.c render_game.c sprites.c utils.c)
#--- OBJECTS ---
OBJS := $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
#--- HEADERS ---
HEADERS := $(addprefix $(INCDIR)/, cub3d.h)
LIBFTHEADERS := $(addprefix $(LIBFTDIR)/, libft.h ft_printf.h\
	get_next_line.h)
MLXHEADER := /usr/local/include
#--- FLAGS ---
CC := cc
CFLAGS := -Wall -Wextra -Werror -I$(INCDIR) -I$(LIBFTDIR) -I$(MINILIBXDIR) \
	-I$(MLXHEADER) -g
LDFLAGS := -L$(LIBFTDIR) -L$(MINILIBXDIR)
LDLIBS := -lft -lmlx
LFLAGS := -lbsd -lXext -lX11 -lm

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(HEADERS) $(MLXHEADER) $(LIBFT) $(LIBMLX) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) $(LDLIBS) $(LFLAGS)

$(LIBFT): $(LIBFTHEADERS)
	$(MAKE) -C $(LIBFTDIR)

$(LIBMLX):
	$(MAKE) -C $(MINILIBXDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJS)
	$(RM) -r $(OBJDIR)
	$(MAKE) -C $(LIBFTDIR) clean
	$(MAKE) -C $(MINILIBXDIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all
