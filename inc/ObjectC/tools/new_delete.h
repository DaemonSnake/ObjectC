/*
** delete_new.h for  in /home/penava_b/perso/ObjLang3/Lib
** 
** Made by bastien penavayre
** Login   <penava_b@epitech.net>
** 
** Started on  Fri Oct 30 15:38:53 2015 bastien penavayre
** Last update Sat Apr  2 15:00:33 2016 penava_b
*/

#pragma once

#include <stddef.h>
#include "ObjectC/tools/lrefval.h"

void	*__new_push_ptor(size_t);
void	*__new_get_ptor();
void	*__new_push_tmp(const void *);
void	__delete_func(const void *, ...);
void	*__malloc(size_t);

#define new(type, ctor, ...)						\
  (type ## _ ## ctor							\
   (type ## _type_instance->pre_ctor(__new_push_ptor(sizeof(type))), ##__VA_ARGS__), \
   (type *)__new_get_ptor())

#define newDef(type, ...) new(type, ctor, ##__VA_ARGS__)

#define delete(obj, ...) __delete_func(obj, ##__VA_ARGS__, 0)

#define _init(type, ctor, var, ...)				\
  =								\
    (__protect_kill_stack((char[1]){0}),			\
     type ## _ ## ctor						\
     (type ## _type_instance->pre_ctor				\
      (__push_var((struct s_left_reference_value_node[1])	\
		  {{ &var,					\
			(void *)type ## _dtor,			\
			42,					\
			__get_current_level(),			\
			(void *)0, (void *)0			\
			}})), ##__VA_ARGS__),			\
     var)
 
#define _def(type, var, ...) _init(type, ctor, var, ##__VA_ARGS__)

#define Ginit(type, ctor, var, ...)					\
  __attribute__((no_instrument_function, constructor))			\
  static inline void	__global_ctor_ ## var()				\
  {									\
    static								\
      struct s_left_reference_value_node	tmp = {			\
      &var,								\
      (void *)type ## _dtor,						\
      42,								\
      0,								\
      (void *)0,							\
      (void *)0								\
    };									\
    									\
    __protect_kill_stack((char[1]){0});					\
    type ## _ ## ctor							\
      (type ## _type_instance->pre_ctor					\
       (__push_var(&tmp)), ##__VA_ARGS__);				\
  }									\
									\
  __attribute__((no_instrument_function, constructor))			\
  static inline void __user_code_gctor_ ## var()
