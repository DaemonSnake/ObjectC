/*
** Object.h for  in /home/penava_b/perso/Obj/Obj4/inc
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Mon Dec 14 23:43:01 2015 penava_b
** Last update Mon Dec 21 21:51:36 2015 penava_b
*/

#pragma once

#define M(var, name, ...)						\
  ((typeof(var))__new_push_tmp(var))->_virtual->name			\
  (((typeof(var))__new_get_ptor())->this, ##__VA_ARGS__)

void	*__new_push_tmp(void *);
void	*__new_get_ptor();

typedef struct Object Object;

struct	__virtual_Object
{
  void	(*dtor)(void *);
  const char *(*toString)(const void *);
  const Type *(*getType)(const void *);
};

struct	__data_Object
{
  const Type *__class_type;
};

struct	Object
{
  Object *this;
  const struct __virtual_Object *_virtual;
  struct __data_Object;
};

void	Object_dtor(void *);
void	Object_ctor(void *);

extern const Type * const Object_type_instance;
extern const struct __virtual_Object * const __vtable_instance_Object;
