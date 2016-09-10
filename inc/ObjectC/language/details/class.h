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
#pragma once

/* axM() macro
   if 2 argument are given -> getter
   else -> setter
*/
#define __axor_call_0(var, name) M(var, get_ ## name)
#define __axor_call_N(var, name, args...) M(var, set_ ## name, ##args)

/* AXORS METHODS DECL */
#define __axor_get(type, name) type (*get_ ## name)(void *);
#define __axor_(type, name)
#define __axor_set(type, name) void (*set_ ## name)(void *, type name, ...);
#define __launch_axor(type, name, x, y...)      \
    __axor_ ## x(type, name)                    \
    __axor_ ## y(type, name)

/* method() macro 
   Adds 'void *' at the front of an argument list
*/
#define __ADD_THISP__(args...) (void *, ##args)
