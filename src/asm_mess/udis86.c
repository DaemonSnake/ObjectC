/* udis86 - libudis86/udis86.c
 *
 * Copyright (c) 2002-2013 Vivek Thampi
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 * 
 *     * Redistributions of source code must retain the above copyright notice, 
 *       this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright notice, 
 *       this list of conditions and the following disclaimer in the documentation 
 *       and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR 
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON 
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "udint.h"
#include "extern.h"
#include "decode.h"
#include <string.h>

static inline void ud_inp_init(struct ud *u);

/* =============================================================================
 * ud_init
 *    Initializes ud_t object.
 * =============================================================================
 */
extern void 
ud_init(struct ud* u)
{
  memset((void*)u, 0, sizeof(struct ud));
  u->dis_mode = 64;
  u->mnemonic = UD_Iinvalid;
  u->pc = 0;
  u->asm_buf = u->asm_buf_int;
  u->asm_buf_size = sizeof(u->asm_buf_int);
}

/* =============================================================================
 * ud_disassemble
 *    Disassembles one instruction and returns the number of 
 *    bytes disassembled. A zero means end of disassembly.
 * =============================================================================
 */
extern unsigned int
ud_disassemble(struct ud* u)
{
  int len;
  if (u->inp_end) {
    return 0;
  }
  if ((len = ud_decode(u)) > 0) {
    u->asm_buf[0] = '\0';
    ud_translate_intel(u);
  }
  return len;
}


/* =============================================================================
 * ud_opr_is_sreg
 *    Returns non-zero if the given operand is of a segment register type.
 * =============================================================================
 */
int
ud_opr_is_sreg(const struct ud_operand *opr)
{
  return opr->type == UD_OP_REG && 
         opr->base >= UD_R_ES   &&
         opr->base <= UD_R_GS;
}

/* =============================================================================
 * ud_lookup_mnemonic
 *    Looks up mnemonic code in the mnemonic string table.
 *    Returns NULL if the mnemonic code is invalid.
 * =============================================================================
 */
const char*
ud_lookup_mnemonic(enum ud_mnemonic_code c)
{
  if (c < UD_MAX_MNEMONIC_CODE) {
    return ud_mnemonics_str[c];
  } else {
    return NULL;
  }
}


/* 
 * ud_inp_init
 *    Initializes the input system.
 */
static inline void
ud_inp_init(struct ud *u)
{
  u->inp_hook      = NULL;
  u->inp_buf       = NULL;
  u->inp_buf_size  = 0;
  u->inp_buf_index = 0;
  u->inp_curr      = 0;
  u->inp_ctr       = 0;
  u->inp_end       = 0;
  UD_NON_STANDALONE(u->inp_file = NULL);
}

/* =============================================================================
 * ud_inp_set_buffer
 *    Set buffer as input.
 * =============================================================================
 */
void 
ud_set_input_buffer(register struct ud* u, const uint8_t* buf, size_t len)
{
  ud_inp_init(u);
  u->inp_buf = buf;
  u->inp_buf_size = len;
  u->inp_buf_index = 0;
}

/* vim:set ts=2 sw=2 expandtab */
