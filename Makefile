##
## Makefile for  in /home/penava_b/perso/test/Obj4
## 
## Made by penava_b
## Login   <penava_b@epitech.net>
## 
## Started on  Tue Dec  8 20:35:08 2015 penava_b
## Last update Sun Jul  3 03:43:24 2016 penava_b
##

CC =		gcc

RM =		rm -f

NAME =		libObjectC.so

SRC =		src/class.c			\
		src/yield.c			\
		src/new_delete.c		\
		src/exceptions.c		\
		src/lrefval.c			\
						\
		src/std/Object.c		\
		src/std/String.c		\
		src/std/Exceptions.c

OBJ =		$(SRC:.c=.o)

COMMON =	-W -Wall -Wextra -Werror -fplan9-extensions -g3 -std=c99

CFLAGS =	$(COMMON) -fPIC -Iinc

LDFLAGS =	$(COMMON) -shared

all: 		$(NAME)

src/std/%.o:	src/std/%.c
		$(CC) $(CFLAGS) -finstrument-functions -c -o $@ $<

$(NAME): 	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
clean:
		$(RM) $(OBJ)

fclean: 	clean
		$(RM) $(NAME)

re: 		fclean all
