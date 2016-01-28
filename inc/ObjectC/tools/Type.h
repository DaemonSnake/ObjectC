/*
** __object_type_type.h for  in /home/penava_b/perso/test/Obj4/inc
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sun Dec 13 01:29:19 2015 penava_b
** Last update Tue Jan 26 13:35:18 2016 penava_b
*/

#pragma once

typedef			struct Type
{
  const char		*name;
  const struct Type	*super;
  unsigned long		size;
  unsigned long		nbMethods;
  const char   		**methodsName;
  //
  //unsigned		nbImplements;
  //const struct Type	**implements; -> find a way to count (structure of pointers ?)
  //unsigned long	*offsets; -> offset of this_nameofinterface for dynamic_cast
  //
  void			*(*pre_ctor)(void *);
  void			(*dtor)(void *);
}			Type;

char			__is_same_kind_type(const Type *, const Type *);
const void		*__typeGetMethod(const Type * const, const void * const * const, const char const *);
const Type		*Object_getType(const void *);

#define static_cast(type, var) ((var)->this_ ## type) //takes pointer

#define as(type) .this_ ## type //takes value

#define dynamic_cast(type, var)						\
  (__is_same_kind_type(Object_getType(var), type ##_type_instance) ? \
   (type *)var->this : 0)

#define isInstanceOf(type, pointer)					\
  (pointer != NULL &&							\
   __is_same_kind_type(Object_getType(pointer), type ## _type_instance))

# define	getMethod(obj, name)					\
  (__typeGetMethod(Object_getType(obj),					\
		   (const void *)(((const Object * const )obj)->this)->_virtual, name))

# define	invoke(ret, obj, name, ...)				\
  (((ret (*)(const void*, ...))getMethod(obj, name))((const void*)(((const Object * const)obj)->this), ##__VA_ARGS__))

# define	invokeM(method, obj, ...)				\
  (method)((void *)(((const Object * const)obj)->this), ##__VA_ARGS__)