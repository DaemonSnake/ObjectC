/*
** test.c for  in /home/penava_b/perso/test
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sat Dec 12 17:42:16 2015 penava_b
** Last update Mon Dec 14 07:24:58 2015 penava_b
*/

#pragma once

#include "for_each_va_args_macro.h"
#include "__object_macro_tools.h"
#include "__object_userfront_macro.h"
#include "__object_type_type.h"

typedef struct Object Object;

struct	__virtual_Object
{
  void	(*dtor)(void *);
};

struct	__data_Object
{
  const Type *__class_type;
};

struct	Object
{
  void *this;
  const struct __virtual_Object *_virtual;
  struct __data_Object;
};

void	Object_dtor(void *);
void	Object_ctor(void *);

extern const Type * const Object_type_instance;
extern const struct __virtual_Object * const __vtable_instance_Object;

void	__object_clean_up(void *);
