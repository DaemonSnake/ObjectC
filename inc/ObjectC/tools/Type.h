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

typedef			struct Type
{
  const char		*name;
  const struct Type	*super;
  unsigned long		size;
  unsigned long		nbMethods;
  const char   		**methodsName;
  unsigned		nbImplements;
  const struct Type	**implements;
  unsigned long		*offsets;
  void			(*dtor)(void *);
}			Type;

void			*__tmp_pointer__(void *);
char			__is_same_kind_type(const Type *, const Type *);
void     		*__dynamic_cast(const Type *, const Type *, void *);
const void		*__typeGetMethod(const Type * const, const void * const * const, const char const *);
const Type		*Object_getType(const void *);

# define	      	static_cast(type, var) ((var)->this_ ## type) //takes pointer

# define		as(type) ->this_ ## type //takes value

# define	      	dynamic_cast(type, var)						\
  ((type *)__dynamic_cast(Object_getType(var), type ##_type_instance, var->this))

# define		isInstanceOf(type, pointer)					\
  (pointer != NULL &&							\
   __is_same_kind_type(Object_getType(pointer), type ## _type_instance))

# define		getMethod(obj, name)					\
  (__typeGetMethod(Object_getType(obj),					\
		   (const void *)(((const Object * const )obj)->this)->_virtual, name))

# define		invoke(ret, obj, name, ...)				\
  (((ret (*)(const void*, ...))getMethod(obj, name))((const void*)(((const Object * const)obj)->this), ##__VA_ARGS__))

# define		invokeM(method, obj, ...)				\
  (method)((void *)(((const Object * const)obj)->this), ##__VA_ARGS__)

# define	       	ifIs(type, name, ...)				\
  if (__tmp_pointer__(dynamic_cast(type, (name, ##__VA_ARGS__))))	\
    for (type *name = __tmp_pointer__((void *)0x42); name != 0; name = 0)
