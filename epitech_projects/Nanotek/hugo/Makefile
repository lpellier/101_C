##
## EPITECH PROJECT, 2022
## MAKEFILE
## File description:
## Makefile
##

NAME		=	nanotekspice

CPPFLAGS	=	-std=c++2a -W -Wall -Wextra -Werror -I./include/ -I./include/Exception/ -I./include/ParserNTS/ -I./include/ParserNTS/Chipsets/ -I./include/ParserNTS/Links/ -I./include/Component/

SRC_DIR		=	./src/

EXCEP_DIR	=	$(SRC_DIR)Exception/

PARSER_DIR	=	$(SRC_DIR)ParserNTS/

CHIPSET_DIR	=	$(PARSER_DIR)/Chipsets/

LINK_DIR	=	$(PARSER_DIR)/Links/

TEST_DIR	=	./tests/

SRCS		=	$(SRC_DIR)main.cpp			\
				$(SRC_DIR)NanoTekSpice.cpp	\
				$(EXCEP_DIR)Exception.cpp	\
				$(PARSER_DIR)ParserNTS.cpp	\
				$(CHIPSET_DIR)Chipsets.cpp	\
				$(LINK_DIR)Links.cpp		\

OBJS		=	$(SRCS:.cpp=.o)

VAL_TO		=	--track-origins=yes
VAL_SL		=	--show-leak-kinds=all
VAL_LC		=	--leak-check=full

all: $(NAME)
	@echo "Build ok!"

$(NAME): $(OBJS)
	g++ -o $(NAME) $(OBJS) $(CFLAGS) $(CPPFLAGS)

debug: CPPFLAGS += -g3
debug: $(NAME)
	@echo "Build debug ok!"

tests_run: $(NAME)
	make -C $(TEST_DIR)
	@echo "Build tests_run ok!"
	gcovr --html --html-details -o $(TEST_DIR)cov.html
	gcovr

clean:
	$(RM) $(OBJS)
	make clean -C $(TEST_DIR) -s
	@echo "Clean ok!"

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(TEST_DIR) -s
	@echo "Fclean ok!"

re: fclean all

.PHONY: all debug tests_run clean fclean re