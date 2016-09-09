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
#include "ObjectC.h"

const char *new_method(String, toString) //Bad override
{
    (void)this;
    return 0;
}

yields(String) yieldList()
{
    I _var(Debug, tmp, ctor) as(I);

    yield(new(String, ctorS, "First yield"));
    yield(new(String, ctorS, "Second yield"));
    yield(new(String, ctorS, "Last yield"));
    yield_break(String);
}

void		yieldTest()
{
    printf("YIELD::\n");
    for_yield(str, yieldList())
    {
        printf("Yield2 : '%s'\n", M(str, c_str));
        delete(str);
    }
}

void		type(void)
{
    Object	tmp;

    printf("TYPE::\n");
    tmp = static_cast(Object, new(String, ctor));
    printf("%s\n", M(tmp, getType)->name);
    if (isInstanceOf(String, tmp))
        printf("Is a String\n");
    delete(tmp);
    tmp = new(Object, ctor);
    if (isInstanceOf(String, tmp))
        printf("Will not work!\n");
    delete(tmp);
}

void		new_delete(void)
{
    Object	tmp;
    I		tmp2;

    printf("NEW DELETE::\n");
    delete(new(String, ctorS, "Hello"));
    tmp = static_cast(Object, new(String, ctorS, "Lol"));
    tmp2 = new(Debug, ctor) as(I);
    delete(tmp, tmp2);
}

void		invoke_test(void)
{
    const void  *tmp = new(String, ctorS, "Invoke print this");
    char	*method(c_str)();
  
    printf("INVOKE::\n");
    try {
        printf("%s\n", invoke(char *, tmp, "c_str"));
        printf("%s\n", invoke(char *, tmp, "lol"));
    } catch(String, exp) {
        printf("%s\n", M(exp, c_str));
    }
    if ((c_str = getMethod(tmp, "c_str")) != NULL)
        printf("Second invoke : %s\n", invokeM(c_str, tmp));
    delete(tmp);
}

void	string_test()
{
    String _def(String, tmp1), _var(String, tmp, ctorS, "Hello");

    printf("STRING TEST::\n");
    printf("%s\n", M(tmp, c_str));
}

void		throwing()
{
    String _var(String, tmp, ctorS, "Not a leak");
  
    try {
        try {
            printf("Does not except!\n");
        }
        finally {
            printf("Is called anyway.\n");
            throw(String, ctorS, "Throwing");
        }
    }
    finally {
        printf("Is going to be deleted : %p of value '%s'\n", tmp, M(tmp, c_str));
        return ;
    }
}

void		exceptions()
{
    printf("EXCEPTIONS::\n");
    try {
        throwing();
    } catch(String, tmp) {
        printf("Exception return : %s\n", M(tmp, c_str));
    }
}

void		dynamic_func(const I tmp)
{
    Debug      	tmp2 = dynamic_cast(Debug, tmp);
    Object	tmp3 = static_cast(Object, tmp2);

    ifIs(I, tmp3) {
        M(tmp3, print);
    }
    printf("Object:%p\nB:%p\n", tmp, tmp2);
    printf("Object vtable %p\n", tmp->_virtual);
    printf("Start vtable %p\n", tmp2->_virtual);
    M(tmp, print);
    M(tmp2, print);
}

void	castTest()
{
    Debug _def(Debug, tmp);

    printf("CAST::\n");
    printf("true:%p\n", tmp);
    dynamic_func(tmp as(I));
}

void	trace_back_test()
{
    printf("TRACEBACK::\n");
    try {
        throw(String, ctorS, "EXCEPTION!!");
    }
    finally {
        printf("traceback!\n");
    }
}

void	debug_printer(Debug tmp)
{
    printf("Debug object %p\n", tmp);
}

void	rvalue_test()
{
    printf("LEFT REFERENCE VALUE::\n");
    debug_printer(rvalue(Debug, ctor));
}

yields(int)	range(int begin, int end)
{
    char	sup = (end > begin);

    if (begin != end)
        for (int i = begin; (sup ? i < end : i > end + 1); i += (sup ? 1 : -1))
            yield(i);
    yield_break(int);
}

void	range_test()
{
    printf("RANGE TEST::\n");
    for_yield(i, range(0, 0)) {
        (void)i;
        fprintf(stderr, "Error if printed???\n");
    }
    for_yield(i, range(0, 10)) {
        printf("range value %d\n", i);
    }
    printf("\nBackward\n");
    for_yield(i, range(10, 0)) {
        printf("range value %d\n", i);
    }
}

void	loop_init_test()
{
    for (int i = 0; i < 5; i++)
    {
        Object _def(Debug, tmp) as(Object);
    }
}

void scope_test()
{
    printf("SCOPE TEST::\n");
    printf("begin of new scope\n");
    if (42)
    {
        Debug _def(Debug, tmp);
    }
    printf("end of new scope\n");
}

void foreach_test()
{
    printf("FOREACH TEST::\n");
    foreach(c, String, rvalue(String, ctorS, "Hello")) {
        printf("%c", (c <= 'z' && c >= 'a' ? (c + 'A' - 'a') : c));
    }
    printf("\n");
}

static struct Debug static_test;

Ginit(Debug, ctor, static_test)
{
    // gloabal post constructor of static_test
}

int	main()
{
    void	(*tests[])() = {
        castTest,
        string_test,
        yieldTest,
        exceptions,
        type,
        invoke_test,
        rvalue_test,
        range_test,
        loop_init_test,
        scope_test,
        foreach_test,
        trace_back_test
    };

    for (unsigned i = 0; i < sizeof(tests) / sizeof(void *); i++) {
        printf("\n");
        tests[i]();
    }
    return 0;
}
