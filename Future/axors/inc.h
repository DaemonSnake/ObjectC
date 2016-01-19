/*
** inc.h for  in /home/penava_b/perso/Obj/Obj4/Future/axors
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Tue Jan 19 14:28:21 2016 penava_b
** Last update Tue Jan 19 15:34:51 2016 penava_b
*/

#pragma once

#define __axor_get(type, name) type (*get_ ## name)(void *);
#define __axor_(type, name)
#define __axor_set(type, name) void (*set_ ## name)(void *, type name);
#define __launch_axor(type, name, x, ...) __axor_ ## x(type, name) __axor_ ## __VA_ARGS__(type, name)
#define axor(type, name, ...)  __launch_axor(type, name, __VA_ARGS__)

#define __new_axor_get(class, name)					\
  typeof(((class *)0)->name) class ## _ ## get_ ## name(class *arg)	\
  {									\
    return arg->name;							\
  }

#define __new_axor_set(class, name)					\
  void class ## _ ## set_ ## name(class *arg,				\
				 typeof(((class *)0)->name) name)	\
  {									\
    arg->name = name;							\
  }

#define __new_axor_(class, name)
#define __launch_new_axors(class, name, x, y...) __new_axor_ ## x(class, name) __new_axor_ ## y(class, name)
#define new_axors(class, name, x...) __launch_new_axors(class, name, x)

#define M(this, name, ...) ((this)->_virtual->name(this, ##__VA_ARGS__))
#define __axor_call_0(var, name, ...) M(var, get_ ## name)
#define __axor_call_1(var, name, arg) M(var, set_ ## name, arg)

#define CNV_ARGS(_0, _1, _2, N, ...) N
#define VA_NARGS(...) CNV_ARGS(__VA_ARGS__, 2, 1, 0)
#define PASTE2(x, y) x ## y
#define PASTE(x, y) PASTE2(x, y)
#define axM(this, name, ...) PASTE(__axor_call_, VA_NARGS(lol, ##__VA_ARGS__))(this, name, ##__VA_ARGS__)
