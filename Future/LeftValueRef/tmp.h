/*
** tmp.h for  in /home/penava_b/perso/Obj/Obj4/Future/LeftValueRef
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Fri Dec 18 03:23:09 2015 penava_b
** Last update Fri Dec 18 03:24:43 2015 penava_b
*/

#pragma once

struct	t_node
{
  void	*data;
  const void	*from;
  void	(*dtor)(void *);
  struct t_node *next;
};

extern
void	*__push_front(void *, void *, void *);

extern
void	*__set_tmp(void *);

extern
void	*__get_tmp(void);

#define lvref(type, ctor, ...)						\
  ((type *)								\
   __push_front((type ## _ ## ctor(__set_tmp((type[1]){}),		\
				   ##__VA_ARGS__),			\
		 __get_tmp()),						\
		(struct t_node[1]){},					\
		(void*)type ## _ ## dtor))
