static __thread char allow_cleanup = 42;

void dtor(void *arg)
{
    register const void *rbx asm("rbx");
    const void *ret = rbx;

    if (!allow_cleanup || *(void **)arg == 0 || *(void **)arg == ret)
        return ;
    printf("Dtor %p\n", arg);
    *(void **)arg = 0;
}

__attribute__((no_instrument_function))
void __cyg_profile_func_exit(void *a, void *b)
{
    (void)a, (void)b;
}

void *test_func()
{
    void *i __attribute__((cleanup(dtor))) = &i;

    return i;
}

int main()
{
    test_func();
}
