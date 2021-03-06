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
#include "Debug.h"

static __thread int index = 0;

new_tor(Debug, ctor)
{
  superCtor(Object, ctor);
  $.index = ++index;
  printf("[Debug]Birth of %d\n", $.index);
  $.var = 42;
}

new_tor(Debug, dtor)
{
  printf("[Debug]Death of %d\n", $.index);
  superDtor();
}

void	new_method(Debug, print)
{
  printf("This is %p %d\n", this, $.var);
}

new_def_axors(Debug, var, get);

new_axor(Debug, var, int var)
{
    if (var == 0)
        return ;
    printf("[Debug]Update value from %d to %d\n", $.var, var);
    $.var = var;
}

implement(Debug, Object, I)
{
  printf("Debug Class type Operational!\n");
}
