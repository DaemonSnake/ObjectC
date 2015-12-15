/*
** test.h for  in /home/penava_b/perso/test/Obj4
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sat Dec 12 22:16:21 2015 penava_b
** Last update Mon Dec 14 23:46:50 2015 penava_b
*/

#include "String.h"

interface(IClosable)
{
  void	method(close);
};

class(FileD, Object, IClosable)
{
  int	fd;
  char	opened;
};

virtual(FileD)
{
  void 	method(open, const char *name);
  int	const_method(read, int size, char *buff);
};

new_tor(FileD, ctorS, const char *name);

end_decl(FileD);
