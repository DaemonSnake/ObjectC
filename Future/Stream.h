/*
** Stream.h for  in /home/penava_b/perso/Obj/ObjLang3/Tools
**
** Made by penava_b
** Login   <penava_b@epitech.net>
**
** Started on  Wed Nov 25 18:54:30 2015 penava_b
** Last update Fri Dec 18 03:30:35 2015 penava_b
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
  Stream	*method(read, Object *);
  Stream	*method(print, Object *);
  Stream	*method(printf, const char *, ...);
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
