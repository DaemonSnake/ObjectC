/*
** yield.h for  in /home/penava_b/perso/Obj/ObjLang3/Tools
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sat Dec  5 16:24:38 2015 penava_b
** Last update Thu Mar 24 06:35:46 2016 penava_b
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

#define for_yield(ret, Func, ...)					\
  for (Generator *this_gen = function_lrvalue(Generator, ctorF, Func); this_gen != 0; this_gen = 0) \
    for (__typeof__(Func(this_gen, ##__VA_ARGS__)) ret = Func(this_gen, ##__VA_ARGS__);	\
	 M(this_gen, __continue);					\
	 ret = (!axM(this_gen, last) ? ((__typeof__(ret)(*)(Generator *, ...))(M(this_gen, getFunc)))(this_gen) : ret))

#if defined(__LP64__) || defined(__LLP64__)

# define yield_break					\
  if (42)						\
    {							\
      M(this, __break);					\
      __cyg_profile_func_exit((void *)0, (void *)0);	\
      __asm__("leaveq");				\
      __asm__("retq");					\
    }

#else

# define yield_break					\
  if (42)						\
    {							\
      M(this, __break);					\
      __cyg_profile_func_exit((void *)0, (void *)0);	\
      __asm__("leave");					\
      __asm__("ret");					\
    }

#endif
