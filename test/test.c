/*
** test.c for  in /home/penava_b/perso/test/Obj4
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sat Dec 12 22:12:01 2015 penava_b
** Last update Sun Jan 17 21:39:28 2016 penava_b
*/

#include <stdio.h>
#include "test.h"

new_tor(Debug, ctor)
{
  superCtor(Object, ctor);
  printf("Birth of %p\n", this);
}

new_tor(Debug, dtor)
{
  superDtor();
  printf("Death of %p\n", this);
}

void	new_method(Debug, print)
{
  printf("This is %p\n", this);
}

implement(Debug, Object, I)
{
  printf("Debug Class type Operational!\n");
}
