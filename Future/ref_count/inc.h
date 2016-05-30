/*
** inc.h for  in /home/penava_b/perso/Obj/Obj4/Future/ref_count
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sat May 28 15:29:26 2016 penava_b
** Last update Sat May 28 15:35:03 2016 penava_b
*/

#pragma once

#include <string.h>

typedef struct Object *Object;
struct Object
{
};

#define _var(name, val) name = (gc_var_init((void *)&name), val)

void gc_var_init();
void *gc_new(size_t);
