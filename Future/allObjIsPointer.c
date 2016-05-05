/*
** test.c for  in /home/penava_b/perso/test
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Thu Jan 28 14:08:29 2016 penava_b
** Last update Fri Apr 22 16:00:05 2016 penava_b
*/

#include <stdio.h>

#define _init(type, name, ...)						\
  = (type ## _ ## name(push_var((struct type[1]){0}), ##__VA_ARGS__), (type)get_var())

#define local_loop_safe(type, name, ...)	\
  = (type ## _ ## name(push_var(alloca(sizeof(struct type))), ##__VA_ARGS__), (type)get_var())

typedef struct String *String;
typedef struct String const *const(String);
struct String
{
  const char *c_str;
  void	(*print)(const(String));
};

__thread void *__data__ = 0;

void	*push_var(void *arg)
{
  __data__ = arg;
  return arg;
}

void	*get_var()
{
  return __data__;
}

void	String_print(const(String) this)
{
  printf("%s\n", this->c_str);
}

void	String_ctor(String this, const char *str)
{
  this->c_str = str;
  this->print = String_print;
}

int	main()
{
  const(String) tmp _init(String, ctor, "Hello"); // stack
  String	tmp2 _init(String, ctor, "Yolo"); // stack
  String	tmp3 = new(String, ctor, "Yia"); // heap

  tmp->print(tmp);
  tmp2->print(tmp2);
}
