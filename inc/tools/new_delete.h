/*
** delete_new.h for  in /home/penava_b/perso/ObjLang3/Lib
** 
** Made by bastien penavayre
** Login   <penava_b@epitech.net>
** 
** Started on  Fri Oct 30 15:38:53 2015 bastien penavayre
** Last update Tue Dec 15 02:27:12 2015 penava_b
*/

#pragma once

#include <stddef.h>

void	*__new_push_ptor(size_t);
void	*__new_get_ptor();
void	__delete_func(void *, ...);

#define __init__(type, var, ctorName, ...) (type ## _ ## ctorName(type ## _type_instance->pre_ctor(var), ##__VA_ARGS__))

#define new(type, ctor, ...)						\
  (type *)(type ## _ ## ctor(type ## _type_instance->pre_ctor(__new_push_ptor(sizeof(type))), ##__VA_ARGS__), __new_get_ptor())

#define newDef(type, ...) new(type, ctor, ##__VA_ARGS__)

#define delete(obj, ...) __delete_func(obj, ##__VA_ARGS__, 0)

#define local __attribute__((cleanup(__object_clean_up)))
