# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agengemb <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/21 16:23:39 by agengemb          #+#    #+#              #
#    Updated: 2023/03/23 18:11:46 by agengemb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
NAME = minishell
LIBFT = ./libft/libft.a
SRC = $(wildcard srcs/*.c)
BUILT = $(wildcard srcs/builtins/*.c)
ENVP = $(wildcard srcs/envp/*.c)
OBJ = $(SRC:.c=.o)
OBJBUILT = $(BUILT:.c=.o)
OBJENVP = $(ENVP:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(OBJBUILT) $(OBJENVP) $(LIBFT)
	$(CC) $^ -o $@ -lreadline

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) -D BUFFER_SIZE=42
	
$(LIBFT):
	make -C libft

clean: 
	make -C libft clean
	rm -rf $(LIBFT)
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
