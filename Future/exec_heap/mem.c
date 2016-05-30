#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static void *__this__ = 0;

void *push_this(void *this)
{
    __this__ = this;
    this += sizeof(void *);
    return (*(void **)this);
}

void *__get_this__()
{
    return __this__;
}

void *(*return_func(void *addr))()
{
#if (ULONG_MAX == UINT_MAX)
# define PRE_MOV_OP "\x48"
# define OFFSET 1
#else
# define PRE_MOV_OP
# define OFFSET 0
#endif
    char *exec = mmap(NULL, 23,
                      PROT_WRITE|PROT_EXEC,
                      MAP_ANON|MAP_PRIVATE, -1, 0);
    unsigned i = 0;
    char *f = (void *)push_this;

    i = OFFSET + 1;
    strncpy(exec, PRE_MOV_OP "\xbf", i); //mov $0, %rdi
    strncpy(exec + i, (void *)&addr, sizeof(void *));
    i += sizeof(void *);
    strncpy(exec + i, PRE_MOV_OP "\xba", OFFSET + 1); //mov $0, %rdx
    i += OFFSET + 1;
    strncpy(exec + i, (void *)&f, sizeof(void *));
    i += sizeof(void *);
    strncpy(exec + i, "\xff\xd2", 2); //callq *%rdx
    i += 2;
    exec[i] = 0xc3;
    mprotect(exec, 23, PROT_READ|PROT_EXEC);
    return (void *)exec;
    #undef PRE_MOV_OP
    #undef OFFSET
}
