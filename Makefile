NAME := ft_ping

CC := clang
CFLAGS := -Wextra -Wall -Werror -g

SRC_DIR := src
OBJS_DIR := obj
SRCS := $(shell find $(SRC_DIR) -name "*.c")
OBJS    := $(addprefix $(OBJS_DIR)/,$(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "\033[1m\033[32mCompiling\033[0m" $@
	@echo "\033[42mSuccessfully compiled :)\033[0m"

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

get_ping:
	@wget https://ftpmirror.gnu.org/inetutils/inetutils-2.0.tar.gz -O inetutils-2.0.tar.gz
	@tar -xvf inetutils-2.0.tar.gz
	@rm inetutils-2.0.tar.gz
	@cd inetutils-2.0 && ./configure && make && sudo make install && cd .. && rm -rf inetutils-2.0

clean:
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
