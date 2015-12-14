/*
** String.c for  in /home/penava_b/perso/test/Obj4/inc
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Mon Dec 14 07:42:19 2015 penava_b
** Last update Mon Dec 14 17:56:51 2015 penava_b
*/

#include <string.h>
#include <stdlib.h>

#include "String.h"

new_tor(String, ctor)
{
  superCtor(Object, ctor);
  $.c_str = 0;
  $.length = 0;
}

new_tor(String, ctorS, const char *str)
{
  superCtor(Object, ctor);
  $.c_str = strdup(str);
  $.length = strlen(str);
}

new_tor(String, dtor)
{
  free($.c_str);
  superDtor();
}

const char	*new_const_method(String, c_str)
{
  return $.c_str;
}

size_t		new_const_method(String, size)
{
  return $.length;
}

char		new_method(String, get, int i)
{
  if (!$.length || !$.c_str)
    return 0;
  return $.c_str[i];
}

char		new_method(String, set, int i, char newVal)
{
  char		tmp;

  if (!$.length || !$.c_str)
    return 0;
  tmp = $.c_str[i];
  $.c_str[i] = newVal;
  return tmp;
}

implement(String, Object)
{
  push_methods(String, c_str, size, get, set);
}
