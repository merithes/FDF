# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vboivin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/29 14:12:57 by vboivin           #+#    #+#              #
#    Updated: 2017/03/29 15:13:23 by vboivin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vboivin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/17 14:50:04 by vboivin           #+#    #+#              #
#    Updated: 2017/03/29 14:07:04 by vboivin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fdf
HPATH		= ./includes/
INC		= -I$(HPATH) -I./libft -I./minilibx_macos
FLAGS		= -Wall -Werror -Wextra
FLAGSMLX	= -framework OpenGL -framework Appkit
COMP		= gcc
LIBFT		= -L ./libft -lft
MLX			= -L ./minilibx_macos -lmlx

SRCS 		= main.c draw.c #menu.c dispall.c parse.c
DIR_SRC		= $(addprefix $(SRCPATH)/, $(SRCS))
SRCPATH		= src

OBJ 		= $(SRCS:.c=.o)
DIR_OBJ		= $(addprefix $(OBJPATH)/, $(OBJ))
OBJPATH		= obj

all: $(NAME)

$(OBJPATH)/%.o: $(SRCPATH)/%.c
	@$(COMP) $(FLAGS) -c $< -o $@ $(INC)

$(NAME): $(DIR_OBJ)
	make -C libft
	make -C minilibx_macos
	$(COMP) $(DIR_OBJ) -o $(NAME) $(INC) $(LIBFT) $(FLAGS) $(MLX) $(FLAGSMLX)

clean:
	make clean -C minilibx_macos
	make clean -C libft
	rm -rf $(OBJ)

fclean:
	make clean -C minilibx_macos
	make fclean -C libft
	rm -f $(DIR_OBJ)

re: fclean all

sim:
	make
	rm fdf
	make
