/*
** lang_header.h for  in /home/penava_b/perso/Obj/Obj4/Future/compiler
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Tue May 24 00:21:51 2016 penava_b
** Last update Sat May 28 01:21:55 2016 penava_b
*/

#pragma once

#include "system_header.h"

__CREATE_MACRO__(#, __POST_COMP_GLUE__, __POST_COMP_GLUE2__(x, y), x, y)
__CREATE_MACRO__(#, __POST_COMP_GLUE2__, x ## y, x, y)

#define class(name, base, args...)                                      \
    __CREATE_MACRO__(__HASH_WORD__, CLASS, __POST_COMP_GLUE__(name, arg), arg) \
    __CREATE_MACRO__(__HASH_WORD__, name ## _SUPERS, args)              \
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
    __CREATE_MACRO_NF__(__HASH_WORD__, type, __POST_COMP_GLUE__(type, __private)) \
    type ## _ ## name(type const *this, ##__VA_ARGS__)                  \
    __UNDEF_MACRO__(__HASH_WORD__, type)

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
