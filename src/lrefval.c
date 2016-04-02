/*
** test.c for  in /home/penava_b/perso/test
**
** Made by penava_b
** Login   <penava_b@epitech.net>
**
** Started on  Wed Dec 30 03:47:42 2015 penava_b
** Last update Thu Mar 31 14:11:10 2016 penava_b
*/

#include <stdio.h>

/*-----------------------linked list-------------------------------*/

struct		s_node
{
  void		*data;
  void		(*dtor)(void *);
  char		toclean;
  int	       	level;
  struct s_node	*next;
  void		*id;
};

static __thread
struct
{
  int			level;
  void			(*return_dtor)(void *);
  struct s_node		*front;
  void			*new_id;
  struct s_node		*to_update;
  struct s_node		*to_update_next;
}			__stack_list = {0, 0, 0, 0, 0, 0};

void		__except_clean_exit_func(int);

long		__get_front_node_diff(const char *rbp)
{
  if (__stack_list.front == 0)
    return -1;
  return (void *)rbp - (void *)__stack_list.front;
}

static
void		__enter_new_func()
{
  __stack_list.level++;
}

int		__get_current_level()
{
  return __stack_list.level;
}

void		__protect_kill_stack(void *id)
{
  __stack_list.new_id = id;
  for (struct s_node *node = __stack_list.front; node != 0 && node->level == __stack_list.level; node = node->next)
    if (node->id == id)
      {
	__stack_list.to_update = node;
	__stack_list.to_update_next = node->next;
	node->dtor(node->data);
	break ;
      }
}

void		*__push_var(struct s_node *new_node)
{
  if (new_node == __stack_list.to_update)
    {
      new_node->next = __stack_list.to_update_next;
      __stack_list.to_update = 0;
      __stack_list.to_update_next = 0;
    }
  else
    {
      new_node->next = __stack_list.front;
      __stack_list.front = new_node;
    }
  new_node->id = __stack_list.new_id;
  return new_node->data;
}

void		__push_back_on_stack(struct s_node *front, int level)
{
  struct s_node	*node;
  int		start_level = front->level;
  
  for (node = front; node != 0 && node->level == start_level; node = node->next)
    {
      node->level = level;
      __push_var(node);
    }
}

void		*__get_front_var_list()
{
  if (__stack_list.front == 0)
    return 0;
  return __stack_list.front->data;
}

void		__exit_end_func(int level)
{
  struct s_node	*front = __stack_list.front;
  struct s_node *node = 0;

  for (node = __stack_list.front; node != 0 && node->level >= level; node = node->next)
    __stack_list.front = node->next;
  for (node = front; node != 0 && node != __stack_list.front; node = node->next)
    if (node->dtor != 0 && node->toclean != 0)
      node->dtor(node->data);
  __except_clean_exit_func(level);
  __stack_list.level = level - 1;
}

void		__prevent_clean_up()
{
  for (struct s_node *node = __stack_list.front; node != 0 && node->level == __stack_list.level; node = node->next)
    node->toclean = 0;
}

void		__reset_clean_up()
{
  for (struct s_node *node = __stack_list.front; node != 0 && node->level == __stack_list.level; node = node->next)
    node->toclean = 42;
}

void		__delayed_level_encrementation()
{
  if (__stack_list.front == 0 || __stack_list.level == 0)
    return ;
  __stack_list.front->level++;
}

void		*__prevent_clean_up_var(void *arg)
{
  struct
    s_node	*node;

  for (node = __stack_list.front;
       node != 0 && node->data > arg; node = node->next);
  if (node != 0 && node->data == arg)
    {
      __stack_list.return_dtor = node->dtor;
      node->dtor = 0;
    }
  return arg;
}

void		(*__get_return_dtor())(void *)
{
  return __stack_list.return_dtor;
}

__attribute__((destructor))
static inline
void		__clean_for_exit()
{
  __exit_end_func(-1);
}

/*-----------------------instrument functions-------------------------------*/

void	__cyg_profile_func_enter(void *func, void *from)
{
  (void)func, (void)from;
  __enter_new_func();
}

void	__cyg_profile_func_exit(void *func, void *from)
{
  (void)func, (void)from;
  __exit_end_func(__stack_list.level);
}
