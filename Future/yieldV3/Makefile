##
## Makefile for  in /home/penava_b/perso/C/CYield2
## 
## Made by penava_b
## Login   <penava_b@epitech.net>
## 
## Started on  Thu May  5 19:24:12 2016 penava_b
## Last update Thu May  5 19:24:39 2016 penava_b
##

CC =		gcc

RM =		rm -f

NAME =		test

SRC =		test.c \
                yield.c \

OBJ =		$(SRC:.c=.o)

COMMON =	-W -Wall -Werror -Wextra

CFLAGS =	$(COMMON)

LDFLAGS =	$(COMMON)

all: 		$(NAME)

$(NAME): 	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
		@echo "test build"
clean:
		$(RM) $(OBJ)

fclean: 	clean
		$(RM) $(NAME)

re: 		fclean all
