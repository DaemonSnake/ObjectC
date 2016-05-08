/*
** test.c for  in /home/penava_b
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sun Apr  3 20:44:44 2016 penava_b
** Last update Sun May  8 14:38:51 2016 penava_b
*/

#define scope()								\
  for (int __scope_tmp__ = __scope__ + 1,				\
	 __scope__ __attribute__((cleanup(dtor))) = __scope_tmp__;	\
       __scope__ != 0; __scope__ = 0)

void	dtor(int *tmp)
{
  if (*tmp == 0)
    printf("Exiting normaly a scope\n");
  else
    printf("Exiting prematurly %d scopes\n", *tmp);
}

const int	__scope__ = 0;

void	func()
{
  printf("%d\n", __scope__);
  scope()
    {
      printf("%d\n", __scope__);
      scope()
	{
	  dtor(&__scope__);
	  asm("leaveq");
	  asm("retq");
	}
    }
}

int	main()
{
  func();
}
