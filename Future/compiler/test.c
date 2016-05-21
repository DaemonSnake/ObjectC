/*
** test.c for  in /home/penava_b
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sat May 21 11:55:59 2016 penava_b
** Last update Sat May 21 20:49:10 2016 penava_b
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

#define class(name, base, args...)                             \
    __CREATE_MACRO__(__HASH_WORD__, CLASS, name)               \
    __CREATE_MACRO__(__HASH_WORD__, name ## _SUPERS, args)     \
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

#define implement(name)                                         \
    struct name ## _virtual __global_vtable_ ## name = {0};     \
                                                                \
    __attribute__((constructor, no_instrument_function))        \
    static void __implement_ ## name ## _function(void)         \
    {                                                           \
        void __implement_user_ ## name ## _function(void);      \
        __implement_user_ ## name ## _function();               \
    }                                                           \
                                                                \
    inline void __implement_user_ ## name ## _function(void)

class(String, Object)
{
    int i;
    virtual {
        void method(print);
    };
};

implement(String)
{
    printf("Building String type\n");
}

int main()
{
}
