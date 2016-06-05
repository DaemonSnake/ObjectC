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
#include "ObjectC/Exceptions.h"

const char	*new_method(Exception, what)
{
  return $.msg;
}

new_tor(Exception, ctor)
{
  superCtor(Object, ctor);
}

new_tor(Exception, ctorS, const char *str)
{
  superCtor(Object, ctor);
  if (str)
    {
      size_t	size;

      size = strlen(str);
      $.msg = malloc(size + 1);
      memcpy((void *)$.msg, str, size);
    }
  else
    $.msg = 0;
}

new_tor(Exception, dtor)
{
    free((void *)$.msg);
    superDtor();
}

new_tor(AllocFailed, ctor)
{
  superCtor(Exception, ctorS, "Allocation Failed");
}

new_tor(AllocFailed, dtor)
{
  superDtor();
}

new_tor(IsNotObject, ctor)
{
  superCtor(Exception, ctorS, "Is not an Object");
}

new_tor(IsNotObject, dtor)
{
  superDtor();
}
		     
implement(Exception, Object) {}
implement(AllocFailed, Exception) {}
implement(IsNotObject, Exception) {}
