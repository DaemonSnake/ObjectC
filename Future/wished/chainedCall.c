/*
** test.c for  in /home/penava_b
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Sat May 14 01:01:13 2016 penava_b
** Last update Sat May 14 01:08:47 2016 penava_b
*/

#define m(var, name, ...) (var)->_virtual->name(var, ##__VA_ARGS__)
#define $m(name, ...) ->_virtual->name(__tmp__, ##__VA_ARGS__)
#define $m2(name, ...) _virtual->name(__tmp__, ##__VA_ARGS__)


typedef struct Stream Stream;

void *__tmp__;

struct Stream
{
    struct virtualStream
    {
        Stream *(*give)(Stream *, char *);
    }   *_virtual;
};

Stream *give(Stream *this, char *arg)
{
    printf("%s\n", arg);
    __tmp__ = this;
    return this;
}

struct virtualStream _virtual = 
    {
        give
    };

int main()
{
    Stream tmp = { &_virtual };

    m(&tmp, give, "Hello")$m(give, "Yolo");
    m(&tmp, give, "Hello")->$m2(give, "Yolo");
}
