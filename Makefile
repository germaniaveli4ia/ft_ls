NAME		:= ft_ls

MAKE 		:= make
# directories
INC_DIR		:= ./includes
LIBFT		:= ./libft
LIBFT_INC	:= $(LIBFT)/includes
LIB_LNK 	:= -L $(LIBFT) -l ft

SRC_DIR		:= ./src
SRC_FILES	:=  helpers/find_path.c \
				errors.c \
				file_management.c \
				init.c \
				main.c \
				parse.c	\
				print_by_parts.c \
				print.c \
				process.c \
				sort_files.c \
				sort_options.c

SRC			:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ			:= $(SRC:.c=.o)

# compiler and flags
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror

.PHONY: all clean fclean re

%.o:%.c
	@$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIBFT_INC) -c $< -o $@

$(NAME): lib $(OBJ)
	@$(CC) $(OBJ) $(LIB_LNK) -I $(INC_DIR) -o $(NAME) $(CFLAGS)

all: $(NAME)

clean:
	@$(MAKE) -C $(LIBFT) clean --no-print-directory
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT) fclean --no-print-directory

re: fclean all

lib:
	@$(MAKE) -C $(LIBFT) --no-print-directory

relib:
	@$(MAKE) -C $(LIBFT) re --no-print-directory
	@$(MAKE) re --no-print-directory
