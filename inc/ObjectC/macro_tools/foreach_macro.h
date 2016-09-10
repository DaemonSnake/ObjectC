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

/* apply first argument to all the other argument, can handle 100 args max */
#define APPLY_MACRO_VAR(macro, args...) ______VARARG(_____VARS, macro, ##args)
#define APPLY_MACRO_VAR_TWO(macro, arg, args...) ______VARARG(_____VARS_TWO, macro, arg, ##args)

/* TOOLS DON'T USE, DON'T WATCH */
#define ______VA_NARGS_IMPL(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, \
			    _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, \
			    _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, \
			    _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, \
			    _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, \
			    _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, \
			    _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, \
			    _71, _72, _73, _74, _75, _76, _77, _78, _79, _80, \
			    _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, \
			    _91, _92, _93, _94, _95, _96, _97, _98, _99, _100, \
			    N, args...) N
#define ______VA_NARGS(args...)						\
    ______VA_NARGS_IMPL(X, ##args,                                      \
                        100, 99, 98, 97, 96, 95, 94, 93, 92, 91,        \
                        90, 89, 88, 87, 86, 85, 84, 83, 82, 81,		\
                        80, 79, 78, 77, 76, 75, 74, 73, 72, 71,		\
                        70, 69, 68, 67, 66, 65, 64, 63, 62, 61,		\
                        60, 59, 58, 57, 56, 55, 54, 53, 52, 51,		\
                        50, 49, 48, 47, 46, 45, 44, 43, 42, 41,		\
                        40, 39, 38, 37, 36, 35, 34, 33, 32, 31,		\
                        30, 29, 28, 27, 26, 25, 24, 23, 22, 21,		\
                        20, 19, 18, 17, 16, 15, 14, 13, 12, 11,		\
                        10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define ______VARARG_IMPL2(base, count, args...)	\
    base##count
#define ______VARARG_IMPL(base, count, args...) \
    ______VARARG_IMPL2(base, count, args)
#define ______VARARG(base, args...)                             \
    ______VARARG_IMPL(base, ______VA_NARGS(args), args)(args)

/*APPLY_MACRO_VAR*/
#define _____VARS1(macro, args...)
#define _____VARS2(macro, arg) macro(arg)
#define _____VARS3(macro, arg, args...) macro(arg) _____VARS2(macro, args)
#define _____VARS4(macro, arg, args...) macro(arg) _____VARS3(macro, args)
#define _____VARS5(macro, arg, args...) macro(arg) _____VARS4(macro, args)
#define _____VARS6(macro, arg, args...) macro(arg) _____VARS5(macro, args)
#define _____VARS7(macro, arg, args...) macro(arg) _____VARS6(macro, args)
#define _____VARS8(macro, arg, args...) macro(arg) _____VARS7(macro, args)
#define _____VARS9(macro, arg, args...) macro(arg) _____VARS8(macro, args)
#define _____VARS10(macro, arg, args...) macro(arg) _____VARS9(macro, args)
#define _____VARS11(macro, arg, args...) macro(arg) _____VARS10(macro, args)
#define _____VARS12(macro, arg, args...) macro(arg) _____VARS11(macro, args)
#define _____VARS13(macro, arg, args...) macro(arg) _____VARS12(macro, args)
#define _____VARS14(macro, arg, args...) macro(arg) _____VARS13(macro, args)
#define _____VARS15(macro, arg, args...) macro(arg) _____VARS14(macro, args)
#define _____VARS16(macro, arg, args...) macro(arg) _____VARS15(macro, args)
#define _____VARS17(macro, arg, args...) macro(arg) _____VARS16(macro, args)
#define _____VARS18(macro, arg, args...) macro(arg) _____VARS17(macro, args)
#define _____VARS19(macro, arg, args...) macro(arg) _____VARS18(macro, args)
#define _____VARS20(macro, arg, args...) macro(arg) _____VARS19(macro, args)
#define _____VARS21(macro, arg, args...) macro(arg) _____VARS20(macro, args)
#define _____VARS22(macro, arg, args...) macro(arg) _____VARS21(macro, args)
#define _____VARS23(macro, arg, args...) macro(arg) _____VARS22(macro, args)
#define _____VARS24(macro, arg, args...) macro(arg) _____VARS23(macro, args)
#define _____VARS25(macro, arg, args...) macro(arg) _____VARS24(macro, args)
#define _____VARS26(macro, arg, args...) macro(arg) _____VARS25(macro, args)
#define _____VARS27(macro, arg, args...) macro(arg) _____VARS26(macro, args)
#define _____VARS28(macro, arg, args...) macro(arg) _____VARS27(macro, args)
#define _____VARS29(macro, arg, args...) macro(arg) _____VARS28(macro, args)
#define _____VARS30(macro, arg, args...) macro(arg) _____VARS29(macro, args)
#define _____VARS31(macro, arg, args...) macro(arg) _____VARS30(macro, args)
#define _____VARS32(macro, arg, args...) macro(arg) _____VARS31(macro, args)
#define _____VARS33(macro, arg, args...) macro(arg) _____VARS32(macro, args)
#define _____VARS34(macro, arg, args...) macro(arg) _____VARS33(macro, args)
#define _____VARS35(macro, arg, args...) macro(arg) _____VARS34(macro, args)
#define _____VARS36(macro, arg, args...) macro(arg) _____VARS35(macro, args)
#define _____VARS37(macro, arg, args...) macro(arg) _____VARS36(macro, args)
#define _____VARS38(macro, arg, args...) macro(arg) _____VARS37(macro, args)
#define _____VARS39(macro, arg, args...) macro(arg) _____VARS38(macro, args)
#define _____VARS40(macro, arg, args...) macro(arg) _____VARS39(macro, args)
#define _____VARS41(macro, arg, args...) macro(arg) _____VARS40(macro, args)
#define _____VARS42(macro, arg, args...) macro(arg) _____VARS41(macro, args)
#define _____VARS43(macro, arg, args...) macro(arg) _____VARS42(macro, args)
#define _____VARS44(macro, arg, args...) macro(arg) _____VARS43(macro, args)
#define _____VARS45(macro, arg, args...) macro(arg) _____VARS44(macro, args)
#define _____VARS46(macro, arg, args...) macro(arg) _____VARS45(macro, args)
#define _____VARS47(macro, arg, args...) macro(arg) _____VARS46(macro, args)
#define _____VARS48(macro, arg, args...) macro(arg) _____VARS47(macro, args)
#define _____VARS49(macro, arg, args...) macro(arg) _____VARS48(macro, args)
#define _____VARS50(macro, arg, args...) macro(arg) _____VARS49(macro, args)
#define _____VARS51(macro, arg, args...) macro(arg) _____VARS50(macro, args)
#define _____VARS52(macro, arg, args...) macro(arg) _____VARS51(macro, args)
#define _____VARS53(macro, arg, args...) macro(arg) _____VARS52(macro, args)
#define _____VARS54(macro, arg, args...) macro(arg) _____VARS53(macro, args)
#define _____VARS55(macro, arg, args...) macro(arg) _____VARS54(macro, args)
#define _____VARS56(macro, arg, args...) macro(arg) _____VARS55(macro, args)
#define _____VARS57(macro, arg, args...) macro(arg) _____VARS56(macro, args)
#define _____VARS58(macro, arg, args...) macro(arg) _____VARS57(macro, args)
#define _____VARS59(macro, arg, args...) macro(arg) _____VARS58(macro, args)
#define _____VARS60(macro, arg, args...) macro(arg) _____VARS59(macro, args)
#define _____VARS61(macro, arg, args...) macro(arg) _____VARS60(macro, args)
#define _____VARS62(macro, arg, args...) macro(arg) _____VARS61(macro, args)
#define _____VARS63(macro, arg, args...) macro(arg) _____VARS62(macro, args)
#define _____VARS64(macro, arg, args...) macro(arg) _____VARS63(macro, args)
#define _____VARS65(macro, arg, args...) macro(arg) _____VARS64(macro, args)
#define _____VARS66(macro, arg, args...) macro(arg) _____VARS65(macro, args)
#define _____VARS67(macro, arg, args...) macro(arg) _____VARS66(macro, args)
#define _____VARS68(macro, arg, args...) macro(arg) _____VARS67(macro, args)
#define _____VARS69(macro, arg, args...) macro(arg) _____VARS68(macro, args)
#define _____VARS70(macro, arg, args...) macro(arg) _____VARS69(macro, args)
#define _____VARS71(macro, arg, args...) macro(arg) _____VARS70(macro, args)
#define _____VARS72(macro, arg, args...) macro(arg) _____VARS71(macro, args)
#define _____VARS73(macro, arg, args...) macro(arg) _____VARS72(macro, args)
#define _____VARS74(macro, arg, args...) macro(arg) _____VARS73(macro, args)
#define _____VARS75(macro, arg, args...) macro(arg) _____VARS74(macro, args)
#define _____VARS76(macro, arg, args...) macro(arg) _____VARS75(macro, args)
#define _____VARS77(macro, arg, args...) macro(arg) _____VARS76(macro, args)
#define _____VARS78(macro, arg, args...) macro(arg) _____VARS77(macro, args)
#define _____VARS79(macro, arg, args...) macro(arg) _____VARS78(macro, args)
#define _____VARS80(macro, arg, args...) macro(arg) _____VARS79(macro, args)
#define _____VARS81(macro, arg, args...) macro(arg) _____VARS80(macro, args)
#define _____VARS82(macro, arg, args...) macro(arg) _____VARS81(macro, args)
#define _____VARS83(macro, arg, args...) macro(arg) _____VARS82(macro, args)
#define _____VARS84(macro, arg, args...) macro(arg) _____VARS83(macro, args)
#define _____VARS85(macro, arg, args...) macro(arg) _____VARS84(macro, args)
#define _____VARS86(macro, arg, args...) macro(arg) _____VARS85(macro, args)
#define _____VARS87(macro, arg, args...) macro(arg) _____VARS86(macro, args)
#define _____VARS88(macro, arg, args...) macro(arg) _____VARS87(macro, args)
#define _____VARS89(macro, arg, args...) macro(arg) _____VARS88(macro, args)
#define _____VARS90(macro, arg, args...) macro(arg) _____VARS89(macro, args)
#define _____VARS91(macro, arg, args...) macro(arg) _____VARS90(macro, args)
#define _____VARS92(macro, arg, args...) macro(arg) _____VARS91(macro, args)
#define _____VARS93(macro, arg, args...) macro(arg) _____VARS92(macro, args)
#define _____VARS94(macro, arg, args...) macro(arg) _____VARS93(macro, args)
#define _____VARS95(macro, arg, args...) macro(arg) _____VARS94(macro, args)
#define _____VARS96(macro, arg, args...) macro(arg) _____VARS95(macro, args)
#define _____VARS97(macro, arg, args...) macro(arg) _____VARS96(macro, args)
#define _____VARS98(macro, arg, args...) macro(arg) _____VARS97(macro, args)
#define _____VARS99(macro, arg, args...) macro(arg) _____VARS98(macro, args)
#define _____VARS100(macro, arg, args...) macro(arg) _____VARS99(macro, args)

/*APPLY_MACRO_VAR_TWO*/

#define _____VARS_TWO2(macro, arg)
#define _____VARS_TWO3(macro, arg, arg2) macro(arg, arg2)
#define _____VARS_TWO4(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO3(macro, arg, ##args)
#define _____VARS_TWO5(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO4(macro, arg, ##args)
#define _____VARS_TWO6(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO5(macro, arg, ##args)
#define _____VARS_TWO7(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO6(macro, arg, ##args)
#define _____VARS_TWO8(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO7(macro, arg, ##args)
#define _____VARS_TWO9(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO8(macro, arg, ##args)
#define _____VARS_TWO10(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO9(macro, arg, ##args)
#define _____VARS_TWO11(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO10(macro, arg, ##args)
#define _____VARS_TWO12(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO11(macro, arg, ##args)
#define _____VARS_TWO13(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO12(macro, arg, ##args)
#define _____VARS_TWO14(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO13(macro, arg, ##args)
#define _____VARS_TWO15(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO14(macro, arg, ##args)
#define _____VARS_TWO16(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO15(macro, arg, ##args)
#define _____VARS_TWO17(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO16(macro, arg, ##args)
#define _____VARS_TWO18(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO17(macro, arg, ##args)
#define _____VARS_TWO19(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO18(macro, arg, ##args)
#define _____VARS_TWO20(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO19(macro, arg, ##args)
#define _____VARS_TWO21(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO20(macro, arg, ##args)
#define _____VARS_TWO22(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO21(macro, arg, ##args)
#define _____VARS_TWO23(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO22(macro, arg, ##args)
#define _____VARS_TWO24(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO23(macro, arg, ##args)
#define _____VARS_TWO25(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO24(macro, arg, ##args)
#define _____VARS_TWO26(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO25(macro, arg, ##args)
#define _____VARS_TWO27(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO26(macro, arg, ##args)
#define _____VARS_TWO28(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO27(macro, arg, ##args)
#define _____VARS_TWO29(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO28(macro, arg, ##args)
#define _____VARS_TWO30(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO29(macro, arg, ##args)
#define _____VARS_TWO31(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO30(macro, arg, ##args)
#define _____VARS_TWO32(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO31(macro, arg, ##args)
#define _____VARS_TWO33(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO32(macro, arg, ##args)
#define _____VARS_TWO34(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO33(macro, arg, ##args)
#define _____VARS_TWO35(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO34(macro, arg, ##args)
#define _____VARS_TWO36(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO35(macro, arg, ##args)
#define _____VARS_TWO37(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO36(macro, arg, ##args)
#define _____VARS_TWO38(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO37(macro, arg, ##args)
#define _____VARS_TWO39(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO38(macro, arg, ##args)
#define _____VARS_TWO40(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO39(macro, arg, ##args)
#define _____VARS_TWO41(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO40(macro, arg, ##args)
#define _____VARS_TWO42(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO41(macro, arg, ##args)
#define _____VARS_TWO43(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO42(macro, arg, ##args)
#define _____VARS_TWO44(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO43(macro, arg, ##args)
#define _____VARS_TWO45(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO44(macro, arg, ##args)
#define _____VARS_TWO46(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO45(macro, arg, ##args)
#define _____VARS_TWO47(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO46(macro, arg, ##args)
#define _____VARS_TWO48(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO47(macro, arg, ##args)
#define _____VARS_TWO49(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO48(macro, arg, ##args)
#define _____VARS_TWO50(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO49(macro, arg, ##args)
#define _____VARS_TWO51(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO50(macro, arg, ##args)
#define _____VARS_TWO52(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO51(macro, arg, ##args)
#define _____VARS_TWO53(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO52(macro, arg, ##args)
#define _____VARS_TWO54(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO53(macro, arg, ##args)
#define _____VARS_TWO55(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO54(macro, arg, ##args)
#define _____VARS_TWO56(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO55(macro, arg, ##args)
#define _____VARS_TWO57(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO56(macro, arg, ##args)
#define _____VARS_TWO58(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO57(macro, arg, ##args)
#define _____VARS_TWO59(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO58(macro, arg, ##args)
#define _____VARS_TWO60(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO59(macro, arg, ##args)
#define _____VARS_TWO61(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO60(macro, arg, ##args)
#define _____VARS_TWO62(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO61(macro, arg, ##args)
#define _____VARS_TWO63(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO62(macro, arg, ##args)
#define _____VARS_TWO64(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO63(macro, arg, ##args)
#define _____VARS_TWO65(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO64(macro, arg, ##args)
#define _____VARS_TWO66(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO65(macro, arg, ##args)
#define _____VARS_TWO67(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO66(macro, arg, ##args)
#define _____VARS_TWO68(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO67(macro, arg, ##args)
#define _____VARS_TWO69(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO68(macro, arg, ##args)
#define _____VARS_TWO70(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO69(macro, arg, ##args)
#define _____VARS_TWO71(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO70(macro, arg, ##args)
#define _____VARS_TWO72(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO71(macro, arg, ##args)
#define _____VARS_TWO73(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO72(macro, arg, ##args)
#define _____VARS_TWO74(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO73(macro, arg, ##args)
#define _____VARS_TWO75(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO74(macro, arg, ##args)
#define _____VARS_TWO76(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO75(macro, arg, ##args)
#define _____VARS_TWO77(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO76(macro, arg, ##args)
#define _____VARS_TWO78(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO77(macro, arg, ##args)
#define _____VARS_TWO79(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO78(macro, arg, ##args)
#define _____VARS_TWO80(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO79(macro, arg, ##args)
#define _____VARS_TWO81(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO80(macro, arg, ##args)
#define _____VARS_TWO82(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO81(macro, arg, ##args)
#define _____VARS_TWO83(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO82(macro, arg, ##args)
#define _____VARS_TWO84(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO83(macro, arg, ##args)
#define _____VARS_TWO85(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO84(macro, arg, ##args)
#define _____VARS_TWO86(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO85(macro, arg, ##args)
#define _____VARS_TWO87(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO86(macro, arg, ##args)
#define _____VARS_TWO88(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO87(macro, arg, ##args)
#define _____VARS_TWO89(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO88(macro, arg, ##args)
#define _____VARS_TWO90(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO89(macro, arg, ##args)
#define _____VARS_TWO91(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO90(macro, arg, ##args)
#define _____VARS_TWO92(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO91(macro, arg, ##args)
#define _____VARS_TWO93(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO92(macro, arg, ##args)
#define _____VARS_TWO94(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO93(macro, arg, ##args)
#define _____VARS_TWO95(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO94(macro, arg, ##args)
#define _____VARS_TWO96(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO95(macro, arg, ##args)
#define _____VARS_TWO97(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO96(macro, arg, ##args)
#define _____VARS_TWO98(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO97(macro, arg, ##args)
#define _____VARS_TWO99(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO98(macro, arg, ##args)
#define _____VARS_TWO100(macro, arg, arg2, args...) macro(arg, arg2)	\
    _____VARS_TWO99(macro, arg, ##args)
