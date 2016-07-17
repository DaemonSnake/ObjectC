/*
 * Copyright (C) 2016  Bastien Penavayre
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#pragma once

struct		s_right_value_node
{
  void		*data;
  void		(*dtor)(void *);
  int		level;
  struct s_right_value_node	*next;
  void		*id;
};

int		__get_current_level();
void		*__push_var(struct s_right_value_node *);
void		*__get_front_var_list();
void		__exit_end_func(int);
void		__delayed_level_encrementation();
void		*__prevent_clean_up_var(void *);
void		(*__get_return_dtor())(void *);
void		__protect_kill_stack(void *);

#define rvalue(type, ctor, args...)                             \
    (__protect_kill_stack((char[1]){0}),                        \
     type ## _ ## ctor                                          \
     (__pre_ctor_ ## type                                       \
      (__push_var((struct s_right_value_node[1])                \
                  {{ (type[1]){},                               \
                              (void *)type ## _dtor,            \
                                  __get_current_level(),        \
                                  (void *)0, (void *)0          \
                                  }})), ##args),                \
     __delayed_level_encrementation(),                          \
     (type *)__get_front_var_list())

#define function_rvalue(type, ctor, args...)                    \
    (__protect_kill_stack((char[1]){0}),                        \
     type ## _ ## ctor                                          \
     (__pre_ctor_ ## type                                       \
      (__push_var((struct s_right_value_node[1])                \
                  {{ (type[1]){},                               \
                              (void *)type ## _dtor,            \
                                  __get_current_level(),        \
                                  (void *)0, (void *)0          \
                                  }})), ##args),                \
     (type *)__get_front_var_list())

#define stdmove(x) (*(typeof(x))__prevent_clean_up_var(x))

#define retvalue(x)                                     \
    (__protect_kill_stack((char[1]){0}),                \
         (typeof(x) *)                              \
         __push_var((struct s_right_value_node[1])      \
         {{						\
           (typeof(x)[1]){x},			\
               __get_return_dtor(),			\
               __get_current_level() + 1,		\
               (void *)0, (void *)0			\
               }})					\
         )
