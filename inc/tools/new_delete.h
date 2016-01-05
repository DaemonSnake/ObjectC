/*
** delete_new.h for  in /home/penava_b/perso/ObjLang3/Lib
** 
** Made by bastien penavayre
** Login   <penava_b@epitech.net>
** 
** Started on  Fri Oct 30 15:38:53 2015 bastien penavayre
** Last update Tue Jan  5 15:38:48 2016 penava_b
*/

#pragma once

#include <stddef.h>
#include "lrefval.h"

void	*__new_push_ptor(size_t);
void	*__new_get_ptor();
void	*__new_push_tmp(void *);
void	__delete_func(void *, ...);

#define new(type, ctor, ...)						\
  (type ## _ ## ctor							\
   (type ## _type_instance->pre_ctor(__new_push_ptor(sizeof(type))), ##__VA_ARGS__), \
   (type *)__new_get_ptor())

#define newDef(type, ...) new(type, ctor, ##__VA_ARGS__)

#define delete(obj, ...) __delete_func(obj, ##__VA_ARGS__, 0)

#define _init(type, ctor, var, ...)		\
  =						\
    (type ## _ ## ctor				\
     (type ## _type_instance->pre_ctor		\
      (__push_var((struct s_node[1])		\
		  {{ &var,			\
			(void *)type ## _dtor,	\
			42,			\
			__get_current_level(),	\
			(void *)0		\
			}})), ##__VA_ARGS__),	\
     var)
 
#define _def(type, var) _init(type, ctor, var)

#define _ginit(type, ctor, var, ...)					\
  __attribute__((no_instrument_function, constructor))			\
  static inline void	__global_ctor_ ## var()				\
  {									\
    static								\
      struct s_node	tmp = {						\
      &var,								\
      (void *)type ## _dtor,						\
      42,								\
      0,								\
      (void *)0								\
    };									\
    									\
    type ## _ ## ctor							\
      (type ## _type_instance->pre_ctor					\
       (__push_var(&tmp)), ##__VA_ARGS__);				\
  }
