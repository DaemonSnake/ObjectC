/*
** test.c for  in /home/penava_b/perso/test
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Tue Jan 19 12:47:42 2016 penava_b
** Last update Tue Jan 19 13:16:11 2016 penava_b
*/

#define virtual(name)				\
  struct __virtual_ ## name

#define __axor_get(type, name) type (*get_ ## name)(void *);
#define __axor_(type, name)
#define __axor_set(type, name) void (*set_ ## name)(void *, type name);
#define __launch_axor(type, name, x, ...) __axor_ ## x(type, name) __axor_ ## __VA_ARGS__(type, name)
#define axor(type, name, ...)  __launch_axor(type, name, __VA_ARGS__)

virtual(String)
{
  axor(int, i, set, get);
  axor(double, j, get, set);
};

#define __new_axor_get(class, name)					\
  typeof(((class *)0)->name) class ## _ ## get ## name(void *arg)	\
  {									\
    return (typeof(((class *)0)->name)){0};				\
  }

#define __new_axor_set(class, name)					\
  void class ## _ ## set ## name(void *arg,				\
				 typeof(((class *)0)->name) name)	\
  {									\
    printf("setting variable!\n");					\
  }

#define __new_axor_(class, name)
#define __launch_new_axors(class, name, x, y...) __new_axor_ ## x(class, name) __new_axor_ ## y(class, name)  
#define new_axors(class, name, x...) __launch_new_axors(class, name, x)

typedef struct
{
  int	i;
}	String;

new_axors(String, i, get, set);

#define M(this, name)
#define getM(this, name) M(this, get_ ## name)
#define setM(this, name, arg) M(this, set_ ## name, arg)
