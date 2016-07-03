/*
 * Copyright (C) 2016  Bastien Penavayre
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#pragma once

#include <setjmp.h>
#include "ObjectC/tools/new_delete.h"

_Pragma("GCC diagnostic push");
_Pragma("GCC diagnostic ignored \"-Wparentheses\"");

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

#define throw(type, ctor, args...)                              \
    __except_throw_func(type ## _type_instance,                 \
                        new(type, ctor, ##args),                \
                        __FILE__, __FUNCTION__, __LINE__)

#define finally					\
  else {					\
  }						\
  else
