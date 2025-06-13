NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude

SRC_DIR = source
OBJ_DIR = objects
INC_DIR = include

SRC = $(SRC_DIR)/thread.c \
      $(SRC_DIR)/simulation_init.c \
      $(SRC_DIR)/time.c \
      $(SRC_DIR)/main.c \
      $(SRC_DIR)/cleaning.c \
      $(SRC_DIR)/creating.c \
      $(SRC_DIR)/parsing.c \
      $(SRC_DIR)/actions.c

OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	@echo "🔗 Linking object files..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
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
