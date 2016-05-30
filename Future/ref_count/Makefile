##
## Makefile for  in /home/penava_b/perso/Obj/Obj4/Future/ref_count
## 
## Made by penava_b
## Login   <penava_b@epitech.net>
## 
## Started on  Sat May 28 15:35:40 2016 penava_b
## Last update Sat May 28 15:36:22 2016 penava_b
##

CC =		gcc

RM =		rm -f

NAME =		test

SRC =		src.c \
                main.c \

OBJ =		$(SRC:.c=.o)

COMMON =	-W -Wall -Werror -Wextra

CFLAGS =	$(COMMON) -fplan9-extensions -finstrument-functions

LDFLAGS =	$(COMMON)

all: 		$(NAME)

$(NAME): 	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
clean:
		$(RM) $(OBJ)

fclean: 	clean
		$(RM) $(NAME)

re: 		fclean all
