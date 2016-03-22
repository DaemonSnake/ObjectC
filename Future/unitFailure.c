/*
** test.c for  in /home/penava_b
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Tue Mar 22 03:21:09 2016 penava_b
** Last update Tue Mar 22 04:15:08 2016 penava_b
*/

/* Header */

typedef struct unit_failure unit_failure;

struct  	unit_failure
{
  const char	*what;
  const char	*file;
  const char	*function;
  int		line;
  char		active;
};

#define UnitFailed(name, ...) /* EXIT_CODE is the last arg (0 as default)*/ \
  if (unit_ok())							\
    for (unit_failure name = get_unit(); ; exit((0, ##__VA_ARGS__)))	\

#define push_failure(what)						\
  __push_failure((unit_failure){ what, __FILE__, __FUNCTION__, __LINE__, 42 })

void		__push_failure(unit_failure);
int		unit_ok();
const
unit_failure	get_unit();
void		exit(int);

/* Source */

static
unit_failure	__unit_failure = {0};

void		__push_failure(unit_failure new_val)
{
  __unit_failure = new_val;
}

int		unit_ok()
{
  return __unit_failure.active;
}

const unit_failure	get_unit()
{
  return __unit_failure;
}

/* EXAMPLE */

int printf(const char *, ...);

__attribute__((constructor))
void		unit_test()
{
  push_failure("Lol");
}

int		main()
{
  UnitFailed(e) {
    printf("Error exiting!\n");
    printf("In file %s in function %s at line %d\n", e.file, e.function, e.line);
  }
  printf("Worked\n");
}
