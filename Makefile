# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mel-bouh <mel-bouh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/09 14:10:25 by mel-bouh          #+#    #+#              #
#    Updated: 2024/07/31 14:53:36 by mel-bouh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc -Wall -Werror -Wextra
SRC = main.c checker.c init.c routine.c utils.c print.c monitoring.c actions.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) -o $@ $^
clean:
	@rm -rf $(OBJ)
fclean: clean
	@rm -rf $(NAME)
re: fclean all

.PHONY: all clean fclean re
