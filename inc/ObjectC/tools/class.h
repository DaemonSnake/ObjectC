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

#define class(name, extends, args...)					\
    typedef struct name name;						\
									\
    extern const Type * const name ## _type_instance;			\
									\
    struct __supers_virtual_ ## name					\
    {									\
        struct __virtual_ ## extends;					\
        APPLY_MACRO_VAR(__virtualize__, ##args);			\
    };									\
									\
    struct __private_ ## name;						\
									\
    struct __interfaces_for_ ## name					\
    {									\
        char _0[sizeof(struct __interfaces_for_ ## extends) +           \
                ______VA_NARGS(args)];                                  \
    };									\
									\
    struct __supers_data_ ## name                                       \
    {									\
        struct __data_ ## extends;                                      \
        name *this_ ## name;                                            \
        APPLY_MACRO_VAR(__thisify__, ##args);                           \
    };									\
									\
    void	name ## _ctor(struct __private_ ## name *this);         \
    void	name ## _dtor(struct __private_ ## name *this);         \
    void	*__pre_ctor_ ## name(struct __private_ ## name *this);  \
									\
    struct __weak_data_ ## name

#define interface(name)                                 \
    typedef struct name name;                           \
                                                        \
    extern const Type * const                           \
    __attribute__((weak))                               \
         name ## _type_instance;                        \
                                                        \
    struct	name                                    \
    {                                                   \
        Object	*this;                                  \
        const struct __virtual_ ## name *_virtual;      \
    };                                                  \
                                                        \
    const Type * const                                  \
    name ## _type_instance = (Type[1])                  \
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
    struct __virtual_ ## name

#define virtual(name)				\
    struct __weak_virtual_ ## name

#define end_decl(args...)                       \
    APPLY_MACRO_VAR(__true_end_decl, ##args)

#define method(name) (*name)__ADD_THISP__

#define new_tor(type, name, args...)					\
    void type ## _ ## name(struct __private_ ## type * const this, ##args)

#define new_method(type, name, args...)					\
    type ## _fake_ ## name();						\
    typeof(type ## _fake_ ## name())                                \
    type ## _ ## name(struct __private_ ## type * const this,		\
                      ##args);                                          \
									\
    __attribute__((constructor, no_instrument_function))                \
    static inline void	_imp_ ## name()					\
    {									\
        void __implement_function_for_ ## type();                       \
        __implement_function_for_ ## type();				\
        void __push_method_ ## type(void *, const char *, size_t);      \
        __push_method_ ## type(type ## _ ## name, #name,                \
                               offsetof(struct __virtual_ ## type, name)); \
    }									\
									\
    typeof(type ## _fake_ ## name())                                \
    type ## _ ## name(struct __private_ ## type * const this, ##args)
