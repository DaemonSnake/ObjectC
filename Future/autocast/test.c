/*
** test.c for  in /home/penava_b
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Wed May 11 01:37:33 2016 penava_b
** Last update Wed May 11 02:05:41 2016 penava_b
*/

struct A
{
    int j;
};

struct B
{
    int i;
    struct A;
};

struct B __tmp;
void *tmp = &__tmp;

int main()
{
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    struct A *tmp2 = ({
        __attribute__((always_inline))
        inline __typeof__(tmp2) __offset__(struct B *var) {
            return var;
        }
        __offset__((struct B *)tmp);
        });
}
