/*
** tmp.h for  in /home/penava_b/perso/Obj/Obj4/Future/LeftValueRef
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Fri Dec 18 03:23:09 2015 penava_b
** Last update Fri Dec 18 18:53:49 2015 penava_b
*/

#pragma once

struct  __false_node
{
  void	*_1;
  void	*_2;
  void	*_3;
  void	*_4;
};

extern
void	*__push_front(void *, void *, void *);

extern
void	*__set_tmp(void *);

extern
void	*__get_tmp(void);

extern
void	__pop_nodes(const void *);

#define lvref(type, ctor, ...)						\
  ((type *)								\
   __push_front((type ## _ ## ctor(__set_tmp((type[1]){}),		\
				   ##__VA_ARGS__),			\
		 __get_tmp()),						\
		(struct __false_node[1]){},				\
		(void*)type ## _ ## dtor))
