/*
** test.c for  in /home/penava_b/perso/test
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Wed Dec  9 06:10:58 2015 penava_b
** Last update Sun Jan 24 16:02:49 2016 penava_b
*/

#include "../inc/tools/for_each_va_args_macro.h"
#include <stdio.h>

#define _init(type, name, this, ...)			\
  ______VARARG(type ## _ ## name, this, ##__VA_ARGS__)

#define M(x, name, ...) _virtual.______VARARG(name, x, ##__VA_ARGS__)

#define new_method(type, name, ...)			\
  ______VARARG(type ## _ ## name, type *this, ##__VA_ARGS__)

#define method(name, ...)			\
  ______VARARGP(name, void *this, ##__VA_ARGS__)

/*----------------------------------------------------------------------*/

void	new_method(int, ctor)
{
}

void	new_method(int, ctor, int i)
{
  *this = i;
}

void	new_method(int, printf)
{
  printf("%d\n", *this);
}

struct virtual
{
  void	method(printf);
}	_virtual = { (void *)int_printf1 };

int	main()
{
  int	i = 42;

  _init(int, ctor, &i);
  _init(int, ctor, &i, 84);
  M(&i, printf);
}
