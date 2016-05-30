/*
** test.c for  in /home/penava_b
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Thu May  5 17:34:45 2016 penava_b
** Last update Mon May 30 19:19:23 2016 penava_b
*/

#include "yield.h"

int my_setjmp(generator *this_gen)
{
    if (!this_gen)
        return 0;
    this_gen->label = __builtin_return_address(0);
    this_gen->stop = 0;
    return 42;
}
