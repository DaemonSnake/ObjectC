/*
** main.c for  in /home/penava_b/perso/test/Obj4
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sat Dec 12 23:36:57 2015 penava_b
** Last update Wed Jan 13 17:18:48 2016 penava_b
*/

#include <stdio.h>

#include "test.h"
#include "String.h"
#include "yield.h"

/* 
   __attribute__((yield_func))
   would be a way to go around the initYield() issue!
   With the attribute being a custom attribute
*/
String	*yieldList(Generator *this)
{
  initYield();
  Debug	tmp _def(Debug, tmp);

  yield(new(String, ctorS, "First yield"));
  yield(new(String, ctorS, "Second yield"));
  return new(String, ctorS, "After last yield");
}

void		yieldTest()
{
  Generator	tmp _def(Generator, tmp);
  String	*str;

  printf("YIELD::\n");
  for_yield(&tmp, yieldList, str)
    {
      printf("Yield : '%s'\n", M(str, c_str));
      delete(str);
    }
  printf("Returned string '%s'\n", M(str, c_str));
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

  printf("NEW DELETE::\n");
  delete(new(String, ctorS, "Hello"));
  tmp = static_cast(Object, new(String, ctorS, "Lol"));
  tmp2 = static_cast(Object, new(FileD, ctor));
  delete(tmp, tmp2);
}

void		invoke_test(void)
{
  void		*tmp = new(String, ctorS, "Invoke print this");
  
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
  String tmp _init(String, ctorS, tmp, "Hello");

  printf("STRING TEST::\n");
  printf("%s\n", M(&tmp, c_str));
}

void		throwing()
{
  String	tmp _init(String, ctorS, tmp, "Not a leak");

  try {
    throw(String, ctorS, "Throwing");
  }
  finally {
    printf("Is going to be deleted %p of value '%s'\n", &tmp, tmp.c_str);
  }
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

void	dynamic_func(const IClosable *tmp)
{
  FileD	*tmp2 = dynamic_cast(FileD, tmp);
  Object *tmp3 = dynamic_cast(Object, tmp);

  printf("IClosable:%p\nB:%p\nObject:%p\n", tmp, tmp2, tmp3);
  printf("IClosable vtable %p\n", tmp->_virtual);
  printf("Start vtable %p\n", tmp2->_virtual);
  printf("first dynamic_func in IClosable vbtable %p\n", &tmp2->_virtual->close);
}

void	castTest()
{
  FileD tmp _def(FileD, tmp);

  printf("CAST::\n");
  printf("true:%p\n", &tmp);
  dynamic_func(static_cast(IClosable, &tmp));
  M(&tmp, open, "lol");
}

void	trace_back_test()
{
  printf("TRACEBACK::\n");
  try {
    throw(String, ctorS, "EXCEPTION!!");
  }
}

void	debug_printer(Debug *tmp)
{
  printf("Debug object %p\n", tmp);
}

void	lreferencevalue_test()
{
  printf("LEFT REFERENCE VALUE::\n");
  debug_printer(lrvalue(Debug, ctor));
}

Debug	return_instance_debug()
{
  Debug	tmp _def(Debug, tmp);

  printf("begining of returning function\n");
  printf("before return\n");
  return stdmove(tmp);
}

void	return_object_test()
{
  printf("RETURN OBJECT BY VALUE::\n");
  printf("Return object %p\n", rvalue(return_instance_debug()));
}

static Debug static_test;

_ginit(Debug, ctor, static_test);

int	main()
{
  void	(*tests[])() = {
    castTest,
    string_test,
    yieldTest,
    exceptions,
    type,
    invoke_test,
    lreferencevalue_test,
    return_object_test,
    trace_back_test
  };
  
  for (unsigned i = 0; i < sizeof(tests) / sizeof(void *); i++) {
    tests[i]();
    (i + 1) < sizeof(tests) / sizeof(tests[0]) ? printf("\n") : 0;
  }
  return 0;
}
