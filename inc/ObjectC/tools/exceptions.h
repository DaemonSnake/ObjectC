/*
** exception.h for  in /home/penava_b/perso/test
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Fri Nov 27 02:11:31 2015 penava_b
** Last update Thu May  5 15:51:54 2016 penava_b
*/

#pragma once

#include <setjmp.h>
#include "ObjectC/tools/new_delete.h"

_Pragma("GCC diagnostic push");
_Pragma("GCC diagnostic ignored \"-Wparentheses\"")

jmp_buf		*__except_get_front();
void	       	__except_initializer(void *);
int	       	__except_dispatcher(const char *, const char *, int);
void	       	__except_throw_func(const void *, void *, const char *,
				    const char *, int);
int	       	__except_catch_func(const void *);
void		*__except_get_data();
int		__except_try_n_finally();
int		__except_is_try();
void		__except_dtor(void *);

struct	       	__except_list_node
{
  char	       	status;
  char		caught;
  jmp_buf      	buff;
  const void   	*type;
  void	 	*obj;
  void    	*origin;
  int		level;
  void	       	*next;
};

#define try								\
  for (__except_initializer((struct __except_list_node[1]){0});		\
       __except_dispatcher(__FILE__, __FUNCTION__, __LINE__) ;)		\
    for (; __except_try_n_finally();)					\
      if (__except_is_try())						\
	  if (setjmp(*__except_get_front()) == 0)

#define catch(type, name)						\
  else if (__except_catch_func(type ## _type_instance))			\
    for (type *name __attribute__((unused)) = __except_get_data(); name != 0 ; name = 0)

#define throw(type, ctor, ...)						\
  __except_throw_func(type ## _type_instance,				\
		      new(type, ctor, ##__VA_ARGS__),			\
		      __FILE__, __FUNCTION__, __LINE__)

#define finally					\
  else {					\
  }						\
  else
