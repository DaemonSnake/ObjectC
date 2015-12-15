/*
** __object_type_type.h for  in /home/penava_b/perso/test/Obj4/inc
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sun Dec 13 01:29:19 2015 penava_b
** Last update Tue Dec 15 02:29:34 2015 penava_b
*/

#pragma once

typedef			struct Type
{
  const char		*name;
  const struct Type	*super;
  unsigned long		size;
  unsigned long		nbMethods;
  const char   		**methodsName;
  void			*(*pre_ctor)(void *);
  void			(*dtor)(void *);
}			Type;

char			__is_same_kind_type(const Type *, const Type *);
const void		*__typeGetMethod(const Type * const, const void * const * const, const char const *);

#define static_cast(type, var) ((var)->this_ ## type)

#define dynamic_cast(type, var)						\
  (__is_same_kind_type(M(var->this, getType), type ##_type_instance) ?	\
   (type *)var->this : 0)

#define isInstanceOf(type, pointer) (pointer != NULL && __is_same_kind_type(M(pointer->this, getType), type ## _type_instance))

# define	getMethod(obj, name) (__typeGetMethod((const void *)((const Object * const )(obj)->this)->__class_type, (const void *)((const Object * const )(obj)->this)->_virtual, name))

# define	invoke(ret, obj, name, ...)				\
  (((ret (*)(const void*, ...))getMethod(obj, name))((const void*)((obj)->this), ##__VA_ARGS__))

# define	invokeM(ret, method, obj, ...)				\
  (((ret (*)(const void*, ...))(const void *)method)((const void*)((obj)->this), ##__VA_ARGS__))
