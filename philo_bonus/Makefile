NAME    := philo_bonus

CC      := cc
CFLAGS  := -Wall -Wextra -Werror
IFLAGS  := -Iinclude
LFLAGS  := -lpthread

SOURCE_DIR := source


SRC     := $(SOURCE_DIR)/main_bonus.c,

OBJ     := $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(LFLAGS) $(NAME) -o $@

%.o : $(SRC)/%.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $@ -o $<


