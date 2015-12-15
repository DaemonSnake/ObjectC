/*
** Object.h for  in /home/penava_b/perso/Obj/Obj4/inc
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Mon Dec 14 23:43:01 2015 penava_b
** Last update Tue Dec 15 02:12:51 2015 penava_b
*/

#pragma once

#define M(var, name, ...) (var)->_virtual->name((var)->this, ##__VA_ARGS__)

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

void	__object_clean_up(void *);
