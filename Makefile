# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vboivin <marvin42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/17 14:50:04 by vboivin           #+#    #+#              #
#    Updated: 2017/04/07 13:12:35 by vboivin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fdf
HPATH		= ./includes/
MLXPATH		= minilibx
INC			= -I$(HPATH) -I./libft -I$(MLXPATH)
FLAGS		= -Wall -Werror -Wextra
FLAGSMLX	= -framework OpenGL -framework Appkit
FLAGSX11	= -lXext -lX11 -lm 
COMP		= gcc
LIBFT		= -Llibft -lft
MLX			= -L$(MLXPATH) -lmlx $(FLAGSX11)

SRCS 		= main.c draw.c disp_main.c parse.c parse2.c parse_chains.c
DIR_SRC		= $(addprefix $(SRCPATH)/, $(SRCS))
SRCPATH		= src

OBJ 		= $(SRCS:.c=.o)
DIR_OBJ		= $(addprefix $(OBJPATH)/, $(OBJ))
OBJPATH		= obj

all: $(NAME)

$(OBJPATH)/%.o: $(SRCPATH)/%.c
	$(COMP) $(FLAGS) -c $< -o $@ $(INC)

$(NAME): $(DIR_OBJ)
	make -C libft
	make -C $(MLXPATH)
	$(COMP) $(DIR_OBJ) -o $(NAME) $(INC) $(LIBFT) $(FLAGS) $(MLX)

clean:
	make clean -C 
	make clean -C libft
	rm -rf $(OBJ)

fclean:
	make clean -C $(MLXPATH)
	make fclean -C libft
	rm -f $(DIR_OBJ)

re: fclean all

inc:
	rm -rf $(OBJ) $(NAME)
	make
