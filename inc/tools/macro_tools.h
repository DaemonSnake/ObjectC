/*
1;2802;0c** __object_macro_tools.h for  in /home/penava_b/perso/test/Obj4/inc
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sun Dec 13 01:21:22 2015 penava_b
** Last update Sat Jan 23 04:48:19 2016 penava_b
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

#define __implements_in_ctor__(name)				\
  this->this_ ## name = (void *)&this->__true_this_ ## name;	\
  this->__true_this_ ## name = (void *)this;			\
  this->_virtual_ ## name = (void *)this->_virtual + offset;	\
  offset += sizeof(struct __virtual_ ## name);
