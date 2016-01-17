/*
** main.c for  in /home/penava_b/perso/test/objtest
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sun Jan 17 14:43:51 2016 penava_b
** Last update Sun Jan 17 15:45:55 2016 penava_b
*/

#define class(name)				\
  typedef struct name name;			\
						\
  struct __private_ ## name			\

#define public_data(name)			\
  struct __public_ ## name

class(String)
{
  char	*c_str;
};

public_data(String)
{
  int	i;
};

struct	__true_String
{
  struct __private_String;
  struct __public_String;
};

struct	String
{
  char	private[sizeof(struct __private_String)];
  struct __public_String;
};

#include <stdio.h>

void	String_ctor(struct __true_String *this)
{
  this->c_str = "Hello";
  this->i = 5;
}

void	String_print(struct __true_String *this)
{
  printf("%s\n", this->c_str);
}

int	main()
{
  String tmp;

  String_ctor((void *)&tmp);
  printf("%d\n", tmp.i);
  String_print((void *)&tmp);
}
