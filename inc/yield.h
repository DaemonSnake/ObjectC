/*
** yield.h for  in /home/penava_b/perso/Obj/ObjLang3/Tools
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sat Dec  5 16:24:38 2015 penava_b
** Last update Tue Jan  5 12:54:18 2016 penava_b
*/

#pragma once

#include <alloca.h>
#include "Generator.h"

void    	__yield_editRet();
void            __prevent_clean_up();
void		__reset_clean_up();

#define initYield()						\
  if (this != NULL && this->label != NULL)			\
    {								\
      __yield_editRet();					\
      goto *this->label;					\
    }								\
  else								\
    {								\
      if (this != NULL)						\
	{							\
	  this->alive = 0;					\
	  this->init = 42;					\
	}							\
    }

#define yield(val)							\
  if (M(this, __setjmp) == 0)						\
    {									\
      if (this->init)							\
	{								\
	  M(this, saveStack, alloca(0), __builtin_frame_address(0));	\
	  this->alive = 42;						\
	}								\
      __prevent_clean_up();						\
      return val;							\
    }									\
  else									\
    {									\
      if (this != NULL)							\
	{								\
	  M(this, restore, alloca(0));					\
	  __reset_clean_up();						\
	  this->alive = 0;						\
	}								\
    }

#define for_yield(x, Func, ret, ...)					\
  for (ret = Func(M(x, reset, Func), ##__VA_ARGS__);			\
       M(x, __continue);						\
       ret = ((__typeof__(ret)(*)(Generator *,...))(((Generator *)x)->func))(x))

#define yield_interupt(x) if ((M(x, clean), 42))
