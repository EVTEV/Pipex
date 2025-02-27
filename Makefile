NAME = pipex

MAKEFLAGS = --no-print-directory

LIBFT_DIR = ./LIBFT
LIBFT = $(LIBFT_DIR)/libft.a
INC_LIBFT = -I$(LIBFT_DIR)/inc
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

INC_DIR = ./inc
INC = -I$(INC_DIR)

SRC_DIR = src
OBJ_DIR = obj

SRC = main.c \
	  $(wildcard $(SRC_DIR)/Exec/*.c) \
	  $(wildcard $(SRC_DIR)/Pars/*.c) \
	  $(wildcard $(SRC_DIR)/Utils/*.c)
#$(wildcard $(SRC_DIR)/Pars/*.c) \

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror #-g -gdwarf-4
RM = @rm -rf
AR = ar -rcs

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC) $(INC_LIBFT)

$(LIBFT):
	echo "CREATING LIBFT"
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
