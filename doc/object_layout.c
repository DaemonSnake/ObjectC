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

/*
 * Object.h example
*/

//vtable
struct Object__virtual
{
    void (*dtor)(void *);
    const char *(*toString)(const void *);
    const Type *(*getType)(const void *);
};

//private type
struct Object__private
{
    Object *this;
    const struct Object__virtual *_virtual;
    Object *Object__this;
    struct Object__data_weak
    {
        const Type *__class_type;
    };
};

//public type
struct Object
{
    Object *this;
    const struct Object__virtual *_virtual;
    Object *Object__this;
    struct Object__data
    {
        Object *Object__this;
        char Object__private[sizeof(struct Object__data_weak)];
    };
};

/*
 * Debug.h example
*/

//I's vtable
struct I__virtual
{
  void (*print)(void *);
};

//Debug's vtable
struct Debug__virtual
{
    struct Debug__supers_virtual
    {
        struct Object__virtual;
        struct I__virtual;
    };
    struct Debug__weak_virtual
    {
        void (*set_var)(void *, int var);
        int (*get_var)(void *);;
    };
};

//private type
struct Debug__private
{
    Debug *this;
    const struct Debug__virtual *_virtual;
    struct Debug__supers_data
    {
        struct Object__data;
        Debug *Debug__this;
        I *I__this;
        I *I__true_this;
        struct I__virtual *I__virtual;
    };
    struct Debug__weak_data
    {
        int var;
        int index;
    };
};

//public type
struct Debug
{
    Debug *this;
    const struct Debug__virtual *_virtual;
    struct Debug__data
    {
        struct Debug__supers_data
        {
            struct Object__data;
            Debug *Debug__this;
            I *I__this;
            I *I__true_this;
            struct I__virtual *I__virtual;
        };    
        char Debug__private[sizeof(struct Debug__weak_data)];
    };
};
