# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agengemb <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/21 16:23:39 by agengemb          #+#    #+#              #
#    Updated: 2023/04/18 01:06:44 by agengemb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
NAME = minishell
LIBFT = ./libft/libft.a
SRC = $(wildcard srcs/*.c)
FOLDER = $(wildcard srcs/*/*.c)
FOLDER2 = $(wildcard srcs/*/*/*.c)
OBJ = $(SRC:.c=.o)
OBJFOLDER = $(FOLDER:.c=.o)
OBJFOLDER2 = $(FOLDER2:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(OBJFOLDER) $(OBJFOLDER2) $(LIBFT)
	$(CC) $^ -o $@ -lreadline

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) -D BUFFER_SIZE=42
	
$(LIBFT):
	make -C libft

clean: 
	make -C libft clean
	rm -rf $(LIBFT)
	rm -rf $(OBJ)
	rm -rf $(OBJFOLDER)
	rm -rf $(OBJFOLDER2)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
