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

void Object_method(void *this)
{
    printf("%p\n", this);
}

struct VTable
{
    void (*method)(void *);
};

const struct VTable *vtable = (struct VTable[1]){Object_method};

struct Object
{
    const struct VTable *(*get_vtable)(char);
};

const struct VTable *get_vtable(char tmp)
{
    (void)tmp;
    return vtable;
}

static struct Object tmp = { get_vtable };

char lock()
{
    printf("LOCK\n");
    return 0;
}

void *unlock_get_this()
{
    printf("UNLOCK\n");
    return &tmp;
}

#define $M(method, args...) get_vtable(lock())->method(unlock_get_this(), ##args)

int main()
{
    tmp.$M(method);
    tmp.get_vtable(lock())->method(unlock_get_this());
}
