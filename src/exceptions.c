/*
** test.c for  in /home/penava_b/perso/test
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Thu Nov 26 18:54:58 2015 penava_b
** Last update Fri Dec 18 19:16:45 2015 penava_b
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include <stdarg.h>
#include "tools/Type.h"
#include "tools/Object.h"

void		__delete_func(void *, ...);

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
  int	       	status;
  jmp_buf      	buff;
  char		catchTool;
  const Type   	*type;
  Object 	*obj;
  info_node    	*origin;
  void		*rbp_try;
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
  exit(42);
}

void		__except_throw_func(const Type *type, Object *obj, const char *file, const char *func, int line)
{
  info_node	*node;

  while (list != NULL && list->status == 3)
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
      exit(42);
    }
  list->status = 2;
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
  longjmp(list->buff, -1);
}

int    		__except_dispatcher(const char *file, const char *func, int line)
{
  if (list->status == 0)
    {
      list->status = 1;
      return 42;
    }
  if (list->status == 2)
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

void   		__except_initializer(List *node)
{
  List 		*tmp = node;

  tmp->type = NULL;
  tmp->next = list;
  tmp->status = 0;
  tmp->type = NULL;
  tmp->obj = NULL;
  tmp->origin = NULL;
  tmp->catchTool = 0;
  tmp->rbp_try = __builtin_frame_address(0);
  list = tmp;
}

int    		__except_catch_func(const Type *type)
{
  if (list == NULL)
    exit(fprintf(stderr, "[Exception Module] LOL, Wat u fink U R dooing?\n"));
  if (__is_same_kind_type(type, list->type))
    {
      list->status = 3;
      return 42;
    }
  return 0;
}

void		*__except_get_data()
{
  if (list == NULL || list->status != 3)
    exit(fprintf(stderr, "[Exception Module] LOL, Wat u fink U R dooing?\n"));
  return list->obj;
}

void	       	*__except_get_front()
{
  return &list->buff;
}

char		__except_get_catch_tool()
{
  if (list == NULL)
    return 0;
  return (list->catchTool ^= 1);
}
