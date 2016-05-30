/*
** system_header.h for  in /home/penava_b/perso/Obj/Obj4/Future/compiler
** 
** Made by penava_b
** Login   <penava_b@epitech.net>
** 
** Started on  Tue May 24 00:19:49 2016 penava_b
** Last update Sat May 28 01:06:08 2016 penava_b
*/

#pragma once

#ifndef __OBJECT_C_COMPILER__
#error Compiling using the non ObjectC wrapper of gcc
#endif

#define __HASH_WORD__ #
#define __NL__ /*
*/
#define __CREATE_MACRO__(symb, name, val, args...) __NL__       \
    symb ifdef name __NL__                                      \
    symb undef name __NL__                                      \
    symb endif __NL__                                           \
    symb define name(args) val __NL__

#define __CREATE_MACRO_NF__(symb, name, val) __NL__             \
    symb ifdef name __NL__                                      \
    symb undef name __NL__                                      \
    symb endif __NL__                                           \
    symb define name val __NL__

#define __IF_DEF_ERROR__(symb, name, errorM...) __NL__  \
    symb ifdef name __NL__                              \
    symb error errorM __NL__                            \
    symb endif __NL__

#define __UNDEF_MACRO__(symb, name) __NL__      \
    symb undef name __NL__

#define __DEF_LOCK__(symb, name, errorM...)            \
    __IF_DEF_ERROR__(symb, name, errorM)               \
    symb defile name __NL__
