/*
** test.c for  in /home/penava_b/perso/Obj/Obj4/Future/LeftValueRef
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Fri Jan  1 10:11:54 2016 penava_b
** Last update Mon Jan  4 09:45:37 2016 penava_b
*/

#include <stdio.h>
#include "lrefval.h"

/*-----------------------object default tool------------------------------*/

#define local(type, var, ...)						\
  type var;								\
  __push_var((struct s_node[1])						\
	     {{								\
	       &var,							\
		 (void *)type ## _dtor,					\
		 __get_current_level(),					\
		 (void *)0						\
		 }});							\
  type ## _ctor(&var, __VA_ARGS__);

void	int_dtor(int *this)
{
  printf("Dtor of %p %d\n", this, *this);
}

void	int_ctor(int *this, int val)
{
  *this = val;
}

/*------------------------default------------------------------*/

void	default_behaviour()
{
  local(int, tmp, 1);

  printf("\nDEFAULT BEHAVIOUR::\n");
  printf("--END--::\n");
}

/*------------------------yield------------------------------*/

void	yield_case()
{
  local(int, tmp, 2);

  printf("\nYIELD CASE::\n");
  __prevent_clean_up();
  printf("--END--::\n");
  return;
}

/*-----------------------exceptions------------------------------*/

#include <setjmp.h>

#define new_except(name)					\
  struct except_buf name = {__get_current_level() + 1, {}}

struct	except_buf
{
  int	level;
  jmp_buf buff;
};

void	throwing(struct except_buf *buf)
{
  local(int, tmp, 3);

  __end_func(buf->level);
  longjmp(buf->buff, -1);
}

void	except_case(struct except_buf *buf)
{
  local(int, tmp, 4);

  throwing(buf);
}

void	exception_test()
{
  new_except(buff);

  printf("\nEXCEPTIONS TEST::\n");
  if (setjmp(buff.buff) == 0)
    except_case(&buff);
  else
    printf("Exception Caught\n");
  printf("--END--::\n");
}

/*-----------------------left reference value-------------------------------*/

void	lrvalue_func(int *tmp)
{
  printf("::left reference func::\n");
  printf("Value %d\n", *tmp);
  printf("Other value %d\n", *lrvalue(int, ctor, 5));
  printf("::end::\n");
}

void	calling_lrvalue()
{
  printf("\nLEFT REFERENCE TEST::\n");
  lrvalue_func(lrvalue(int, ctor, 6));
  printf("--END--::\n");
}

/*-----------------------return object-------------------------------*/

int	return_object()
{
  local(int, tmp, 7);

  return stdmove(tmp);
}

void	return_object_test()
{
  printf("\nRETURN OBJECT DELETION::\n");
  printf("Return of return_object function %p\n", rvalue(return_object()));
  rvalue(return_object());
  printf("--END--::\n");
}

/*-----------------------main test-------------------------------*/

int		main()
{
  local(int, tmp, 8);

  printf("MAIN::\n");
  default_behaviour();
  yield_case();
  exception_test();
  calling_lrvalue();
  return_object_test();
  printf("\n--MAIN--END--::\n");
}
