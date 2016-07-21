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

__attribute__((no_instrument_function))
void		Object__ctor(void *this __attribute__((unused))) {}

__attribute__((no_instrument_function))
void		Object__dtor(void *this __attribute__((unused))) {}

const char	*Object__toString(void *this __attribute__((unused)))
{
  return "default Object's toString method";
}

__attribute__((no_instrument_function))
const Type	*Object__getType(const void *this)
{
  return ((struct Object__private *)((Object *)this)->this)->__class_type;
}

static struct Object__virtual true_vtable_instance = {
  (void *)Object__dtor,
  (void *)Object__toString,
  (void *)Object__getType
};

const struct Object__virtual * const Object__vtable_instance = &true_vtable_instance;

__attribute__((no_instrument_function))
void	*Object__pre_ctor(struct Object__private *this)
{
  this->this = (void *)this;
  this->Object__this = (void *)this;
  this->_virtual = Object__vtable_instance;
  this->__class_type = Object__type_instance;
  return this;
}

__attribute__((no_instrument_function))
void		Object__pre_ctor_child(struct Object__private *this, const void *type)
{
  this->__class_type = type;
}


static Type	Object__true_type_instance =
  {
    "Object",
    0,
    sizeof(Object),
    sizeof(struct Object__virtual) / sizeof(void *),
    (const char *[sizeof(struct Object__virtual) / sizeof(void *)])
    {"dtor", "toString", "getType"},
    0,
    0,
    0,
    (void *)Object__dtor
  };

const Type * const Object__type_instance = &Object__true_type_instance;

__attribute__((no_instrument_function))
void	Object__implement_function() {}
