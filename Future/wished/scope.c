/*
** scope.c for  in /home/penava_b/perso/Obj/Obj4/Future/wished
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sun Mar 27 04:26:46 2016 penava_b
** Last update Sun Mar 27 04:29:47 2016 penava_b
*/

int	main()
{
  String	*tmp = new(String, ctorS, "Hello");

  scoped(tmp)
  {
    for (int i = 0; i < 10; i++)
      if (i % 2 == 0)
	printf("Ok\n");
      else if (i == 9)
	return ; //will delete tmp beforehand
  }
}
