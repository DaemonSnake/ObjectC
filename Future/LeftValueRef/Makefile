##
## Makefile for  in /home/penava_b/perso/Obj/Obj4/Future/LeftValueRef
## 
## Made by penava_b
## Login   <penava_b@epitech.net>
## 
## Started on  Fri Dec 18 03:25:34 2015 penava_b
## Last update Fri Dec 18 19:38:10 2015 penava_b
##

CC =		gcc

RM =		rm -f

NAME =		test

FLAGS =		-W -Wall -Werror -Wextra

all: 		$(NAME)

$(NAME):
		gcc -c main.c $(FLAGS) -finstrument-functions
		gcc -c lrvalue.c $(FLAGS)
		$(CC) main.o lrvalue.o -o $(NAME) $(FLAGS)
clean:
		$(RM) $(OBJ)

fclean: 	clean
		$(RM) $(NAME)

re: 		fclean all
