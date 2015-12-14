/*
** main.c for  in /home/penava_b/perso/test/Obj4
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sat Dec 12 23:36:57 2015 penava_b
** Last update Mon Dec 14 17:41:48 2015 penava_b
*/

#include "test.h"
#include "String.h"
#include <stdio.h>

void	string_test()
{
  local String tmp;

  __init__(String, &tmp, ctorS, "Hello");
  printf("%s\n", M(&tmp, c_str));
}

void	func(const IClosable *tmp)
{
  FileD	*tmp2 = dynamic_cast(FileD, tmp);
  Object *tmp3 = dynamic_cast(Object, tmp);

  printf("IClosable:%p\nB:%p\nObject:%p\n", tmp, tmp2, tmp3);
  printf("\n");
  printf("IClosable vtable %p\n", tmp->_virtual);
  printf("Start vtable %p\n", tmp2->_virtual);
  printf("first func in IClosable vbtable %p\n", &tmp2->_virtual->close);
}

int	main()
{
  local FileD tmp;

  __init__(FileD, &tmp, ctor);
  printf("true:%p\n", &tmp);
  func(static_cast(IClosable, &tmp));
  M(&tmp, open, "lol");
  string_test();
}
