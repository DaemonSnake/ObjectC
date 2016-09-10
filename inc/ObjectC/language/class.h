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

#include "details/class.h"

#define M(var, name, args...)						\
    (((typeof(var))__tmp_pointer__((void *)var))                        \
     ->_virtual->name(((typeof(var))__tmp_pointer__((void *)0x42))->this, ##args))

#define axM(this, name, args...) ______VARARG(__axor_call_, this, name, ##args)

#define class(name, extends, args...)					\
    typedef struct name *name;						\
									\
    extern const Type * const name ## __type_instance;			\
									\
    struct name ## __supers_virtual					\
    {									\
        struct extends ## __virtual;                                    \
        APPLY_MACRO_VAR(__virtualize__, ##args);			\
    };									\
									\
    struct name ## __private;						\
									\
    struct name ## __interfaces                                         \
    {									\
        char _0[sizeof(struct extends ## __interfaces) +                \
                ______VA_NARGS(args)];                                  \
    };									\
									\
    struct name ## __supers_data                                        \
    {									\
        struct extends ## __data;                                       \
        name name ## __this;                                            \
        APPLY_MACRO_VAR(__thisify__, ##args);                           \
    };									\
									\
    void	name ## __ctor(struct name ## __private *this);         \
    void	name ## __dtor(struct name ## __private *this);         \
    void	*name ## __pre_ctor(struct name ## __private *this);    \
									\
    struct name ## __weak_data

#define interface(name)                                 \
    typedef struct name *name;                          \
                                                        \
    extern const Type * const                           \
    __attribute__((weak))                               \
         name ## __type_instance;                       \
                                                        \
    struct	name                                    \
    {                                                   \
        Object	 this;                                  \
        const struct name ## __virtual *_virtual;       \
    };                                                  \
                                                        \
    const Type * const                                  \
    name ## __type_instance = (Type[1])                 \
    {                                                   \
        {                                               \
            #name,                                      \
            0,                                          \
            sizeof(name),                               \
            0,                                          \
            0,                                          \
            0,                                          \
            0,                                          \
            0,                                          \
            0                                           \
        }                                               \
    };                                                  \
                                                        \
    struct name ## __virtual

#define virtual(name)				\
    struct name ## __weak_virtual

#define end_decl(args...)                       \
    APPLY_MACRO_VAR(__true_end_decl, ##args)

#define method(name) (*name)__ADD_THISP__

#define axors(type, name, args...)  __launch_axor(type, name, args)

#define new_tor(type, name, args...)					\
    void type ## __ ## name(struct type ## __private * const this, ##args)
