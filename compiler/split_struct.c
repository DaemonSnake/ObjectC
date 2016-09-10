#include "lang_header.h"
#undef virtual

#define IFDEF(name, do)                         \
    __NL__                                      \
    __HASH_WORD__ ifdef name __NL__             \
    do __NL__                                   \
    __HASH_WORD__ endif __NL__

#define CALL_MACRO(name, args...) name(args)

#define call_virtual(line)                                              \
    struct CLASS(pre_virtual__ ## line)                                 \
    {                                                                   \
        IFDEF(partial_virtual, partial_virtual());                      \
    };                                                                  \
                                                                        \
    __CREATE_MACRO__(partial_virtual,                                   \
                     struct CLASS(pre_virtual__ ## line);               \
                     struct CLASS(virtual__ ## line);)                  \
                                                                        \
    struct CLASS(virtual__ ## line)

#define virtual() CALL_MACRO(call_virtual, __LINE__)

class(S, Object)
{
    virtual()
    {
    };

    /*
    member()
    {
        int i axors(set, get);
        int public_var(i, set, get);
        // ->: i; }; virtual() { axors(typeof(i), set, get); }; member() {
    }
    */

    virtual()
    {
    };
};

#define finalize_class()                                                \
    struct CLASS(virtual)                                               \
    {                                                                   \
        IFDEF(partial_virtual, partial_virtual());                      \
        __UNDEF_MACRO__(partial_virtual);                               \
    }

finalize_class();
