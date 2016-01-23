/*
** test.c for  in /home/penava_b/perso/test/Obj4
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sat Dec 12 22:12:01 2015 penava_b
** Last update Sat Jan 23 15:22:40 2016 penava_b
*/

#include <stdio.h>
#include "Debug.h"

new_tor(Debug, ctor)
{
  superCtor(Object, ctor);
  printf("Birth of %p\n", this);
  $.var = 42;
}

new_tor(Debug, dtor)
{
  superDtor();
  printf("Death of %p\n", this);
}

void	new_method(Debug, print)
{
  printf("This is %p %d\n", this, $.var);
}

new_def_axors(Debug, var, get);

implement(Debug, Object, I)
{
  printf("Debug Class type Operational!\n");
}
