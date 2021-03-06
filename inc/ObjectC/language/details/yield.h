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

#if defined(__x86_64__)
__attribute__((always_inline, no_instrument_function))
inline void __yield_fgoto(generator *gen)
{
    asm("mov %0, %%rax":: "r"(gen->label));
    asm("jmpq *%rax");
}
#elif defined(__i386__)
__attribute__((always_inline, no_instrument_function))
inline void __yield_fgoto(generator *gen)
{
    asm("mov %0, %%eax":: "r"(gen->label));
    asm("jmp *%eax");
}
#elif defined(__arm__) //NEEDS TO BE CHECKED
__attribute__((always_inline, no_instrument_function))
inline void __yield_fgoto(generator *gen)
{
    asm("ldr r3, %0" :: "r"(gen->label));
    asm("mov pc, r3");
}
#else
# error "System not yet suported"
#endif
