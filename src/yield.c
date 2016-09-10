/*
  Copyright (c) 2015 Bastien Penavayre

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
#include "ObjectC/language/yield.h"
#include <stdio.h>
#include <stdlib.h>

static __thread generator *__gen__ = 0;
static __thread char prevent_cleanup_vars = 0;

static void            __yield_cleanup_attribute_switch()
{
    prevent_cleanup_vars ^= 42;
}

int                     __yield_get_block_cleanup_attribute_switch()
{
    return prevent_cleanup_vars;
}

static void abort_if_bad(void *caller_id, const char *function_name)
{
    if (!__gen__)
    {
        fprintf(stderr, "[YIELD_ERROR]: '%s' wasn't called using for_yield.\n\
[YIELD_ERROR]: Either remove yield or add for_yield in the parent function\n", function_name);
        abort();
    }
    if (caller_id != __gen__->id)
    {
        fprintf(stderr, "[YIELD_ERROR]: trying to yield in incompatible function : %s\n", function_name);
        fprintf(stderr, "[YIELD_ERROR]: To correct this replace the return type of this function with yieds(type)\n");
        fprintf(stderr, "[YIELD_EXAMPLE]:\n");
        fprintf(stderr, "from:  int function() {}\n");
        fprintf(stderr, "to:    yields(int) function() {}\n");
        abort();
    }
}

int __yield_setjmp(void *caller_id, const char *function_name)
{
    abort_if_bad(caller_id, function_name);
    __yield_cleanup_attribute_switch();
    __gen__->label = __builtin_return_address(0);
    __gen__->stop = 0;
    return 42;
}

void __yield_postjump()
{
    if (!__gen__)
        return ;
    __gen__->stop = 42;
    __gen__->label = 0;
}

generator *__yield_get_generator()
{
    return __gen__;
}

generator *__yield_update_generator(generator *val)
{
    __gen__ = val;
    return __gen__;
}

int __yield_continue(void *holder)
{
    ((generator**)holder)[2] = __gen__;
    __gen__ = ((generator**)holder)[0];
    __yield_cleanup_attribute_switch();
    return ((((generator**)holder)[1])->label != 0 && !(((generator**)holder)[1])->stop);
}
