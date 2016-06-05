/*
 * Copyright (C) 2016  Bastien Penavayre
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
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
