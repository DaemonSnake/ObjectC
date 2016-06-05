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

int	write(int, const char *, int);
void	__call_class_super_dtor(Object * const);

#define implement(name, extends, ...)					\
									\
  __attribute__((no_instrument_function))				\
 void		*__pre_ctor_ ## name(struct __private_ ## name *this)	\
  {									\
    void	__pre_ctor_Object_child(const void *, const void *);	\
									\
    __pre_ctor_ ## extends((void *)this);				\
    __pre_ctor_Object_child(this, name ## _type_instance);		\
    this->this = (void *)this;						\
    this->this_ ## name = (void *)this;                                 \
    this->_virtual = __vtable_instance_ ## name;			\
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
      (const char *[sizeof(struct __virtual_ ## name) / sizeof(void *)]){0}, \
      sizeof(struct __interfaces_for_ ## name),				\
      (const Type *[sizeof(struct __interfaces_for_ ## name)]){0},	\
      (unsigned long [sizeof(struct __interfaces_for_ ## name)]){0},	\
      (void *)name ## _ ## dtor						\
    };									\
									\
  const Type * const name ## _type_instance =				\
    &true_ ## name ## _type_instance;					\
  									\
  static struct __virtual_ ## name __true_vtable_instance_ ## name = {0}; \
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
    __true_vtable_instance_ ## name.dtor = (void *)name ## _ ## dtor;	\
    for (i = 0; i < extends ## _type_instance->nbImplements; i++)	\
      {									\
	true_ ## name ## _type_instance.implements[i] =			\
	  extends ## _type_instance->implements[i];			\
	true_ ## name ## _type_instance.offsets[i] =			\
	  extends ## _type_instance->offsets[i];			\
      }									\
    APPLY_MACRO_VAR_TWO(__interface_implements__, name, ##__VA_ARGS__);	\
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

#define $$(method, ...) M(this, method, ##__VA_ARGS__)

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

// get
#define __new_user_axor_2(class, name, ...) \
    __typeof__(((struct __private_ ## class *)0)->name) new_method(class, get_ ## name)

// set
#define __new_user_axor_3(class, name, arg, ...)        \
    void new_method(class, set_ ## name, arg)

#define new_axor(class, name, ...) ______VARARG(__new_user_axor_, class, name, ##__VA_ARGS__)
