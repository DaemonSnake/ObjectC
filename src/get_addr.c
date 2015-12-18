/*
** test.c for  in /home/penava_b/perso/Obj/Obj4/src/asm_mess
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Fri Dec 18 01:52:41 2015 penava_b
** Last update Fri Dec 18 04:03:22 2015 penava_b
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asm_mess/types.h"
#include "asm_mess/extern.h"
#include "asm_mess/itab.h"

static int     	hex_to_int(const char *begin)
{
  int		sign;

  if (begin == 0 || begin[0] == 0)
    return 0;
  sign = (begin[0] == '-' ? (++begin, -1) : 1);
  return strtol(begin + 2, NULL, 16) * sign;
}

void    	*__get_assign_addr(char *rbp)
{
  ud_t		ud_obj;
  const char	*str;

  ud_init(&ud_obj);
  ud_set_input_buffer(&ud_obj, __builtin_return_address(0), 100);
  while (ud_disassemble(&ud_obj))
    if (ud_obj.mnemonic == UD_Imov)
      {
	str = ud_obj.asm_buf;
  	if ((str = strstr(str, "[rbp")) != NULL)
	  return rbp + hex_to_int(str + 4);
      }
  return NULL;
}
