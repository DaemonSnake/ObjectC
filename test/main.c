/*
** main.c for  in /home/penava_b/perso/test/Obj4
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sat Dec 12 23:36:57 2015 penava_b
** Last update Fri Dec 18 03:46:31 2015 penava_b
*/

#include <stdio.h>

#include "test.h"
#include "String.h"
#include "yield.h"

String	*yieldList(Generator *this)
{
  initYield();
  yield(new(String, ctorS, "First yield"));
  yield(new(String, ctorS, "Second yield"));
  return new(String, ctorS, "After last yield");
}

void		yieldTest()
{
  Generator tmp _def(Generator);
  String	*str;

  printf("YIELD::\n");
  for_yield(&tmp, yieldList, str)
    {
      printf("Yield : '%s'\n", M(str, c_str));
      delete(str);
    }
  printf("Returned string %s\n", M(str, c_str));
  delete(str);  
}

void		type(void)
{
  Object	*tmp;

  printf("TYPE::\n");
  tmp = static_cast(Object, new(FileD, ctor));
  printf("%s\n", M(tmp, getType)->name);
  if (isInstanceOf(Object, tmp))
    printf("Is a String\n");
  delete(tmp);
  tmp = new(Object, ctor);
  if (isInstanceOf(String, tmp))
    printf("Will not work!\n");
  delete(tmp);
}

void		new_delete(void)
{
  Object	*tmp;
  Object	*tmp2;

  delete(new(String, ctorS, "Hello"));
  tmp = static_cast(Object, new(String, ctorS, "Lol"));
  tmp2 = static_cast(Object, new(FileD, ctor));
  delete(tmp, tmp2);
}

void		invoke_test(void)
{
  void       	*tmp;

  tmp = new(String, ctorS, "Invoke print this");
  printf("INVOKE::\n");
  try {
    printf("%s\n", invoke(char *, tmp, "c_str"));
    printf("%s\n", invoke(char *, tmp, "lol"));
  } catch(String, exp) {
    printf("%s\n", M(exp, c_str));
  }
  delete(tmp);
}

void	string_test()
{
  String tmp _init(String, ctorS, "Hello");

  printf("%s\n", M(&tmp, c_str));
}

void		throwing()
{
  throw(String, ctorS, "Throwing");
}

void		exceptions()
{
  printf("EXCEPTIONS::\n");
  try {
    throwing();
  } catch(String, tmp) {
    printf("Exception return : %s\n", M(tmp, c_str));
  }
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
  FileD tmp _def(FileD);

  printf("true:%p\n", &tmp);
  func(static_cast(IClosable, &tmp));
  M(&tmp, open, "lol");
  string_test();
  yieldTest();
  exceptions();
  type();
  invoke_test();
  try {
    throw(String, ctorS, "EXCEPTION!!");
  }
  return 0;
}
