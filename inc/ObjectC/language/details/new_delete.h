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

/* new */
#define __new_call__N(type, ctor, args...)                      \
    ({                                                          \
        __attribute__((always_inline, no_instrument_function))  \
            inline type __new__(type const __new_this__)        \
        {                                                       \
            type ## __ ## ctor((void *)__new_this__, ##args);   \
            return __new_this__;                                \
        }                                                       \
        __new__(type ## __pre_ctor(__malloc(sizeof(typeof(*(type)0))))); \
    })

#define __new_call__0(type) __new_call__N(type, ctor)

/* var */
#define __var_call__N(type, var, ctor, args...)                         \
    var __attribute__((cleanup(__pop_var))) =                           \
        (__protect_kill_stack((char[1]){0}),                            \
         type ## __ ## ctor						\
         (type ## __pre_ctor                                            \
          (__push_var((struct s_right_value_node[1])                    \
                      {{                                                \
                              ((*(void **)&var = (typeof(*(type)0)[1]){{0}})), \
                                  (void *)type ## __dtor,               \
                                  __get_current_level(),                \
                                  (void *)0, (void *)0                  \
                                  }})), ##args),                        \
         (type)var)

#define __var_call__0(type, var, ...) __var_call__N(type, var, ctor)
