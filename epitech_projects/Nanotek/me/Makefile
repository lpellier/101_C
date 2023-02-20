##
## EPITECH PROJECT, 2022
## MAKEFILE
## File description:
## Makefile
##

NAME		=	nanotekspice

CPPFLAGS	=	-std=c++2a -W -Wall -Wextra -Werror -g3

SRC_DIR		=	./src/
SRCS		=	$(SRC_DIR)main.cpp	
OBJS		=	$(SRCS:.cpp=.o)

all: $(NAME)
	@echo "Build ok!"

$(NAME): $(OBJS)
	g++ -o $(NAME) $(OBJS) $(CPPFLAGS)

clean:
	rm -rf $(OBJS)
	@echo "Clean ok!"

fclean: clean
	rm -rf $(NAME)
	@echo "Fclean ok!"

re: fclean all
