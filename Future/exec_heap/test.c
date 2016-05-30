/*
** test.c for  in /home/penava_b/perso/Obj/Obj4/Future/head_func
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Fri May 27 02:50:21 2016 penava_b
** Last update Fri May 27 22:10:08 2016 penava_b
*/

#include <stdio.h>
#include <sys/mman.h>
#include "Object.h"

Object *Object_print(Object *this)
{
    printf("Object of addr: %p\n", this);
    return this;
}

struct virtual Object_virtual =  { Object_print };

void Object_ctor(Object *this)
{
    this->this = this;
    this->_virtual = &Object_virtual;
    this->_getV = return_func(this);
}

void Object_dtor(Object *this)
{
    munmap(this->_getV, 36);
}

int main()
{
    Object *a = (Object[1]){0};

    Object_ctor(a);
    a->$M(print)->$M(print);
    /* Object_dtor(a); */
}
