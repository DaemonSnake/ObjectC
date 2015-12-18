/* udis86 - libudis86/syn-intel.c
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
#include "types.h"
#include "extern.h"
#include "decode.h"
#include "itab.h"
#include "syn.h"
#include "udint.h"

/* -----------------------------------------------------------------------------
 * Intel Register Table - Order Matters (types.h)!
 * -----------------------------------------------------------------------------
 */
const char* ud_reg_tab[] = 
{
  "al",   "cl",   "dl",   "bl",
  "ah",   "ch",   "dh",   "bh",
  "spl",  "bpl",    "sil",    "dil",
  "r8b",  "r9b",    "r10b",   "r11b",
  "r12b", "r13b",   "r14b",   "r15b",

  "ax",   "cx",   "dx",   "bx",
  "sp",   "bp",   "si",   "di",
  "r8w",  "r9w",    "r10w",   "r11w",
  "r12w", "r13w"  , "r14w",   "r15w",
  
  "eax",  "ecx",    "edx",    "ebx",
  "esp",  "ebp",    "esi",    "edi",
  "r8d",  "r9d",    "r10d",   "r11d",
  "r12d", "r13d",   "r14d",   "r15d",
  
  "rax",  "rcx",    "rdx",    "rbx",
  "rsp",  "rbp",    "rsi",    "rdi",
  "r8",   "r9",   "r10",    "r11",
  "r12",  "r13",    "r14",    "r15",

  "es",   "cs",   "ss",   "ds",
  "fs",   "gs", 

  "cr0",  "cr1",    "cr2",    "cr3",
  "cr4",  "cr5",    "cr6",    "cr7",
  "cr8",  "cr9",    "cr10",   "cr11",
  "cr12", "cr13",   "cr14",   "cr15",
  
  "dr0",  "dr1",    "dr2",    "dr3",
  "dr4",  "dr5",    "dr6",    "dr7",
  "dr8",  "dr9",    "dr10",   "dr11",
  "dr12", "dr13",   "dr14",   "dr15",

  "mm0",  "mm1",    "mm2",    "mm3",
  "mm4",  "mm5",    "mm6",    "mm7",

  "st0",  "st1",    "st2",    "st3",
  "st4",  "st5",    "st6",    "st7", 

  "xmm0", "xmm1",   "xmm2",   "xmm3",
  "xmm4", "xmm5",   "xmm6",   "xmm7",
  "xmm8", "xmm9",   "xmm10",  "xmm11",
  "xmm12",  "xmm13",  "xmm14",  "xmm15",

  "rip"
};


uint64_t
ud_syn_rel_target(struct ud *u, struct ud_operand *opr)
{
  const uint64_t trunc_mask = 0xffffffffffffffffull >> (64 - u->opr_mode);
  switch (opr->size) {
  case 8 : return (u->pc + opr->lval.sbyte)  & trunc_mask;
  case 16: return (u->pc + opr->lval.sword)  & trunc_mask;
  case 32: return (u->pc + opr->lval.sdword) & trunc_mask;
  default: UD_ASSERT(!"invalid relative offset size.");
    return 0ull;
  }
}


/*
 * asmprintf
 *    Printf style function for printing translated assembly
 *    output. Returns the number of characters written and
 *    moves the buffer pointer forward. On an overflow,
 *    returns a negative number and truncates the output.
 */
int
ud_asmprintf(struct ud *u, const char *fmt, ...)
{
  int ret;
  int avail;
  va_list ap;
  va_start(ap, fmt);
  avail = u->asm_buf_size - u->asm_buf_fill - 1 /* nullchar */;
  ret = vsnprintf((char*) u->asm_buf + u->asm_buf_fill, avail, fmt, ap);
  if (ret < 0 || ret > avail) {
      u->asm_buf_fill = u->asm_buf_size - 1;
  } else {
      u->asm_buf_fill += ret;
  }
  va_end(ap);
  return ret;
}


void
ud_syn_print_addr(struct ud *u, uint64_t addr)
{
  const char *name = NULL;
  if (u->sym_resolver) {
    int64_t offset = 0;
    name = u->sym_resolver(u, addr, &offset);
    if (name) {
      if (offset) {
        ud_asmprintf(u, "%s%+" FMT64 "d", name, offset);
      } else {
        ud_asmprintf(u, "%s", name);
      }
      return;
    }
  }
  ud_asmprintf(u, "0x%" FMT64 "x", addr);
}


void
ud_syn_print_imm(struct ud* u, const struct ud_operand *op)
{
  uint64_t v;
  if (op->_oprcode == OP_sI && op->size != u->opr_mode) {
    if (op->size == 8) {
      v = (int64_t)op->lval.sbyte;
    } else {
      UD_ASSERT(op->size == 32);
      v = (int64_t)op->lval.sdword;
    }
    if (u->opr_mode < 64) {
      v = v & ((1ull << u->opr_mode) - 1ull);
    }
  } else {
    switch (op->size) {
    case 8 : v = op->lval.ubyte;  break;
    case 16: v = op->lval.uword;  break;
    case 32: v = op->lval.udword; break;
    case 64: v = op->lval.uqword; break;
    default: UD_ASSERT(!"invalid offset"); v = 0; /* keep cc happy */
    }
  }
  ud_asmprintf(u, "0x%" FMT64 "x", v);
}


void
ud_syn_print_mem_disp(struct ud* u, const struct ud_operand *op, int sign)
{
  UD_ASSERT(op->offset != 0);
 if (op->base == UD_NONE && op->index == UD_NONE) {
    uint64_t v;
    UD_ASSERT(op->scale == UD_NONE && op->offset != 8);
    /* unsigned mem-offset */
    switch (op->offset) {
    case 16: v = op->lval.uword;  break;
    case 32: v = op->lval.udword; break;
    case 64: v = op->lval.uqword; break;
    default: UD_ASSERT(!"invalid offset"); v = 0; /* keep cc happy */
    }
    ud_asmprintf(u, "0x%" FMT64 "x", v);
  } else {
    int64_t v;
    UD_ASSERT(op->offset != 64);
    switch (op->offset) {
    case 8 : v = op->lval.sbyte;  break;
    case 16: v = op->lval.sword;  break;
    case 32: v = op->lval.sdword; break;
    default: UD_ASSERT(!"invalid offset"); v = 0; /* keep cc happy */
    }
    if (v < 0) {
      ud_asmprintf(u, "-0x%" FMT64 "x", -v);
    } else if (v > 0) {
      ud_asmprintf(u, "%s0x%" FMT64 "x", sign? "+" : "", v);
    }
  }
}

/* -----------------------------------------------------------------------------
 * opr_cast() - Prints an operand cast.
 * -----------------------------------------------------------------------------
 */
static void 
opr_cast(struct ud* u, struct ud_operand* op)
{
  if (u->br_far) {
    ud_asmprintf(u, "far "); 
  }
  switch(op->size) {
  case  8: ud_asmprintf(u, "byte " ); break;
  case 16: ud_asmprintf(u, "word " ); break;
  case 32: ud_asmprintf(u, "dword "); break;
  case 64: ud_asmprintf(u, "qword "); break;
  case 80: ud_asmprintf(u, "tword "); break;
  default: break;
  }
}

/* -----------------------------------------------------------------------------
 * gen_operand() - Generates assembly output for each operand.
 * -----------------------------------------------------------------------------
 */
static void gen_operand(struct ud* u, struct ud_operand* op, int syn_cast)
{
  switch(op->type) {
  case UD_OP_REG:
    ud_asmprintf(u, "%s", ud_reg_tab[op->base - UD_R_AL]);
    break;

  case UD_OP_MEM:
    if (syn_cast) {
      opr_cast(u, op);
    }
    ud_asmprintf(u, "[");
    if (u->pfx_seg) {
      ud_asmprintf(u, "%s:", ud_reg_tab[u->pfx_seg - UD_R_AL]);
    }
    if (op->base) {
      ud_asmprintf(u, "%s", ud_reg_tab[op->base - UD_R_AL]);
    }
    if (op->index) {
      ud_asmprintf(u, "%s%s", op->base != UD_NONE? "+" : "",
                              ud_reg_tab[op->index - UD_R_AL]);
      if (op->scale) {
        ud_asmprintf(u, "*%d", op->scale);
      }
    }
    if (op->offset != 0) {
      ud_syn_print_mem_disp(u, op, (op->base  != UD_NONE || 
                                    op->index != UD_NONE) ? 1 : 0);
    }
    ud_asmprintf(u, "]");
    break;
      
  case UD_OP_IMM:
    ud_syn_print_imm(u, op);
    break;


  case UD_OP_JIMM:
    ud_syn_print_addr(u, ud_syn_rel_target(u, op));
    break;

  case UD_OP_PTR:
    switch (op->size) {
      case 32:
        ud_asmprintf(u, "word 0x%x:0x%x", op->lval.ptr.seg, 
          op->lval.ptr.off & 0xFFFF);
        break;
      case 48:
        ud_asmprintf(u, "dword 0x%x:0x%x", op->lval.ptr.seg, 
          op->lval.ptr.off);
        break;
    }
    break;

  case UD_OP_CONST:
    if (syn_cast) opr_cast(u, op);
    ud_asmprintf(u, "%d", op->lval.udword);
    break;

  default: return;
  }
}

/* =============================================================================
 * translates to intel syntax 
 * =============================================================================
 */
extern void
ud_translate_intel(struct ud* u)
{
  /* check if P_OSO prefix is used */
  if (!P_OSO(u->itab_entry->prefix) && u->pfx_opr) {
    switch (u->dis_mode) {
    case 16: ud_asmprintf(u, "o32 "); break;
    case 32:
    case 64: ud_asmprintf(u, "o16 "); break;
    }
  }

  /* check if P_ASO prefix was used */
  if (!P_ASO(u->itab_entry->prefix) && u->pfx_adr) {
    switch (u->dis_mode) {
    case 16: ud_asmprintf(u, "a32 "); break;
    case 32: ud_asmprintf(u, "a16 "); break;
    case 64: ud_asmprintf(u, "a32 "); break;
    }
  }

  if (u->pfx_seg &&
      u->operand[0].type != UD_OP_MEM &&
      u->operand[1].type != UD_OP_MEM ) {
    ud_asmprintf(u, "%s ", ud_reg_tab[u->pfx_seg - UD_R_AL]);
  }

  if (u->pfx_lock) {
    ud_asmprintf(u, "lock ");
  }
  if (u->pfx_rep) {
    ud_asmprintf(u, "rep ");
  } else if (u->pfx_repe) {
    ud_asmprintf(u, "repe ");
  } else if (u->pfx_repne) {
    ud_asmprintf(u, "repne ");
  }

  /* print the instruction mnemonic */
  ud_asmprintf(u, "%s", ud_lookup_mnemonic(u->mnemonic));

  if (u->operand[0].type != UD_NONE) {
    int cast = 0;
    ud_asmprintf(u, " ");
    if (u->operand[0].type == UD_OP_MEM) {
      if (u->operand[1].type == UD_OP_IMM   ||
          u->operand[1].type == UD_OP_CONST ||
          u->operand[1].type == UD_NONE     ||
          (u->operand[0].size != u->operand[1].size && 
           u->operand[1].type != UD_OP_REG)) {
          cast = 1;
      } else if (u->operand[1].type == UD_OP_REG &&
                 u->operand[1].base == UD_R_CL) {
          switch (u->mnemonic) {
          case UD_Ircl:
          case UD_Irol:
          case UD_Iror:
          case UD_Ircr:
          case UD_Ishl:
          case UD_Ishr:
          case UD_Isar:
              cast = 1;
              break;
          default: break;
          }
      }
    }
    gen_operand(u, &u->operand[0], cast);
  }

  if (u->operand[1].type != UD_NONE) {
    int cast = 0;
    ud_asmprintf(u, ", ");
    if (u->operand[1].type == UD_OP_MEM &&
        u->operand[0].size != u->operand[1].size && 
        !ud_opr_is_sreg(&u->operand[0])) {
      cast = 1;
    }
    gen_operand(u, &u->operand[1], cast);
  }

  if (u->operand[2].type != UD_NONE) {
    ud_asmprintf(u, ", ");
    gen_operand(u, &u->operand[2], 0);
  }
}
