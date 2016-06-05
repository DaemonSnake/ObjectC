/*
** test.c for  in /home/penava_b
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sat May 21 11:55:59 2016 penava_b
** Last update Thu Jun  2 18:39:59 2016 penava_b
*/

#include "lang_header.h"
#include <stdio.h>

class(String, Object)
{
    int i;
    virtual {
        void method(print, String *);
    };
};

end_decl(String);

implement(String)
{
    printf("Building String type\n");
}

void new_method(String, print, String *i)
{
}

int main()
{
}
