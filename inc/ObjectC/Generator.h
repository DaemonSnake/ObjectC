/*
** Generator.h for  in /home/penava_b/perso/Obj/ObjLang3/Tools
**
** Made by penava_b
** Login   <penava_b@epitech.net>
**
** Started on  Sat Dec  5 15:43:48 2015 penava_b
** Last update Thu Mar 24 06:02:13 2016 penava_b
*/

#pragma once

#include "ObjectC/Class.h"

class(Generator, Object)
{
  void		*label;
  char		*stack;
  void		*func;
  long		stack_node;
  char		alive;
  char		init;
  char		last;
  unsigned long	size;
};

virtual(Generator)
{
  void		method(restore, const char *);
  void		method(saveStack, const char *, const char *);
  void		method(reset, void *);
  void		method(clean);
  void		method(beforeYield);
  char		method(isInitialized);
  
  void		*const_method(getFunc);
  char	        const_method(isLabelOk);
  void		*const_method(getLabel);

  int		method(__setjmp);
  char		method(__continue);
  void		method(__break);

  axors(char, last, get);
};

new_tor(Generator, ctorF, void *);

end_decl(Generator);
