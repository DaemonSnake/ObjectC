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
#include "ObjectC.h"
#include <string.h>

static
__thread void	*__tmp_pointer_for_ifIs__ = 0;

void		*__tmp_pointer__(void *new_val)
{
  if (new_val == 0)
    return (void *)0;
  if (new_val != (void *)0x42)
    __tmp_pointer_for_ifIs__ = new_val;
  return __tmp_pointer_for_ifIs__;
}

void     	*__dynamic_cast(const Type *my, const Type *their, void *obj)
{
  const Type   	*tmp;
  unsigned	i;
  
  for (tmp = my; tmp != 0; tmp = tmp->super)
    {
      if (tmp == their)
	return obj;
      else if (tmp->nbImplements && tmp->implements && tmp->offsets)
	for (i = 0; i < tmp->nbImplements; i++)
	  if (tmp->implements[i] == their)
	    return ((char *)obj) + tmp->offsets[i];
    }
  return (void *)0;
}

char		__is_same_kind_type(const Type * my, const Type *their)
{
  return (__dynamic_cast(my, their, (void *)0x42) ? 42 : 0);
}

void		__call_class_super_dtor(Object * const this)
{
  const Type	*super;

  super = ((struct Object__private * const)this)->__class_type->super;
  if (super == 0)
    return ;
  ((struct Object__private * const)this)->__class_type = super;
  super->dtor(this);
}

const void     	*__typeGetMethod(const Type * const type,
				 const void * const * const vtable,
				 const char * const name)
{
  for (unsigned i = 0; i < type->nbMethods; i++)
    {
      if (type->methodsName[i] != 0 && strcmp(name, type->methodsName[i]) == 0)
	{
	  if (vtable[i] == 0)
	    throw(String, ctorS, "BadInvode: Not implemented");
	  return vtable[i];
	}
    }
  throw(String, ctorS, "BadInvoke : No such method");
  return (void *)0;
}
