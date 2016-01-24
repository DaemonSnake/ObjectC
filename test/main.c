/*
** main.c for  in /home/penava_b/perso/test/Obj4
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sat Dec 12 23:36:57 2015 penava_b
** Last update Sat Jan 23 21:29:04 2016 penava_b
*/

#include <stdio.h>

#include "Debug.h"
#include "String.h"
#include "yield.h"
#include "Range.h"

const char *new_method(String, toString) //Bad override
{
  (void)this;
  return 0;
}

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
  tmp = static_cast(Object, new(String, ctor));
  printf("%s\n", M(tmp, getType)->name);
  if (isInstanceOf(String, tmp))
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
  I		*tmp2;

  printf("NEW DELETE::\n");
  delete(new(String, ctorS, "Hello"));
  tmp = static_cast(Object, new(String, ctorS, "Lol"));
  tmp2 = static_cast(I, new(Debug, ctor));
  delete(tmp, tmp2);
}

void		invoke_test(void)
{
  const void   	*tmp = new(String, ctorS, "Invoke print this");
  char		*method(c_str);
  
  printf("INVOKE::\n");
  try {
    printf("%s\n", invoke(char *, tmp, "c_str"));
    printf("%s\n", invoke(char *, tmp, "lol"));
  } catch(String, exp) {
    printf("%s\n", M(exp, c_str));
  }
  if ((c_str = getMethod(tmp, "c_str")) != NULL)
    printf("Second invoke : %s\n", invokeM(c_str, tmp));
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
    try {
      printf("Does not except!\n");
    }
    finally {
      printf("Is called anyway.\n");
      throw(String, ctorS, "Throwing");
    }
  }
  finally {
    printf("Is going to be deleted %p of value '%s'\n", &tmp, M(&tmp, c_str));
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

void		dynamic_func(const I *tmp)
{
  Debug		*tmp2 = dynamic_cast(Debug, tmp);

  printf("Object:%p\nB:%p\n", tmp, tmp2);
  printf("Object vtable %p\n", tmp->_virtual);
  printf("Start vtable %p\n", tmp2->_virtual);
  M(tmp, print);
  M(tmp2, print);
}

void	castTest()
{
  Debug	tmp _def(Debug, tmp);

  printf("CAST::\n");
  printf("true:%p\n", &tmp);
  dynamic_func(static_cast(I, &tmp));
}

void	trace_back_test()
{
  printf("TRACEBACK::\n");
  try {
    throw(String, ctorS, "EXCEPTION!!");
  }
  finally {
    printf("traceback!\n");
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

void	range_test()
{
  Range	tmp _init(Range, ctorBE, tmp, 0, 10);

  printf("RANGE TEST::\n");
  for_in(i, &tmp)
    {
      printf("range value %d\n", i);
    }
}

static Debug static_test;

Ginit(Debug, ctor, static_test)
{
  // gloabal post constructor of static_test
}

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
    range_test,
    trace_back_test
  };

  for (unsigned i = 0; i < sizeof(tests) / sizeof(void *); i++) {
    tests[i]();
    (i + 1) < sizeof(tests) / sizeof(tests[0]) ? printf("\n") : 0;
  }
  return 0;
}
