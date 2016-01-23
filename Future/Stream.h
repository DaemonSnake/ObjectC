/*
** Stream.h for  in /home/penava_b/perso/Obj/ObjLang3/Tools
**
** Made by penava_b
** Login   <penava_b@epitech.net>
**
** Started on  Wed Nov 25 18:54:30 2015 penava_b
** Last update Sat Jan 23 05:22:39 2016 penava_b
*/

#pragma once

#include "Class.h"

class(Stream, Object)
{
  int		fd;
  char		opened;
};

virtual(Stream)
{
  void		method(scan, Object *); // scan from input and use method in Object to push data in the Object
  void		method(scanf, const char *, ...); // call true scanf then mine with {n}... inside and act like above
  void		method(print, Object *);
  void		method(printf, const char *, ...);
  void		method(open, const char *);
  void		method(openFd, int);
  void		method(close);
};

end_decl(Stream);

new_tor(ctorFile, const char *);
new_tor(ctorFd, int);

extern Stream	* const cout;
extern Stream	* const cin;
extern Stream	* const cerr;
