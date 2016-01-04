/*
** lrefval.h for  in /home/penava_b/perso/Obj/Obj4/Future/LeftValueRef
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Fri Jan  1 10:12:30 2016 penava_b
** Last update Mon Jan  4 09:32:10 2016 penava_b
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
void		*__prevent_clean_up_var(void *);
void		(*__get_return_dtor())(void *);

#define lrvalue(type, ctor, ...)				\
  (type ## _ ## ctor(__push_var((struct s_node[1])		\
				{{ (type[1]){},			\
				    (void *)type ## _dtor,	\
				      __get_current_level(),	\
				      (void *)0			\
				      }}), ##__VA_ARGS__),	\
   __delayed_level_encrementation(),				\
   (type *)__get_front())

#define stdmove(x) (*(__typeof__(x) *)__prevent_clean_up_var(&x))

#define rvalue(x)						\
  ((__typeof__(x) *)						\
     __push_var((struct s_node[1])				\
		{{						\
		    (__typeof__(x)[1]){(x)},			\
		      __get_return_dtor(),			\
			__get_current_level() + 1,		\
			(void *)0				\
			}}))
