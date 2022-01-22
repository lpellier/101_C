NAME = minishell1

FLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address

SRCS =	./srcs/main.c \
		./srcs/utils.c \
		./srcs/free.c \
		./srcs/execute.c \
		./srcs/init.c 

HEADERS = ./includes/minishell1.h

OBJS = $(SRCS:.c=.o)

CC = gcc

all : $(NAME)

$(NAME) : $(OBJS) $(HEADERS)
	export MallocNanoZone=0
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)
	rm -rf $(NAME).dSYM

re : fclean all
