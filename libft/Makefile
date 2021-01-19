# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alkapolly <alkapolly@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/08 16:21:59 by cblasphe          #+#    #+#              #
#    Updated: 2020/08/13 17:37:09 by alkapolly        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
HEADERS = -I includes
FLAGS = -Wall -Wextra -Werror

SOURCE_FILES = ft_putchar.c \
			ft_putchar_fd.c \
			ft_lstnew.c \
			ft_lstadd.c \
			ft_lstdelone.c \
			ft_lstdel.c \
			ft_lstpurge.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_lstlast.c \
			ft_lst_put_last.c \
			ft_memalloc.c \
			ft_memdel.c \
			ft_memdup.c \
			ft_strdel.c \
			ft_putstr.c \
			ft_putstr_fd.c \
			ft_putendl.c \
			ft_putendl_fd.c \
			ft_putnbr.c \
			ft_putnbr_fd.c \
			ft_strnew.c \
			ft_strclr.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strmap.c \
			ft_strmapi.c \
			ft_strsub.c \
			ft_strtrim.c \
			ft_strjoin.c \
			ft_isspace.c \
			ft_isupper.c \
			ft_islower.c \
			ft_isdigit.c \
			ft_iseven.c \
			ft_isalpha.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_intsdup.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memcpy_bwd.c \
			ft_memmove.c \
			ft_memset.c \
			ft_bzero.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_intlen.c \
			ft_strlen.c \
			ft_strempty.c\
			ft_strdup.c \
			ft_strndup.c \
			ft_strcpy.c \
			ft_strncpy.c \
			ft_strcat.c \
			ft_strncat.c \
			ft_strlcat.c \
			ft_strchr.c \
			ft_strchr_pos.c \
			ft_strrchr.c \
			ft_strstr.c \
			ft_strnstr.c \
			ft_strcmp.c \
			ft_strncmp.c \
			ft_strequ.c \
			ft_strnequ.c \
			ft_strsplit.c \
			ft_itoa.c \
			ft_atoi.c \
			get_next_line.c \
			ft_numlen.c \
			ft_max.c \
			ft_printf/handlers/ft_treatcsp.c \
			ft_printf/handlers/ft_treatfloat.c \
			ft_printf/handlers/ft_treatn.c \
			ft_printf/handlers/ft_treatint.c \
			ft_printf/handlers/ft_treatuox.c \
			ft_printf/helpers/ft_prec_numb.c \
			ft_printf/helpers/ft_itoa_double.c \
			ft_printf/ft_specifications.c \
			ft_printf/buffer.c \
			ft_printf/ft_parse.c \
			ft_printf/ft_printf.c

SOURCE_DIR = srcs

SOURCES = $(addprefix $(SOURCE_DIR)/, $(SOURCE_FILES))

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@ar rcs $(NAME) $(OBJECTS)
	@ranlib $@

%.o: %.c
	@gcc -o $@ -c $< $(FLAGS) $(HEADERS)

clean:
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean re
