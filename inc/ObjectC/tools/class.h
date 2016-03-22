/*
** __object_userfront_macro.h for  in /home/penava_b/perso/test/Obj4/inc
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sun Dec 13 01:23:03 2015 penava_b
** Last update Tue Mar 22 06:20:16 2016 penava_b
*/

#pragma once

#define class(name, extends, ...)					\
  typedef struct name name;						\
									\
  extern const Type * const name ## _type_instance;			\
									\
  struct __supers_virtual_ ## name					\
  {									\
    struct __virtual_ ## extends;					\
    APPLY_MACRO_VAR(__virtualize__, ##__VA_ARGS__);			\
  };									\
									\
  struct __private_ ## name;						\
									\
  struct __supers_data_ ## name						\
  {									\
    struct __data_ ## extends;						\
    extends *this_ ## extends;						\
    APPLY_MACRO_VAR(__thisify__, ##__VA_ARGS__);			\
  };									\
									\
  void	name ## _ctor(struct __private_ ## name *this);			\
  void	name ## _dtor(struct __private_ ## name *this);			\
									\
  struct __weak_data_ ## name

#define interface(name)							\
  typedef struct name name;						\
									\
  extern const Type * const						\
  __attribute__((weak))							\
       name ## _type_instance;						\
  									\
  struct	name							\
  {									\
    Object	*this;							\
    const struct __virtual_ ## name *_virtual;				\
  };									\
									\
  const Type * const							\
  name ## _type_instance = (Type[1])					\
  {									\
    {									\
      #name,								\
      0,								\
      sizeof(name),							\
      0,								\
      0,								\
      0,								\
      0,								\
      0,								\
      0,								\
      0									\
    }									\
  };									\
									\
  struct __virtual_ ## name

#define virtual(name)				\
  struct __weak_virtual_ ## name

#define end_decl(...)				\
  APPLY_MACRO_VAR(__true_end_decl, ##__VA_ARGS__)

#define method(name, ...) (*name)(void *, ##__VA_ARGS__)

#define const_method(name, ...) (*name)(const void *, ##__VA_ARGS__)

#define new_tor(type, name, ...)					\
  void type ## _ ## name(struct __private_ ## type * const this, ##__VA_ARGS__)

#define new_method(type, name, ...)					\
  type ## _fake_ ## name();						\
  __typeof__(type ## _fake_ ## name())					\
  type ## _ ## name(struct __private_ ## type * const this,		\
		    ##__VA_ARGS__);					\
									\
  __attribute__((constructor, no_instrument_function))			\
  static inline void	_imp_ ## name()					\
  {									\
    void __implement_function_for_ ## type();				\
    __implement_function_for_ ## type();				\
    void __push_method_ ## type(void *, const char *, size_t);		\
    __push_method_ ## type(type ## _ ## name, #name,			\
			   offsetof(struct __virtual_ ## type, name));	\
  }									\
									\
  __typeof__(type ## _fake_ ## name())					\
  type ## _ ## name(struct __private_ ## type * const this, ##__VA_ARGS__)

#define new_const_method(type, name, ...)				\
  type ## _fake_ ## name();						\
  __typeof__(type ## _fake_ ## name())					\
  type ## _ ## name(const struct __private_ ## type * const this,	\
		    ##__VA_ARGS__);					\
									\
  __attribute__((constructor, no_instrument_function))			\
  static inline void	_imp_ ## name()					\
  {									\
   void __implement_function_for_ ## type();				\
   __implement_function_for_ ## type();					\
   void __push_method_ ## type(void *, const char *, size_t);		\
   __push_method_ ## type(type ## _ ## name, #name,			\
			    offsetof(struct __virtual_ ## type, name)); \
   }									\
									\
  __typeof__(type ## _fake_ ## name())					\
  type ## _ ## name(const struct __private_ ## type * const this,	\
		    ##__VA_ARGS__)

