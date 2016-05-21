/*
** test.c for  in /home/penava_b
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sat May 21 11:55:59 2016 penava_b
** Last update Sat May 21 14:21:08 2016 penava_b
*/

#define __HASH_WORD__ #
#define __NL__ /*
*/
#define __CREATE_MACRO__(symb, name, val, args...)      \
    symb ifdef name __NL__                              \
    symb undef name __NL__                              \
    symb endif __NL__                                   \
    symb define name(args) val __NL__

__CREATE_MACRO__(#, __POST_COMP_GLUE__, __POST_COMP_GLUE2__(x, y), x, y)
__CREATE_MACRO__(#, __POST_COMP_GLUE2__, x ## y, x, y)

#define class(name)                                            \
    __CREATE_MACRO__(__HASH_WORD__, CLASS, name)               \
                                                               \
    typedef struct name name; __NL__                           \
                                                               \
    struct name

#define virtual                                                 \
    }; __NL__                                                   \
                                                                \
       struct __POST_COMP_GLUE__(CLASS(),  _virtual)            \
    {                                                           \
        struct                                                  \

#define method(name, ...) (*name)(CLASS() * const this, ##__VA_ARGS__)

class(String)
{
    int i;
    virtual {
        void method(print);
    };
};

int main()
{
}
