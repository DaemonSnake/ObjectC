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
