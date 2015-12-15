/*
** test.c for  in /home/penava_b/perso/test
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Wed Dec  2 17:01:42 2015 penava_b
** Last update Sun Dec  6 16:11:46 2015 penava_b
*/

#include <stdio.h>

typedef	struct String
{
  const char   	*str;
}		String;

void		*save = NULL;

void		*getAssignObj(void *rbp)
{
  unsigned char	*tmp = __builtin_return_address(0);

  while (*tmp != 0x45)
    tmp++;
  tmp++;
  save = rbp - (255 - *tmp + 1);
  return save;
}

void		*getSave()
{
  return save;
}

void		String_ctorS(String *this, const char *str)
{
  this->str = str;
}

void		String_dtor(String *this)
{
  printf("Dtor!\n");
}

#define HASH3(x, y) x ## y
#define HASH2(x, y) HASH3(x, y)
#define HASH(x, y) HASH2(x, y)

#define __init__(type, ctor, ...)					\
  __attribute__((cleanup(HASH(type, _dtor)))) =				\
    (HASH(HASH(type, _), ctor)(getAssignObj(__builtin_frame_address(0)), ##__VA_ARGS__), \
     *(type *)getSave())

int		main()
{
  String       	i __init__(String, ctorS, "Hello");
  
  printf("%s\n", i.str);
}
