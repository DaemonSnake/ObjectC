/*
** __object_type_type.h for  in /home/penava_b/perso/test/Obj4/inc
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sun Dec 13 01:29:19 2015 penava_b
** Last update Mon Dec 14 04:26:55 2015 penava_b
*/

#pragma once

typedef			struct Type
{
  const char		*name;
  const struct Type	*super;
  unsigned long		size;
  void			(*pre_ctor)(void *);
  void			(*dtor)(void *);
}			Type;

char	__is_same_kind_type(const Type *, const Type *);
