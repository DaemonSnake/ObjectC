/*
** String.c for  in /home/penava_b/perso/test/Obj4/inc
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Mon Dec 14 07:42:19 2015 penava_b
** Last update Tue Jan 26 22:39:44 2016 penava_b
*/

#include <string.h>
#include <stdlib.h>

#include "ObjectC/String.h"

new_tor(String, ctor)
{
  superCtor(Object, ctor);
  $.c_str = 0;
  $.length = 0;
}

new_tor(String, ctorS, const char *str)
{
  superCtor(Object, ctor);
  $.length = strlen(str);
  $.c_str = malloc($.length + 1);
  if (!$.c_str)
    return ((void)($.length = 0));
  memcpy($.c_str, str, $.length);
  $.c_str[$.length] = 0;
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

const char	*new_method(String, toString)
{
  return $.c_str;
}

implement(String, Object)
{
  //global ctor of String class
}
