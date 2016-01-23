/*
** Object.c for  in /home/penava_b/perso/Obj/Obj4/src
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Mon Dec 21 21:47:42 2015 penava_b
** Last update Sat Jan 23 01:14:33 2016 penava_b
*/

#include "Class.h"
#include "String.h"
#include <string.h>

__attribute__((no_instrument_function))
void		Object_ctor(void *this __attribute__((unused))) {}

__attribute__((no_instrument_function))
void		Object_dtor(void *this __attribute__((unused))) {}

const char	*Object_toString(void *this __attribute__((unused)))
{
  return "default Object's toString method";
}

const Type	*Object_getType(const void *this)
{
  return ((Object *)this)->this->__class_type;
}

static struct __virtual_Object true_vtable_instance = {
  (void *)Object_dtor,
  (void *)Object_toString,
  (void *)Object_getType
};

const struct __virtual_Object * const __vtable_instance_Object = &true_vtable_instance;

__attribute__((no_instrument_function))
static void *__pre_ctor_Object(Object *this)
{
  this->this = this;
  this->_virtual = __vtable_instance_Object;
  this->__class_type = Object_type_instance;
  return this;
}

static Type	true_Object_type_instance =
  {
    "Object",
    0,
    sizeof(Object),
    sizeof(struct __virtual_Object) / sizeof(void *),
    (const char *[sizeof(struct __virtual_Object) / sizeof(void *)])
    {"dtor", "toString", "getType"},
    (void *)__pre_ctor_Object,
    (void *)Object_dtor
  };

const Type * const Object_type_instance = &true_Object_type_instance;

__attribute__((no_instrument_function))
void	__implement_function_for_Object() {}
