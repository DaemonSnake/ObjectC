/*
** class.c for  in /home/penava_b/perso/test/Obj4
**
** Made by penava_b
** Login   <penava_b@epitech.net>
**
** Started on  Sat Dec 12 22:09:46 2015 penava_b
** Last update Sun Mar 27 08:32:33 2016 penava_b
*/

#include "ObjectC/Class.h"
#include "ObjectC/String.h"
#include <string.h>


static
__thread void	*__tmp_pointer_for_ifIs__ = 0;

void		*__tmp_pointer__(void *new_val)
{
  if (new_val == 0)
    return (void *)0;
  if (new_val != (void *)0x42)
    __tmp_pointer_for_ifIs__ = new_val;
  return __tmp_pointer_for_ifIs__;
}

void     	*__dynamic_cast(const Type *my, const Type *their, void *obj)
{
  const Type   	*tmp;
  unsigned	i;
  
  for (tmp = my; tmp != 0; tmp = tmp->super)
    {
      if (tmp == their)
	return obj;
      else if (tmp->nbImplements && tmp->implements && tmp->offsets)
	for (i = 0; i < tmp->nbImplements; i++)
	  if (tmp->implements[i] == their)
	    return ((char *)obj) + tmp->offsets[i];
    }
  return (void *)0;
}

char		__is_same_kind_type(const Type * my, const Type *their)
{
  return (__dynamic_cast(my, their, (void *)0x42) ? 42 : 0);
}

void		__call_class_super_dtor(Object * const this)
{
  const Type	*super;

  super = ((struct __private_Object * const)this)->__class_type->super;
  if (super == 0)
    return ;
  ((struct __private_Object * const)this)->__class_type = super;
  super->dtor(this);
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
