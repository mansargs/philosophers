MAKEFLAGS += --no-print-directory

NAME    := philo_bonus

CC      := cc
CFLAGS  := -Wall -Wextra -Werror

IFLAGS  := -Iinclude
LFLAGS  := -lpthread

SOURCE_DIR := source
OBJ_DIR    := objects

SRC     := $(SOURCE_DIR)/actions_bonus.c \
           $(SOURCE_DIR)/cleaning_bonus.c \
		   $(SOURCE_DIR)/main_bonus.c \
		   $(SOURCE_DIR)/parsing_bonus.c \
		   $(SOURCE_DIR)/simulation_init_bonus.c \
		   $(SOURCE_DIR)/time_bonus.c \
		   $(SOURCE_DIR)/utils_bonus.c


OBJ     := $(OBJ_DIR)/actions_bonus.o \
		   $(OBJ_DIR)/cleaning_bonus.o \
		   $(OBJ_DIR)/main_bonus.o \
		   $(OBJ_DIR)/parsing_bonus.o \
		   $(OBJ_DIR)/simulation_init_bonus.o \
		   $(OBJ_DIR)/time_bonus.o \
		   $(OBJ_DIR)/utils_bonus.o

all: $(NAME)

$(NAME): $(OBJ)
	@echo "🔗 Linking object files..."
	@$(CC) $(CFLAGS) $(OBJ) $(LFLAGS) -o $@
	@echo "✅ Build complete: $(NAME)"

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "🔧 Compiling ..."
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	@echo "🧹 Cleaning object files..."
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "🧽 Removing binary: $(NAME)..."
	@rm -f $(NAME)


re: fclean all

.PHONY: all clean fclean re


