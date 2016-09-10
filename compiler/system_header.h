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

#ifndef __OBJECT_C_COMPILER__
#error Compiling using the non ObjectC wrapper of gcc
#endif

#define __HASH_WORD__ __NL__ #
#define __NL__ _Pragma("")

#define __CREATE_MACRO__(name, val, args...)      \
    __HASH_WORD__ ifdef name                      \
    __HASH_WORD__ undef name                      \
    __HASH_WORD__ endif                           \
    __HASH_WORD__ define name(args) val __NL__

#define __CREATE_MACRO_NF__(name, val)    \
    __HASH_WORD__ ifdef name              \
    __HASH_WORD__ undef name              \
    __HASH_WORD__ endif                   \
    __HASH_WORD__ define name val __NL__

#define __IF_DEF_ERROR__(name, errorM...)         \
    __HASH_WORD__ ifdef name                      \
    __HASH_WORD__ error errorM                    \
    __HASH_WORD__ endif __NL__

#define __UNDEF_MACRO__(name)             \
    __HASH_WORD__ ifdef name              \
    __HASH_WORD__ undef name              \
    __HASH_WORD__ endif __NL__    

#define __DEF_LOCK__(name, errorM...)           \
    __IF_DEF_ERROR__(name, errorM)              \
    __HASH_WORD__ define name __NL__
