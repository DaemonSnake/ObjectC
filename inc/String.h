/*
** String.h for  in /home/penava_b/perso/test/Obj4/inc
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Mon Dec 14 07:40:39 2015 penava_b
** Last update Mon Jan  4 11:37:02 2016 penava_b
*/

#pragma once

#include "Class.h"

class(String, Object)
{
  char *c_str;
  unsigned long	length;
};

virtual(String)
{
  const char	*const_method(c_str);
  unsigned long	const_method(size);
  char		const_method(get, int);
  char		method(set, int, char);
  /* 
     --ToDo--
  String	const_method(copy);
  String	const_method(subStr, int, int);
  String	const_method(opEq, const char *);
  char		const_method(isEq, const char *);
  void		method(replace, const char *to, const char *whith);
  */
};

new_tor(String, ctorS, const char *);

end_decl(String);
