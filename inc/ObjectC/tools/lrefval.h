/*
1;2802;0c** lrefval.h for  in /home/penava_b/perso/Obj/Obj4/Future/LeftValueRef
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Fri Jan  1 10:12:30 2016 penava_b
** Last update Wed Mar 23 06:05:07 2016 penava_b
*/

#pragma once

struct		s_left_reference_value_node
{
  void		*data;
  void		(*dtor)(void *);
  char		toclean;
  int		level;
  struct
  s_left_reference_value_node	*next;
};

int		__get_current_level();
void		*__push_var(struct s_left_reference_value_node *);
void		*__get_front_var_list();
void		__exit_end_func(int);
void		__prevent_clean_up();
void		__reset_clean_up();
void		__delayed_level_encrementation();
void		*__prevent_clean_up_var(void *);
void		(*__get_return_dtor())(void *);
long		__get_front_node_diff(const char *);
void		__push_back_on_stack(void *, int);

#define lrvalue(type, ctor, ...)					\
  (type ## _ ## ctor							\
   (type ## _type_instance->pre_ctor					\
    (__push_var((struct s_left_reference_value_node[1])			\
		{{ (type[1]){},						\
		      (void *)type ## _dtor,				\
			42,						\
			__get_current_level(),				\
			(void *)0					\
			}})), ##__VA_ARGS__),				\
    __delayed_level_encrementation(),					\
    (type *)__get_front_var_list())

#define function_lrvalue(type, ctor, ...)				\
  (type ## _ ## ctor							\
   (type ## _type_instance->pre_ctor					\
    (__push_var((struct s_left_reference_value_node[1])			\
		{{ (type[1]){},						\
		      (void *)type ## _dtor,				\
			42,						\
			__get_current_level(),				\
			(void *)0					\
			}})), ##__VA_ARGS__),				\
   (type *)__get_front_var_list())

#define stdmove(x) (*(__typeof__(x) *)__prevent_clean_up_var(&x))

#define rvalue(x)						\
  ((__typeof__(x) *)						\
   __push_var((struct s_left_reference_value_node[1])		\
	      {{						\
		  (__typeof__(x)[1]){x},			\
		    __get_return_dtor(),			\
		      42,					\
		      __get_current_level() + 1,		\
		      (void *)0					\
		      }})					\
   )
