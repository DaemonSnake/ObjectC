/*
** Range.h for  in /home/penava_b/perso/Obj/Obj4/test
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sat Jan 23 18:48:43 2016 penava_b
** Last update Mon Jan 25 17:29:01 2016 penava_b
*/

#pragma once

#include "yield.h"
#include "Generator.h"


#define for_in(name, gen)						\
  for (typeof((gen)->_virtual->operator_function_void(gen)) name =	\
	 (M(gen, reset, (gen)->_virtual->operator_function_void),	\
	  M(gen, operator_function_void));				\
       M(gen, __continue); name = M(gen, operator_function_void))

class(Range, Generator)
{
  int	b, e;
};

virtual(Range)
{
  int	const_method(operator_function_void);
};

new_tor(Range, ctorBE, int, int);

end_decl(Range);
