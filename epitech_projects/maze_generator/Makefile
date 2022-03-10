NAME = maze_generator

FLAGS = -Wall -Werror -Wextra -g3

SRCS =	./main.c

HEADERS = ./maze.h

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
