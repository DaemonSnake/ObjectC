/*
** test.c for  in /home/penava_b/perso/test
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sun Dec 13 04:16:53 2015 penava_b
** Last update Sun Dec 13 05:45:34 2015 penava_b
*/

#include <stdio.h>
#include <stdlib.h>

struct	t_node
{
  void	*data;
  const void	*from;
  struct t_node *next;
};

typedef	struct
{
  struct t_node *begin;
  struct t_node *to_push;
}	list;

static list _list = {0, 0};

void	*__push_front(void *data)
{
  struct t_node *tmp;

  tmp = malloc(sizeof(struct t_node));
  tmp->data = data;
  tmp->next = _list.begin;
  tmp->from = 0;
  _list.to_push = tmp;
  return data;
}

void	__pop_nodes(const void *from)
{
  struct t_node *prev = 0;
  struct t_node *tmp;

  for (tmp = _list.begin; tmp != 0; )
    {
      if (0)
	{
	  if (prev == 0)
	    {
	      _list.begin = tmp->next;
	      free(tmp->data);
	      free(tmp);
	      tmp = _list.begin;
	      prev = 0;
	    }
	  else
	    {
	      prev->next = prev->next->next;
	      free(tmp->data);
	      free(tmp);
	      tmp = prev->next;
	    }
	}
      else
	{
	  prev = tmp;
	  tmp = tmp->next;
	}
    }
}

__attribute__((no_instrument_function))
void	__cyg_profile_func_exit(void *func, void *caller)
{
}

#define local(type) __push_front(malloc(sizeof(type)))

void	*func(int *ptr)
{
  return ptr;
}

int	main()
{
  func(local(int));
  func(local(int));
  printf("main!\n");
}
