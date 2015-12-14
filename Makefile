##
## Makefile for  in /home/penava_b/perso/test/Obj4
## 
## Made by penava_b
## Login   <penava_b@epitech.net>
## 
## Started on  Tue Dec  8 20:35:08 2015 penava_b
## Last update Mon Dec 14 07:52:47 2015 penava_b
##

CC =		gcc

RM =		rm -f

NAME =		libObject.so

SRC =		src/class.c	\
		src/String.c

OBJ =		$(SRC:.c=.o)

COMMON =	-fplan9-extensions

CFLAGS =	$(COMMON) -fPIC -Iinc

LDFLAGS =	$(COMMON) -shared

all: 		$(NAME)

$(NAME): 	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
clean:
		$(RM) $(OBJ)

fclean: 	clean
		$(RM) $(NAME)

re: 		fclean all
