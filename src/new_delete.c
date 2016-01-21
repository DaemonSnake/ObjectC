/*
** delete_new.c for  in /home/penava_b/perso/ObjLang3/Lib
** 
** Made by bastien penavayre
** Login   <penava_b@epitech.net>
** 
** Started on  Fri Oct 30 14:40:19 2015 bastien penavayre
** Last update Wed Jan 20 18:31:39 2016 penava_b
*/

#include <stdlib.h>
#include <stdarg.h>
#include "tools/Type.h"
#include "tools/Object.h"
#include "String.h"
#include "tools/exceptions.h"

typedef struct s_node t_node;

struct		s_node
{
  void		*pointer;
  struct
  s_node	*next;
};

typedef		struct
{
  t_node	*begin;
}		List;

static __thread List	stack = {NULL};

void		*__malloc(size_t size)
{
  if ((size = (size_t)malloc(size)) == 0)
    throw(String, ctorS, "[Error] Alloction failure!");
  return (void *)size;
}

static void	*push_on_stack(const void *addr)
{
  t_node	*tmp;

  if ((tmp = malloc(sizeof(struct s_node))) == 0)
    return NULL;
  tmp->pointer = (void *)addr;
  tmp->next = stack.begin;
  if (stack.begin == NULL)
    stack.begin = tmp;
  else
    stack.begin->next = tmp;
  return tmp->pointer;
}

static void	*pop_on_stack()
{
  t_node	*save;
  void		*tmp;

  if (stack.begin == NULL)
    return NULL;
  tmp = stack.begin->pointer;
  save = stack.begin;
  stack.begin = stack.begin->next;
  free(save);
  return tmp;
}

void	*__new_push_ptor(size_t size)
{
  if (size < sizeof(Object))
    return 0;
  return push_on_stack(malloc(size));
}

void	*__new_get_ptor()
{
  return pop_on_stack();
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

void	*__new_push_tmp(const void *obj)
{
  return push_on_stack(obj);
}
