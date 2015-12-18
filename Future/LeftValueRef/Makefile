##
## Makefile for  in /home/penava_b/perso/Obj/Obj4/Future/LeftValueRef
## 
## Made by penava_b
## Login   <penava_b@epitech.net>
## 
## Started on  Fri Dec 18 03:25:34 2015 penava_b
## Last update Fri Dec 18 03:25:49 2015 penava_b
##

CC =		gcc

RM =		rm -f

NAME =		test

SRC =		main.c		\
                tmpObject.c

OBJ =		$(SRC:.c=.o)

COMMON =	-W -Wall -Werror -Wextra

CFLAGS =	$(COMMON) -finstrument-functions

LDFLAGS =	$(COMMON)

all: 		$(NAME)

$(NAME): 	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
clean:
		$(RM) $(OBJ)

fclean: 	clean
		$(RM) $(NAME)

re: 		fclean all
