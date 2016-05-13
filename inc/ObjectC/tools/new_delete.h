/*
** delete_new.h for  in /home/penava_b/perso/ObjLang3/Lib
** 
** Made by bastien penavayre
** Login   <penava_b@epitech.net>
** 
** Started on  Fri Oct 30 15:38:53 2015 bastien penavayre
** Last update Sat May 14 00:23:25 2016 penava_b
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
    static inline void	__global_ctor_ ## var()                 \
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
    static inline void __user_code_gctor_ ## var()
