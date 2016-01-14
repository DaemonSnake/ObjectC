/*
** exception.h for  in /home/penava_b/perso/test
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Fri Nov 27 02:11:31 2015 penava_b
** Last update Thu Jan 14 17:39:11 2016 penava_b
*/

#pragma once

#include <setjmp.h>
#include "tools/new_delete.h"

jmp_buf		*__except_get_front();
void	       	__except_initializer(void *);
int	       	__except_dispatcher(const char *, const char *, int);
void	       	__except_throw_func(const void *, void *, const char *,
				    const char *, int);
int	       	__except_catch_func(const void *);
void		*__except_get_data();
char		__except_get_catch_tool();
int		__except_try_n_finally();
int		__except_is_try();

#pragma GCC diagnostic ignored "-Wparentheses"

struct	       	__false_except_list
{
  char	       	_2;
  char		_9;
  jmp_buf      	_6;
  char		_8;
  void		*_1;
  void	       	*_3;
  void   	*_4;
  int		_7;
  void	 	*_5;
};

#define try								\
  for (__except_initializer((struct __false_except_list[1]){});		\
       __except_dispatcher(__FILE__, __FUNCTION__, __LINE__) ;)		\
    for (; __except_try_n_finally();)					\
      if (__except_is_try())						\
	if (setjmp(*__except_get_front()) == 0)

#define catch(type, name)						\
  else if (__except_catch_func(type ## _type_instance))				\
    for (type *name __attribute__((unused)) = __except_get_data(); __except_get_catch_tool(); )

#define throw(type, ctor, ...)						\
  __except_throw_func(type ## _type_instance,				\
		      new(type, ctor, ##__VA_ARGS__),			\
		      __FILE__, __FUNCTION__, __LINE__)

#define finally					\
  else {					\
  }						\
  else
