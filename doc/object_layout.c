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
