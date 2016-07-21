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

#define implement(name, extends, args...)                               \
									\
  __attribute__((no_instrument_function))				\
  void		*name ## __pre_ctor(struct name ## __private *this)	\
  {									\
    void	Object__pre_ctor_child(const void *, const void *);	\
									\
    extends ## __pre_ctor((void *)this);				\
    Object__pre_ctor_child(this, name ## __type_instance);		\
    this->this = (void *)this;						\
    this->name ## __this = (void *)this;                                \
    this->_virtual = name ## __vtable_instance;                         \
    APPLY_MACRO_VAR(__implements_in_ctor__, ##args);                    \
    return this;							\
  }									\
    									\
  static Type name ## __true_type_instance =				\
    {									\
      #name,								\
      0,								\
      sizeof(name),							\
      sizeof(struct name ## __virtual) / sizeof(void *),		\
      (const char *[sizeof(struct name ## __virtual) / sizeof(void *)]){0}, \
      sizeof(struct name ## __interfaces),				\
      (const Type *[sizeof(struct name ## __interfaces) + 1]){0},       \
      (unsigned long [sizeof(struct name ## __interfaces) + 1]){0},	\
      (void *)name ## __ ## dtor                                        \
    };									\
									\
  const Type * const name ## __type_instance =				\
    &name ## __true_type_instance;					\
  									\
  static struct name ## __virtual name ## __true_vtable_instance = {0}; \
									\
  const struct name ## __virtual * const name ## __vtable_instance =	\
      &name ## __true_vtable_instance;					\
									\
  static void name ## __hidden_implement_function();                    \
  void extends ## __implement_function();				\
  									\
  __attribute__((constructor, no_instrument_function))		        \
  void name ## __implement_function()                                   \
  {									\
    static char implemented = 0;					\
    unsigned long i;							\
									\
    if (implemented++ != 0)						\
      return ;								\
    name ## __true_type_instance.super = extends ## __type_instance;	\
    extends ## __implement_function();                                  \
    for (i = 0; i < sizeof(struct extends ## __virtual)                 \
	   / sizeof(void *); i++)					\
      {									\
          ((void **)&name ## __true_vtable_instance)[i] =		\
              ((void **)extends ## __vtable_instance)[i];               \
          name ## __true_type_instance.methodsName[i] =                 \
	  extends ## __type_instance->methodsName[i];			\
      }									\
    name ## __true_vtable_instance.dtor = (void *)name ## __ ## dtor;	\
    for (i = 0; i < extends ## __type_instance->nbImplements; i++)	\
      {									\
        name ## __true_type_instance.implements[i] =			\
	  extends ## __type_instance->implements[i];			\
        name ## __true_type_instance.offsets[i] =			\
            extends ## __type_instance->offsets[i];			\
      }									\
    APPLY_MACRO_VAR_TWO(__interface_implements__, name, ##args);	\
  }									\
      									\
  __attribute__((no_instrument_function))				\
  void		name ## __push_method(void *arg, const char *name_m,	\
                                      size_t offset)			\
  {									\
    int		__get_current_level();					\
    void		**member =					\
        &((void **)&name ## __true_vtable_instance)			\
        [offset / sizeof(void *)];					\
									\
    if (__get_current_level() > 0)					\
      {									\
	write(2, "[Error]Illegal call to __push_method\n", 37);		\
	return ;							\
      }									\
    if (offset < sizeof(struct extends ## __virtual) &&                 \
	*member != 0 && *member !=					\
	((void **)extends ## __vtable_instance)                         \
	[offset / sizeof(void *)])					\
      {									\
	write(2, "[Error]Trying to override twice a method\n", 41);	\
	return;								\
      }									\
    *member = arg;							\
    ((void **)&name ## __true_vtable_instance)                          \
      [offset / sizeof(void *)] = arg;					\
    name ## __true_type_instance.methodsName				\
      [offset / sizeof(void *)] = name_m;				\
    for (size_t i = 0; i < sizeof(struct name ## __virtual)		\
	   / sizeof(void *); i++)					\
        if (((void **)name ## __vtable_instance)[i] == 0)		\
            return ;							\
    name ## __hidden_implement_function();				\
  }									\
									\
  __attribute__((no_instrument_function))				\
  static void name ## __hidden_implement_function()

#define superCtor(type, name, args...)		\
  type ## __ ## name((void *)this, ##args)

#define superDtor()				\
  __call_class_super_dtor((void *)this)

#define $ (*this)

#define $$(method, args...) M(this, method, ##args)

/* AXORS METHODS IMPL */

#define __new_def_axor_get(class, name)			\
  typeof(((struct class ## __private *)0)->name)	\
  new_method(class, get_ ## name)			\
  {							\
    return $.name;					\
  }

#define __new_def_axor_set(class, name)					\
  void									\
  new_method(class, set_ ## name,					\
	     typeof(((struct class ## __private *)0)->name) name)	\
  {									\
    $.name = name;							\
  }

#define __new_def_axor_(class, name)

#define __launch_new_def_axors(class, name, x, y...)	\
    __new_def_axor_ ## x(class, name)			\
    __new_def_axor_ ## y(class, name)

#define new_def_axors(class, name, x...) __launch_new_def_axors(class, name, x)

// get
#define __new_user_axor_2(class, name, ...)                             \
    typeof(((struct class ## __private *)0)->name) new_method(class, get_ ## name)

// set
#define __new_user_axor_3(class, name, arg, ...)        \
    void new_method(class, set_ ## name, arg)

#define new_axor(class, name, args...) ______VARARG(__new_user_axor_, class, name, ##args)
