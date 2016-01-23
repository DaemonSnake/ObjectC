/*
** class.c for  in /home/penava_b/perso/test/Obj4
**
** Made by penava_b
** Login   <penava_b@epitech.net>
**
** Started on  Sat Dec 12 22:09:46 2015 penava_b
** Last update Sat Jan 23 05:03:17 2016 penava_b
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

void		__call_class_super_dtor(const Object * const this)
{
  if (this->_virtual == __vtable_instance_Object)
    Object_dtor(this->this);
  else
    ((const struct __private_Object * const)this)->__class_type->super->dtor(this->this);
  //THE FUCKKKK, can't call function Object_getType or valgrind complains!
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
