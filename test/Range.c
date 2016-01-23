/*
** Range.c for  in /home/penava_b/perso/Obj/Obj4/test
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sat Jan 23 19:01:21 2016 penava_b
** Last update Sat Jan 23 19:53:23 2016 penava_b
*/

#include "Range.h"

new_tor(Range, ctor)
{
  superCtor(Generator, ctor);
}

new_tor(Range, ctorBE, int start, int end)
{
  superCtor(Generator, ctor);
  $.b = start;
  $.e = end;
}

new_tor(Range, dtor)
{
  superDtor();
}

int	new_const_method(Range, operator_function_void)
{
  initYield();
  for (int i = $.b; i < $.e; i++)
    yield(i);
  return 0;
}

implement(Range, Generator)
{
}
