/*
** main.c for  in /home/penava_b/perso/Obj/Obj4/Future/return_intercept
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Fri May 27 23:43:48 2016 penava_b
** Last update Fri May 27 23:53:07 2016 penava_b
*/

#include <stdio.h>

__attribute__((no_instrument_function))
void *alter_func(void *return_arg)
{
    printf("%p\n", return_arg);
    return (void *)0x4242;
}

__attribute__((no_instrument_function))
void __cyg_profile_func_exit(void *arg, void *arg2)
{
    void *return_arg;
    (void)arg, (void)arg2;

    asm("mov %%rbx, %0" : "=r"(return_arg));
    return_arg = alter_func(return_arg);
    //other code
    asm("mov %0, %%rbx" :: "r"(return_arg));
}

void *return_ff()
{
    return (void *)0x523;
}

void *return_f()
{
    return return_ff();
}

int main()
{
    return_f();
}
