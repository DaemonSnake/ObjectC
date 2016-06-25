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
#include "ObjectC/tools/rvalref.h"

void	__delete_func(const void *, ...);
void	*__malloc(size_t);

#define new(type, ctor, ...)						\
    ({                                                                  \
        __attribute__((always_inline, no_instrument_function))          \
            inline type *__new__(type * const __new_this__)             \
        {                                                               \
            type ## _ ## ctor((void *)__new_this__, ##__VA_ARGS__);     \
            return __new_this__;                                        \
        }                                                               \
        __new__(__pre_ctor_ ## type(__malloc(sizeof(type))));           \
    })

#define newDef(type, ...) new(type, ctor, ##__VA_ARGS__)

#define delete(obj, ...) __delete_func(obj, ##__VA_ARGS__, 0)

#define _var(type, var, ctor, ...)                                      \
    * const var =                                                       \
        (__protect_kill_stack((char[1]){0}),                            \
         type ## _ ## ctor						\
         (__pre_ctor_ ## type                                           \
          (__push_var((struct s_right_value_node[1])                    \
                      {{                                                \
                              ((*(void **)&var = (type[1]){{0}})),      \
                                  (void *)type ## _dtor,                \
                                  42,                                   \
                                  __get_current_level(),                \
                                  (void *)0, (void *)0                  \
                                  }})), ##__VA_ARGS__),                 \
         (type *)var)
 
#define _def(type, var, ...) _var(type, var, ctor, ##__VA_ARGS__)

#define Ginit(type, ctor, var, ...)                             \
    __attribute__((no_instrument_function, constructor))	\
    static void	__global_ctor_ ## var()                         \
    {                                                           \
        static                                                  \
            struct s_right_value_node	tmp =                   \
            {                                                   \
                &var,						\
                (void *)type ## _dtor,				\
                42,						\
                0,						\
                (void *)0,					\
                (void *)0					\
            };                                                  \
                                                                \
        __protect_kill_stack((char[1]){0});			\
        type ## _ ## ctor					\
            (__pre_ctor_ ## type				\
             (__push_var(&tmp)), ##__VA_ARGS__);		\
    }                                                           \
                                                                \
    __attribute__((no_instrument_function, constructor))	\
    static void __user_code_gctor_ ## var()
