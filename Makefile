# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csolari <csolari@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/15 10:48:16 by csolari           #+#    #+#              #
#    Updated: 2025/04/15 11:05:34 by csolari          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = ./sources/
INC_DIR = ./includes/
OBJ_DIR = ./objects/
LIBFT_DIR = ./Libft

PARSING_DIR= $(addprefix $(SRC_DIR), parsing/)
LEXING_DIR=	$(addprefix $(SRC_DIR), lexing/)
EXECUTION_DIR= $(addprefix $(SRC_DIR), execution/)
MAIN_DIR= $(addprefix $(SRC_DIR), main/)	

MAIN_SRC = main.c 
PARSING_SRC = parsing.c
LEXING_SRC = lexing.c
EXECUTION_SRC = execute.c


OBJ = $(addprefix $(OBJ_DIR), $(PARSING_SRC:.c=.o)) \
	  $(addprefix $(OBJ_DIR), $(LEXING_SRC:.c=.o)) \
	  $(addprefix $(OBJ_DIR), $(EXECUTION_SRC:.c=.o)) \
	  $(addprefix $(OBJ_DIR), $(MAIN_SRC:.c=.o)) \


HEADERS =  -I includes/ -I $(LIBFT_DIR)/includes
CC = cc -g
CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(OBJ_DIR) :
		mkdir -p $(OBJ_DIR)

$(NAME) : $(OBJ)
		make -C $(LIBFT_DIR) all
		$(CC) $(CFLAGS) $(INC_H) $(OBJ) -L $(LIBFT_DIR) -lft -o $(NAME)


$(OBJ_DIR)%.o: $(MAIN_DIR)%.c | $(OBJ_DIR)
		$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR)%.o: $(PARSING_DIR)%.c | $(OBJ_DIR)
		$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR)%.o: $(LEXING_DIR)%.c | $(OBJ_DIR)
		$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR)%.o: $(EXECUTION_DIR)%.c | $(OBJ_DIR)
		$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@


clean :
		rm -rf $(OBJ_DIR)
		make -C $(LIBFT_DIR) clean

fclean : clean
		rm -f $(NAME)
		make -C $(LIBFT_DIR) fclean

re : fclean all

.PHONY : all clean fclean re 
