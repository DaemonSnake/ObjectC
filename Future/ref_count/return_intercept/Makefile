##
## Makefile for  in /home/penava_b/perso/Obj/Obj4/Future/return_intercept
## 
## Made by penava_b
## Login   <penava_b@epitech.net>
## 
## Started on  Fri May 27 23:53:33 2016 penava_b
## Last update Fri May 27 23:53:45 2016 penava_b
##

CC =		gcc

RM =		rm -f

NAME =		test

SRC =		main.c \

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
