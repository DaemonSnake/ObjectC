/*
1;2802;0c** __object_macro_tools.h for  in /home/penava_b/perso/test/Obj4/inc
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sun Dec 13 01:21:22 2015 penava_b
** Last update Tue Mar 22 06:34:06 2016 penava_b
*/

#pragma once

#include <stddef.h>

#define __virtualize__(name) struct __virtual_ ## name;

#define __true_end_decl(name)						\
  struct __virtual_ ## name						\
  {									\
    struct __supers_virtual_ ## name;					\
    struct __weak_virtual_ ## name;					\
  };									\
									\
  extern								\
  const struct __virtual_ ## name * const __vtable_instance_ ## name;	\
  									\
  struct __data_ ## name						\
  {									\
    struct __supers_data_ ## name;					\
    char __private_ ## name[sizeof(struct __weak_data_ ## name)];	\
  };									\
									\
  struct __private_ ## name						\
  {									\
    name *this;								\
    const struct __virtual_ ## name *_virtual;				\
    struct __supers_data_ ## name;					\
    struct __weak_data_ ## name;					\
  };									\
									\
  struct name								\
  {									\
    name *this;								\
    const struct __virtual_ ## name *_virtual;				\
    struct __data_ ## name;						\
  };

#define __thisify__(name)			\
  name *this_ ## name;				\
  name *__true_this_ ## name;			\
  struct __virtual_ ## name *_virtual_ ## name;

#define __implements_in_ctor__(name)					\
  this->this_ ## name = (void *)&this->__true_this_ ## name;		\
  this->__true_this_ ## name = (void *)this;				\
  if (42)								\
    {									\
      __attribute__((always_inline, no_instrument_function))		\
      inline void *__offset__(struct __virtual_ ## name *tmp)		\
      {									\
	return tmp;							\
      }									\
      this->_virtual_ ## name = __offset__(this->_virtual);		\
    }									\

#define __interface_implements__(name, interface)			\
  true_ ## name ## _type_instance.implements[i] = interface ## _type_instance; \
  true_ ## name ## _type_instance.offsets[i++] = offsetof(name, __true_this_ ## interface)

/* AXORS METHODS DECL */

#define __axor_get(type, name) type (*get_ ## name)(const void *);
#define __axor_(type, name)
#define __axor_set(type, name) void (*set_ ## name)(void *, type name);
#define __launch_axor(type, name, x, ...) \
  __axor_ ## x(type, name)		  \
  __axor_ ## __VA_ARGS__(type, name)

#define axors(type, name, ...)  __launch_axor(type, name, __VA_ARGS__)
