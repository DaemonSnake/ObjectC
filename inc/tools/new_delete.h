/*
** delete_new.h for  in /home/penava_b/perso/ObjLang3/Lib
** 
** Made by bastien penavayre
** Login   <penava_b@epitech.net>
** 
** Started on  Fri Oct 30 15:38:53 2015 bastien penavayre
** Last update Fri Dec 18 04:02:53 2015 penava_b
*/

#pragma once

#include <stddef.h>

void	*__new_push_ptor(size_t);
void	*__new_get_ptor();
void	*__new_push_tmp(void *);
void	__delete_func(void *, ...);
void	*__get_assign_addr(void *);

#define new(type, ctor, ...)						\
  (type *)(type ## _ ## ctor(type ## _type_instance->pre_ctor(__new_push_ptor(sizeof(type))), ##__VA_ARGS__), __new_get_ptor())

#define newDef(type, ...) new(type, ctor, ##__VA_ARGS__)

#define delete(obj, ...) __delete_func(obj, ##__VA_ARGS__, 0)

#define _init(type, ctor, ...)						\
  __attribute__((cleanup(type ## _ ## dtor)))				\
  =									\
    (type ## _ ## ctor							\
     (type ## _type_instance->pre_ctor					\
      (__new_push_tmp							\
       (__get_assign_addr						\
	(__builtin_frame_address(0))					\
	)								\
       ),								\
      ##__VA_ARGS__),							\
     *(type *)__new_get_ptor())
 
#define _def(type) _init(type, ctor)
