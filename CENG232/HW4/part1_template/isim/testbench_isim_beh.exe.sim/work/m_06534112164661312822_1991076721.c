/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0xfbc00daa */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "/home/ise/HW4/part1_template/BMM_module.v";
static int ng1[] = {0, 0};
static int ng2[] = {8, 0};
static unsigned int ng3[] = {0U, 0U};
static int ng4[] = {1, 0};
static unsigned int ng5[] = {1U, 0U};
static unsigned int ng6[] = {2U, 0U};
static unsigned int ng7[] = {3U, 0U};



static void Initial_45_0(char *t0)
{
    char t5[8];
    char t14[8];
    char t15[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t6;
    unsigned int t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    char *t12;
    char *t13;
    char *t16;
    char *t17;
    char *t18;
    char *t19;
    char *t20;
    char *t21;
    char *t22;
    char *t23;
    char *t24;
    char *t25;
    unsigned int t26;
    int t27;
    char *t28;
    unsigned int t29;
    int t30;
    int t31;
    unsigned int t32;
    unsigned int t33;
    int t34;
    int t35;

LAB0:    xsi_set_current_line(45, ng0);

LAB2:    xsi_set_current_line(46, ng0);
    xsi_set_current_line(46, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 2568);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 32);

LAB3:    t1 = (t0 + 2568);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = ((char*)((ng2)));
    memset(t5, 0, 8);
    xsi_vlog_signed_less(t5, 32, t3, 32, t4, 32);
    t6 = (t5 + 4);
    t7 = *((unsigned int *)t6);
    t8 = (~(t7));
    t9 = *((unsigned int *)t5);
    t10 = (t9 & t8);
    t11 = (t10 != 0);
    if (t11 > 0)
        goto LAB4;

LAB5:
LAB1:    return;
LAB4:    xsi_set_current_line(46, ng0);

LAB6:    xsi_set_current_line(47, ng0);
    t12 = ((char*)((ng3)));
    t13 = (t0 + 2408);
    t16 = (t0 + 2408);
    t17 = (t16 + 72U);
    t18 = *((char **)t17);
    t19 = (t0 + 2408);
    t20 = (t19 + 64U);
    t21 = *((char **)t20);
    t22 = (t0 + 2568);
    t23 = (t22 + 56U);
    t24 = *((char **)t23);
    xsi_vlog_generic_convert_array_indices(t14, t15, t18, t21, 2, 1, t24, 32, 1);
    t25 = (t14 + 4);
    t26 = *((unsigned int *)t25);
    t27 = (!(t26));
    t28 = (t15 + 4);
    t29 = *((unsigned int *)t28);
    t30 = (!(t29));
    t31 = (t27 && t30);
    if (t31 == 1)
        goto LAB7;

LAB8:    xsi_set_current_line(46, ng0);
    t1 = (t0 + 2568);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = ((char*)((ng4)));
    memset(t5, 0, 8);
    xsi_vlog_signed_add(t5, 32, t3, 32, t4, 32);
    t6 = (t0 + 2568);
    xsi_vlogvar_assign_value(t6, t5, 0, 0, 32);
    goto LAB3;

LAB7:    t32 = *((unsigned int *)t14);
    t33 = *((unsigned int *)t15);
    t34 = (t32 - t33);
    t35 = (t34 + 1);
    xsi_vlogvar_assign_value(t13, t12, 0, *((unsigned int *)t15), t35);
    goto LAB8;

}

static void Always_52_1(char *t0)
{
    char t6[8];
    char t34[8];
    char t66[8];
    char t67[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t7;
    char *t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    char *t21;
    char *t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    char *t28;
    char *t29;
    int t30;
    char *t31;
    char *t32;
    char *t33;
    unsigned int t35;
    unsigned int t36;
    unsigned int t37;
    char *t38;
    char *t39;
    unsigned int t40;
    unsigned int t41;
    unsigned int t42;
    unsigned int t43;
    unsigned int t44;
    unsigned int t45;
    unsigned int t46;
    char *t47;
    char *t48;
    unsigned int t49;
    unsigned int t50;
    unsigned int t51;
    unsigned int t52;
    unsigned int t53;
    unsigned int t54;
    unsigned int t55;
    unsigned int t56;
    int t57;
    int t58;
    unsigned int t59;
    unsigned int t60;
    unsigned int t61;
    unsigned int t62;
    unsigned int t63;
    unsigned int t64;
    char *t65;
    char *t68;
    char *t69;
    char *t70;
    char *t71;
    char *t72;
    char *t73;
    char *t74;
    char *t75;
    unsigned int t76;
    int t77;
    char *t78;
    unsigned int t79;
    int t80;
    int t81;
    unsigned int t82;
    unsigned int t83;
    int t84;
    int t85;

LAB0:    t1 = (t0 + 3728U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(52, ng0);
    t2 = (t0 + 4296);
    *((int *)t2) = 1;
    t3 = (t0 + 3760);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(52, ng0);

LAB5:    xsi_set_current_line(53, ng0);
    t4 = (t0 + 1048U);
    t5 = *((char **)t4);
    t4 = ((char*)((ng1)));
    memset(t6, 0, 8);
    t7 = (t5 + 4);
    t8 = (t4 + 4);
    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t4);
    t11 = (t9 ^ t10);
    t12 = *((unsigned int *)t7);
    t13 = *((unsigned int *)t8);
    t14 = (t12 ^ t13);
    t15 = (t11 | t14);
    t16 = *((unsigned int *)t7);
    t17 = *((unsigned int *)t8);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB9;

LAB6:    if (t18 != 0)
        goto LAB8;

LAB7:    *((unsigned int *)t6) = 1;

LAB9:    t22 = (t6 + 4);
    t23 = *((unsigned int *)t22);
    t24 = (~(t23));
    t25 = *((unsigned int *)t6);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB10;

LAB11:
LAB12:    goto LAB2;

LAB8:    t21 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t21) = 1;
    goto LAB9;

LAB10:    xsi_set_current_line(53, ng0);

LAB13:    xsi_set_current_line(54, ng0);
    t28 = (t0 + 1368U);
    t29 = *((char **)t28);

LAB14:    t28 = ((char*)((ng3)));
    t30 = xsi_vlog_unsigned_case_compare(t29, 2, t28, 2);
    if (t30 == 1)
        goto LAB15;

LAB16:    t2 = ((char*)((ng5)));
    t30 = xsi_vlog_unsigned_case_compare(t29, 2, t2, 2);
    if (t30 == 1)
        goto LAB17;

LAB18:    t2 = ((char*)((ng6)));
    t30 = xsi_vlog_unsigned_case_compare(t29, 2, t2, 2);
    if (t30 == 1)
        goto LAB19;

LAB20:    t2 = ((char*)((ng7)));
    t30 = xsi_vlog_unsigned_case_compare(t29, 2, t2, 2);
    if (t30 == 1)
        goto LAB21;

LAB22:
LAB24:
LAB23:    xsi_set_current_line(59, ng0);
    t2 = ((char*)((ng3)));
    t3 = (t0 + 2408);
    t4 = (t0 + 2408);
    t5 = (t4 + 72U);
    t7 = *((char **)t5);
    t8 = (t0 + 2408);
    t21 = (t8 + 64U);
    t22 = *((char **)t21);
    t28 = (t0 + 1208U);
    t31 = *((char **)t28);
    xsi_vlog_generic_convert_array_indices(t6, t34, t7, t22, 2, 1, t31, 3, 2);
    t28 = (t6 + 4);
    t9 = *((unsigned int *)t28);
    t30 = (!(t9));
    t32 = (t34 + 4);
    t10 = *((unsigned int *)t32);
    t57 = (!(t10));
    t58 = (t30 && t57);
    if (t58 == 1)
        goto LAB48;

LAB49:
LAB25:    goto LAB12;

LAB15:    xsi_set_current_line(55, ng0);
    t31 = (t0 + 1528U);
    t32 = *((char **)t31);
    t31 = (t0 + 1688U);
    t33 = *((char **)t31);
    t35 = *((unsigned int *)t32);
    t36 = *((unsigned int *)t33);
    t37 = (t35 & t36);
    *((unsigned int *)t34) = t37;
    t31 = (t32 + 4);
    t38 = (t33 + 4);
    t39 = (t34 + 4);
    t40 = *((unsigned int *)t31);
    t41 = *((unsigned int *)t38);
    t42 = (t40 | t41);
    *((unsigned int *)t39) = t42;
    t43 = *((unsigned int *)t39);
    t44 = (t43 != 0);
    if (t44 == 1)
        goto LAB26;

LAB27:
LAB28:    t65 = (t0 + 2408);
    t68 = (t0 + 2408);
    t69 = (t68 + 72U);
    t70 = *((char **)t69);
    t71 = (t0 + 2408);
    t72 = (t71 + 64U);
    t73 = *((char **)t72);
    t74 = (t0 + 1208U);
    t75 = *((char **)t74);
    xsi_vlog_generic_convert_array_indices(t66, t67, t70, t73, 2, 1, t75, 3, 2);
    t74 = (t66 + 4);
    t76 = *((unsigned int *)t74);
    t77 = (!(t76));
    t78 = (t67 + 4);
    t79 = *((unsigned int *)t78);
    t80 = (!(t79));
    t81 = (t77 && t80);
    if (t81 == 1)
        goto LAB29;

LAB30:    goto LAB25;

LAB17:    xsi_set_current_line(56, ng0);
    t3 = (t0 + 1528U);
    t4 = *((char **)t3);
    t3 = (t0 + 1688U);
    t5 = *((char **)t3);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t5);
    t11 = (t9 | t10);
    *((unsigned int *)t6) = t11;
    t3 = (t4 + 4);
    t7 = (t5 + 4);
    t8 = (t6 + 4);
    t12 = *((unsigned int *)t3);
    t13 = *((unsigned int *)t7);
    t14 = (t12 | t13);
    *((unsigned int *)t8) = t14;
    t15 = *((unsigned int *)t8);
    t16 = (t15 != 0);
    if (t16 == 1)
        goto LAB31;

LAB32:
LAB33:    t28 = (t0 + 2408);
    t31 = (t0 + 2408);
    t32 = (t31 + 72U);
    t33 = *((char **)t32);
    t38 = (t0 + 2408);
    t39 = (t38 + 64U);
    t47 = *((char **)t39);
    t48 = (t0 + 1208U);
    t65 = *((char **)t48);
    xsi_vlog_generic_convert_array_indices(t34, t66, t33, t47, 2, 1, t65, 3, 2);
    t48 = (t34 + 4);
    t40 = *((unsigned int *)t48);
    t77 = (!(t40));
    t68 = (t66 + 4);
    t41 = *((unsigned int *)t68);
    t80 = (!(t41));
    t81 = (t77 && t80);
    if (t81 == 1)
        goto LAB34;

LAB35:    goto LAB25;

LAB19:    xsi_set_current_line(57, ng0);
    t3 = (t0 + 1528U);
    t4 = *((char **)t3);
    t3 = (t0 + 1688U);
    t5 = *((char **)t3);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t5);
    t11 = (t9 ^ t10);
    *((unsigned int *)t6) = t11;
    t3 = (t4 + 4);
    t7 = (t5 + 4);
    t8 = (t6 + 4);
    t12 = *((unsigned int *)t3);
    t13 = *((unsigned int *)t7);
    t14 = (t12 | t13);
    *((unsigned int *)t8) = t14;
    t15 = *((unsigned int *)t8);
    t16 = (t15 != 0);
    if (t16 == 1)
        goto LAB36;

LAB37:
LAB38:    t21 = (t0 + 2408);
    t22 = (t0 + 2408);
    t28 = (t22 + 72U);
    t31 = *((char **)t28);
    t32 = (t0 + 2408);
    t33 = (t32 + 64U);
    t38 = *((char **)t33);
    t39 = (t0 + 1208U);
    t47 = *((char **)t39);
    xsi_vlog_generic_convert_array_indices(t34, t66, t31, t38, 2, 1, t47, 3, 2);
    t39 = (t34 + 4);
    t19 = *((unsigned int *)t39);
    t57 = (!(t19));
    t48 = (t66 + 4);
    t20 = *((unsigned int *)t48);
    t58 = (!(t20));
    t77 = (t57 && t58);
    if (t77 == 1)
        goto LAB39;

LAB40:    goto LAB25;

LAB21:    xsi_set_current_line(58, ng0);
    t3 = (t0 + 1528U);
    t4 = *((char **)t3);
    t3 = (t0 + 1688U);
    t5 = *((char **)t3);
    t9 = *((unsigned int *)t4);
    t10 = *((unsigned int *)t5);
    t11 = (t9 & t10);
    *((unsigned int *)t34) = t11;
    t3 = (t4 + 4);
    t7 = (t5 + 4);
    t8 = (t34 + 4);
    t12 = *((unsigned int *)t3);
    t13 = *((unsigned int *)t7);
    t14 = (t12 | t13);
    *((unsigned int *)t8) = t14;
    t15 = *((unsigned int *)t8);
    t16 = (t15 != 0);
    if (t16 == 1)
        goto LAB41;

LAB42:
LAB43:    memset(t6, 0, 8);
    t28 = (t6 + 4);
    t31 = (t34 + 4);
    t44 = *((unsigned int *)t34);
    t45 = (~(t44));
    *((unsigned int *)t6) = t45;
    *((unsigned int *)t28) = 0;
    if (*((unsigned int *)t31) != 0)
        goto LAB45;

LAB44:    t52 = *((unsigned int *)t6);
    *((unsigned int *)t6) = (t52 & 255U);
    t53 = *((unsigned int *)t28);
    *((unsigned int *)t28) = (t53 & 255U);
    t32 = (t0 + 2408);
    t33 = (t0 + 2408);
    t38 = (t33 + 72U);
    t39 = *((char **)t38);
    t47 = (t0 + 2408);
    t48 = (t47 + 64U);
    t65 = *((char **)t48);
    t68 = (t0 + 1208U);
    t69 = *((char **)t68);
    xsi_vlog_generic_convert_array_indices(t66, t67, t39, t65, 2, 1, t69, 3, 2);
    t68 = (t66 + 4);
    t54 = *((unsigned int *)t68);
    t77 = (!(t54));
    t70 = (t67 + 4);
    t55 = *((unsigned int *)t70);
    t80 = (!(t55));
    t81 = (t77 && t80);
    if (t81 == 1)
        goto LAB46;

LAB47:    goto LAB25;

LAB26:    t45 = *((unsigned int *)t34);
    t46 = *((unsigned int *)t39);
    *((unsigned int *)t34) = (t45 | t46);
    t47 = (t32 + 4);
    t48 = (t33 + 4);
    t49 = *((unsigned int *)t32);
    t50 = (~(t49));
    t51 = *((unsigned int *)t47);
    t52 = (~(t51));
    t53 = *((unsigned int *)t33);
    t54 = (~(t53));
    t55 = *((unsigned int *)t48);
    t56 = (~(t55));
    t57 = (t50 & t52);
    t58 = (t54 & t56);
    t59 = (~(t57));
    t60 = (~(t58));
    t61 = *((unsigned int *)t39);
    *((unsigned int *)t39) = (t61 & t59);
    t62 = *((unsigned int *)t39);
    *((unsigned int *)t39) = (t62 & t60);
    t63 = *((unsigned int *)t34);
    *((unsigned int *)t34) = (t63 & t59);
    t64 = *((unsigned int *)t34);
    *((unsigned int *)t34) = (t64 & t60);
    goto LAB28;

LAB29:    t82 = *((unsigned int *)t66);
    t83 = *((unsigned int *)t67);
    t84 = (t82 - t83);
    t85 = (t84 + 1);
    xsi_vlogvar_wait_assign_value(t65, t34, 0, *((unsigned int *)t67), t85, 0LL);
    goto LAB30;

LAB31:    t17 = *((unsigned int *)t6);
    t18 = *((unsigned int *)t8);
    *((unsigned int *)t6) = (t17 | t18);
    t21 = (t4 + 4);
    t22 = (t5 + 4);
    t19 = *((unsigned int *)t21);
    t20 = (~(t19));
    t23 = *((unsigned int *)t4);
    t57 = (t23 & t20);
    t24 = *((unsigned int *)t22);
    t25 = (~(t24));
    t26 = *((unsigned int *)t5);
    t58 = (t26 & t25);
    t27 = (~(t57));
    t35 = (~(t58));
    t36 = *((unsigned int *)t8);
    *((unsigned int *)t8) = (t36 & t27);
    t37 = *((unsigned int *)t8);
    *((unsigned int *)t8) = (t37 & t35);
    goto LAB33;

LAB34:    t42 = *((unsigned int *)t34);
    t43 = *((unsigned int *)t66);
    t84 = (t42 - t43);
    t85 = (t84 + 1);
    xsi_vlogvar_wait_assign_value(t28, t6, 0, *((unsigned int *)t66), t85, 0LL);
    goto LAB35;

LAB36:    t17 = *((unsigned int *)t6);
    t18 = *((unsigned int *)t8);
    *((unsigned int *)t6) = (t17 | t18);
    goto LAB38;

LAB39:    t23 = *((unsigned int *)t34);
    t24 = *((unsigned int *)t66);
    t80 = (t23 - t24);
    t81 = (t80 + 1);
    xsi_vlogvar_wait_assign_value(t21, t6, 0, *((unsigned int *)t66), t81, 0LL);
    goto LAB40;

LAB41:    t17 = *((unsigned int *)t34);
    t18 = *((unsigned int *)t8);
    *((unsigned int *)t34) = (t17 | t18);
    t21 = (t4 + 4);
    t22 = (t5 + 4);
    t19 = *((unsigned int *)t4);
    t20 = (~(t19));
    t23 = *((unsigned int *)t21);
    t24 = (~(t23));
    t25 = *((unsigned int *)t5);
    t26 = (~(t25));
    t27 = *((unsigned int *)t22);
    t35 = (~(t27));
    t57 = (t20 & t24);
    t58 = (t26 & t35);
    t36 = (~(t57));
    t37 = (~(t58));
    t40 = *((unsigned int *)t8);
    *((unsigned int *)t8) = (t40 & t36);
    t41 = *((unsigned int *)t8);
    *((unsigned int *)t8) = (t41 & t37);
    t42 = *((unsigned int *)t34);
    *((unsigned int *)t34) = (t42 & t36);
    t43 = *((unsigned int *)t34);
    *((unsigned int *)t34) = (t43 & t37);
    goto LAB43;

LAB45:    t46 = *((unsigned int *)t6);
    t49 = *((unsigned int *)t31);
    *((unsigned int *)t6) = (t46 | t49);
    t50 = *((unsigned int *)t28);
    t51 = *((unsigned int *)t31);
    *((unsigned int *)t28) = (t50 | t51);
    goto LAB44;

LAB46:    t56 = *((unsigned int *)t66);
    t59 = *((unsigned int *)t67);
    t84 = (t56 - t59);
    t85 = (t84 + 1);
    xsi_vlogvar_wait_assign_value(t32, t6, 0, *((unsigned int *)t67), t85, 0LL);
    goto LAB47;

LAB48:    t11 = *((unsigned int *)t6);
    t12 = *((unsigned int *)t34);
    t77 = (t11 - t12);
    t80 = (t77 + 1);
    xsi_vlogvar_wait_assign_value(t3, t2, 0, *((unsigned int *)t34), t80, 0LL);
    goto LAB49;

}

static void Always_65_2(char *t0)
{
    char t6[8];
    char t31[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t7;
    char *t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    unsigned int t14;
    unsigned int t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    char *t21;
    char *t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    unsigned int t27;
    char *t28;
    char *t29;
    char *t30;
    char *t32;
    char *t33;
    char *t34;
    char *t35;
    char *t36;
    char *t37;
    char *t38;
    char *t39;

LAB0:    t1 = (t0 + 3976U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(65, ng0);
    t2 = (t0 + 4312);
    *((int *)t2) = 1;
    t3 = (t0 + 4008);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(65, ng0);

LAB5:    xsi_set_current_line(66, ng0);
    t4 = (t0 + 1048U);
    t5 = *((char **)t4);
    t4 = ((char*)((ng4)));
    memset(t6, 0, 8);
    t7 = (t5 + 4);
    t8 = (t4 + 4);
    t9 = *((unsigned int *)t5);
    t10 = *((unsigned int *)t4);
    t11 = (t9 ^ t10);
    t12 = *((unsigned int *)t7);
    t13 = *((unsigned int *)t8);
    t14 = (t12 ^ t13);
    t15 = (t11 | t14);
    t16 = *((unsigned int *)t7);
    t17 = *((unsigned int *)t8);
    t18 = (t16 | t17);
    t19 = (~(t18));
    t20 = (t15 & t19);
    if (t20 != 0)
        goto LAB9;

LAB6:    if (t18 != 0)
        goto LAB8;

LAB7:    *((unsigned int *)t6) = 1;

LAB9:    t22 = (t6 + 4);
    t23 = *((unsigned int *)t22);
    t24 = (~(t23));
    t25 = *((unsigned int *)t6);
    t26 = (t25 & t24);
    t27 = (t26 != 0);
    if (t27 > 0)
        goto LAB10;

LAB11:
LAB12:    goto LAB2;

LAB8:    t21 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t21) = 1;
    goto LAB9;

LAB10:    xsi_set_current_line(66, ng0);

LAB13:    xsi_set_current_line(67, ng0);
    t28 = (t0 + 2408);
    t29 = (t28 + 56U);
    t30 = *((char **)t29);
    t32 = (t0 + 2408);
    t33 = (t32 + 72U);
    t34 = *((char **)t33);
    t35 = (t0 + 2408);
    t36 = (t35 + 64U);
    t37 = *((char **)t36);
    t38 = (t0 + 1208U);
    t39 = *((char **)t38);
    xsi_vlog_generic_get_array_select_value(t31, 8, t30, t34, t37, 2, 1, t39, 3, 2);
    t38 = (t0 + 2248);
    xsi_vlogvar_assign_value(t38, t31, 0, 0, 8);
    goto LAB12;

}


extern void work_m_06534112164661312822_1991076721_init()
{
	static char *pe[] = {(void *)Initial_45_0,(void *)Always_52_1,(void *)Always_65_2};
	xsi_register_didat("work_m_06534112164661312822_1991076721", "isim/testbench_isim_beh.exe.sim/work/m_06534112164661312822_1991076721.didat");
	xsi_register_executes(pe);
}
