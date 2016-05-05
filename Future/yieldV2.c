/*
** test.c for  in /home/penava_b
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sat Apr  2 09:49:17 2016 penava_b
** Last update Sat Apr 23 15:04:22 2016 penava_b
*/

int	printf(const char *, ...);

__thread
void	*__yield_func__ = 0;

typedef struct Gen
{
  void	*label;
  void	*func;
  int	alive;
}	Gen;

__attribute__((no_instrument_function))
void	__cyg_profile_func_enter(void *func, void *caller)
{
  Gen	*this;
  
  if (func != __yield_func__) {
    __yield_func__ = 0;
    return ;
  }
  __yield_func__ = 0;
  asm("mov 0x18(%%rbp), %0" : "=r"(this));
  if (this == 0)
      return ;
  if (!this->alive)
      {
	  //fill stack
	  //cleanup local nodes
	  asm("leaveq");
	  asm("leaveq");
	  asm("retq");
      }
  this->alive = 0;
  if (this->label != 0)
    {
	asm("leaveq");
	asm("add $0x8, %rsp");
	asm("jmpq *%rax");
    }
}

int	my_setjmp(Gen *this)
{
  this->label = __builtin_return_address(0);
  return 42;
}

#define yield(val)				\
  if (my_setjmp(this) == 42)			\
    {						\
      this->alive = 42;				\
      return val;				\
    }						\
  else						\
      this->label = 0;

#define for_yield(ret, func, ...)					\
    for (Gen *this_gen = (Gen[1]){0, 0, 42}; this_gen != 0; this_gen = 0) \
	for (typeof(func(this_gen, ##__VA_ARGS__)) ret =		\
		 ((__yield_func__ = func), func(this_gen, ##__VA_ARGS__)); \
	     (this_gen)->alive; ret = ((__typeof__(ret)(*)(Gen *))(__yield_func__ = func))(this_gen))

int	func(Gen *this)
{
  printf("this: %p\n", this);
  yield(42);
  printf("Yes?\n");
  return 0;
}

int	main()
{
  for_yield(i, func) {
    printf("Yielded : %d\n", i);
  }
}
