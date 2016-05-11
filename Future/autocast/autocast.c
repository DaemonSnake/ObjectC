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
//###########################

struct Object_Autocast
{
    char _Object_0[sizeof(void *) * 2]; //this + virtual
    char _Object_1[sizeof(struct __data_Object)]; //data for Object
    char _Objcet_2[sizeof(void *)]; // this_Object
};

struct Debug_Autocast
{
    char _Debug_3[sizeof(void *) * 2]; //this + virtual
    struct Object_Autocast; //get parent casts
    char _Debug_4[sizeof(void *)]; //this_Debug
    char _Debug_5[sizeof(void *)]; //this_I
    I; //type I
    /*
      char _Debug_(5+1)[sizeof(void *)];
      next_interface;
      ...
     */
    char _Debug_(n)[sizeof(struct __weak_data_Debug)];
};
