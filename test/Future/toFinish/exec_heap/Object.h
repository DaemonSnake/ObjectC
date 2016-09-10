/*
** Object.h for  in /home/penava_b/perso/Obj/Obj4/Future/head_func
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Fri May 27 02:51:15 2016 penava_b
** Last update Fri May 27 02:52:42 2016 penava_b
*/

#pragma once

typedef struct Object Object;

struct Object
{
    Object *this;
    struct virtual
    {
        Object *(*print)(Object *);
    }           *_virtual;
    struct virtual *(*_getV)();
};

#define $M(name, ...) _getV()->name(__get_this__(), ##__VA_ARGS__)

void *__get_this__();
void *return_func(void *);
