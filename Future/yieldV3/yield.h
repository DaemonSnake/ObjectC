/*
** yield.h for  in /home/penava_b/perso/C/CYield2
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Thu May  5 19:15:46 2016 penava_b
** Last update Mon May 30 19:19:28 2016 penava_b
*/

#pragma once

/* TYPE */
typedef struct
{
    void *label;
    int stop;
}       generator;

/* FUNCTIONS */
int my_setjmp(generator *);

__attribute__((always_inline))
inline void fgoto(generator *gen)
{
    asm("mov %0, %%rax":: "r"(gen->label));
    asm("jmpq *%rax");
}

/* MACROS */
#define for_yield(ret, call)                                            \
    for (generator *this_gen = (generator[1]){{0, 42}}; this_gen != 0; this_gen = 0) \
        for (typeof(call) ret = ({ call; }); (this_gen && !this_gen->stop); fgoto(this_gen))

#define yields(type) __attribute__((always_inline, no_instrument_function)) inline type

#define yield_break(type) return (type){0}

#define yield(val)                                      \
    if (my_setjmp(_gen_) == 42)                         \
        return val;                                     \
    else                                                \
        {                                               \
            if (_gen_)                                  \
                {                                       \
                    _gen_->label = 0;                   \
                    _gen_->stop = 42;                   \
                }                                       \
        }
