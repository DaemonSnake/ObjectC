#pragma once

#include <pthread.h>
#include <unistd.h>

struct page_mmap_list;
struct subpage_head;

struct global_mmap_data
{
    struct page_mmap_list *front;
    unsigned pages;
    unsigned page_size;
    pthread_mutex mu;
};

struct page_mmap_list
{
    struct subpage_head *begin;
    pthread_mutex mu;
    struct page_mmap_list *next;
};

struct subpage_head
{
    size_t size;
    char free;
};

#define m_a(action, x) pthread_mutex_ ## action(x->mu)
