MAKEFLAGS += --no-print-directory

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -I. #-g -O0 #	-fsanitize=address

SRC = thread_handlers.c simulation_init.c time.c main.c cleaning.c creating.c parsing.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

