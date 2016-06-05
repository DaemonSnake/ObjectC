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
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

#define Method() (locking(), ((void(*)())addr)(), unlocking())

void mmap_init();
void mmap_stuff();
void locking();
void unlocking();

void *using_thread(void *arg)
{
    for (int i = 0; i < 100; i++)
    {
        if (random() % 2 == 0)
            Method();
        else
            mmap_stuff();
    }
    return 0;
}

int main()
{
    pthread_t th[100];

    srandom(time(0));
    mmap_init();
    for (int i = 0; i < sizeof(th) / sizeof(th[0]); i++)
        pthread_create(&th[i], NULL, using_thread, NULL);
    for (int i = 0; i < sizeof(th) / sizeof(th[0]); i++)
        pthread_join(th[i], NULL);
}
