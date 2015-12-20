##
## Makefile for  in /home/penava_b/perso/test/Obj4/test
## 
## Made by penava_b
## Login   <penava_b@epitech.net>
## 
## Started on  Sun Dec 13 01:18:43 2015 penava_b
## Last update Fri Dec 18 18:47:58 2015 penava_b
##

CC =		gcc

RM =		rm -f

NAME =		unit

SRC =		main.c \
                test.c

OBJ =		$(SRC:.c=.o)

COMMON =	-W -Wall -Werror -Wextra -fplan9-extensions -g3

CFLAGS =	$(COMMON) -I../inc

LDFLAGS =	$(COMMON) -Wl,-rpath=../ -L../ -lObject

all: 		$(NAME)

$(NAME): 	$(OBJ)
		$(MAKE) -C ../
		$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
clean:
		$(RM) $(OBJ)

fclean: 	clean
		$(MAKE) -C ../ clean
		$(RM) $(NAME)

re: 		fclean all
