/*
** test.c for  in /home/penava_b/perso/test
**
** Made by penava_b
** Login   <penava_b@epitech.net>
**
** Started on  Wed Dec 30 03:47:42 2015 penava_b
** Last update Thu Dec 31 08:08:05 2015 penava_b
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
  __new_func();
}

__attribute__((no_instrument_function))
void	__cyg_profile_func_exit(void *func, void *from)
{
  __end_func(__stack_list.level);
}

/*-----------------------object default tool------------------------------*/

#define local(type, var, ...)						\
  type var;								\
  __push_var((struct s_node[1])						\
	     {&var, (void *)type ## _dtor, __get_current_level()});	\
  type ## _ctor(&var, __VA_ARGS__);

void	int_dtor(int *this)
{
  printf("Dtor of %p %d\n", this, *this);
}

void	int_ctor(int *this, int val)
{
  *this = val;
}

/*------------------------default------------------------------*/

void	default_behaviour()
{
  local(int, tmp, 1);
}

/*------------------------yield------------------------------*/

void	yield_case()
{
  local(int, tmp, 2);

  __prevent_clean_up();
  return;
}

/*-----------------------exceptions------------------------------*/

#include <setjmp.h>

#define new_except(name)					\
  struct except_buf name = {__get_current_level() + 1, {}}

struct	except_buf
{
  int	level;
  jmp_buf buff;
};

void	throwing(struct except_buf *buf)
{
  local(int, tmp, 3);

  __end_func(buf->level);
  longjmp(buf->buff, -1);
}

void	except_case(struct except_buf *buf)
{
  local(int, tmp, 4);

  throwing(buf);
}

/*-----------------------left reference value-------------------------------*/

#define lrvalue(type, ctor, ...)				\
  (type ## _ ## ctor(__push_var((struct s_node[1])		\
				{ (type[1]){},			\
				    (void *)type ## _dtor,	\
				      __get_current_level()	\
				      }), ##__VA_ARGS__),	\
   __delayed_level_encrementation(),				\
   (type *)__get_front())

void	lrvalue_func(int *tmp)
{
  printf("Value %d\n", *tmp);
  printf("Other value %d\n", *lrvalue(int, ctor, 5));
  printf("End of lrvalue_func\n");
}

void	calling_lrvalue()
{
  lrvalue_func(lrvalue(int, ctor, 6));
}

/*-----------------------main test-------------------------------*/

int		main()
{
  local(int, tmp, 7);
  new_except(buff);

  default_behaviour();
  yield_case();
  if (setjmp(buff.buff) == 0)
    except_case(&buff);
  else
    printf("Exception Caught\n");
  calling_lrvalue();
}
