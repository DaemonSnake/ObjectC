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
#include <string.h>
#include <stdlib.h>

#include "ObjectC/String.h"

new_tor(String, ctor)
{
  superCtor(Object, ctor);
  $.c_str = 0;
  $.length = 0;
}

new_tor(String, ctorS, const char *str)
{
  superCtor(Object, ctor);
  $.length = strlen(str);
  $.c_str = malloc($.length + 1);
  if (!$.c_str)
    return ((void)($.length = 0)); //Throw badalloc exception
  memcpy($.c_str, str, $.length);
  $.c_str[$.length] = 0;
}

new_tor(String, dtor)
{
  free($.c_str);
  superDtor();
}

const char	*new_method(String, c_str)
{
  return $.c_str;
}

size_t		new_method(String, size)
{
  return $.length;
}

char		new_method(String, get, int i)
{
  if (!$.length || !$.c_str)
    return 0;
  return $.c_str[i];
}

char		new_method(String, set, int i, char newVal)
{
  char		tmp;

  if (!$.length || !$.c_str)
    return 0;
  tmp = $.c_str[i];
  $.c_str[i] = newVal;
  return tmp;
}

const char	*new_method(String, toString)
{
  return $.c_str;
}

implement(String, Object)
{
  //global ctor of String class
}
