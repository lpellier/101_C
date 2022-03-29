NAME = tetris

FLAGS = -Wall -Werror -Wextra -g3

SRCS =	./main.c \
		./init.c \
		./free.c

HEADERS = ./includes/tetris.h

OBJS = $(SRCS:.c=.o)

CC = gcc

LIBS = -lncurses

all : $(NAME)

$(NAME) : $(OBJS) 
	$(CC) $(FLAGS) $(LIBS) $(SRCS) -o $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)
	rm -rf $(NAME).dSYM

re : fclean all
