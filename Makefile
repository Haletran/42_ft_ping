NAME := ft_ping

CC := clang
CFLAGS := -Wextra -Wall -Werror -g

SRC_DIR := src
OBJS_DIR := obj
SRCS := $(shell find $(SRC_DIR) -name "*.c")
OBJS    := $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

all: $(NAME)
	echo "Compilation done"

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	echo "Compiling\033[1m\033[32m" $@ "\033[0m"
	echo "\033[42mSuccessfully compiled :)\033[0m"

$(OBJS_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)
	echo "Objects removed"

fclean: clean
	rm -f $(NAME)
	echo "Executable removed"

re: fclean all

.PHONY: all clean fclean re
