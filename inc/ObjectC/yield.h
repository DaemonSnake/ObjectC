/*
** yield.h for  in /home/penava_b/perso/Obj/ObjLang3/Tools
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sat Dec  5 16:24:38 2015 penava_b
** Last update Wed Mar 23 06:07:55 2016 penava_b
*/

#pragma once

#include <alloca.h>
#include "ObjectC/Generator.h"

void    	__yield_editRet();
void            __prevent_clean_up();
void		__reset_clean_up();

#define initYield()						\
  if (this != NULL && M(this, isLabelOk))			\
    {								\
      __yield_editRet();					\
      goto *M(this, getLabel);					\
    }								\
  else								\
    {								\
      if (this != NULL)						\
	M(this, beforeYield);					\
    }

#define yield(val)							\
  if (this != NULL && M(this, __setjmp) == 0)				\
    {									\
      if (M(this, isInitialized))					\
	M(this, saveStack, alloca(0), __builtin_frame_address(0));	\
      __prevent_clean_up();						\
      return val;							\
    }									\
  else									\
    {									\
      if (this != NULL)							\
	{								\
	  M(this, restore, __builtin_frame_address(0));			\
	  __reset_clean_up();						\
	}								\
    }

#define for_yield(Func, ret, ...)					\
  for (Generator *this_gen = function_lrvalue(Generator, ctorF, Func); this_gen != 0; this_gen = 0) \
    for (__typeof__(Func(this_gen, ##__VA_ARGS__)) ret = Func(this_gen, ##__VA_ARGS__);	\
	 M(this_gen, __continue);					\
	 ret = (!axM(this_gen, last) ? ((__typeof__(ret)(*)(Generator *, ...))(M(this_gen, getFunc)))(this_gen) : ret))
