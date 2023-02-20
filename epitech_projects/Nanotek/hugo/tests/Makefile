##
## EPITECH PROJECT, 2023
## MAKEFILE
## File description:
## Makefile
##

NAME		=	unit_tests

CPPFLAGS	=	-W -Wall -Wextra -Werror -I../include/ -I../include/Exception/ -I../include/ParserNTS/ -I../include/ParserNTS/Chipsets/ -I../include/ParserNTS/Links/

LDFLAGS		=	--coverage -lcriterion

SRC_DIR		=	../src/

EXCEP_DIR	=	$(SRC_DIR)Exception/

PARSER_DIR	=	$(SRC_DIR)ParserNTS/

CHIPSET_DIR	=	$(PARSER_DIR)/Chipsets/

LINK_DIR	=	$(PARSER_DIR)/Links/

SRC_TESTS	=	$(CHIPSET_DIR)Chipsets.cpp	\
				$(LINK_DIR)Links.cpp		\
				$(EXCEP_DIR)Exception.cpp	\

UT_FILES	=	TestsChipsets.cpp	\
				TestsLinks.cpp		\

SRC_OBJS	=	$(SRC_TESTS:.c=.o)

UT_OBJS		=	$(UT_FILES:.c=.o)

all: $(NAME)
	@echo "Build ok!"

$(NAME) :
	g++ -c $(SRC_TESTS) $(CPPFLAGS) $(LFLAGS) $(LDFLAGS)
	g++ -c $(UT_FILES) $(CPPFLAGS) $(LFLAGS)
	g++ -o $(NAME) *.o $(CPPFLAGS) $(LFLAGS) -lcriterion -lgcov
	./$(NAME)


clean:
	$(RM) *.html
	$(RM) *.css
	$(RM) $(SRC_DIR)*.gcno
	$(RM) $(SRC_DIR)*.gcda
	$(RM) $(TEST_DIR)*.gcda
	$(RM) $(TEST_DIR)*.gcno
	$(RM) $(TEST_DIR)*.o
	$(RM) $(TESTS_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
