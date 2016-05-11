/*
** test.c for  in /home/penava_b/perso/Obj/Obj4/Future/compiler
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Wed May 11 02:12:22 2016 penava_b
** Last update Wed May 11 03:11:05 2016 penava_b
*/

#include <stdio.h>

#define new_pragma_string(data) ObjectC(#data)
#define to_string2(data) #data
#define to_string(data) to_string2(data)
#define to_pragma(string) _Pragma(string)

to_pragma(to_string(new_pragma_string(yolo)))

int main()
{
    printf("Hello\n");
    return 0;
}
