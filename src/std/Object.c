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
void		Object_ctor(void *this __attribute__((unused))) {}

__attribute__((no_instrument_function))
void		Object_dtor(void *this __attribute__((unused))) {}

const char	*Object_toString(void *this __attribute__((unused)))
{
  return "default Object's toString method";
}

__attribute__((no_instrument_function))
const Type	*Object_getType(const void *this)
{
  return ((struct __private_Object *)((Object *)this)->this)->__class_type;
}

static struct __virtual_Object true_vtable_instance = {
  (void *)Object_dtor,
  (void *)Object_toString,
  (void *)Object_getType
};

const struct __virtual_Object * const __vtable_instance_Object = &true_vtable_instance;

__attribute__((no_instrument_function))
void	*__pre_ctor_Object(struct __private_Object *this)
{
  this->this = (void *)this;
  this->this_Object = (void *)this;
  this->_virtual = __vtable_instance_Object;
  this->__class_type = Object_type_instance;
  return this;
}

__attribute__((no_instrument_function))
void		__pre_ctor_Object_child(struct __private_Object *this, const void *type)
{
  this->__class_type = type;
}


static Type	true_Object_type_instance =
  {
    "Object",
    0,
    sizeof(Object),
    sizeof(struct __virtual_Object) / sizeof(void *),
    (const char *[sizeof(struct __virtual_Object) / sizeof(void *)])
    {"dtor", "toString", "getType"},
    0,
    0,
    0,
    (void *)Object_dtor
  };

const Type * const Object_type_instance = &true_Object_type_instance;

__attribute__((no_instrument_function))
void	__implement_function_for_Object() {}
