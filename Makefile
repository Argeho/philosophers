# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/16 10:23:46 by ahornstr          #+#    #+#              #
#    Updated: 2023/10/16 10:23:46 by ahornstr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CFLAGS = -Wall -Wextra -Werror
CC = gcc
OBJ_DIR = obj
SRC_UTILS = main.c\
			utils.c\
			alg.c\
			time.c\
			init.c\
			error.c\

vpath %.c src

CGREEN=\033[0;32m
CRED=\033[0;31m
CBLUE=\033[0;34m
CEND=\033[0m

OBJ_FILES = $(addprefix $(OBJ_DIR)/,$(SRC_UTILS:.c=.o))

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -Isrc

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $(OBJ_FILES)

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: libft