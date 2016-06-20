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

#include "scope_exit.h"

static __thread unsigned level = 0;
static __thread struct exit_struct *ge = 0;

__attribute__((no_instrument_function))
int mysetjmp(struct exit_struct *e)
{
    e->start = __builtin_return_address(0);
    e->level = level;
    e->next = ge;
    ge = e;
    return 42;
}

__attribute__((no_instrument_function))
void __cyg_profile_func_enter(void *arg, void *arg2)
{
    (void)arg, (void)arg2;
    level++;
}

static void empty_func()
{
}

__attribute__((no_instrument_function))
static void (*pop_node(int arg))()
{
    struct exit_struct *tmp = ge;

    ge = ge->next;
    if (arg)
        return tmp->start;
    return empty_func;
}

__thread int scope_current_state = scope_success_state;

__attribute__((no_instrument_function))
void __cyg_profile_func_exit(void *arg, void *arg2)
{
    (void)arg, (void)arg2;
    asm("leaveq");
    while (ge != 0 && ge->level >= level)
        pop_node(ge->state == scope_exit_state || ge->state == scope_current_state)();
    level--;
    asm("retq");
}

void bad_exit()
{
    scope_current_state = scope_failure_state;
}
