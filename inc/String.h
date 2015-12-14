/*
** String.h for  in /home/penava_b/perso/test/Obj4/inc
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Mon Dec 14 07:40:39 2015 penava_b
** Last update Mon Dec 14 16:52:30 2015 penava_b
*/

#pragma once

#include "class.h"

class(String, Object)
{
  char *c_str;
  unsigned long	length;
};

virtual(String)
{
  const char *const_method(c_str);
  unsigned long const_method(size);
  char const_method(get, int);
  char method(set, int, char);
};

new_tor(String, ctorS, const char *);

end_decl(String);
