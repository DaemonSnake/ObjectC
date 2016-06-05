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
#include <stdio.h>
#include <stdlib.h>

struct scope_list
{
    void (*func)();
    unsigned level;
    struct scope_list *next;
};

static __thread unsigned level = 0;
static __thread struct scope_list *_list = 0;

__attribute__((no_instrument_function))
void push_scope_exit(void (*func)())
{
    struct scope_list *tmp;

    tmp = malloc(sizeof(struct scope_list));
    tmp->func = func;
    tmp->next = _list;
    tmp->level = level;
    _list = tmp;
}

__attribute__((no_instrument_function))
void __cyg_profile_func_enter(void *a, void *b)
{
    (void)a, (void)b;
    level++;
}

__attribute__((no_instrument_function))
void __cyg_profile_func_exit(void *a, void *b)
{
    (void)b;
    level--;
    for (struct scope_list *tmp = _list; tmp != 0 && tmp->level > level; tmp = a)
    {
        a = tmp->next;
        tmp->func();
        free(tmp);
    }
}

#define __SCOPE_exit__(counter)                         \
    __attribute__((no_instrument_function))             \
    auto void __scope_exit_function_ ## counter();      \
    push_scope_exit(__scope_exit_function_ ## counter); \
    auto void __scope_exit_function_ ## counter()

#define __CALL__(macro, val) macro(val)

#define scope(name)                                     \
    __CALL__(__SCOPE_ ## name ## __, __COUNTER__)

    int main()
    {
        scope(exit)
        {
            printf("At end\n");
        }
        scope(exit)
        {
            printf("After first end\n");
        }
        printf("Before\n");
    }
