/*
** test.c for  in /home/penava_b/perso/test/Obj4
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sat Dec 12 22:12:01 2015 penava_b
** Last update Sun Jan 17 16:16:22 2016 penava_b
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "test.h"

void	new_method(FileD, close)
{
  close($.fd);
  $.opened = 0;
}

void	new_method(FileD, open, const char *name)
{
  $.fd = open(name, O_RDWR);
  if ($.fd == -1)
    return ;
  $.opened = 42;
}

int	new_const_method(FileD, read, int size, char *buff)
{
  return read($.fd, buff, size);
}

new_tor(FileD, ctor)
{
  superCtor(Object, ctor);
  $.fd = 0;
  $.opened = 0;
}

new_tor(FileD, ctorS, const char *name)
{
  superCtor(Object, ctor);
  $.opened = 0;
  M(this, open, name);
}

new_tor(FileD, dtor)
{
  if ($.opened)
    M(this, close);
  superDtor();
}

implement(FileD, Object, IClosable)
{
  push_methods(FileD, close, open, read);
}

new_tor(Debug, ctor)
{
  superCtor(Object, ctor);
  printf("Birth of %p\n", this);
}

new_tor(Debug, dtor)
{
  superDtor();
  printf("Death of %p\n", this);
}

implement(Debug, Object)
{
  // global constructor of Debug
}
