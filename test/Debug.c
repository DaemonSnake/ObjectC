/*
** test.c for  in /home/penava_b/perso/test/Obj4
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sat Dec 12 22:12:01 2015 penava_b
** Last update Fri Jan 22 23:56:36 2016 penava_b
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

implement(Debug, Object, I)
{
  printf("Debug Class type Operational!\n");
}
