/*
** Exceptions.c for  in /home/penava_b/perso/Obj/Obj4/src/std
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Thu Jan 28 16:00:29 2016 penava_b
** Last update Thu Jan 28 16:34:41 2016 penava_b
*/

#include <string.h>
#include <stdlib.h>
#include "ObjectC/Exceptions.h"

const char	*new_method(Exception, what)
{
  return $.msg;
}

new_tor(Exception, ctor)
{
  superCtor(Object, ctor);
}

new_tor(Exception, ctorS, const char *str)
{
  superCtor(Object, ctor);
  if (str)
    {
      size_t	size;
	
      size = strlen(str);
      $.msg = malloc(size + 1);
      memcpy((void *)$.msg, str, size);
    }
  else
    $.msg = 0;
}

new_tor(Exception, dtor)
{
  free((void *)$.msg);
  superDtor();
}

new_tor(AllocFailed, ctor)
{
  superCtor(Exception, ctorS, "AllocFailed");
}

new_tor(AllocFailed, dtor)
{
  superDtor();
}

new_tor(IsNotObject, ctor)
{
  superCtor(Exception, ctorS, "IsNotObject");
}

new_tor(IsNotObject, dtor)
{
  superDtor();
}
		     
implement(Exception, Object) {}
implement(AllocFailed, Exception) {}
implement(IsNotObject, Exception) {}
