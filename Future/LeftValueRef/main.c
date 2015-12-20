/*
** main.c for  in /home/penava_b/perso/Obj/Obj4/Future/LeftValueRef
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Fri Dec 18 03:22:31 2015 penava_b
** Last update Fri Dec 18 23:39:13 2015 penava_b
*/

#include <stdio.h>
#include <setjmp.h>
#include "tmp.h"

jmp_buf	env;
void	*rbp = 0;

void	int_ctorVal(int *ptr, int val)
{
  *ptr = val;
}

void	int_dtor(int *ptr)
{
  printf("The end of %p %d\n", ptr, *ptr);
}

void	*func(int *ptr)
{
  __pop_nodes(rbp);
  longjmp(env, -1);
  return ptr;
}

void	func2()
{
  func(lvref(int, ctorVal, 42));
  func(lvref(int, ctorVal, -2));
}

void    set_rbp()
{
  rbp = __builtin_frame_address(0);
}

int	main()
{
  if (set_rbp(), setjmp(env) == 0)
    func2();
  lvref(int, ctorVal, 250);
  printf("end of main!\n");
  return 0;
}
