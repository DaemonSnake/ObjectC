/*
** test.c for  in /home/penava_b
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sat May 28 11:51:06 2016 penava_b
** Last update Sat May 28 15:32:55 2016 penava_b
*/

#include <stdio.h>
#include "inc.h"

typedef struct String *String;
struct String
{
    struct Object;
    const char *str;
    unsigned length;
};

String new_string(const char *str)
{
    String tmp = gc_new(sizeof(struct String));

    tmp->str = str;
    tmp->length = strlen(str);
    return tmp;
}

void print(String str)
{
    printf("%s\n", str->str);
}

int main()
{
    String _var(tmp, new_string("Hello"));

    print(tmp);
    tmp = new_string("Yolo");
    print(tmp);
    print(new_string("third string") /* here */);
    /* ->$M(move) => would make this string be deleted in print*/
}
