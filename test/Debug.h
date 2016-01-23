/*
** test.h for  in /home/penava_b/perso/test/Obj4
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sat Dec 12 22:16:21 2015 penava_b
** Last update Sat Jan 23 18:48:41 2016 penava_b
*/

#pragma once

#include "String.h"

interface(I)
{
  void	method(print);
};

class(Debug, Object, I)
{
  int	var;
};

virtual(Debug)
{
  axors(int, var, get);
};

end_decl(Debug);
