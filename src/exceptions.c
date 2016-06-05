/*
 * Copyright (C) 2016  Bastien Penavayre
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include <stdarg.h>
#include "ObjectC/tools/Type.h"
#include "ObjectC/tools/Object.h"

void		__delete_func(void *, ...);
int             __get_current_level();
void            __exit_end_func(int);
void		__enter_try_block();
void		__exit_try_block();

enum
  {
    BEFORE_TRY = 0,
    IN_TRY = 1,
    IN_FINALLY = 2,
    END = 3
  };

enum
  {
    NOT_THROWN = 0,
    UNCAUGHT = 1,
    CAUGHT = 2
  };

typedef struct 	s_info_node
{
  const char	*file;
  const char	*func;
  int		line;
  struct s_info_node *next;
}		info_node;

typedef struct s_node List;

struct	       	s_node
{
  char	       	status;
  char		caught;
  jmp_buf      	buff;
  const Type   	*type;
  Object 	*obj;
  info_node    	*origin;
  int		level;
  List	       	*next;
};

static List    	*list = NULL;

static void	clean_node(List *node)
{
  info_node	*save;
  info_node	*save2;

  save = node->origin;
  node->origin = NULL;
  while (save != NULL)
    {
      save2 = save;
      save = save->next;
      free(save2);
    }
  if (node->obj != NULL)
    __delete_func(node->obj, 0, 0);
  node->obj = NULL;
}

static void    	pop_current()
{
  List		*tmp;

  tmp = list;
  list = list->next;
  clean_node(tmp);
}

static void    	trace_back(const char *file, const char *func, int line)
{
  info_node	*tmp;

  fprintf(stderr, "!!! TRACE_BACK !!!\n");
  fprintf(stderr, "\tDispatched in file '%s' in function '%s' at line '%d'\n",
	  file, func, line);
  for (tmp = list->origin; tmp != NULL; tmp = tmp->next)
    if (tmp->next != NULL)
      fprintf(stderr, "\tDispatched in file '%s' in function '%s' at line '%d'\n",
	      tmp->file, tmp->func, tmp->line);
    else
      fprintf(stderr, "\tComming from file '%s' in function '%s' at line '%d'\n",
	      tmp->file, tmp->func, tmp->line);
  fprintf(stderr, "Uncaught exception: (%s): '%s'\n", list->type->name, M(list->obj, toString));
  pop_current();
  __exit_end_func(-1);
  exit(42);
}

void		__except_throw_func(const Type *type, Object *obj, const char *file, const char *func, int line)
{
  info_node	*node;

  while (list != NULL && (list->caught == CAUGHT || list->status >= IN_FINALLY))
    {
      if (list->next == NULL)
	trace_back(file, func, line);
      if (list->obj == obj)
	list->obj = NULL;
      pop_current();
    }
  if (list == NULL)
    {
      fprintf(stderr, "Uncaught exception: in file '%s' in func '%s' at line '%d'\n\
(%s): '%s'\n", file, func, line, type->name, M(obj, toString));
      __delete_func(obj, 0, 0);
      __exit_end_func(-1);
      exit(42);
    }
  list->caught = UNCAUGHT;
  list->type = type;
  list->obj = obj;
  if ((node = malloc(sizeof(info_node))) != NULL)
    {
      node->file = file;
      node->func = func;
      node->line = line;
      node->next = list->origin;
      list->origin = node;
    }
  __exit_end_func(list->level);
  longjmp(list->buff, -1);
}

void		__except_clean_exit_func(int level)
{
  while (list != NULL && list->level - 1 == level)
    pop_current();
}

int    		__except_dispatcher(const char *file, const char *func, int line)
{
  if (list->status == BEFORE_TRY)
    return 42;
  if (list->caught == UNCAUGHT)
    {
      if (list->next == NULL)
	trace_back(file, func, line);
      clean_node(list->next);
      list->next->type = list->type;
      list->next->obj = list->obj;
      list->next->origin = list->origin;
      list->origin = NULL;
      list->obj = NULL;
      pop_current();
      __except_throw_func(list->type, list->obj, file, func, line);
    }
  pop_current();
  return 0;
}

int		__except_try_n_finally()
{
  if (++list->status < END)
    return 42;
  return 0;
}

int		__except_is_try()
{
  return list->status == IN_TRY;
}

void   		__except_initializer(List *node)
{
  node->type = NULL;
  node->next = list;
  node->status = BEFORE_TRY;
  node->caught = NOT_THROWN;
  node->type = NULL;
  node->obj = NULL;
  node->origin = NULL;
  node->level = __get_current_level() + 1;
  list = node;
}

int    		__except_catch_func(const Type *type)
{
  if (list == NULL)
    {
      __exit_end_func(-1);
      exit(fprintf(stderr, "[Exception Module] LOL, Wat u fink U R dooing?\n"));
    }
  if (__is_same_kind_type(type, list->type))
    {
      list->caught = CAUGHT;
      return 42;
    }
  return 0;
}

void		*__except_get_data()
{
  if (list == NULL || list->caught != CAUGHT)
    {
      __exit_end_func(-1);
      exit(fprintf(stderr, "[Exception Module] LOL, Wat u fink U R dooing?\n"));
    }
  return list->obj;
}

void	       	*__except_get_front()
{
  return &list->buff;
}
