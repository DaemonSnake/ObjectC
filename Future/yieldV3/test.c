/*
** test.c for  in /home/penava_b/perso/C/CYield2
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Thu May  5 19:16:40 2016 penava_b
** Last update Mon May 30 19:23:41 2016 penava_b
*/

#include "yield.h"
#include <stdio.h>

yields(int) range(int b, int e, generator *_gen_)
{
    for (int i = b; i != e; i += (b < e ? 1 : -1))
        yield(i);
    yield_break(int);
}

yields(int) squareRange(generator *_gen_, int b, int e)
{
    for (int i = b; i != e; i += (b < e ? 1 : -1))
    {
        for_yield(ret, range(i, e, this_gen))
            yield(ret);
        printf("\n");
    }
    yield_break(int);
}

int main()
{
    for_yield(i, range(0, 5, this_gen)) {
        printf("%d\n", i);
    }
    printf("\n");
    for_yield(i, range(5, 0, this_gen)) {
        printf("%d\n", i);
    }
    printf("\n");
    for_yield(i, squareRange(this_gen, 0, 2))
        printf("%d\n", i);
    return 0;
}
