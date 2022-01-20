NAME = antman

FLAGS = -Wall -Werror -Wextra -g3

SRCS =	./srcs/main.c \
		./srcs/utils.c

HEADERS = ./includes/antman.h

OBJS = $(SRCS:.c=.o)

CC = gcc

all : $(NAME)

$(NAME) : $(OBJS) $(HEADERS)
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)
	rm -rf $(NAME).dSYM

re : fclean all
