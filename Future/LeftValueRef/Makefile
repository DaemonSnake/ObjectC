##
## Makefile for  in /home/penava_b/perso/Obj/Obj4/Future/LeftValueRef
## 
## Made by penava_b
## Login   <penava_b@epitech.net>
## 
## Started on  Fri Jan  1 10:15:38 2016 penava_b
## Last update Fri Jan  1 11:37:54 2016 penava_b
##

CC =		gcc

RM =		rm -f

NAME =		test

SRC =		lrefval.c	\
                test.c

OBJ =		$(SRC:.c=.o)

COMMON =	-W -Wall -Werror -Wextra

CFLAGS =	$(COMMON)

LDFLAGS =	$(COMMON)

all: 		$(NAME)

test.o:		test.c
		gcc $(CFLAGS) -finstrument-functions -c -o $@ $<

$(NAME): 	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
clean:
		$(RM) $(OBJ)

fclean: 	clean
		$(RM) $(NAME)

re: 		fclean all
