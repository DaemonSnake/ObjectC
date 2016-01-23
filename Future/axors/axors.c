/*
** test.c for  in /home/penava_b/perso/test
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Tue Jan 19 12:47:42 2016 penava_b
** Last update Sat Jan 23 01:29:54 2016 penava_b
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
  virtual(String) *_virtual;
  int	i;
  char	*lol;
  double j;
}	String;

new_def_axors(String, i, get, set);

virtual(String) _virtual = {
  (void *)String_set_i, (void *)String_get_i,
  0, 0, 0, 0
};

#include <stdio.h>

int	main()
{
  String tmp = { &_virtual, 0, 0, 0 };

  printf("%d\n", axM(&tmp, i));
  axM(&tmp, i, 25);
  printf("%d\n", axM(&tmp, i));
}
