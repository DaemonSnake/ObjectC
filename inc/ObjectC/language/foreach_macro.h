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

#define __virtualize__(name) struct name ## __virtual;

#define __true_end_decl(name)						\
  struct name ## __virtual						\
  {									\
      struct name ## __supers_virtual;					\
      struct name ## __weak_virtual;					\
  };									\
									\
  extern								\
  const struct name ## __virtual * const name ## __vtable_instance;	\
  									\
  struct name ## __data                                                 \
  {									\
      struct name ## __supers_data;					\
      char name ## __private[sizeof(struct name ## __weak_data)];	\
  };									\
									\
  struct name ## __private						\
  {									\
    name this;								\
    const struct name ## __virtual *_virtual;				\
    struct name ## __supers_data;					\
    struct name ## __weak_data;                                         \
  };									\
									\
  struct name								\
  {									\
    name this;								\
    const struct name ## __virtual *_virtual;				\
    struct name ## __data;						\
  };

#define __thisify__(name)			\
  name name ## __this;				\
  name name ## __true_this;			\
  struct name ## __virtual *name ## __virtual;

#define __implements_in_ctor__(name)					\
    this->name ## __this = (void *)&this->name ## __true_this;		\
    this->name ## __true_this = (void *)this;				\
    if (42)								\
    {									\
      __attribute__((always_inline, no_instrument_function))		\
      inline void *__offset__(struct name ## __virtual *tmp)		\
      {									\
	return tmp;							\
      }									\
      this->name ## __virtual = __offset__(this->_virtual);		\
    }									\

#define __interface_implements__(name, interface)			\
  name ## __true_type_instance.implements[i] = interface ## __type_instance; \
  name ## __true_type_instance.offsets[i++] = offsetof(typeof(*(name)0), interface ## __true_this)
