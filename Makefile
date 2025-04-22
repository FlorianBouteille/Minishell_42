# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csolari <csolari@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/15 10:48:16 by csolari           #+#    #+#              #
#    Updated: 2025/04/18 16:38:40 by csolari          ###   ########.fr        #
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
MEMORY_DIR= $(addprefix $(SRC_DIR), memory_utils/)
DEBUG_DIR= $(addprefix $(SRC_DIR), debug/)
ERROR_DIR= $(addprefix $(SRC_DIR), error/)
MAIN_DIR = $(SRC_DIR)

PARSING_SRC = parsing.c checks.c build_commands.c file_utils.c
LEXING_SRC = lexing.c word_utils.c add_spaces.c
EXECUTION_SRC = execute.c path.c heredoc.c file_redirection.c
MEMORY_SRC = free.c
ERROR_SRC = error.c
DEBUG_SRC = print.c
MAIN_SRC = main.c

OBJ = $(addprefix $(OBJ_DIR), $(PARSING_SRC:.c=.o)) \
	  $(addprefix $(OBJ_DIR), $(LEXING_SRC:.c=.o)) \
	  $(addprefix $(OBJ_DIR), $(EXECUTION_SRC:.c=.o)) \
	  $(addprefix $(OBJ_DIR), $(MEMORY_SRC:.c=.o)) \
	  $(addprefix $(OBJ_DIR), $(DEBUG_SRC:.c=.o)) \
	  $(addprefix $(OBJ_DIR), $(ERROR_SRC:.c=.o)) \
	  $(addprefix $(OBJ_DIR), $(MAIN_SRC:.c=.o)) \

HEADERS =  -I includes/ -I $(LIBFT_DIR)/includes
CC = cc -g
CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(OBJ_DIR) :
		mkdir -p $(OBJ_DIR)

$(NAME) : $(OBJ)
		make -C $(LIBFT_DIR) all
		$(CC) $(CFLAGS) $(INC_H) $(OBJ) -L $(LIBFT_DIR) -lft -lreadline -o $(NAME)

$(OBJ_DIR)%.o: $(MAIN_DIR)%.c | $(OBJ_DIR)
		$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR)%.o: $(DEBUG_DIR)%.c | $(OBJ_DIR)
		$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR)%.o: $(ERROR_DIR)%.c | $(OBJ_DIR)
		$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR)%.o: $(PARSING_DIR)%.c | $(OBJ_DIR)
		$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR)%.o: $(MEMORY_DIR)%.c | $(OBJ_DIR)
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
