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

#define M(var, name, ...)						\
    (((__typeof__(var))__tmp_pointer__((void *)var))                    \
     ->_virtual->name(((__typeof__(var))__tmp_pointer__((void *)0x42))->this, ##__VA_ARGS__))
    
typedef struct Object Object;

struct	__virtual_Object
{
  void	(*dtor)(void *);
  const char *(*toString)(const void *);
  const Type *(*getType)(const void *);
};

struct __interfaces_for_Object
{
};

struct	__data_weak_Object
{
  const Type *__class_type;
};

struct	__data_Object
{
  Object *this_Object;
  char	__private_Object[sizeof(struct __data_weak_Object)];
};

struct	__private_Object
{
  Object *this;
  const struct __virtual_Object *_virtual;
  Object *this_Object;
  struct __data_weak_Object;
};

struct	Object
{
  Object *this;
  const struct __virtual_Object *_virtual;
  struct __data_Object;
};

void	Object_dtor(void *);
void	Object_ctor(void *);

extern const Type * const Object_type_instance;
extern const struct __virtual_Object * const __vtable_instance_Object;

void	*__pre_ctor_Object(struct __private_Object *);
