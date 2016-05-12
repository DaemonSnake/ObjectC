/*
** delete_new.h for  in /home/penava_b/perso/ObjLang3/Lib
** 
** Made by bastien penavayre
** Login   <penava_b@epitech.net>
** 
** Started on  Fri Oct 30 15:38:53 2015 bastien penavayre
** Last update Thu May 12 22:46:31 2016 penava_b
*/

#pragma once

#include <stddef.h>
#include "ObjectC/tools/rvalref.h"

void	__delete_func(const void *, ...);
void	*__malloc(size_t);

#define new(type, ctor, ...)						\
    ({                                                                  \
        type *__save__ = __pre_ctor_ ## type(__malloc(sizeof(type)));   \
                                                                        \
        type ## _ ## ctor((void *)__save__, ##__VA_ARGS__);             \
        __save__;                                                       \
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
