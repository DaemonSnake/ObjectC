/*
** Exceptions.h for  in /home/penava_b/perso/Obj/Obj4/src/std
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Thu Jan 28 15:55:07 2016 penava_b
** Last update Thu Jan 28 16:32:38 2016 penava_b
*/

#include "ObjectC/Class.h"

class(Exception, Object)
{
  const char *msg;
};

virtual(Exception)
{
  const char *const_method(what);
};

new_tor(Exception, ctorS, const char *);

end_decl(Exception);

class(AllocFailed, Exception) {};
virtual(AllocFailed) {};

class(IsNotObject, Exception) {};
virtual(IsNotObject) {};

end_decl(AllocFailed, IsNotObject);
