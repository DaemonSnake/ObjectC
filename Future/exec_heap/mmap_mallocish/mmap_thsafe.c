/*
 * Copyright (C) 2016  Bastien Penavayre
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <pthread.h>
#include <sys/mman.h>
#include <stdio.h>

struct page_mmap_list
{
    void *begin;
    unsigned short free_blocks;
    unsigned pages;
    struct page_mmap_list *next;
};

struct global_mmap_data
{
    struct page_mmap_list *begin;
    unsigned pages;
    unsigned page_size;
};

struct subpage_node //not a header, seperate list on different region of heap
{
    size_t size;
    char free;
    void *addr;
    struct subpage_node *end;
};

#if 0
//  Requester/Provider idea (difficult to implement)

routine(size)
{
    req = new_request(size);
    push_request(&req); //updates request minimum size
    while (!request_validated(&req))
    {
        for (chunk : get_thread_unique_page())
        {
            if (!chunk.freed)
                continue;
            //free flag alteration in this function for true
            if (remove_request_if_selfvalid_else_give(&chunk, &req))
                goto manage;
        }
    }
 manage:
    //an otherthread may have already (un)set permissions
    tryopen_permission(req.page);
    fill(req.data, size);
    tryclose_permission(req.page);
    return req.data;
}

#elif 0
//Inner thread pool
#elif 0
//MultiThread request, single thread use
#endif

static global_mmap_data data = { 0, 0 };

char *addr = 0;
static pthread_mutex_t data_edit_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void mmap_init()
{
    addr = mmap(0, 4000, PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    addr[0] = '\xc3';
    mprotect(addr, 4000, PROT_EXEC);
    printf("Init finished\n");
}

static char __data_edit_locked__ = 0;
static unsigned __nb_locked__ = 0;

void *mmap_stuff()
{
    pthread_mutex_lock(&data_edit_mutex);
    while (__nb_locked__ != 0)
        pthread_cond_wait(&cond, &data_edit_mutex);
    __data_edit_locked__ = 42;
    //
    mprotect(addr, 4000, PROT_WRITE);
    addr[0] = '\xc3';
    mprotect(addr, 4000, PROT_EXEC);
    //
    __data_edit_locked__ = 0;
    pthread_mutex_unlock(&data_edit_mutex);
    return 0;
}

static __thread char _thread_has_locked_ = 0;
static pthread_mutex_t locking_func_mutex = PTHREAD_MUTEX_INITIALIZER;

void locking()
{
    if (pthread_mutex_trylock(&data_edit_mutex) == 0)
        _thread_has_locked_ = 42;
    else
    {
        if (__data_edit_locked__)
        {
            pthread_mutex_lock(&data_edit_mutex);
            _thread_has_locked_ = 42;
        }
    }
    pthread_mutex_lock(&locking_func_mutex);
    __nb_locked__++;
    pthread_mutex_unlock(&locking_func_mutex);
}

void unlocking()
{
    if (_thread_has_locked_)
        pthread_mutex_unlock(&data_edit_mutex);
    pthread_mutex_lock(&locking_func_mutex);
    __nb_locked__--;
    pthread_mutex_unlock(&locking_func_mutex);
    pthread_cond_broadcast(&cond);
    _thread_has_locked_ = 0;
}
