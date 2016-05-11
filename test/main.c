/*
** main.c for  in /home/penava_b/perso/test/Obj4
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sat Dec 12 23:36:57 2015 penava_b
** Last update Wed May 11 01:36:34 2016 penava_b
*/

#include <stdio.h>
#include "Debug.h"

const char *new_method(String, toString) //Bad override
{
    (void)this;
    return 0;
}

String	*yieldList(Generator *this)
{
    initYield();
    I _var(Debug, tmp, ctor) as(I);

    yield(new(String, ctorS, "First yield"));
    yield(new(String, ctorS, "Second yield"));
    return new(String, ctorS, "After last yield");
}

void		yieldTest()
{
    printf("YIELD::\n");
    for_yield(str, yieldList)
        {
            printf("Yield2 : '%s'\n", M(str, c_str));
            delete(str);
        }
}

void		type(void)
{
    Object	*tmp;

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
    Object	*tmp;
    I		*tmp2;

    printf("NEW DELETE::\n");
    delete(new(String, ctorS, "Hello"));
    tmp = static_cast(Object, new(String, ctorS, "Lol"));
    tmp2 = new(Debug, ctor) as(I);
    delete(tmp, tmp2);
}

void		invoke_test(void)
{
    const void   	*tmp = new(String, ctorS, "Invoke print this");
    char		*method(c_str);
  
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

void		dynamic_func(const I *tmp)
{
    Debug      	*tmp2 = dynamic_cast(Debug, tmp);
    Object	*tmp3 = static_cast(Object, tmp2);

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

void	debug_printer(Debug *tmp)
{
    printf("Debug object %p\n", tmp);
}

void	rvalue_test()
{
    printf("LEFT REFERENCE VALUE::\n");
    debug_printer(rvalue(Debug, ctor));
}

Debug	return_instance_debug()
{
    Debug	_def(Debug, tmp);

    printf("begining of returning function\n");
    printf("before return\n");
    axM(tmp, var, 84);
    printf("Get data %d\n", axM(tmp, var));
    return stdmove(tmp);
}

void	return_object_test()
{
    printf("RETURN OBJECT BY VALUE::\n");
    printf("Return object %p\n", retvalue(return_instance_debug()));
}

int	range(Generator *this, int begin, int end)
{
    int  	i;
    char	sup = (end > begin);

    initYield();
    if (begin == end)
        yield_break;
    for (i = begin; (sup ? i < end - 1 : i > end + 1); i += (sup ? 1 : -1))
        yield(i);
    return i;
}

void	range_test()
{
    printf("RANGE TEST::\n");
    for_yield(i, range, 0, 0) {
        fprintf(stderr, "Error if printed???\n");
    }
    for_yield(i, range, 0, 10) {
        printf("range value %d\n", i);
    }
    printf("\nBackward\n");
    for_yield(i, range, 10, 0) {
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

static Debug static_test;

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
        return_object_test,
        range_test,
        loop_init_test,
        trace_back_test
    };

    for (unsigned i = 0; i < sizeof(tests) / sizeof(void *); i++) {
        printf("\n");
        tests[i]();
    }
    return 0;
}
