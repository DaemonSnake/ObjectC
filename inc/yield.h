/*
** yield.h for  in /home/penava_b/perso/Obj/ObjLang3/Tools
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sat Dec  5 16:24:38 2015 penava_b
** Last update Mon Jan 18 16:31:19 2016 penava_b
*/

#pragma once

#include <alloca.h>
#include "Generator.h"

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

#define for_yield(x, Func, ret, ...)					\
  for (M(x, reset, Func), ret = Func(x, ##__VA_ARGS__);			\
       M(x, __continue);						\
       ret = ((__typeof__(ret)(*)(Generator *,...))(M(x, getFunc)))(x))

#define yield_interupt(x) if ((M(x, clean), 42))
