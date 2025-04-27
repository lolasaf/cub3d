# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/03 14:03:23 by wel-safa          #+#    #+#              #
#    Updated: 2025/04/27 21:51:42 by wel-safa         ###   ########.fr        #
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
SRCS := $(addprefix $(SRCDIR)/, map_validation.c parse.c minimap.c dda.c)
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