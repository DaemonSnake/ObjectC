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
/* Header */

typedef struct unit_failure unit_failure;

struct  	unit_failure
{
  const char	*what;
  const char	*file;
  const char	*function;
  int		line;
  char		active;
};

#define UnitFailed(name, ...) /* EXIT_CODE is the last arg (1 as default)*/ \
  if (unit_ok())							\
    for (unit_failure name = get_unit(); ; exit((1, ##__VA_ARGS__)))	\

#define push_failure(what)						\
  __push_failure((unit_failure){ what, __FILE__, __FUNCTION__, __LINE__, 42 })

#define new_unit(name)                                          \
    __attribute__((constructor, no_instrument_functions))       \
    void name()

void		__push_failure(unit_failure);
int		unit_ok();
const
unit_failure	get_unit();
void		exit(int);

/* Source */

static
unit_failure	__unit_failure = {0};

void		__push_failure(unit_failure new_val)
{
  __unit_failure = new_val;
}

int		unit_ok()
{
  return __unit_failure.active;
}

const unit_failure	get_unit()
{
  return __unit_failure;
}

/* EXAMPLE */

int printf(const char *, ...);

new_unit(test)
{
  push_failure("Lol");
}

int		main()
{
  UnitFailed(e) {
    printf("Error exiting!\n");
    printf("In file %s in function %s at line %d\n", e.file, e.function, e.line);
  }
  printf("Worked\n");
}
