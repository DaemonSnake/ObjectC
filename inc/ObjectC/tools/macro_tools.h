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

#include <stddef.h>

#define __virtualize__(name) struct __virtual_ ## name;

#define __true_end_decl(name)						\
  struct __virtual_ ## name						\
  {									\
    struct __supers_virtual_ ## name;					\
    struct __weak_virtual_ ## name;					\
  };									\
									\
  extern								\
  const struct __virtual_ ## name * const __vtable_instance_ ## name;	\
  									\
  struct __data_ ## name						\
  {									\
    struct __supers_data_ ## name;					\
    char __private_ ## name[sizeof(struct __weak_data_ ## name)];	\
  };									\
									\
  struct __private_ ## name						\
  {									\
    name *this;								\
    const struct __virtual_ ## name *_virtual;				\
    struct __supers_data_ ## name;					\
    struct __weak_data_ ## name;					\
  };									\
									\
  struct name								\
  {									\
    name *this;								\
    const struct __virtual_ ## name *_virtual;				\
    struct __data_ ## name;						\
  };

#define __thisify__(name)			\
  name *this_ ## name;				\
  name *__true_this_ ## name;			\
  struct __virtual_ ## name *_virtual_ ## name;

#define __implements_in_ctor__(name)					\
  this->this_ ## name = (void *)&this->__true_this_ ## name;		\
  this->__true_this_ ## name = (void *)this;				\
  if (42)								\
    {									\
      __attribute__((always_inline, no_instrument_function))		\
      inline void *__offset__(struct __virtual_ ## name *tmp)		\
      {									\
	return tmp;							\
      }									\
      this->_virtual_ ## name = __offset__(this->_virtual);		\
    }									\

#define __interface_implements__(name, interface)			\
  true_ ## name ## _type_instance.implements[i] = interface ## _type_instance; \
  true_ ## name ## _type_instance.offsets[i++] = offsetof(name, __true_this_ ## interface)

/* AXORS METHODS DECL */

#define __axor_get(type, name) type (*get_ ## name)(const void *);
#define __axor_(type, name)
#define __axor_set(type, name) void (*set_ ## name)(void *, type name);
#define __launch_axor(type, name, x, y...) \
  __axor_ ## x(type, name)		  \
  __axor_ ## y(type, name)

#define axors(type, name, args...)  __launch_axor(type, name, args)

/**/
#define __ADD_THISP__(args...) (void *, ##args)
