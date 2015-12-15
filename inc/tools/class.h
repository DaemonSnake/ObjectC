/*
1;2802;0c** __object_userfront_macro.h for  in /home/penava_b/perso/test/Obj4/inc
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sun Dec 13 01:23:03 2015 penava_b
** Last update Tue Dec 15 00:49:57 2015 penava_b
*/

#pragma once

#define interface(name)							\
  typedef struct name name;						\
  struct	name							\
  {									\
    Object	*this;							\
    const struct __virtual_ ## name *_virtual;				\
  };									\
									\
  struct __virtual_ ## name

#define class(name, extends, ...)			\
  typedef struct name name;				\
							\
  extern const Type * const name ## _type_instance;	\
							\
  struct __supers_virtual_ ## name			\
  {							\
    struct __virtual_ ## extends;			\
    APPLY_MACRO_VAR(__virtualize__, ##__VA_ARGS__);	\
  };							\
							\
  struct __supers_data_ ## name				\
  {							\
    struct __data_ ## extends;				\
    extends *this_ ## extends;				\
    APPLY_MACRO_VAR(__thisify__, ##__VA_ARGS__);	\
  };							\
							\
  void	name ## _ctor(name *this);			\
  void	name ## _dtor(name *this);			\
							\
  struct __weak_data_ ## name

#define virtual(name)				\
  struct __weak_virtual_ ## name

#define end_decl(...)				\
  APPLY_MACRO_VAR(__true_end_decl, ##__VA_ARGS__)

#define method(name, ...) (*name)(void *, ##__VA_ARGS__)

#define const_method(name, ...) (*name)(const void *, ##__VA_ARGS__)

#define new_tor(type, name, ...)			\
  void type ## _ ## name(type * const this, ##__VA_ARGS__)

#define new_method(type, name, ...) type ## _ ## name(type * const this, ##__VA_ARGS__)

#define new_const_method(type, name, ...) type ## _ ## name(const type * const this, \
							    ##__VA_ARGS__)
