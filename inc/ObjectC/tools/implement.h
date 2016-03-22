/*
** implement.h for  in /home/penava_b/perso/Obj/Obj4/inc/tools
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Mon Dec 14 23:48:27 2015 penava_b
** Last update Tue Mar 22 05:21:23 2016 penava_b
*/

#pragma once

int	write(int, const char *, int);
void	__call_class_super_dtor(Object * const);

#define implement(name, extends, ...)					\
									\
  __attribute__((no_instrument_function))				\
  static void *__pre_ctor_ ## name(struct __private_ ## name *this)	\
  {									\
    void	__pre_ctor_Object_child(const void *, const void *);	\
									\
    __pre_ctor_Object_child(this, name ## _type_instance);		\
    this->this = (void *)this;						\
    this->_virtual = __vtable_instance_ ## name;			\
    this->this_ ## extends = (void *)this;				\
    APPLY_MACRO_VAR(__implements_in_ctor__, ##__VA_ARGS__);		\
    return this;							\
  }									\
    									\
  static Type true_ ## name ## _type_instance =				\
    {									\
      #name,								\
      0,								\
      sizeof(name),							\
      sizeof(struct __virtual_ ## name) / sizeof(void *),		\
      (const char *[sizeof(struct __virtual_ ## name) / sizeof(void *)])\
      {},								\
      ______VA_NARGS(__VA_ARGS__),					\
      (void *)__pre_ctor_ ## name,					\
      (void *)name ## _ ## dtor						\
    };									\
									\
  const Type * const name ## _type_instance =				\
    &true_ ## name ## _type_instance;					\
  									\
  static struct __virtual_ ## name __true_vtable_instance_ ## name;	\
									\
  const struct __virtual_ ## name * const __vtable_instance_ ## name =	\
    &__true_vtable_instance_ ## name;					\
									\
  static void __hidden_implement_function_for_ ## name();		\
  void __implement_function_for_ ## extends();				\
  									\
  __attribute__((constructor, no_instrument_function))		        \
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
      {									\
	((void **)&__true_vtable_instance_ ## name)[i] =		\
	  ((void **)__vtable_instance_ ## extends)[i];			\
	true_ ## name ## _type_instance.methodsName[i] =		\
	  extends ## _type_instance->methodsName[i];			\
      }									\
    for (; i < sizeof(struct __virtual_ ## name)			\
	   / sizeof(void *); i++)					\
      {									\
	((void **)&__true_vtable_instance_ ## name)[i] = 0;		\
	true_ ## name ## _type_instance.methodsName[i] = 0;		\
      }									\
    __true_vtable_instance_ ## name.dtor = (void *)name ## _ ## dtor;	\
  }									\
      									\
  __attribute__((no_instrument_function))				\
  void		__push_method_ ## name(void *arg, const char *name_m,	\
				       size_t offset)			\
  {									\
    int		__get_current_level();					\
    void		**member =					\
      &((void **)&__true_vtable_instance_ ## name)			\
      [offset / sizeof(void *)];					\
									\
    if (__get_current_level() > 0)					\
      {									\
	write(2, "[Error]Illegal call to __push_method\n", 37);		\
	return ;							\
      }									\
    if (offset < sizeof(struct __virtual_ ## extends) &&		\
	*member != 0 && *member !=					\
	((void **)__vtable_instance_ ## extends)			\
	[offset / sizeof(void *)])					\
      {									\
	write(2, "[Error]Trying to override twice a method\n", 41);	\
	return;								\
      }									\
    *member = arg;							\
    ((void **)&__true_vtable_instance_ ## name)				\
      [offset / sizeof(void *)] = arg;					\
    true_ ## name ## _type_instance.methodsName				\
      [offset / sizeof(void *)] = name_m;				\
    for (size_t i = 0; i < sizeof(struct __virtual_ ## name)		\
	   / sizeof(void *); i++)					\
      if (((void **)__vtable_instance_ ## name)[i] == 0)		\
	return ;							\
    __hidden_implement_function_for_ ## name();				\
  }									\
									\
  __attribute__((no_instrument_function))				\
  static void __hidden_implement_function_for_ ## name()

#define superCtor(type, name, ...)		\
  type ## _ ## name((void *)this, ##__VA_ARGS__)

#define superDtor()				\
  __call_class_super_dtor((void *)this)

#define $ (*this)

/* AXORS METHODS IMPL */

#define __new_def_axor_get(class, name)			\
  __typeof__(((struct __private_ ## class *)0)->name)	\
  new_method(class, get_ ## name)			\
  {							\
    return $.name;					\
  }

#define __new_def_axor_set(class, name)					\
  void									\
  new_method(class, set_ ## name,					\
	     __typeof__(((struct __private_ ## class *)0)->name) name)	\
  {									\
    $.name = name;							\
  }

#define __new_def_axor_(class, name)

#define __launch_new_def_axors(class, name, x, y...)	\
  __new_def_axor_ ## x(class, name)			\
  __new_def_axor_ ## y(class, name)

#define new_def_axors(class, name, x...) __launch_new_def_axors(class, name, x)
