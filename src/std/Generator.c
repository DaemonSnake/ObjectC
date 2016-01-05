/*
** Generator.c for  in /home/penava_b/perso/Obj/Obj4/src
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Mon Dec 21 22:04:06 2015 penava_b
** Last update Tue Jan  5 13:08:50 2016 penava_b
*/

#include <stdlib.h>
#include "Generator.h"

new_tor(Generator, ctor)
{
  superCtor(Object, ctor);
  $.label = NULL;
  $.stack = NULL;
  $.func = NULL;
  $.alive = 0;
  $.init = 0;
  $.size = 0;
}

new_tor(Generator, dtor)
{
  M(this, clean);
  superDtor();
}

int		new_method(Generator, __setjmp)
{
  if (this == NULL)
    return -1;
  $.label = __builtin_return_address(0);
  return 0;
}

void		*__get_front_node_private();
int		printf(const char *, ...);

void		new_method(Generator, saveStack, const char *rsp, const char *rbp)
{
  size_t       	i;

  if (this == NULL || rsp == NULL || rbp == NULL)
    return ;
  if ($.size != 0)
    free($.stack);
  $.stack = NULL;
  $.size = 0;
  $.stack_node = (void *)rbp - __get_front_node_private();
  if (($.stack = malloc(rbp - rsp)) == NULL)
    return ;
  $.size = rbp - rsp;
  for (i = 0; i < $.size; i++)
    $.stack[i] = rsp[i];
}

void		new_method(Generator, restore, const char *rsp)
{
  size_t       	i;

  if (this == NULL || $.stack == NULL || rsp == NULL)
    return ;
  for (i = 0; i < $.size; i++)
    ((char *)rsp)[i] = $.stack[i];
  free($.stack);
  if ($.stack_node > 0)
    {
      // add old nodes to current tree
    }
  $.stack = 0;
  $.size = 0;
}

Generator	*new_method(Generator, reset, void *func)
{
  if (this == NULL)
    return this;
  $.label = 0;
  $.func = func;
  $.size = 0;
  $.stack = 0;
  $.alive = 42;
  $.init = 0;
  return this;
}

void	        new_method(Generator, clean)
{
  if (this == NULL)
    return ;
  if ($.size != 0 || $.stack != NULL)
    {
      free($.stack);
      $.stack = NULL;
      $.size = 0;
    }
  $.label = NULL;
  $.func = NULL;
  $.alive = 0;
  $.init = 0;
}

char	        new_method(Generator, __continue)
{
  if (this != NULL && $.label != NULL && $.alive)
    return 42;
  if (this == NULL)
    return 0;
  M(this, clean);
  return 0;
}

implement(Generator, Object)
{
  push_methods(Generator, __setjmp, saveStack, restore,
	       reset, __continue, clean);
}
