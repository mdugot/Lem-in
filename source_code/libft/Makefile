# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdugot <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/03 12:08:51 by mdugot            #+#    #+#              #
#    Updated: 2016/01/19 17:21:15 by mdugot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= libft.a
export ARCHIVE=../libft.a
CC= gcc
CFLAGS= -Wall -Werror -Wextra
SRC_NAME= ft_printf.c print.c read.c search.c type.c value.c wprint.c\
		  print_str.c utils.c
SRC_PATH= ./sources/
INC_PATH= ./includes/
LIB_NAME= libft.a
LIB_ID= ft
LIB_PATH= ./libft/
OBJ_NAME= $(SRC_NAME:.c=.o)
OBJ_PATH= ./obj/
SRC= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ= $(addprefix $(OBJ_PATH), $(OBJ_NAME))
LIB= $(addprefix $(LIB_PATH), $(LIB_NAME))

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ)
	ar r $(NAME) $(OBJ)
	make add_to_archive -C $(LIB_PATH)
	ranlib $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CC) -I$(INC_PATH) -I$(LIB_PATH) $(CFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -fv $(OBJ)
	@rm -rf $(OBJ_PATH)
	make $@ -C $(LIB_PATH)

.PHONY: fclean
fclean: clean
	rm -fv $(NAME)
	make $@ -C $(LIB_PATH)

.PHONY: re
re: fclean all
