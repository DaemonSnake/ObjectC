/*
** Object.h for  in /home/penava_b/perso/Obj/Obj4/inc
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Mon Dec 14 23:43:01 2015 penava_b
** Last update Thu May 12 22:51:19 2016 penava_b
*/

#pragma once

#define M(var, name, ...)						\
    ({ __typeof__(var) __save__ = var;                                  \
        var->_virtual->name(__save__->this, ##__VA_ARGS__);             \
    })

typedef struct Object Object;

struct	__virtual_Object
{
  void	(*dtor)(void *);
  const char *(*toString)(const void *);
  const Type *(*getType)(const void *);
};

struct __interfaces_for_Object
{
};

struct	__data_weak_Object
{
  const Type *__class_type;
};

struct	__data_Object
{
  Object *this_Object;
  char	__private_Object[sizeof(struct __data_weak_Object)];
};

struct	__private_Object
{
  Object *this;
  const struct __virtual_Object *_virtual;
  Object *this_Object;
  struct __data_weak_Object;
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

void	*__pre_ctor_Object(struct __private_Object *);
