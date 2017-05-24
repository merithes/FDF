# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vboivin <marvin42.fr>                     +#+   +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/17 14:50:04 by vboivin           #+#    #+#              #
#    Updated: 2017/05/24 18:08:45 by vboivin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fdf
HPATH		= includes
MLXPATH		= minilibx_macos
INC			= -I$(HPATH) -Ilibft -I$(MLXPATH)
FLAGS		= -Wall -Werror -Wextra
FLAGSMLX	= -framework OpenGL -framework Appkit
FLAGSX11	= -lXext -lX11 -lm 
COMP		= gcc
LIBFT		= -Llibft -lft
MLX			= -L$(MLXPATH) -lmlx

SRCS 		= main.c draw.c disp_main.c parse.c parse2.c tools.c image_manage.c
DIR_SRC		= $(addprefix $(SRCPATH)/, $(SRCS))
SRCPATH		= src

OBJ 		= $(SRCS:.c=.o)
DIR_OBJ		= $(addprefix $(OBJPATH)/, $(OBJ))
OBJPATH		= obj

all: $(NAME)

$(OBJPATH)/%.o: $(SRCPATH)/%.c
	$(COMP) $(FLAGS) -c $< -o $@ $(INC)
	@printf "mlx:\tcompiling $<\r"

$(NAME): $(DIR_OBJ)
	@printf "\r                                                           \r"
	@printf "mlx:\tdone\n"
	@make -C libft
	@make -C $(MLXPATH)
	@$(COMP) $(DIR_OBJ) -o $(NAME) $(INCMAC) $(LIBFT) $(FLAGS) $(MLX) $(FLAGSMLX)

clean:
	@make clean -C $(MLXPATH)
	@make clean -C libft
	@rm -rf $(DIR_OBJ)

fclean:
	@make clean -C $(MLXPATH)
	@make fclean -C libft
	@rm -f fdf
	@rm -rf $(DIR_OBJ)

re: fclean all
