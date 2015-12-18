/*
** main.c for  in /home/penava_b/perso/Obj/Obj4/Future/LeftValueRef
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Fri Dec 18 03:22:31 2015 penava_b
** Last update Fri Dec 18 03:26:01 2015 penava_b
*/

#include <stdio.h>
#include "tmp.h"

void	int_dtor(int *ptr)
{
  printf("The end of %p %d\n", ptr, *ptr);
}

void	int_ctorVal(int *ptr, int val)
{
  *ptr = val;
}

void	*func(int *ptr)
{
  return ptr;
}

int	main()
{
  func(lvref(int, ctorVal, 5));
  func(lvref(int, ctorVal, 42));

  lvref(int, ctorVal, 250);
  
  printf("main!\n");
  return 0;
}
