#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *func()
{
    return (void *)0x424345;
}

void f()
{
}

int main()
{
    char *exec = mmap(NULL, 32,
                      PROT_READ|PROT_WRITE|PROT_EXEC,
                      MAP_ANON|MAP_PRIVATE, -1, 0);
    /* void *fc = f; */
    /* char *fstr = (void *)&fc; */

    /* snprintf(exec, 12, "\xc3"); */
    /* sprintf(exec, "\x48\xc7\xc0%.4s\xc3", "\x45\x43\x42\x00"); */
    sprintf(exec, "\xc3");
    printf("%p\n", exec);
    void *ret = ((void *(*)())exec)();
}
