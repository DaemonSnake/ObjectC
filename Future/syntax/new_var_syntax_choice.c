void func(void *addr)
{
    printf("%p\n", addr);
}

#define create_macro(value...) (CALL, (void *)0, ##value)

int main()
{
    void *i =
#define CALL i = 0, func(&i)
        create_macro();
#undef CALL

    void *j =
#define CALL j = 0, func(&j)
        create_macro(&i);
#undef CALL
    
    void *k =
#define CALL k = 0, func(&k)
        create_macro() + 0x42;

    void *l = (l = 0, func(&l), l) + 0x42;

    //string _var(tmp)(new(string));
    //string _var(tmp)();
    ///////////////////////////////
    //string _var(tmp) + new(string);
    //string _var(tmp);
    
}
