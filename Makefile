##
## Makefile for  in /home/penava_b/perso/test/Obj4
## 
## Made by penava_b
## Login   <penava_b@epitech.net>
## 
## Started on  Tue Dec  8 20:35:08 2015 penava_b
## Last update Fri Dec 18 03:48:35 2015 penava_b
##

CC =		gcc

RM =		rm -f

NAME =		libObject.so

SRC =		src/class.c			\
		src/String.c			\
		src/yield.c			\
		src/get_addr.c			\
		src/new_delete.c		\
		src/exceptions.c		\
		src/asm_mess/decode.c		\
		src/asm_mess/itab.c		\
		src/asm_mess/syn.c		\
		src/asm_mess/udis86.c


OBJ =		$(SRC:.c=.o)

COMMON =	-W -Wall -Wextra -Werror -fplan9-extensions -g3

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
