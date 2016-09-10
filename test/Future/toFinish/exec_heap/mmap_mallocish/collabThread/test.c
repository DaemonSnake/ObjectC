#include "inc.h"

enum {
    false = 0,
    true
};

struct global_mmap_data global = {
    0,
    0,
    0
    PTHREAD_MUTEX_INIT
};

struct page_mmap_list *add_new_page()
{
    struct page_mmap_list *ret = malloc(sizeof(struct page_mmap_list));
        
    ret->begin = mmap(0, global.page_size, PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    ret->begin->size = 0;
    ret->begin->free = 42;
    ret->next = global.front;
    global.front = ret;
    return ret;
}

struct page_mmap_list *aquire_page(struct page_mmap_list *begin)
{
    struct page_mmap_list *node;

    m_a(lock, &global);
    if (begin == NULL)
    {
        if (global.page_size == 0)
            global.page_size = sysconf(_SC_PAGESIZE);
        node = global.front;
    }
    else
        node = begin;
    for (; node != 0 && m_a(try_lock, node) != 0);
    if (node == 0)
        node = add_new_page();
    m_a(unlock, &global);
}

void *alloc(size_t size)
{
    struct page_mmap_list *node = aquire_page(0);
}
