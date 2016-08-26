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

#include "ObjectC.h"

class(String, Object)
{
  char *c_str;
  unsigned long	length;
};

virtual(String)
{
  const char	*method(c_str)();
  unsigned long	method(size)();
  char		method(get)(int);
  char		method(set)(int, char);
  /* 
     --ToDo--
  String	method(copy);
  String	method(subStr, int, int);
  String	method(opEq, const char *);
  char		method(isEq, const char *);
  void		method(replace, const char *to, const char *whith);
  */
};

new_tor(String, ctorS, const char *);

end_decl(String);

yields(char) new_foreach(String)
{
    for (int i = 0; i < (int)$.length; i++)
        yield($.c_str[i]);
    yield_break(char);
}
