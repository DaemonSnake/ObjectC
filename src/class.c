/*
** class.c for  in /home/penava_b/perso/test/Obj4
**
** Made by penava_b
** Login   <penava_b@epitech.net>
**
** Started on  Sat Dec 12 22:09:46 2015 penava_b
** Last update Tue Dec 15 02:18:02 2015 penava_b
*/

#include "Class.h"
#include "String.h"
#include <string.h>

char		__is_same_kind_type(const Type * my, const Type *their)
{
  const Type   	*tmp;

  for (tmp = my; tmp != 0; tmp = tmp->super)
    if (tmp == their)
      return 42;
  return 0;
}

void		Object_ctor(void *this __attribute__((unused))) {}
void		Object_dtor(void *this __attribute__((unused))) {}

const char	*Object_toString(void *this __attribute__((unused)))
{
  return "default Object's toString method";
}

const Type	*Object_getType(const Object *this)
{
  return $.__class_type;
}

static struct __virtual_Object true_vtable_instance = {
  (void *)Object_dtor,
  (void *)Object_toString,
  (void *)Object_getType
};

const struct __virtual_Object * const __vtable_instance_Object = &true_vtable_instance;

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

void	__implement_function_for_Object() {}

void	__object_clean_up(void *arg)
{
  ((Object *)arg)->_virtual->dtor(arg);
}

const void     	*__typeGetMethod(const Type * const type,
				 const void * const * const vtable,
				 const char * const name)
{
  for (unsigned i = 0; i < type->nbMethods; i++)
    {
      if (type->methodsName[i] != 0 && strcmp(name, type->methodsName[i]) == 0)
	{
	  if (vtable[i] == 0)
	    throw(String, ctorS, "BadInvode: Not implemented");
	  return vtable[i];
	}
    }
  throw(String, ctorS, "BadInvoke : No such method");
  return (void *)0;
}
