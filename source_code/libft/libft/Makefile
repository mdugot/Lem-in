# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdugot <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/23 14:09:58 by mdugot            #+#    #+#              #
#    Updated: 2016/02/24 16:18:02 by mdugot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-Wall -Wextra -Werror -c
SOURCE=ft_strlen.c ft_memset.c ft_strdup.c ft_bzero.c ft_memcpy.c ft_memccpy.c \
	   ft_memmove.c ft_memchr.c ft_memcmp.c ft_strcpy.c ft_strncpy.c \
	   ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c \
	   ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c \
	   ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	   ft_tolower.c ft_toupper.c ft_memalloc.c ft_memdel.c ft_strnew.c \
	   ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c \
	   ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c \
	   ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c \
	   ft_putendl_fd.c ft_putnbr_fd.c ft_putchar.c ft_putstr.c ft_putendl.c \
	   ft_putnbr.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c \
	   ft_lstiter.c ft_lstmap.c ft_lstfind.c ft_lstadd_end.c ft_lstadd_after.c \
	   ft_lstadd_before.c ft_lstbefore.c ft_lstdelin.c ft_lstsize.c \
	   ft_lstsort.c ft_lstadd_sorted.c ft_lstsplit.c nbrcmp.c ft_lstmaxsize.c \
	   ft_deltab.c get_next_line.c ft_itoa_base.c significant_bit.c \
	   ft_putwchar.c ft_ftoa.c ft_isin.c ft_sorttab.c ft_readstr.c ft_random.c \
	   ft_isint.c
OBJECT= $(SOURCE:.c=.o)
NAME=libft.a
INCLUDE=../includes/

.PHONY: all
all: $(NAME)

.PHONY: add_to_archive
add_to_archive: $(OBJECT)
	ar r $(ARCHIVE) $(OBJECT)

$(NAME): $(OBJECT)
	ar r $(NAME) $(OBJECT) 
	ranlib $(NAME)
	
%.o: %.c
	$(CC) -I $(INCLUDE) $(CFLAGS) $<

.PHONY: clean
clean:
	rm -f $(OBJECT)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all
