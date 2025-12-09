# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/12 16:23:30 by cdeville          #+#    #+#              #
#    Updated: 2025/12/09 15:58:55 by cdeville         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=btc

CC=c++

CFLAGS= -Wall -Werror -Wextra -std=c++98

DEBUG = -g

SRC_DIR = ./

SRC =	main.cpp \
		BitcoinExchange.cpp

SRCS = $(addprefix $(SRC_DIR), $(SRC))

INCLUDES_DIR= ./

OBJ_DIR= ./objects/
OBJ= $(SRC:.cpp=.o)
OBJS= $(addprefix $(OBJ_DIR), $(OBJ))

INCLUDES= $(addprefix $(INCLUDES_DIR), $(addsuffix .hpp, $(INCLUDES_FILES)))

.PHONY: all clean fclean re

all: $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	echo "Compiling $< to $@"
	$(CC) $(CFLAGS) $(DEBUG) -c $< -o $@

$(NAME): $(OBJS)
	@echo -e "\e[0;32m\nLinking executable:\n\e[0m"
	$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo -e "\e[0;32m\nMandatory part compiled !\n\e[0m"

clean:
	@echo -e "\e[0;31m\nDeleting objects\n\e[0m"
	rm -rf $(OBJ_DIR)

fclean: clean
	@echo -e "\e[0;31m\nDeleting executable\n\e[0m"
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)

re: fclean all
