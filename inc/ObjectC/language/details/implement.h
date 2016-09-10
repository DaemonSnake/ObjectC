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

/* AXORS METHODS IMPL */
#define __new_def_axor_get(class, name)			\
  typeof(((struct class ## __private *)0)->name)	\
  new_method(class, get_ ## name)			\
  {							\
    return $.name;					\
  }

#define __new_def_axor_set(class, name)					\
  void									\
  new_method(class, set_ ## name,					\
	     typeof(((struct class ## __private *)0)->name) name)	\
  {									\
    $.name = name;							\
  }

#define __new_def_axor_(class, name)

#define __launch_new_def_axors(class, name, x, y...)	\
    __new_def_axor_ ## x(class, name)			\
    __new_def_axor_ ## y(class, name)

// get
#define __new_user_axor_0(class, name)                             \
    typeof(((struct class ## __private *)0)->name) new_method(class, get_ ## name)

// set
#define __new_user_axor_N(class, name, args...)         \
    void new_method(class, set_ ## name, ##args)
