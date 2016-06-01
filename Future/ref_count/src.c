/*
** src.c for  in /home/penava_b/perso/Obj/Obj4/Future/ref_count
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sat May 28 15:30:03 2016 penava_b
** Last update Wed Jun  1 15:53:38 2016 penava_b
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "inc.h"

struct var_list
{
    Object *var;
    unsigned level;
    struct var_list *next;
};

struct heap_list
{
    Object address;
    unsigned level;
    struct heap_list *next;
};

static __thread struct heap_list *heap_list = 0;
static __thread struct var_list *var_list = 0;
static __thread unsigned level = 0;

__attribute__((no_instrument_function))
void *gc_new(size_t size)
{
    struct heap_list *tmp = malloc(sizeof(struct heap_list));

    if (!tmp)
        return NULL;
    tmp->address = malloc(size);
    tmp->next = heap_list;
    tmp->level = level;
    heap_list = tmp;
    return tmp->address;
}

__attribute__((no_instrument_function))
void    gc_var_init(Object *var)
{
    struct var_list *tmp = malloc(sizeof(struct var_list));

    if (!tmp)
        return ;
    *var = 0;
    tmp->var = var;
    tmp->next = var_list;
    tmp->level = level;
    var_list = tmp;
}

__attribute__((no_instrument_function))
void __cyg_profile_func_enter(void *save_var, void *b)
{
    (void)save_var, (void)b;
    level++;
}

__attribute__((no_instrument_function))
void __cyg_profile_func_exit(void *save_var, void *save_return)
{
    struct var_list *tmp;

    asm("mov %%rbx, %0" : "=r"(save_return));
    level--;
    for (tmp = var_list; tmp != 0 && tmp->level > level; tmp = var_list)
    {
        var_list = tmp->next;
        free(tmp);
    }
    struct heap_list *prev = 0;
    for (struct heap_list *tmp = heap_list; tmp != 0 && tmp->level > level; tmp = save_var)
    {
        save_var = tmp->next;
        if (tmp->address == save_return)
            goto skip;
        for (struct var_list *tmp2 = var_list; tmp2 != 0; tmp2 = tmp2->next)
            if (*tmp2->var == tmp->address)
                goto skip;
        free(tmp->address);
        free(tmp);
        *(prev == NULL ? &heap_list : &prev->next) = save_var;
        continue;
    skip:
        (tmp->level > level ? tmp->level-- : 0);
        prev = tmp;
        break;
    }
}
