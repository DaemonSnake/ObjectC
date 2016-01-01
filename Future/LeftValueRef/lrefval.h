/*
** lrefval.h for  in /home/penava_b/perso/Obj/Obj4/Future/LeftValueRef
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Fri Jan  1 10:12:30 2016 penava_b
** Last update Fri Jan  1 10:14:21 2016 penava_b
*/

#pragma once

struct		s_node
{
  void		*data;
  void		(*dtor)(void *);
  int		level;
  struct
  s_node	*next;
};

int		__get_current_level();
void		*__push_var(struct s_node *);
void		*__get_front();
void		__end_func(int);
void		__prevent_clean_up();
void		__delayed_level_encrementation();
