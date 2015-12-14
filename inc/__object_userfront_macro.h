/*
1;2802;0c** __object_userfront_macro.h for  in /home/penava_b/perso/test/Obj4/inc
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sun Dec 13 01:23:03 2015 penava_b
** Last update Mon Dec 14 17:56:55 2015 penava_b
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

#define static_cast(type, var) ((var)->this_ ## type)

#define dynamic_cast(type, var)						\
  (__is_same_kind_type((var->this)->__class_type, type ##_type_instance) ? \
   (type *)var->this : 0)

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

#define implement(name, extends, ...)					\
									\
  static void __pre_ctor_ ## name(name *this)				\
  {									\
    unsigned long offset = sizeof(struct __virtual_ ## extends);	\
									\
    this->this = this;							\
    this->_virtual = __vtable_instance_ ## name;			\
    this->__class_type = name ## _type_instance;			\
    this->this_ ## extends = (void *)this;				\
    APPLY_MACRO_VAR(__implements_in_ctor__, ##__VA_ARGS__);		\
  }									\
    									\
  static Type true_ ## name ## _type_instance =				\
    {									\
      #name,								\
      0,								\
      sizeof(name),							\
      (void *)__pre_ctor_ ## name,					\
      (void *)name ## _ ## dtor						\
    };									\
									\
  const Type * const name ## _type_instance =				\
    &true_ ## name ## _type_instance;					\
  static struct __virtual_ ## name __true_vtable_instance_ ## name;	\
  const struct __virtual_ ## name * const __vtable_instance_ ## name =	\
    &__true_vtable_instance_ ## name;					\
									\
  static void __hidden_implement_function_for_ ## name();		\
  void __implement_function_for_ ## extends();				\
  									\
  __attribute__((constructor))						\
  void __implement_function_for_ ## name()				\
  {									\
    static char implemented = 0;					\
    unsigned long i;							\
									\
    if (implemented++ != 0)						\
      return ;								\
    true_ ## name ## _type_instance.super = extends ## _type_instance;	\
    __implement_function_for_ ## extends();				\
    for (i = 0; i < sizeof(struct __virtual_ ## extends)		\
	   / sizeof(void *); i++)					\
      ((void **)&__true_vtable_instance_ ## name)[i] =			\
	((void **)__vtable_instance_ ## extends)[i];			\
    for (; i < sizeof(struct __virtual_ ## name)			\
	   / sizeof(void *); i++)					\
      ((void **)&__true_vtable_instance_ ## name)[i] = 0;		\
    __hidden_implement_function_for_ ## name();				\
    __true_vtable_instance_ ## name.dtor = (void *)name ## _ ## dtor;	\
  }									\
  									\
  static void __hidden_implement_function_for_ ## name()

#define virtual(name)				\
  struct __weak_virtual_ ## name

#define end_decl(...)				\
  APPLY_MACRO_VAR(__true_end_decl, ##__VA_ARGS__)

#define method(name, ...) (*name)(void *, ##__VA_ARGS__)

#define const_method(name, ...) (*name)(const void *, ##__VA_ARGS__)

#define new_tor(type, name, ...)			\
  void type ## _ ## name(type * const this, ##__VA_ARGS__)

#define superCtor(type, name, ...)		\
  type ## _ ## name(this, ##__VA_ARGS__)

#define superDtor()				\
  this->__class_type->super->dtor(this);

#define new_method(type, name, ...) type ## _ ## name(type * const this, ##__VA_ARGS__)

#define new_const_method(type, name, ...) type ## _ ## name(const type * const this, \
							    ##__VA_ARGS__)

#define M(var, name, ...) (var)->_virtual->name((var)->this, ##__VA_ARGS__)

#define __init__(type, var, ctorName, ...) (type ## _type_instance->pre_ctor(var), type ## _ ## ctorName(var, ##__VA_ARGS__))

#define local __attribute__((cleanup(__object_clean_up)))

#define push_methods(type, name, ...) APPLY_MACRO_VAR_TWO(__true_push_method__, type, name, ##__VA_ARGS__)

#define $ (*this)
