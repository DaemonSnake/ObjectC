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
#include <stdlib.h>
#include <stdarg.h>
#include "ObjectC.h"

void		*__malloc(size_t size)
{
  if ((size = (size_t)malloc(size)) == 0)
    throw(String, ctorS, "[Error] Alloction failure!");
  return (void *)size;
}

static void	__delete__(const void *obj)
{
  void		(*dtor)(void *);
  Object	*tmp;

  if (obj == 0)
    return ;
  tmp = (void *)obj;
  tmp = tmp->this;
  dtor = tmp->_virtual->dtor;
  dtor(tmp);
  free(tmp);
}

void	__delete_func(const void *obj, ...)
{
  va_list ap;

  __delete__(obj);
  va_start(ap, obj);
  while ((obj = va_arg(ap, void *)) != 0)
    __delete__(obj);
  va_end(ap);
}
