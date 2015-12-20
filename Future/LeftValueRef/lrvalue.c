/*
** test.c for  in /home/penava_b/perso/test
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sun Dec 13 04:16:53 2015 penava_b
** Last update Fri Dec 18 19:27:27 2015 penava_b
*/

struct	t_node
{
  void	*data;
  const void	*from;
  void	(*dtor)(void *);
  struct t_node *next;
};

typedef	struct
{
  struct t_node *begin;
}	list;

static __thread
list _list = {0};

void	*__push_front(void *data, void *node, void (*dtor)(void *))
{
  struct t_node *tmp;

  tmp = node;
  tmp->data = data;
  tmp->next = _list.begin;
  tmp->dtor = dtor;
  tmp->from = 0;
  _list.begin = tmp;
  return data;
}

void	__pop_nodes(const void *from)
{
  struct t_node *prev = 0;
  struct t_node *tmp;

  for (tmp = _list.begin; tmp != 0 && (tmp->from <= from || tmp->from == 0); )
    {
      if (prev == 0)
	{
	  _list.begin = tmp->next;
	  tmp->dtor(tmp->data);
	  tmp = _list.begin;
	  prev = 0;
	}
      else
	{
	  prev->next = prev->next->next;
	  tmp->dtor(tmp->data);
	  tmp = prev->next;
	}
    }
}

void	__cyg_profile_func_enter(void *from, void *caller)
{
  (void)from, (void)caller;
  for (struct t_node *tmp = _list.begin; tmp != 0 && tmp->from == 0; tmp = tmp->next)
    tmp->from = __builtin_frame_address(0);
}

void	__cyg_profile_func_exit(void *from, void *caller)
{
  (void)from, (void)caller;
  __pop_nodes(__builtin_frame_address(0));
}

static __thread
void	*__tmp;

void	*__set_tmp(void *arg)
{
  return (__tmp = arg);
}

void	*__get_tmp()
{
  return __tmp;
}
