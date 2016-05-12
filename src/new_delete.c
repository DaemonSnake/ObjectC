/*
** delete_new.c for  in /home/penava_b/perso/ObjLang3/Lib
** 
** Made by bastien penavayre
** Login   <penava_b@epitech.net>
** 
** Started on  Fri Oct 30 14:40:19 2015 bastien penavayre
** Last update Thu May 12 22:41:49 2016 penava_b
*/

#include <stdlib.h>
#include <stdarg.h>
#include "ObjectC/tools/Type.h"
#include "ObjectC/tools/Object.h"
#include "ObjectC/String.h"
#include "ObjectC/tools/exceptions.h"

void		*__malloc(size_t size)
{
  if ((size = (size_t)malloc(size)) == 0)
    throw(String, ctorS, "[Error] Alloction failure!");
  return (void *)size;
}

static void	__delete__(const void *obj)
{
  void		(*dtor)(void *);
  Object	*tmp;

  if (obj == 0)
    return ;
  tmp = (void *)obj;
  tmp = tmp->this;
  dtor = tmp->_virtual->dtor;
  dtor(tmp);
  free(tmp);
}

void	__delete_func(const void *obj, ...)
{
  va_list ap;

  __delete__(obj);
  va_start(ap, obj);
  while ((obj = va_arg(ap, void *)) != 0)
    __delete__(obj);
  va_end(ap);
}
