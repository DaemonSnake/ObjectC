/*
** Generator.c for  in /home/penava_b/perso/Obj/Obj4/src
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Mon Dec 21 22:04:06 2015 penava_b
** Last update Mon Jan 18 16:22:17 2016 penava_b
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
  $.label = __builtin_return_address(0);
  return 0;
}

void		new_method(Generator, saveStack, const char *rsp, const char *rbp)
{
  size_t       	i;

  if (rsp == NULL || rbp == NULL)
    return ;
  if ($.size != 0)
    free($.stack);
  $.stack = NULL;
  $.size = 0;
  $.stack_node = __get_front_node_diff(rbp);
  if (($.stack = malloc(rbp - rsp)) == NULL)
    return ;
  $.size = rbp - rsp;
  for (i = 0; i < $.size; i++)
    $.stack[i] = rsp[i];
  $.alive = 42;
}

char		new_const_method(Generator, isLabelOk)
{
  return ($.label != NULL);
}

void		*new_const_method(Generator, getLabel)
{
  return $.label;
}

void		new_method(Generator, beforeYield)
{
  $.alive = 0;
  $.init = 42;
}

char		new_method(Generator, isInitialized)
{
  return $.init;
}

void		*new_const_method(Generator, getFunc)
{
  return $.func;
}

void		new_method(Generator, restore, const char *rbp)
{
  size_t       	i;

  if (this == NULL || $.stack == NULL || rbp == NULL)
    return ;
  for (i = 0; i < $.size; i++)
    ((char *)rbp - $.size)[i] = $.stack[i];
  free($.stack);
  if ($.stack_node > 0)
    __push_back_on_stack((void *)rbp - $.stack_node, __get_current_level() - 1);
  $.stack = 0;
  $.size = 0;
  $.alive = 0;
}

void		new_method(Generator, reset, void *func)
{
  $.label = 0;
  $.func = func;
  $.size = 0;
  $.stack = 0;
  $.alive = 42;
  $.init = 0;
}

void	        new_method(Generator, clean)
{
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
  if ($.label != NULL && $.alive)
    return 42;
  if (this == NULL)
    return 0;
  M(this, clean);
  return 0;
}

implement(Generator, Object) {}
