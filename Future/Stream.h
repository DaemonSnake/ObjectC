/*
** Stream.h for  in /home/penava_b/perso/Obj/ObjLang3/Tools
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Wed Nov 25 18:54:30 2015 penava_b
** Last update Thu Nov 26 18:13:05 2015 penava_b
*/

#pragma once

#include "Object.h"
#include "CleanMacros.h"

#define CLASS Stream

#define CTORS					\
  new_tor(ctorFile, const char *);		\
  new_tor(ctorFd, int);

#define SUPER__Stream Object

#define VIRTUAL__Stream					\
  VIRTUAL__Object;					\
  Stream	*add_method(read, Object *);		\
  Stream	*add_method(print, Object *);		\
  Stream	*add_method(printf, const char *, ...);	\
  void		add_method(open, const char *);		\
  void		add_method(openFd, int);		\
  void		add_method(close);

#define DATA__Stream				\
  DATA__Object;					\
  int		fd;				\
  char		opened;

#include "CreateClass.h"

extern Stream	* const cout;
extern Stream	* const cin;
extern Stream	* const cerr;
