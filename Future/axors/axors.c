/*
** test.c for  in /home/penava_b/perso/test
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Tue Jan 19 12:47:42 2016 penava_b
** Last update Tue Jan 19 15:42:07 2016 penava_b
*/

#include "inc.h"

#define virtual(name)				\
  struct __virtual_ ## name

#define newvirtual(name)			\
  struct __virtual_ ## name ##  _virtual = {	\
    (void *)name ## _set_i,			\
    (void *)name ## _get_i,			\
    0, 0,					\
    0, 0					\
  };

virtual(String)
{
  axor(int, i, set, get);
  axor(double, j, get, set);
  axor(char *, lol);
  axor(char *, lol, set);
  axor(char *, lol, get);
};

typedef struct
{
  struct __virtual_String *_virtual;
  int	i;
  char	*lol;
  double j;
}	String;

new_axors(String, i, get, set);


#include <stdio.h>

int	main()
{
  String tmp = { &_virtual, 0, 0, 0 };

  printf("%d\n", axM(&tmp, i));
  axM(&tmp, i, 25);
  printf("%d\n", axM(&tmp, i));
}
