# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/09 14:10:25 by mel-bouh          #+#    #+#              #
#    Updated: 2024/08/05 10:14:28 by mel-bouh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc  -Wall -Werror -Wextra #-fsanitize=thread -g3
SRC = main.c checker.c init.c routine.c utils.c print.c monitoring.c actions.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) -o $@ $^
	@make clean
clean:
	@rm -rf $(OBJ)
fclean: clean
	@rm -rf $(NAME)
re: fclean all

.PHONY: all clean fclean re
