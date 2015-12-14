/*
** test.c for  in /home/penava_b/perso/test
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sun Dec 13 03:21:14 2015 penava_b
** Last update Sun Dec 13 04:15:51 2015 penava_b
*/

#define translator(name) add(name)

void	*func(void *left, void *right, const char *op)
{
  const char []l_or_r = {
    "++", "--" 
  };
  
  if (left == 0 && right == 0)
    return 0;
  if (left == 0)
    {
      
    }
  else if (right == 0)
    {
    }
  else
    {
      const char []lr = {
	"+", "-", "*", "/", "<<", ">>", "^", "[]"
	"=", "+=", "-=", "*=", "/=", "^=",
	"==", "<=", ">=", "<", ">"
      };
      const int []offsets = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
      }
      for (int i = 0; i < sizeof(lr); i++)
	if (strcmp(lr[i], op) == 0)
	  return 
    }
}

#define $op$(left, op, right) func(left, right, #op)
#define op$(left, op) func(left, 0, #op)
#define $op(op, right) func(0, right, #op)

int	main()
{
  void	*tmp;

  $op$(tmp, +, tmp);
  op$(tmp, ++);
  $op(++, tmp);
}
