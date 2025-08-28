MAKEFLAGS += --no-print-directory

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude
LDFLAGS = -lpthread

SRC_DIR = source
OBJ_DIR = objects

SRC = $(SRC_DIR)/thread.c \
      $(SRC_DIR)/simulation_init.c \
      $(SRC_DIR)/time.c \
      $(SRC_DIR)/main.c \
      $(SRC_DIR)/cleaning.c \
      $(SRC_DIR)/creating.c \
      $(SRC_DIR)/parsing.c \
      $(SRC_DIR)/actions.c

OBJ = $(OBJ_DIR)/thread.o \
      $(OBJ_DIR)/simulation_init.o \
      $(OBJ_DIR)/time.o \
      $(OBJ_DIR)/main.o \
      $(OBJ_DIR)/cleaning.o \
      $(OBJ_DIR)/creating.o \
      $(OBJ_DIR)/parsing.o \
      $(OBJ_DIR)/actions.o

all: $(NAME)

$(NAME): $(OBJ)
	@echo "🔗 Linking object files..."
	@$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
	@echo "✅ Build complete: $(NAME)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "🔧 Compiling ..."
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "🧹 Cleaning object files..."
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "🧽 Removing binary: $(NAME)..."
	@rm -f $(NAME)

re:
	@echo "🔄 Rebuilding everything..."
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re
