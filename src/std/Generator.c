/*
** Generator.c for  in /home/penava_b/perso/Obj/Obj4/src
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Mon Dec 21 22:04:06 2015 penava_b
** Last update Wed Mar 23 05:50:51 2016 penava_b
*/

#include <stdlib.h>
#include "ObjectC/Generator.h"

new_tor(Generator, ctor)
{
  superCtor(Object, ctor);
  $.label = NULL;
  $.stack = NULL;
  $.func = NULL;
  $.alive = 0;
  $.init = 0;
  $.size = 0;
  $.last = 0;
}

#define $$(method, ...) M(this, method, ##__VA_ARGS__) // ??

new_tor(Generator, ctorF, void *func)
{
  Generator_ctor(this);
  $$(reset, func);
}

new_tor(Generator, dtor)
{
  M(this, clean);
  $$(clean);
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

  if (rsp == NULL || rbp == NULL || rsp > rbp)
    return ; //throw instead
  if ($.size == 0 || $.size != (unsigned long)(rbp - rsp))
    {
      free($.stack);
      $.stack = NULL;
      $.size = 0;
      if (($.stack = malloc(rbp - rsp)) == NULL)
	return ; //throw instead
      $.size = rbp - rsp;
    }
  $.stack_node = __get_front_node_diff(rbp);
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
    return ; //throw instead
  for (i = 0; i < $.size; i++)
    ((char *)rbp - $.size)[i] = $.stack[i];
  if ($.stack_node > 0)
    __push_back_on_stack((void *)rbp - $.stack_node, __get_current_level() - 1);
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
  $.last = 0;
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
  if ($.last)
    {
      M(this, clean);
      return 0;
    }
  return ($.last = 42);
}

new_def_axors(Generator, last, get);

implement(Generator, Object) {}
