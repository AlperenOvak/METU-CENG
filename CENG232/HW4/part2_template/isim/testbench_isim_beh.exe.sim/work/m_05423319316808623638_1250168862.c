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
static const char *ng0 = "/home/ise/HW4/part2_template/Lab4_2.v";
static unsigned int ng1[] = {0U, 0U};
static int ng2[] = {0, 0};
static int ng3[] = {1, 0};
static int ng4[] = {2, 0};
static int ng5[] = {3, 0};
static unsigned int ng6[] = {1U, 0U};
static unsigned int ng7[] = {2U, 0U};
static unsigned int ng8[] = {3U, 0U};
static int ng9[] = {16, 0};



static void Initial_25_0(char *t0)
{
    char t3[8];
    char t4[8];
    char *t1;
    char *t2;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    char *t10;
    char *t11;
    char *t12;
    unsigned int t13;
    int t14;
    char *t15;
    unsigned int t16;
    int t17;
    int t18;
    unsigned int t19;
    unsigned int t20;
    int t21;
    int t22;

LAB0:    xsi_set_current_line(25, ng0);

LAB2:    xsi_set_current_line(26, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 2568);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 16);
    xsi_set_current_line(27, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 2728);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 16);
    xsi_set_current_line(28, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 2888);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 16);
    xsi_set_current_line(29, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 3048);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 16);
    xsi_set_current_line(30, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 1768);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 2);
    xsi_set_current_line(31, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 1928);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 6);
    xsi_set_current_line(32, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 2088);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 6);
    xsi_set_current_line(33, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 2248);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 1);
    xsi_set_current_line(34, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 2408);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 1);
    xsi_set_current_line(35, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 3528);
    t5 = (t0 + 3528);
    t6 = (t5 + 72U);
    t7 = *((char **)t6);
    t8 = (t0 + 3528);
    t9 = (t8 + 64U);
    t10 = *((char **)t9);
    t11 = ((char*)((ng2)));
    xsi_vlog_generic_convert_array_indices(t3, t4, t7, t10, 2, 1, t11, 32, 1);
    t12 = (t3 + 4);
    t13 = *((unsigned int *)t12);
    t14 = (!(t13));
    t15 = (t4 + 4);
    t16 = *((unsigned int *)t15);
    t17 = (!(t16));
    t18 = (t14 && t17);
    if (t18 == 1)
        goto LAB3;

LAB4:    xsi_set_current_line(36, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 3528);
    t5 = (t0 + 3528);
    t6 = (t5 + 72U);
    t7 = *((char **)t6);
    t8 = (t0 + 3528);
    t9 = (t8 + 64U);
    t10 = *((char **)t9);
    t11 = ((char*)((ng3)));
    xsi_vlog_generic_convert_array_indices(t3, t4, t7, t10, 2, 1, t11, 32, 1);
    t12 = (t3 + 4);
    t13 = *((unsigned int *)t12);
    t14 = (!(t13));
    t15 = (t4 + 4);
    t16 = *((unsigned int *)t15);
    t17 = (!(t16));
    t18 = (t14 && t17);
    if (t18 == 1)
        goto LAB5;

LAB6:    xsi_set_current_line(37, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 3528);
    t5 = (t0 + 3528);
    t6 = (t5 + 72U);
    t7 = *((char **)t6);
    t8 = (t0 + 3528);
    t9 = (t8 + 64U);
    t10 = *((char **)t9);
    t11 = ((char*)((ng4)));
    xsi_vlog_generic_convert_array_indices(t3, t4, t7, t10, 2, 1, t11, 32, 1);
    t12 = (t3 + 4);
    t13 = *((unsigned int *)t12);
    t14 = (!(t13));
    t15 = (t4 + 4);
    t16 = *((unsigned int *)t15);
    t17 = (!(t16));
    t18 = (t14 && t17);
    if (t18 == 1)
        goto LAB7;

LAB8:    xsi_set_current_line(38, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 3528);
    t5 = (t0 + 3528);
    t6 = (t5 + 72U);
    t7 = *((char **)t6);
    t8 = (t0 + 3528);
    t9 = (t8 + 64U);
    t10 = *((char **)t9);
    t11 = ((char*)((ng5)));
    xsi_vlog_generic_convert_array_indices(t3, t4, t7, t10, 2, 1, t11, 32, 1);
    t12 = (t3 + 4);
    t13 = *((unsigned int *)t12);
    t14 = (!(t13));
    t15 = (t4 + 4);
    t16 = *((unsigned int *)t15);
    t17 = (!(t16));
    t18 = (t14 && t17);
    if (t18 == 1)
        goto LAB9;

LAB10:
LAB1:    return;
LAB3:    t19 = *((unsigned int *)t3);
    t20 = *((unsigned int *)t4);
    t21 = (t19 - t20);
    t22 = (t21 + 1);
    xsi_vlogvar_assign_value(t2, t1, 0, *((unsigned int *)t4), t22);
    goto LAB4;

LAB5:    t19 = *((unsigned int *)t3);
    t20 = *((unsigned int *)t4);
    t21 = (t19 - t20);
    t22 = (t21 + 1);
    xsi_vlogvar_assign_value(t2, t1, 0, *((unsigned int *)t4), t22);
    goto LAB6;

LAB7:    t19 = *((unsigned int *)t3);
    t20 = *((unsigned int *)t4);
    t21 = (t19 - t20);
    t22 = (t21 + 1);
    xsi_vlogvar_assign_value(t2, t1, 0, *((unsigned int *)t4), t22);
    goto LAB8;

LAB9:    t19 = *((unsigned int *)t3);
    t20 = *((unsigned int *)t4);
    t21 = (t19 - t20);
    t22 = (t21 + 1);
    xsi_vlogvar_assign_value(t2, t1, 0, *((unsigned int *)t4), t22);
    goto LAB10;

}

static void Always_42_1(char *t0)
{
    char t4[8];
    char t25[8];
    char t27[8];
    char t28[8];
    char *t1;
    char *t2;
    char *t3;
    char *t5;
    char *t6;
    char *t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    char *t14;
    int t15;
    char *t16;
    char *t17;
    char *t18;
    char *t19;
    char *t20;
    char *t21;
    char *t22;
    char *t23;
    char *t24;
    char *t26;
    char *t29;
    char *t30;
    char *t31;
    char *t32;
    char *t33;
    char *t34;
    char *t35;
    char *t36;
    char *t37;
    char *t38;
    char *t39;
    int t40;
    int t41;
    int t42;
    int t43;
    unsigned int t44;
    unsigned int t45;
    unsigned int t46;
    unsigned int t47;
    unsigned int t48;
    unsigned int t49;
    unsigned int t50;
    unsigned int t51;
    unsigned int t52;
    unsigned int t53;

LAB0:    t1 = (t0 + 4848U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(42, ng0);
    t2 = (t0 + 5168);
    *((int *)t2) = 1;
    t3 = (t0 + 4880);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(42, ng0);

LAB5:    xsi_set_current_line(44, ng0);
    t5 = (t0 + 1208U);
    t6 = *((char **)t5);
    memset(t4, 0, 8);
    t5 = (t4 + 4);
    t7 = (t6 + 4);
    t8 = *((unsigned int *)t6);
    t9 = (t8 >> 4);
    *((unsigned int *)t4) = t9;
    t10 = *((unsigned int *)t7);
    t11 = (t10 >> 4);
    *((unsigned int *)t5) = t11;
    t12 = *((unsigned int *)t4);
    *((unsigned int *)t4) = (t12 & 3U);
    t13 = *((unsigned int *)t5);
    *((unsigned int *)t5) = (t13 & 3U);
    t14 = (t0 + 1768);
    xsi_vlogvar_assign_value(t14, t4, 0, 0, 2);
    xsi_set_current_line(45, ng0);
    t2 = (t0 + 1208U);
    t3 = *((char **)t2);
    memset(t4, 0, 8);
    t2 = (t4 + 4);
    t5 = (t3 + 4);
    t8 = *((unsigned int *)t3);
    t9 = (t8 >> 0);
    *((unsigned int *)t4) = t9;
    t10 = *((unsigned int *)t5);
    t11 = (t10 >> 0);
    *((unsigned int *)t2) = t11;
    t12 = *((unsigned int *)t4);
    *((unsigned int *)t4) = (t12 & 15U);
    t13 = *((unsigned int *)t2);
    *((unsigned int *)t2) = (t13 & 15U);
    t6 = (t0 + 3208);
    xsi_vlogvar_assign_value(t6, t4, 0, 0, 4);
    xsi_set_current_line(48, ng0);
    t2 = (t0 + 1768);
    t3 = (t2 + 56U);
    t5 = *((char **)t3);

LAB6:    t6 = ((char*)((ng1)));
    t15 = xsi_vlog_unsigned_case_compare(t5, 2, t6, 2);
    if (t15 == 1)
        goto LAB7;

LAB8:    t2 = ((char*)((ng6)));
    t15 = xsi_vlog_unsigned_case_compare(t5, 2, t2, 2);
    if (t15 == 1)
        goto LAB9;

LAB10:    t2 = ((char*)((ng7)));
    t15 = xsi_vlog_unsigned_case_compare(t5, 2, t2, 2);
    if (t15 == 1)
        goto LAB11;

LAB12:    t2 = ((char*)((ng8)));
    t15 = xsi_vlog_unsigned_case_compare(t5, 2, t2, 2);
    if (t15 == 1)
        goto LAB13;

LAB14:
LAB16:
LAB15:    xsi_set_current_line(53, ng0);
    t2 = (t0 + 2568);
    t3 = (t2 + 56U);
    t6 = *((char **)t3);
    t7 = (t0 + 3368);
    xsi_vlogvar_assign_value(t7, t6, 0, 0, 16);

LAB17:    xsi_set_current_line(57, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 2248);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(58, ng0);
    t2 = ((char*)((ng1)));
    t3 = (t0 + 2408);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(60, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);

LAB18:    t2 = ((char*)((ng6)));
    t15 = xsi_vlog_unsigned_case_compare(t3, 2, t2, 2);
    if (t15 == 1)
        goto LAB19;

LAB20:    t2 = ((char*)((ng1)));
    t15 = xsi_vlog_unsigned_case_compare(t3, 2, t2, 2);
    if (t15 == 1)
        goto LAB21;

LAB22:    t2 = ((char*)((ng7)));
    t15 = xsi_vlog_unsigned_case_compare(t3, 2, t2, 2);
    if (t15 == 1)
        goto LAB23;

LAB24:    t2 = ((char*)((ng8)));
    t15 = xsi_vlog_unsigned_case_compare(t3, 2, t2, 2);
    if (t15 == 1)
        goto LAB25;

LAB26:
LAB28:
LAB27:
LAB29:    xsi_set_current_line(105, ng0);
    t2 = (t0 + 1768);
    t6 = (t2 + 56U);
    t7 = *((char **)t6);

LAB65:    t14 = ((char*)((ng1)));
    t15 = xsi_vlog_unsigned_case_compare(t7, 2, t14, 2);
    if (t15 == 1)
        goto LAB66;

LAB67:    t2 = ((char*)((ng6)));
    t15 = xsi_vlog_unsigned_case_compare(t7, 2, t2, 2);
    if (t15 == 1)
        goto LAB68;

LAB69:    t2 = ((char*)((ng7)));
    t15 = xsi_vlog_unsigned_case_compare(t7, 2, t2, 2);
    if (t15 == 1)
        goto LAB70;

LAB71:    t2 = ((char*)((ng8)));
    t15 = xsi_vlog_unsigned_case_compare(t7, 2, t2, 2);
    if (t15 == 1)
        goto LAB72;

LAB73:
LAB74:    xsi_set_current_line(113, ng0);
    t2 = (t0 + 3528);
    t6 = (t2 + 56U);
    t14 = *((char **)t6);
    t16 = (t0 + 3528);
    t17 = (t16 + 72U);
    t18 = *((char **)t17);
    t19 = (t0 + 3528);
    t20 = (t19 + 64U);
    t21 = *((char **)t20);
    t22 = (t0 + 1768);
    t23 = (t22 + 56U);
    t24 = *((char **)t23);
    xsi_vlog_generic_get_array_select_value(t4, 6, t14, t18, t21, 2, 1, t24, 2, 2);
    t26 = (t0 + 1928);
    xsi_vlogvar_assign_value(t26, t4, 0, 0, 6);
    goto LAB2;

LAB7:    xsi_set_current_line(49, ng0);
    t7 = (t0 + 2568);
    t14 = (t7 + 56U);
    t16 = *((char **)t14);
    t17 = (t0 + 3368);
    xsi_vlogvar_assign_value(t17, t16, 0, 0, 16);
    goto LAB17;

LAB9:    xsi_set_current_line(50, ng0);
    t3 = (t0 + 2728);
    t6 = (t3 + 56U);
    t7 = *((char **)t6);
    t14 = (t0 + 3368);
    xsi_vlogvar_assign_value(t14, t7, 0, 0, 16);
    goto LAB17;

LAB11:    xsi_set_current_line(51, ng0);
    t3 = (t0 + 2888);
    t6 = (t3 + 56U);
    t7 = *((char **)t6);
    t14 = (t0 + 3368);
    xsi_vlogvar_assign_value(t14, t7, 0, 0, 16);
    goto LAB17;

LAB13:    xsi_set_current_line(52, ng0);
    t3 = (t0 + 3048);
    t6 = (t3 + 56U);
    t7 = *((char **)t6);
    t14 = (t0 + 3368);
    xsi_vlogvar_assign_value(t14, t7, 0, 0, 16);
    goto LAB17;

LAB19:    xsi_set_current_line(62, ng0);

LAB30:    xsi_set_current_line(63, ng0);
    t6 = (t0 + 3368);
    t7 = (t6 + 56U);
    t14 = *((char **)t7);
    t16 = (t0 + 3368);
    t17 = (t16 + 72U);
    t18 = *((char **)t17);
    t19 = (t0 + 3208);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    xsi_vlog_generic_get_index_select_value(t4, 1, t14, t18, 2, t21, 4, 2);
    t22 = (t4 + 4);
    t8 = *((unsigned int *)t22);
    t9 = (~(t8));
    t10 = *((unsigned int *)t4);
    t11 = (t10 & t9);
    t12 = (t11 != 0);
    if (t12 > 0)
        goto LAB31;

LAB32:    xsi_set_current_line(65, ng0);

LAB35:    xsi_set_current_line(66, ng0);
    t2 = ((char*)((ng6)));
    t6 = (t0 + 3368);
    t7 = (t0 + 3368);
    t14 = (t7 + 72U);
    t16 = *((char **)t14);
    t17 = (t0 + 3208);
    t18 = (t17 + 56U);
    t19 = *((char **)t18);
    xsi_vlog_generic_convert_bit_index(t4, t16, 2, t19, 4, 2);
    t20 = (t4 + 4);
    t8 = *((unsigned int *)t20);
    t15 = (!(t8));
    if (t15 == 1)
        goto LAB36;

LAB37:    xsi_set_current_line(67, ng0);
    t2 = (t0 + 3528);
    t6 = (t2 + 56U);
    t7 = *((char **)t6);
    t14 = (t0 + 3528);
    t16 = (t14 + 72U);
    t17 = *((char **)t16);
    t18 = (t0 + 3528);
    t19 = (t18 + 64U);
    t20 = *((char **)t19);
    t21 = (t0 + 1768);
    t22 = (t21 + 56U);
    t23 = *((char **)t22);
    xsi_vlog_generic_get_array_select_value(t4, 32, t7, t17, t20, 2, 1, t23, 2, 2);
    t24 = ((char*)((ng3)));
    memset(t25, 0, 8);
    xsi_vlog_unsigned_add(t25, 32, t4, 32, t24, 32);
    t26 = (t0 + 3528);
    t29 = (t0 + 3528);
    t30 = (t29 + 72U);
    t31 = *((char **)t30);
    t32 = (t0 + 3528);
    t33 = (t32 + 64U);
    t34 = *((char **)t33);
    t35 = (t0 + 1768);
    t36 = (t35 + 56U);
    t37 = *((char **)t36);
    xsi_vlog_generic_convert_array_indices(t27, t28, t31, t34, 2, 1, t37, 2, 2);
    t38 = (t27 + 4);
    t8 = *((unsigned int *)t38);
    t15 = (!(t8));
    t39 = (t28 + 4);
    t9 = *((unsigned int *)t39);
    t40 = (!(t9));
    t41 = (t15 && t40);
    if (t41 == 1)
        goto LAB38;

LAB39:
LAB33:    goto LAB29;

LAB21:    xsi_set_current_line(72, ng0);

LAB40:    xsi_set_current_line(73, ng0);
    t6 = (t0 + 3368);
    t7 = (t6 + 56U);
    t14 = *((char **)t7);
    t16 = (t0 + 3368);
    t17 = (t16 + 72U);
    t18 = *((char **)t17);
    t19 = (t0 + 3208);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    xsi_vlog_generic_get_index_select_value(t4, 1, t14, t18, 2, t21, 4, 2);
    t22 = (t4 + 4);
    t8 = *((unsigned int *)t22);
    t9 = (~(t8));
    t10 = *((unsigned int *)t4);
    t11 = (t10 & t9);
    t12 = (t11 != 0);
    if (t12 > 0)
        goto LAB41;

LAB42:    xsi_set_current_line(76, ng0);

LAB49:    xsi_set_current_line(77, ng0);
    t2 = ((char*)((ng6)));
    t6 = (t0 + 2408);
    xsi_vlogvar_assign_value(t6, t2, 0, 0, 1);

LAB43:    goto LAB29;

LAB23:    xsi_set_current_line(82, ng0);

LAB50:    xsi_set_current_line(83, ng0);
    t6 = (t0 + 3368);
    t7 = (t6 + 56U);
    t14 = *((char **)t7);
    t16 = (t0 + 3368);
    t17 = (t16 + 72U);
    t18 = *((char **)t17);
    t19 = (t0 + 3208);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    xsi_vlog_generic_get_index_select_value(t4, 1, t14, t18, 2, t21, 4, 2);
    t22 = (t4 + 4);
    t8 = *((unsigned int *)t22);
    t9 = (~(t8));
    t10 = *((unsigned int *)t4);
    t11 = (t10 & t9);
    t12 = (t11 != 0);
    if (t12 > 0)
        goto LAB51;

LAB52:    xsi_set_current_line(85, ng0);

LAB55:    xsi_set_current_line(86, ng0);
    t2 = ((char*)((ng6)));
    t6 = (t0 + 2408);
    xsi_vlogvar_assign_value(t6, t2, 0, 0, 1);

LAB53:    goto LAB29;

LAB25:    xsi_set_current_line(91, ng0);

LAB56:    xsi_set_current_line(92, ng0);
    t6 = ((char*)((ng1)));
    t7 = (t0 + 2088);
    xsi_vlogvar_assign_value(t7, t6, 0, 0, 6);
    xsi_set_current_line(93, ng0);
    xsi_set_current_line(93, ng0);
    t2 = ((char*)((ng2)));
    t6 = (t0 + 3688);
    xsi_vlogvar_assign_value(t6, t2, 0, 0, 32);

LAB57:    t2 = (t0 + 3688);
    t6 = (t2 + 56U);
    t7 = *((char **)t6);
    t14 = ((char*)((ng9)));
    memset(t4, 0, 8);
    xsi_vlog_signed_less(t4, 32, t7, 32, t14, 32);
    t16 = (t4 + 4);
    t8 = *((unsigned int *)t16);
    t9 = (~(t8));
    t10 = *((unsigned int *)t4);
    t11 = (t10 & t9);
    t12 = (t11 != 0);
    if (t12 > 0)
        goto LAB58;

LAB59:    goto LAB29;

LAB31:    xsi_set_current_line(63, ng0);

LAB34:    xsi_set_current_line(64, ng0);
    t23 = ((char*)((ng6)));
    t24 = (t0 + 2248);
    xsi_vlogvar_assign_value(t24, t23, 0, 0, 1);
    goto LAB33;

LAB36:    xsi_vlogvar_assign_value(t6, t2, 0, *((unsigned int *)t4), 1);
    goto LAB37;

LAB38:    t10 = *((unsigned int *)t27);
    t11 = *((unsigned int *)t28);
    t42 = (t10 - t11);
    t43 = (t42 + 1);
    xsi_vlogvar_assign_value(t26, t25, 0, *((unsigned int *)t28), t43);
    goto LAB39;

LAB41:    xsi_set_current_line(73, ng0);

LAB44:    xsi_set_current_line(74, ng0);
    t23 = ((char*)((ng1)));
    t24 = (t0 + 3368);
    t26 = (t0 + 3368);
    t29 = (t26 + 72U);
    t30 = *((char **)t29);
    t31 = (t0 + 3208);
    t32 = (t31 + 56U);
    t33 = *((char **)t32);
    xsi_vlog_generic_convert_bit_index(t25, t30, 2, t33, 4, 2);
    t34 = (t25 + 4);
    t13 = *((unsigned int *)t34);
    t40 = (!(t13));
    if (t40 == 1)
        goto LAB45;

LAB46:    xsi_set_current_line(75, ng0);
    t2 = (t0 + 3528);
    t6 = (t2 + 56U);
    t7 = *((char **)t6);
    t14 = (t0 + 3528);
    t16 = (t14 + 72U);
    t17 = *((char **)t16);
    t18 = (t0 + 3528);
    t19 = (t18 + 64U);
    t20 = *((char **)t19);
    t21 = (t0 + 1768);
    t22 = (t21 + 56U);
    t23 = *((char **)t22);
    xsi_vlog_generic_get_array_select_value(t4, 32, t7, t17, t20, 2, 1, t23, 2, 2);
    t24 = ((char*)((ng3)));
    memset(t25, 0, 8);
    xsi_vlog_unsigned_minus(t25, 32, t4, 32, t24, 32);
    t26 = (t0 + 3528);
    t29 = (t0 + 3528);
    t30 = (t29 + 72U);
    t31 = *((char **)t30);
    t32 = (t0 + 3528);
    t33 = (t32 + 64U);
    t34 = *((char **)t33);
    t35 = (t0 + 1768);
    t36 = (t35 + 56U);
    t37 = *((char **)t36);
    xsi_vlog_generic_convert_array_indices(t27, t28, t31, t34, 2, 1, t37, 2, 2);
    t38 = (t27 + 4);
    t8 = *((unsigned int *)t38);
    t15 = (!(t8));
    t39 = (t28 + 4);
    t9 = *((unsigned int *)t39);
    t40 = (!(t9));
    t41 = (t15 && t40);
    if (t41 == 1)
        goto LAB47;

LAB48:    goto LAB43;

LAB45:    xsi_vlogvar_assign_value(t24, t23, 0, *((unsigned int *)t25), 1);
    goto LAB46;

LAB47:    t10 = *((unsigned int *)t27);
    t11 = *((unsigned int *)t28);
    t42 = (t10 - t11);
    t43 = (t42 + 1);
    xsi_vlogvar_assign_value(t26, t25, 0, *((unsigned int *)t28), t43);
    goto LAB48;

LAB51:    xsi_set_current_line(83, ng0);

LAB54:    xsi_set_current_line(84, ng0);
    t23 = ((char*)((ng6)));
    t24 = (t0 + 2248);
    xsi_vlogvar_assign_value(t24, t23, 0, 0, 1);
    goto LAB53;

LAB58:    xsi_set_current_line(93, ng0);

LAB60:    xsi_set_current_line(94, ng0);
    t17 = (t0 + 3368);
    t18 = (t17 + 56U);
    t19 = *((char **)t18);
    t20 = (t0 + 3368);
    t21 = (t20 + 72U);
    t22 = *((char **)t21);
    t23 = (t0 + 3688);
    t24 = (t23 + 56U);
    t26 = *((char **)t24);
    xsi_vlog_generic_get_index_select_value(t25, 1, t19, t22, 2, t26, 32, 1);
    t29 = (t25 + 4);
    t13 = *((unsigned int *)t29);
    t44 = (~(t13));
    t45 = *((unsigned int *)t25);
    t46 = (t45 & t44);
    t47 = (t46 != 0);
    if (t47 > 0)
        goto LAB61;

LAB62:
LAB63:    xsi_set_current_line(93, ng0);
    t2 = (t0 + 3688);
    t6 = (t2 + 56U);
    t7 = *((char **)t6);
    t14 = ((char*)((ng3)));
    memset(t4, 0, 8);
    xsi_vlog_signed_add(t4, 32, t7, 32, t14, 32);
    t16 = (t0 + 3688);
    xsi_vlogvar_assign_value(t16, t4, 0, 0, 32);
    goto LAB57;

LAB61:    xsi_set_current_line(94, ng0);

LAB64:    xsi_set_current_line(95, ng0);
    t30 = (t0 + 3688);
    t31 = (t30 + 56U);
    t32 = *((char **)t31);
    memset(t28, 0, 8);
    t33 = (t28 + 4);
    t34 = (t32 + 4);
    t48 = *((unsigned int *)t32);
    t49 = (t48 >> 0);
    *((unsigned int *)t28) = t49;
    t50 = *((unsigned int *)t34);
    t51 = (t50 >> 0);
    *((unsigned int *)t33) = t51;
    t52 = *((unsigned int *)t28);
    *((unsigned int *)t28) = (t52 & 15U);
    t53 = *((unsigned int *)t33);
    *((unsigned int *)t33) = (t53 & 15U);
    t35 = (t0 + 1768);
    t36 = (t35 + 56U);
    t37 = *((char **)t36);
    xsi_vlogtype_concat(t27, 6, 6, 2U, t37, 2, t28, 4);
    t38 = (t0 + 2088);
    xsi_vlogvar_assign_value(t38, t27, 0, 0, 6);
    goto LAB63;

LAB66:    xsi_set_current_line(106, ng0);
    t16 = (t0 + 3368);
    t17 = (t16 + 56U);
    t18 = *((char **)t17);
    t19 = (t0 + 2568);
    xsi_vlogvar_assign_value(t19, t18, 0, 0, 16);
    goto LAB74;

LAB68:    xsi_set_current_line(107, ng0);
    t6 = (t0 + 3368);
    t14 = (t6 + 56U);
    t16 = *((char **)t14);
    t17 = (t0 + 2728);
    xsi_vlogvar_assign_value(t17, t16, 0, 0, 16);
    goto LAB74;

LAB70:    xsi_set_current_line(108, ng0);
    t6 = (t0 + 3368);
    t14 = (t6 + 56U);
    t16 = *((char **)t14);
    t17 = (t0 + 2888);
    xsi_vlogvar_assign_value(t17, t16, 0, 0, 16);
    goto LAB74;

LAB72:    xsi_set_current_line(109, ng0);
    t6 = (t0 + 3368);
    t14 = (t6 + 56U);
    t16 = *((char **)t14);
    t17 = (t0 + 3048);
    xsi_vlogvar_assign_value(t17, t16, 0, 0, 16);
    goto LAB74;

}


extern void work_m_05423319316808623638_1250168862_init()
{
	static char *pe[] = {(void *)Initial_25_0,(void *)Always_42_1};
	xsi_register_didat("work_m_05423319316808623638_1250168862", "isim/testbench_isim_beh.exe.sim/work/m_05423319316808623638_1250168862.didat");
	xsi_register_executes(pe);
}
