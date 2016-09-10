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

#include "system_header.h"

__CREATE_MACRO__(__POST_COMP_GLUE__, __POST_COMP_GLUE2__(x, y), x, y)
__CREATE_MACRO__(__POST_COMP_GLUE2__, x ## y, x, y)

#define class(name, base, args...)                                      \
    __CREATE_MACRO__(CLASS, __POST_COMP_GLUE__(name, arg), arg)         \
    __CREATE_MACRO__(name ## _SUPERS, args)                             \
                                                                        \
    typedef struct name name; __NL__                                    \
    typedef struct name name ## __private; __NL__                       \
                                                                        \
    struct name

#define virtual                                                 \
    }; __NL__                                                   \
                                                                \
       struct CLASS(_virtual)                                   \
    {                                                           \
        struct                                                  \

#define method(name, ...)                               \
    (*name)(void * const this, ##__VA_ARGS__)

// all type argument will as accessible as this
#define new_method(type, name, ...)                                     \
    __CREATE_MACRO_NF__(type, __POST_COMP_GLUE__(type, __private))      \
    type ## _ ## name(type const *this, ##__VA_ARGS__)                  \
    __UNDEF_MACRO__(type)

#define implement(name) __NL__                                         \
    struct name ## _virtual __global_vtable_ ## name = {0};__NL__      \
                                                                       \
    __attribute__((constructor, no_instrument_function))   __NL__      \
    static void __implement_ ## name ## _function(void)    __NL__      \
    {                                                      __NL__      \
        void __implement_user_ ## name ## _function(void); __NL__      \
        __implement_user_ ## name ## _function();          __NL__      \
    }                                                      __NL__      \
                                                                       \
    inline void __implement_user_ ## name ## _function(void)

#define end_decl(...)
