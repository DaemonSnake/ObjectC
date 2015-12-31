/*
** test.c for  in /home/penava_b/perso/test
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Fri Dec  4 21:57:06 2015 penava_b
** Last update Thu Dec 31 08:00:44 2015 penava_b
*/

#include <stdio.h>
#include <string.h>

typedef		struct
{
  char		*type;
}		Object;

typedef		struct
{
  char		*type;
}		String;

typedef		struct
{
  char		*type;
}		SuperS;

static __thread void	*pointer;

int		__push_tmp(void *tmp)
{
  pointer = tmp;
  return 42;
}

void		*__pop_tmp()
{
  return pointer;
}

int		type_check(void *addr, char *type)
{
  return strcmp(((Object*)addr)->type, type) == 0;
}

#define template(Type, name)				\
  else if (type_check(__pop_tmp(), #Type))		\
    for (Type *name = __pop_tmp(); name != 0; name = 0)

#define specialize(name)					\
  if (__push_tmp(name))						\
    for (const void *name = __pop_tmp(); name != 0; name = 0)	\
      if (0) {}

void		func(Object *test)
{
  specialize(test) template(SuperS, test)
    {
      printf("%p %p\n", test, &test);
    }
  template(String, test)
    {
      printf("Is String!\n");
    }
  else
    {
      printf("Is something else\n");
    }
  printf("For all %p %p\n", test, &test);
}

int		main()
{
  Object	tmp = {"SuperS"};

  func(&tmp);
  return 0;
}
