/*
** test.c for  in /home/penava_b/perso/test
**
** Made by penava_b
** Login   <penava_b@epitech.net>
**
** Started on  Wed Dec 30 03:47:42 2015 penava_b
** Last update Mon Jan  4 10:36:54 2016 penava_b
*/

#include <stdio.h>

/*-----------------------linked list-------------------------------*/

static __thread
struct
{
  int		level;
  void		(*return_dtor)(void *);
  struct	s_node
  {
    void	*data;
    void	(*dtor)(void *);
    int		level;
    struct
    s_node	*next;
  }		*begin;
}	        __stack_list = {0, 0, 0};

void		__new_func()
{
  __stack_list.level++;
}

int		__get_current_level()
{
  return __stack_list.level;
}

void		*__push_var(struct s_node *new_node)
{
  new_node->next = __stack_list.begin;
  __stack_list.begin = new_node;
  return new_node->data;
}

void		*__get_front()
{
  if (__stack_list.begin == 0)
    return 0;
  return __stack_list.begin->data;
}

void		__end_func(int level)
{
  struct s_node	*begin = __stack_list.begin;
  struct s_node *node = 0;
  
  for (node = __stack_list.begin; node != 0 && node->level >= level; node = node->next)
    __stack_list.begin = node->next;
  for (node = begin; node != 0 && node != __stack_list.begin; node = node->next)
    if (node->dtor != 0)
      node->dtor(node->data);
  __stack_list.level = level - 1;
}

void		__prevent_clean_up()
{
  for (struct s_node *node = __stack_list.begin; node != 0 && node->level == __stack_list.level; node = node->next)
    node->dtor = 0;
}

void		__delayed_level_encrementation()
{
  if (__stack_list.begin == 0)
    return ;
  __stack_list.begin->level++;
}

void		*__prevent_clean_up_var(void *arg)
{
  struct
    s_node	*node;

  for (node = __stack_list.begin;
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
  __end_func(-1);
}

/*-----------------------instrument functions-------------------------------*/

void	__cyg_profile_func_enter(void *func, void *from)
{
  (void)func, (void)from;
  __new_func();
}

void	__cyg_profile_func_exit(void *func, void *from)
{
  (void)func, (void)from;
  __end_func(__stack_list.level);
}
