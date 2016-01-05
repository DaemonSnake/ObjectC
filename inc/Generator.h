/*
** Generator.h for  in /home/penava_b/perso/Obj/ObjLang3/Tools
**
** Made by penava_b
** Login   <penava_b@epitech.net>
**
** Started on  Sat Dec  5 15:43:48 2015 penava_b
** Last update Tue Jan  5 13:08:18 2016 penava_b
*/

#pragma once

#include "Class.h"

class(Generator, Object)
{
  void		*label;
  char		*stack;
  void		*func;
  long		stack_node;
  char		alive;
  char		init;
  unsigned long	size;
};

virtual(Generator)
{
  void		method(restore, const char *);
  void		method(saveStack, const char *, const char *);
  int		method(__setjmp);
  char		method(__continue);
  Generator	*method(reset, void *);
  void		method(clean);
};

end_decl(Generator);
