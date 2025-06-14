MAKEFLAGS += --no-print-directory

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

# 🔧 Proper object file paths (objects/thread.o, etc.)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

# Default target
all: $(NAME)

# 🔗 Link all object files into the final binary
$(NAME): $(OBJ)
	@echo "🔗 Linking object files..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo "✅ Build complete: $(NAME)"

# 🔨 Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "🔧 Compiling ..."
	@$(CC) $(CFLAGS) -c $< -o $@

# 🧹 Clean object files
clean:
	@echo "🧹 Cleaning object files..."
	@rm -rf $(OBJ_DIR)

# 🧽 Clean object files and the final binary
fclean: clean
	@echo "🧽 Removing binary: $(NAME)..."
	@rm -f $(NAME)

# 🔄 Full rebuild
re:
	@echo "🔄 Rebuilding everything..."
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re
