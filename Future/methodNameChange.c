/*
** test.c for  in /home/penava_b/perso/test
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Wed Dec  9 06:10:58 2015 penava_b
** Last update Thu Jan 28 15:18:26 2016 penava_b
*/

#include "../inc/tools/for_each_va_args_macro.h"
#include <stdio.h>

#define _init(type, name, this, ...)			\
  ______VARARG(type ## _ ## name, this, ##__VA_ARGS__)

#define M(x, name, ...) _virtual.______VARARG(name, x, ##__VA_ARGS__)

#define new_method(type, name, ...)			\
  ______VARARG(type ## _ ## name, type *this, ##__VA_ARGS__)

#define method(name, ...)			\
  ______VARARGP(name, void *this, ##__VA_ARGS__)

/*----------------------------------------------------------------------*/

typedef int Object;
typedef double String;

#define Mv(x, name, ...)						\
  _virtual.name ## 0(x, ______VA_NARGS(x, ##__VA_ARGS__) - 1, ##__VA_ARGS__)

#define new_var_method(type, name, ...)					\
  type ## _ ## name ## 0(type *this, ##__VA_ARGS__, unsigned __va_count__, ...)

#define var_method(name, ...)			\
  (*name ## 0)(void *this, ##__VA_ARGS__, unsigned, ...)

#include <stdarg.h>

#define for_arg(type, name)						\
  for (va_list __ap; (__va_count__ > 0 && (va_start(__ap, __va_count__), 42)); va_end(__ap)) \
    for (type *name; (__va_count__ > 0 && (name = va_arg(__ap, type *), 42)); __va_count__--) \
      if (__isinstanceof(#type, name))					\

#define bad_arg(type, name)					\
  else								\
    if (__push_name(name))					\
      for (type *name = __pop_name(); name != 0; name = 0)	\
	if (__isinstanceof(#type, name))

/*----------------------------------------------------------------------*/

int	__isinstanceof(void *a, void *b)
{
  static int i = 0;

  if (b == (void *)0x37)
    return (i++);
  return 42;
}

static __thread void *__save__ = 0;

int	__push_name(void *arg)
{
  return ((__save__ = arg) != 0);
}

void	*__pop_name()
{
  return __save__;
}

/*----------------------------------------------------------------------*/
void	new_method(int, ctor)
{
}

void	new_method(int, ctor, int i)
{
  *this = i;
}

void	new_method(int, printf)
{
  printf("%d\n", *this);
}

void	new_var_method(int, printf)
{
  printf("Number of arguments is %d\n", __va_count__);
  for_arg(Object, arg)
    {
      printf("%p\n", arg);
    }
  bad_arg(String, arg)
    {
      printf("Bad Object is a string %p\n", arg);
    }
}

struct virtual
{
  void	method(printf);
  void	var_method(printf);
}	_virtual = {
  (void *)int_printf1,
  (void *)int_printf0
};

int	main()
{
  int	i = 42;

  _init(int, ctor, &i);
  _init(int, ctor, &i, 84);
  M(&i, printf);
  Mv(&i, printf, 0x42, 0x37, 0x53);
}
