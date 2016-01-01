/*
** test.c for  in /home/penava_b/perso/test
**
** Made by penava_b
** Login   <penava_b@epitech.net>
**
** Started on  Wed Dec 30 03:47:42 2015 penava_b
** Last update Fri Jan  1 10:16:32 2016 penava_b
*/

#include <stdio.h>

/*-----------------------linked list-------------------------------*/

static __thread
struct
{
  int		level;
  struct	s_node
  {
    void	*data;
    void	(*dtor)(void *);
    int		level;
    struct
    s_node	*next;
  }		*begin;
}	        __stack_list = {0, 0};

__attribute__((no_instrument_function))
void		__new_func()
{
  __stack_list.level++;
}

__attribute__((no_instrument_function))
int		__get_current_level()
{
  return __stack_list.level;
}

__attribute__((no_instrument_function))
void		*__push_var(struct s_node *new_node)
{
  new_node->next = __stack_list.begin;
  __stack_list.begin = new_node;
  return new_node->data;
}

__attribute__((no_instrument_function))
void		*__get_front()
{
  if (__stack_list.begin == 0)
    return 0;
  return __stack_list.begin->data;
}

__attribute__((no_instrument_function))
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

__attribute__((no_instrument_function))
void		__prevent_clean_up()
{
  for (struct s_node *node = __stack_list.begin; node != 0 && node->level == __stack_list.level; node = node->next)
    node->dtor = 0;
}

__attribute__((no_instrument_function))
void		__delayed_level_encrementation()
{
  if (__stack_list.begin == 0)
    return ;
  __stack_list.begin->level++;
}

/*-----------------------instrument functions-------------------------------*/

__attribute__((no_instrument_function))
void	__cyg_profile_func_enter(void *func, void *from)
{
  (void)func, (void)from;
  __new_func();
}

__attribute__((no_instrument_function))
void	__cyg_profile_func_exit(void *func, void *from)
{
  (void)func, (void)from;
  __end_func(__stack_list.level);
}
