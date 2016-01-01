/*
** test.c for  in /home/penava_b/perso/Obj/Obj4/Future/LeftValueRef
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Fri Jan  1 10:11:54 2016 penava_b
** Last update Fri Jan  1 10:22:17 2016 penava_b
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
}

/*------------------------yield------------------------------*/

void	yield_case()
{
  local(int, tmp, 2);

  __prevent_clean_up();
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

/*-----------------------left reference value-------------------------------*/

#define lrvalue(type, ctor, ...)				\
  (type ## _ ## ctor(__push_var((struct s_node[1])		\
				{{ (type[1]){},			\
				    (void *)type ## _dtor,	\
				      __get_current_level(),	\
				      (void *)0			\
				      }}), ##__VA_ARGS__),	\
   __delayed_level_encrementation(),				\
   (type *)__get_front())

void	lrvalue_func(int *tmp)
{
  printf("Value %d\n", *tmp);
  printf("Other value %d\n", *lrvalue(int, ctor, 5));
  printf("End of lrvalue_func\n");
}

void	calling_lrvalue()
{
  lrvalue_func(lrvalue(int, ctor, 6));
}

/*-----------------------main test-------------------------------*/

int		main()
{
  local(int, tmp, 7);
  new_except(buff);

  default_behaviour();
  yield_case();
  if (setjmp(buff.buff) == 0)
    except_case(&buff);
  else
    printf("Exception Caught\n");
  calling_lrvalue();
}
