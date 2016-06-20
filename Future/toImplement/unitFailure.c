#include <stdio.h>

#ifndef UNITTEST
# define UNITTEST 0
#endif

#define paste(x, y) paste2(x, y)
#define paste2(x, y) x ## y

#define unit_test()                                                     \
    __attribute__((always_inline))                                      \
    inline char paste(__unit_test_, __LINE__)();                        \
                                                                        \
    __attribute__((constructor))                                        \
    static inline void paste(__unit_test_caller_, __LINE__)()           \
    {                                                                   \
        if (UNITTEST && !paste(__unit_test_, __LINE__)())               \
            fprintf(stderr,                                             \
                 "[Error : UnitTest failed] in file : %s at line %d\n", \
                    __FILE__, __LINE__);                                \
    }                                                                   \
                                                                        \
    __attribute__((always_inline))                                      \
    inline char paste(__unit_test_, __LINE__)()

unit_test()
{
    return 0;
}

int main()
{
}
