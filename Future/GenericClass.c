/*
** GenericClass.c for  in /home/penava_b/perso/Obj/Obj4/Future
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Tue Jan 26 11:30:13 2016 penava_b
** Last update Tue Jan 26 12:00:29 2016 penava_b
*/

struct	Type
{
  const char *name;
  unsigned long size;
};

typedef struct Object Object;
struct	Object
{
  struct	__virtual_Object {}
    *_virtual;
  struct Type _type;
};

#define class(name)				\
  typedef struct name name;			\
						\
  struct	__data_ ## name			\

#define virtual(name)				\
  struct	__virtual_ ## name

#define end_decl(name)				\
  struct name					\
  {						\
    struct __virtual_ ## name *_virtual;	\
    struct Type _type;				\
    struct __data_ ## name;			\
  };

#define method(name, ...) (*name)(void *this, ##__VA_ARGS__)

#define generic(T) struct Type __generic_ ## T;

#define getGeneric(name) $.__generic_ ## name

class(String)
{
  generic(T);
  generic(V);
};

virtual(String)
{
  void	method(test, Object *var);
};

end_decl(String);

void		test(String *this, Object *var)
{
  if (__isinstanceof(var, getGeneric(T)))
    {
    }
}

virtual(String) _virtual = {};

int	main()
{
}
