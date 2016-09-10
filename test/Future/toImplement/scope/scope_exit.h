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

#pragma once

#include <alloca.h>

struct exit_struct
{
    void *start;
    unsigned level;
    void *rbp;
    enum        {
        scope_failure_state = 0,
        scope_success_state,
        scope_exit_state
    } state;
    struct exit_struct *next;
};

__attribute__((always_inline, no_instrument_function))
inline void __force_exit_function()
{
    asm("retq");
}

#define scope(type)                                                     \
    for (; mysetjmp(__builtin_frame_address(0),                         \
                    (struct exit_struct[1]){0, 0, 0, scope_ ## type ## _state }) != 42; \
         __force_exit_function())                                       \
            for (;; __force_exit_function())

int mysetjmp(void *, struct exit_struct *);
void all_scopes_exit();
