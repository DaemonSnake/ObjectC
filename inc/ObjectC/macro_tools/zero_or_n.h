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

/*Details */
#define __IMPLEMENT_COUNT__(_1, _2, N, ...) N
#define __MACRO_ARGUMENT_COUNT_EXTRACT__(arg...) __IMPLEMENT_COUNT__(0, ##arg, N, 0)

/*Usefull macros*/
#define ONE_OR_N(x, args...) __MACRO_ARGUMENT_COUNT_EXTRACT__(x)
#define PASTE_TOKENS_2(x, y) x ## y
#define PASTE_TOKENS(x, y) PASTE_TOKENS_2(x, y)
#define CALL_ZERO_OR_N(name, args_list, args...) PASTE_TOKENS(name, ONE_OR_N args_list)(args)
