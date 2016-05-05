##
## Makefile for  in /home/penava_b/perso/test/Obj4/test
## 
## Made by penava_b
## Login   <penava_b@epitech.net>
## 
## Started on  Sun Dec 13 01:18:43 2015 penava_b
## Last update Thu May  5 15:23:59 2016 penava_b
##

CC =		gcc

RM =		rm -f

NAME =		unit

SRC =		main.c 	\
                Debug.c

OBJ =		$(SRC:.c=.o)

COMMON =	-W -Wall -Werror -Wextra -fplan9-extensions -g3 -finstrument-functions -std=c99

CFLAGS =	$(COMMON) -I../inc

LDFLAGS =	$(COMMON) -Wl,-rpath=../ -L../ -lObject

all: 		$(NAME)

$(NAME): 	$(OBJ)
		$(MAKE) -C ../
		$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)
clean:
		$(RM) $(OBJ)

fclean: 	clean
		$(RM) $(NAME)

re: 		fclean all

layout.c:
		@echo "...Building layout.c"
		@for file in $(SRC);						\
		do								\
			./debug/structDump $$file $(CFLAGS) > layout.c;		\
		done;

cleanlib:	fclean
		@$(MAKE) -C ../ fclean

relib:		fclean cleanlib all
