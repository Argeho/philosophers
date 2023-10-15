NAME = philosophers
CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread -g
CC = gcc
OBJ_DIR = obj
SRC_UTILS = main.c\
			utils.c\
			alg.c\
			time.c\
			init.c\
			error.c\

vpath %.c src

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