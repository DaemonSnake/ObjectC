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

#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static void *__this__ = 0;

void *push_this(void *this)
{
    __this__ = this;
    this += sizeof(void *);
    return (*(void **)this);
}

void *__get_this__()
{
    return __this__;
}

void *(*return_func(void *addr))()
{
#if (ULONG_MAX == UINT_MAX)
# define PRE_MOV_OP "\x48"
# define OFFSET 1
#else
# define PRE_MOV_OP
# define OFFSET 0
#endif
    char *exec = mmap(NULL, 23,
                      PROT_WRITE|PROT_EXEC,
                      MAP_ANON|MAP_PRIVATE, -1, 0);
    unsigned i = 0;
    char *f = (void *)push_this;

    i = OFFSET + 1;
    strncpy(exec, PRE_MOV_OP "\xbf", i); //mov $0, %rdi
    strncpy(exec + i, (void *)&addr, sizeof(void *));
    i += sizeof(void *);
    strncpy(exec + i, PRE_MOV_OP "\xba", OFFSET + 1); //mov $0, %rdx
    i += OFFSET + 1;
    strncpy(exec + i, (void *)&f, sizeof(void *));
    i += sizeof(void *);
    strncpy(exec + i, "\xff\xd2", 2); //callq *%rdx
    i += 2;
    exec[i] = 0xc3;
    mprotect(exec, 23, PROT_READ|PROT_EXEC);
    return (void *)exec;
    #undef PRE_MOV_OP
    #undef OFFSET
}
