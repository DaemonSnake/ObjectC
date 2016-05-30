struct __private_Debug
{
    Debug *this;
    const struct __virtual_Debug *_virtual;
    struct __supers_data_Debug
    {
        struct __data_Object
        {
            Object *this_Object;
            char __private_Object[sizeof(struct __data_weak_Object)];
        };
        Debug *this_Debug;
        I *this_I;
        I *__true_this_I;
        struct __virtual_I *_virtual_I;
    };
    struct __weak_data_Debug
    {
        int var;
    };
};

struct Debug
{
    Debug *this;
    const struct __virtual_Debug *_virtual;
    struct __data_Debug
    {
        struct __supers_data_Debug
        {
            struct __data_Object
            {
                Object *this_Object;
                char __private_Object[sizeof(struct __data_weak_Object)];
            };
            Debug *this_Debug;
            I *this_I;
            I *__true_this_I;
            struct __virtual_I *_virtual_I;
        };
        char __private_Debug[sizeof(struct __weak_data_Debug)];
    };
};
