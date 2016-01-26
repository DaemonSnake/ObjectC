/*
** Format.c for  in /home/penava_b/perso/Obj/Obj4/test
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Wed Jan 20 18:44:41 2016 penava_b
** Last update Tue Jan 26 14:35:36 2016 penava_b
*/

#include <stdio.h>
#include <stdarg.h>
#include <alloca.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_node t_args;
typedef struct string_list t_str;
typedef struct result_list result;

struct		s_node
{
  int		index;
  char		*arg;
  t_args	*next;
};

struct		result_list
{
  struct       	string_list
  {
    int		begin, end;
    t_args	*node;
    t_str	*next;
  }		*next;
};

int		vasprintf(char **, const char *, va_list);
void		free(void *);
int		atoi(const char *);
char		*create_result(result *, char *);

void		push_res(result *res, t_str *to_add, t_args *node, int begin, int end)
{
  *to_add = (t_str){begin, end, node, res->next};
  res->next = to_add;
}

#define push(n, b, e) push_res(&res, alloca(sizeof(t_str)), n, b, e)

char		*format(const char *format, ...)
{
  va_list	ap;
  char		*str = 0, in_b = 0, *ret;
  int		i, b = 0, tmp = 0, inbb = 0, j;
  t_args	*args = 0, *it = 0;
  result	res = {0};

  va_start(ap, format);
  vasprintf(&str, format, ap);
  for (i = 0; str[i] != 0; i++)
    {
      if (str[i] == '{')
	{
	  if ((i > 0 && str[i - 1] != '\\') || (i == 0))
	    {
	      inbb = i;
	      in_b = 42;
	    }
	  else if (i != 0)
	    {
	      push(0, b, i - 1);
	      b = i;
	    }
	}
      else if (in_b)
	{
	  if ((str[i] < '0' || str[i] > '9') && str[i] != '}')
	    in_b = 0;
	  else if (str[i] == '}')
	    {
	      tmp = atoi(&str[inbb + 1]);
	      if (args == 0 || tmp > args->index)
	      	{
	      	  for (j = (args == 0 ? 0 : args->index + 1); j <= tmp; j++)
		    {
		      it = alloca(sizeof(*args));
		      *it = (__typeof__(*args)){j, va_arg(ap, void *), args};
		      args = it;
		    }
	      	  it = args;
	      	}
	      else
		for (it = args; it != 0 && it->index != tmp; it = it->next);
	      if (it != 0)
	      	{
		  push(0, b, inbb);
		  push(it, 0, strlen(it->arg));
		  b = i + 1;
		  in_b = 0;
		}
	    }
	}
    }
  push_res(&res, (t_str[1]){0}, 0, b, i);
  ret = create_result(&res, str);
  va_end(ap);
  free(str);
  for (it = args; it != 0; it = it->next)
    free(it->arg);
  return ret;
}

char	*create_result(result *res, char *str)
{
  char	*ret;
  int	len = 0, i;
  t_str	*it;

  for (it = res->next; it != 0; it = it->next)
    len += (it->end - it->begin);
  ret = malloc(len + 1);
  ret[len] = 0;
  for (it = res->next; it != 0; (len -= (it->end - it->begin), it = it->next))
    for (i = 0; i < (it->end - it->begin); i++)
      ret[len - (it->end - it->begin) + i] = (&((it->node ? it->node->arg : str)[it->begin]))[i];
  return ret;
}

int	main()
{
  char	*obj1 = strdup("first"), *obj2 = strdup("second");
  char	*str = format("\\{Hello %s {1} {0} \\{0} {-1} {{0}}", "yolo", obj1, obj2);

  printf("%s\n", str);
  free(str);
}
