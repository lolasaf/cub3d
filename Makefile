# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kforfoli <kforfoli@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/03 14:03:23 by wel-safa          #+#    #+#              #
#    Updated: 2025/04/29 20:30:43 by kforfoli         ###   ########.fr        #
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
SRCS := $(addprefix $(SRCDIR)/, main.c minimap.c dda.c render_map.c parse.c \
	parse_colors.c parse_map.c parse_textures.c)
#--- OBJECTS ---
OBJS := $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
#--- HEADERS ---
HEADERS := $(addprefix $(INCDIR)/, cub3d.h)
LIBFTHEADERS := $(addprefix $(LIBFTDIR)/, libft.h ft_printf.h\
	get_next_line_bonus.h)
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