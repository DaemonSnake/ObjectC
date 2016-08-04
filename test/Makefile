##
## Makefile for  in /home/penava_b/perso/test/Obj4/test
## 
## Made by penava_b
## Login   <penava_b@epitech.net>
## 
## Started on  Sun Dec 13 01:18:43 2015 penava_b
## Last update Thu Aug  4 23:26:41 2016 penava_b
##

CC =		../Future/toImplement/compiler/gcc-ObjectC

RM =		rm -f

NAME =		unit

SRC =		main.c 	\
                Debug.c

OBJ =		$(SRC:.c=.o)

COMMON =	-W -Wall -Werror -Wextra -fplan9-extensions -g3 -finstrument-functions

CFLAGS =	$(COMMON) -I../inc

LDFLAGS =	$(COMMON) -Wl,-rpath=../ -L../ -lObjectC

all: 		$(NAME)

$(NAME): 	$(OBJ)
		$(MAKE) -C ../
		$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
clean:
		$(RM) $(OBJ)

fclean: 	clean
		$(RM) $(NAME)

re: 		fclean all

cleanlib:	fclean
		@$(MAKE) -C ../ fclean

relib:		fclean cleanlib all
