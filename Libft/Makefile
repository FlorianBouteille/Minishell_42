# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csolari <csolari@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/12 13:11:51 by csolari           #+#    #+#              #
#    Updated: 2025/03/19 11:55:31 by csolari          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_DIR = ./sources/
INC_DIR = ./includes/
OBJ_DIR = ./objects/

CHECKS_DIR=$(addprefix $(SRC_DIR), checks/)
CONVERSION_DIR=	$(addprefix $(SRC_DIR), conversion/)
DISPLAY_DIR= $(addprefix $(SRC_DIR), display/)
LISTS_DIR= $(addprefix $(SRC_DIR), lists/)
MEMORY_DIR= $(addprefix $(SRC_DIR), memory/)
STRINGS_DIR= $(addprefix $(SRC_DIR), strings/)

CHECKS_SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \

CONVERSION_SRC = ft_atoi.c ft_convert_base.c ft_uitoa.c ft_itoa.c ft_toupper.c ft_tolower.c ft_atol.c \

DISPLAY_SRC = ft_printf.c ft_printf_outils.c ft_printf_outils2.c ft_putchar_fd.c ft_putstr_fd.c \
				ft_putendl_fd.c ft_putnbr_fd.c get_next_line_bonus.c

LISTS_SRC = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
				ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_ps_lstadd_back.c ft_ps_lstnew.c \
				ft_ps_lstfree.c ft_ps_printlist.c ft_ps_lstadd_front.c ft_ps_lstlast.c ft_ps_lstpenultimate.c \
				ft_ps_lstsize.c ft_ps_lstmax.c ft_ps_index.c ft_ps_firstsup.c ft_ps_firstinf.c ft_ps_lstmin.c\

MEMORY_SRC = ft_memchr.c ft_memcmp.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_calloc.c \

STRINGS_SRC = ft_strlen.c  ft_strlcpy.c ft_strlcat.c  ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strmapi.c \
				ft_strnstr.c   ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_striteri.c \
				ft_strjoin_free.c\

OBJ = $(addprefix $(OBJ_DIR), $(CHECKS_SRC:.c=.o)) \
	  $(addprefix $(OBJ_DIR), $(CONVERSION_SRC:.c=.o)) \
	  $(addprefix $(OBJ_DIR), $(DISPLAY_SRC:.c=.o)) \
	  $(addprefix $(OBJ_DIR), $(LISTS_SRC:.c=.o)) \
	  $(addprefix $(OBJ_DIR), $(MEMORY_SRC:.c=.o)) \
	  $(addprefix $(OBJ_DIR), $(STRINGS_SRC:.c=.o)) \

HEADERS = -I $(INC_DIR)
CC = cc -g
CFLAGS = -Wall -Wextra -Werror
AR = ar -rcs

all : $(NAME)

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

$(NAME) : $(OBJ)
	$(AR) $(NAME) $(OBJ)

$(OBJ_DIR)%.o: $(CHECKS_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR)%.o: $(CONVERSION_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR)%.o: $(DISPLAY_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR)%.o: $(LISTS_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR)%.o: $(MEMORY_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

$(OBJ_DIR)%.o: $(STRINGS_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re 
