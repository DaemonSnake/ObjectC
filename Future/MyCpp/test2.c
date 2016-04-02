/*
** test2.c for  in /home/penava_b
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sun Mar 27 13:29:36 2016 penava_b
** Last update Sun Mar 27 15:37:48 2016 penava_b
*/

#include <stdio.h>

#define toPragma(name) push_my_macro(name)
#define toString2(name) #name
#define toString(name) toString2(name)

#define class(name)				\
  typedef struct name name;			\
  _Pragma(toString(toPragma(name)))		\
  struct name

#define method(name, ...) (*name)(CLASS *this, ##__VA_ARGS__)

class(String)
{
  char method(get, int);
};

void	func(CLASS *tmp)
{
}

int	main()
{
}
