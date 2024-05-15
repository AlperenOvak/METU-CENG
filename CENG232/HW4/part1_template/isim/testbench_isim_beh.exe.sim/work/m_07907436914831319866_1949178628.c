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
static const char *ng0 = "/home/ise/HW4/part1_template/testbench_p1.v";
static int ng1[] = {0, 0};
static const char *ng2 = "Rom test begin";
static unsigned int ng3[] = {0U, 0U};
static int ng4[] = {1, 0, 0, 0};
static const char *ng5 = "Pass case 1";
static const char *ng6 = "";
static const char *ng7 = "Error in case 1";
static unsigned int ng8[] = {1U, 0U};
static const char *ng9 = "Pass case 2";
static const char *ng10 = "Error in case 2";
static unsigned int ng11[] = {2U, 0U};
static const char *ng12 = "Pass case 3";
static const char *ng13 = "Error in case 3";
static unsigned int ng14[] = {3U, 0U};
static unsigned int ng15[] = {35U, 0U};
static const char *ng16 = "Pass case 4";
static const char *ng17 = "Error in case 4";
static unsigned int ng18[] = {4U, 0U};
static unsigned int ng19[] = {196U, 0U};
static const char *ng20 = "Pass case 5";
static const char *ng21 = "Error in case 5";
static unsigned int ng22[] = {5U, 0U};
static unsigned int ng23[] = {101U, 0U};
static const char *ng24 = "Pass case 6";
static const char *ng25 = "Error in case 6";
static unsigned int ng26[] = {6U, 0U};
static unsigned int ng27[] = {30U, 0U};
static const char *ng28 = "Pass case 7";
static const char *ng29 = "Error in case 7";
static unsigned int ng30[] = {7U, 0U};
static unsigned int ng31[] = {69U, 0U};
static const char *ng32 = "Pass case 8";
static const char *ng33 = "Error in case 8";
static const char *ng34 = "Ram test begin";
static const char *ng35 = "Error in case 9";
static const char *ng36 = "RAM_dataOut: %b";
static unsigned int ng37[] = {87U, 0U};
static const char *ng38 = "Error in case 10";
static unsigned int ng39[] = {248U, 0U};
static const char *ng40 = "Error in case 11";
static const char *ng41 = "Error in case 12";
static const char *ng42 = "Error in case 13";
static const char *ng43 = "Result is:%2.2f";



static void Initial_43_0(char *t0)
{
    char *t1;
    char *t2;

LAB0:    xsi_set_current_line(43, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 1768);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 1);

LAB1:    return;
}

static void Always_44_1(char *t0)
{
    char t3[8];
    char *t1;
    char *t2;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    unsigned int t8;
    unsigned int t9;
    unsigned int t10;
    unsigned int t11;
    unsigned int t12;
    char *t13;
    char *t14;
    char *t15;
    unsigned int t16;
    unsigned int t17;
    unsigned int t18;
    unsigned int t19;
    unsigned int t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    char *t24;

LAB0:    t1 = (t0 + 4848U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(44, ng0);
    t2 = (t0 + 4656);
    xsi_process_wait(t2, 5000LL);
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(44, ng0);
    t4 = (t0 + 1768);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    memset(t3, 0, 8);
    t7 = (t6 + 4);
    t8 = *((unsigned int *)t7);
    t9 = (~(t8));
    t10 = *((unsigned int *)t6);
    t11 = (t10 & t9);
    t12 = (t11 & 1U);
    if (t12 != 0)
        goto LAB8;

LAB6:    if (*((unsigned int *)t7) == 0)
        goto LAB5;

LAB7:    t13 = (t3 + 4);
    *((unsigned int *)t3) = 1;
    *((unsigned int *)t13) = 1;

LAB8:    t14 = (t3 + 4);
    t15 = (t6 + 4);
    t16 = *((unsigned int *)t6);
    t17 = (~(t16));
    *((unsigned int *)t3) = t17;
    *((unsigned int *)t14) = 0;
    if (*((unsigned int *)t15) != 0)
        goto LAB10;

LAB9:    t22 = *((unsigned int *)t3);
    *((unsigned int *)t3) = (t22 & 1U);
    t23 = *((unsigned int *)t14);
    *((unsigned int *)t14) = (t23 & 1U);
    t24 = (t0 + 1768);
    xsi_vlogvar_assign_value(t24, t3, 0, 0, 1);
    goto LAB2;

LAB5:    *((unsigned int *)t3) = 1;
    goto LAB8;

LAB10:    t18 = *((unsigned int *)t3);
    t19 = *((unsigned int *)t15);
    *((unsigned int *)t3) = (t18 | t19);
    t20 = *((unsigned int *)t14);
    t21 = *((unsigned int *)t15);
    *((unsigned int *)t14) = (t20 | t21);
    goto LAB9;

}

static void Initial_49_2(char *t0)
{
    char t5[8];
    char t35[8];
    char t72[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t6;
    char *t7;
    unsigned int t8;
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
    char *t20;
    char *t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    unsigned int t26;
    char *t27;
    char *t28;
    char *t29;
    double t30;
    char *t31;
    double t32;
    double t33;
    char *t34;
    char *t36;
    char *t37;
    unsigned int t38;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    unsigned int t42;
    char *t43;
    char *t44;
    unsigned int t45;
    unsigned int t46;
    unsigned int t47;
    unsigned int t48;
    unsigned int t49;
    unsigned int t50;
    unsigned int t51;
    unsigned int t52;
    int t53;
    int t54;
    unsigned int t55;
    unsigned int t56;
    unsigned int t57;
    unsigned int t58;
    unsigned int t59;
    unsigned int t60;
    char *t61;
    unsigned int t62;
    unsigned int t63;
    unsigned int t64;
    unsigned int t65;
    unsigned int t66;
    char *t67;
    char *t68;
    char *t69;
    char *t70;
    char *t71;
    unsigned int t73;
    unsigned int t74;
    unsigned int t75;
    unsigned int t76;
    unsigned int t77;
    unsigned int t78;
    unsigned int t79;
    unsigned int t80;
    char *t81;
    char *t82;

LAB0:    t1 = (t0 + 5096U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(49, ng0);

LAB4:    xsi_set_current_line(50, ng0);
    xsi_vlogfile_write(1, 0, 0, ng2, 1, t0);
    xsi_set_current_line(56, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB5;

LAB1:    return;
LAB5:    xsi_set_current_line(56, ng0);
    t3 = ((char*)((ng3)));
    t4 = (t0 + 2088);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 3);
    xsi_set_current_line(57, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB6;
    goto LAB1;

LAB6:    xsi_set_current_line(58, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    t3 = ((char*)((ng3)));
    memset(t5, 0, 8);
    t6 = (t4 + 4);
    t7 = (t3 + 4);
    t8 = *((unsigned int *)t4);
    t9 = *((unsigned int *)t3);
    t10 = (t8 ^ t9);
    t11 = *((unsigned int *)t6);
    t12 = *((unsigned int *)t7);
    t13 = (t11 ^ t12);
    t14 = (t10 | t13);
    t15 = *((unsigned int *)t6);
    t16 = *((unsigned int *)t7);
    t17 = (t15 | t16);
    t18 = (~(t17));
    t19 = (t14 & t18);
    if (t19 != 0)
        goto LAB10;

LAB7:    if (t17 != 0)
        goto LAB9;

LAB8:    *((unsigned int *)t5) = 1;

LAB10:    t21 = (t5 + 4);
    t22 = *((unsigned int *)t21);
    t23 = (~(t22));
    t24 = *((unsigned int *)t5);
    t25 = (t24 & t23);
    t26 = (t25 != 0);
    if (t26 > 0)
        goto LAB11;

LAB12:    xsi_set_current_line(62, ng0);

LAB15:    xsi_set_current_line(63, ng0);
    xsi_vlogfile_write(1, 0, 0, ng7, 1, t0);

LAB13:    xsi_set_current_line(66, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB16;
    goto LAB1;

LAB9:    t20 = (t5 + 4);
    *((unsigned int *)t5) = 1;
    *((unsigned int *)t20) = 1;
    goto LAB10;

LAB11:    xsi_set_current_line(58, ng0);

LAB14:    xsi_set_current_line(59, ng0);
    t27 = (t0 + 1928);
    t28 = (t27 + 56U);
    t29 = *((char **)t28);
    t30 = *((double *)t29);
    t31 = ((char*)((ng4)));
    t32 = xsi_vlog_convert_to_real(t31, 32, 1);
    t33 = (t30 + t32);
    t34 = (t0 + 1928);
    xsi_vlogvar_assign_value_double(t34, t33, 0);
    xsi_set_current_line(60, ng0);
    xsi_vlogfile_write(1, 0, 0, ng5, 1, t0);
    xsi_set_current_line(61, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    xsi_vlogfile_write(1, 0, 0, ng6, 2, t0, (char)118, t3, 8);
    goto LAB13;

LAB16:    xsi_set_current_line(66, ng0);
    t3 = ((char*)((ng8)));
    t4 = (t0 + 2088);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 3);
    xsi_set_current_line(67, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB17;
    goto LAB1;

LAB17:    xsi_set_current_line(68, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    t3 = ((char*)((ng8)));
    memset(t5, 0, 8);
    t6 = (t4 + 4);
    t7 = (t3 + 4);
    t8 = *((unsigned int *)t4);
    t9 = *((unsigned int *)t3);
    t10 = (t8 ^ t9);
    t11 = *((unsigned int *)t6);
    t12 = *((unsigned int *)t7);
    t13 = (t11 ^ t12);
    t14 = (t10 | t13);
    t15 = *((unsigned int *)t6);
    t16 = *((unsigned int *)t7);
    t17 = (t15 | t16);
    t18 = (~(t17));
    t19 = (t14 & t18);
    if (t19 != 0)
        goto LAB21;

LAB18:    if (t17 != 0)
        goto LAB20;

LAB19:    *((unsigned int *)t5) = 1;

LAB21:    t21 = (t5 + 4);
    t22 = *((unsigned int *)t21);
    t23 = (~(t22));
    t24 = *((unsigned int *)t5);
    t25 = (t24 & t23);
    t26 = (t25 != 0);
    if (t26 > 0)
        goto LAB22;

LAB23:    xsi_set_current_line(72, ng0);

LAB26:    xsi_set_current_line(73, ng0);
    xsi_vlogfile_write(1, 0, 0, ng10, 1, t0);

LAB24:    xsi_set_current_line(76, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB27;
    goto LAB1;

LAB20:    t20 = (t5 + 4);
    *((unsigned int *)t5) = 1;
    *((unsigned int *)t20) = 1;
    goto LAB21;

LAB22:    xsi_set_current_line(68, ng0);

LAB25:    xsi_set_current_line(69, ng0);
    t27 = (t0 + 1928);
    t28 = (t27 + 56U);
    t29 = *((char **)t28);
    t30 = *((double *)t29);
    t31 = ((char*)((ng4)));
    t32 = xsi_vlog_convert_to_real(t31, 32, 1);
    t33 = (t30 + t32);
    t34 = (t0 + 1928);
    xsi_vlogvar_assign_value_double(t34, t33, 0);
    xsi_set_current_line(70, ng0);
    xsi_vlogfile_write(1, 0, 0, ng9, 1, t0);
    xsi_set_current_line(71, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    xsi_vlogfile_write(1, 0, 0, ng6, 2, t0, (char)118, t3, 8);
    goto LAB24;

LAB27:    xsi_set_current_line(76, ng0);
    t3 = ((char*)((ng11)));
    t4 = (t0 + 2088);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 3);
    xsi_set_current_line(77, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB28;
    goto LAB1;

LAB28:    xsi_set_current_line(78, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    t3 = ((char*)((ng11)));
    memset(t5, 0, 8);
    t6 = (t4 + 4);
    t7 = (t3 + 4);
    t8 = *((unsigned int *)t4);
    t9 = *((unsigned int *)t3);
    t10 = (t8 ^ t9);
    t11 = *((unsigned int *)t6);
    t12 = *((unsigned int *)t7);
    t13 = (t11 ^ t12);
    t14 = (t10 | t13);
    t15 = *((unsigned int *)t6);
    t16 = *((unsigned int *)t7);
    t17 = (t15 | t16);
    t18 = (~(t17));
    t19 = (t14 & t18);
    if (t19 != 0)
        goto LAB32;

LAB29:    if (t17 != 0)
        goto LAB31;

LAB30:    *((unsigned int *)t5) = 1;

LAB32:    t21 = (t5 + 4);
    t22 = *((unsigned int *)t21);
    t23 = (~(t22));
    t24 = *((unsigned int *)t5);
    t25 = (t24 & t23);
    t26 = (t25 != 0);
    if (t26 > 0)
        goto LAB33;

LAB34:    xsi_set_current_line(82, ng0);

LAB37:    xsi_set_current_line(83, ng0);
    xsi_vlogfile_write(1, 0, 0, ng13, 1, t0);

LAB35:    xsi_set_current_line(86, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB38;
    goto LAB1;

LAB31:    t20 = (t5 + 4);
    *((unsigned int *)t5) = 1;
    *((unsigned int *)t20) = 1;
    goto LAB32;

LAB33:    xsi_set_current_line(78, ng0);

LAB36:    xsi_set_current_line(79, ng0);
    t27 = (t0 + 1928);
    t28 = (t27 + 56U);
    t29 = *((char **)t28);
    t30 = *((double *)t29);
    t31 = ((char*)((ng4)));
    t32 = xsi_vlog_convert_to_real(t31, 32, 1);
    t33 = (t30 + t32);
    t34 = (t0 + 1928);
    xsi_vlogvar_assign_value_double(t34, t33, 0);
    xsi_set_current_line(80, ng0);
    xsi_vlogfile_write(1, 0, 0, ng12, 1, t0);
    xsi_set_current_line(81, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    xsi_vlogfile_write(1, 0, 0, ng6, 2, t0, (char)118, t3, 8);
    goto LAB35;

LAB38:    xsi_set_current_line(86, ng0);
    t3 = ((char*)((ng14)));
    t4 = (t0 + 2088);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 3);
    xsi_set_current_line(87, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB39;
    goto LAB1;

LAB39:    xsi_set_current_line(88, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    t3 = ((char*)((ng15)));
    memset(t5, 0, 8);
    t6 = (t4 + 4);
    t7 = (t3 + 4);
    t8 = *((unsigned int *)t4);
    t9 = *((unsigned int *)t3);
    t10 = (t8 ^ t9);
    t11 = *((unsigned int *)t6);
    t12 = *((unsigned int *)t7);
    t13 = (t11 ^ t12);
    t14 = (t10 | t13);
    t15 = *((unsigned int *)t6);
    t16 = *((unsigned int *)t7);
    t17 = (t15 | t16);
    t18 = (~(t17));
    t19 = (t14 & t18);
    if (t19 != 0)
        goto LAB43;

LAB40:    if (t17 != 0)
        goto LAB42;

LAB41:    *((unsigned int *)t5) = 1;

LAB43:    t21 = (t5 + 4);
    t22 = *((unsigned int *)t21);
    t23 = (~(t22));
    t24 = *((unsigned int *)t5);
    t25 = (t24 & t23);
    t26 = (t25 != 0);
    if (t26 > 0)
        goto LAB44;

LAB45:    xsi_set_current_line(92, ng0);

LAB48:    xsi_set_current_line(93, ng0);
    xsi_vlogfile_write(1, 0, 0, ng17, 1, t0);

LAB46:    xsi_set_current_line(96, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB49;
    goto LAB1;

LAB42:    t20 = (t5 + 4);
    *((unsigned int *)t5) = 1;
    *((unsigned int *)t20) = 1;
    goto LAB43;

LAB44:    xsi_set_current_line(88, ng0);

LAB47:    xsi_set_current_line(89, ng0);
    t27 = (t0 + 1928);
    t28 = (t27 + 56U);
    t29 = *((char **)t28);
    t30 = *((double *)t29);
    t31 = ((char*)((ng4)));
    t32 = xsi_vlog_convert_to_real(t31, 32, 1);
    t33 = (t30 + t32);
    t34 = (t0 + 1928);
    xsi_vlogvar_assign_value_double(t34, t33, 0);
    xsi_set_current_line(90, ng0);
    xsi_vlogfile_write(1, 0, 0, ng16, 1, t0);
    xsi_set_current_line(91, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    xsi_vlogfile_write(1, 0, 0, ng6, 2, t0, (char)118, t3, 8);
    goto LAB46;

LAB49:    xsi_set_current_line(96, ng0);
    t3 = ((char*)((ng18)));
    t4 = (t0 + 2088);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 3);
    xsi_set_current_line(97, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB50;
    goto LAB1;

LAB50:    xsi_set_current_line(98, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    t3 = ((char*)((ng19)));
    memset(t5, 0, 8);
    t6 = (t4 + 4);
    t7 = (t3 + 4);
    t8 = *((unsigned int *)t4);
    t9 = *((unsigned int *)t3);
    t10 = (t8 ^ t9);
    t11 = *((unsigned int *)t6);
    t12 = *((unsigned int *)t7);
    t13 = (t11 ^ t12);
    t14 = (t10 | t13);
    t15 = *((unsigned int *)t6);
    t16 = *((unsigned int *)t7);
    t17 = (t15 | t16);
    t18 = (~(t17));
    t19 = (t14 & t18);
    if (t19 != 0)
        goto LAB54;

LAB51:    if (t17 != 0)
        goto LAB53;

LAB52:    *((unsigned int *)t5) = 1;

LAB54:    t21 = (t5 + 4);
    t22 = *((unsigned int *)t21);
    t23 = (~(t22));
    t24 = *((unsigned int *)t5);
    t25 = (t24 & t23);
    t26 = (t25 != 0);
    if (t26 > 0)
        goto LAB55;

LAB56:    xsi_set_current_line(102, ng0);

LAB59:    xsi_set_current_line(103, ng0);
    xsi_vlogfile_write(1, 0, 0, ng21, 1, t0);

LAB57:    xsi_set_current_line(106, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB60;
    goto LAB1;

LAB53:    t20 = (t5 + 4);
    *((unsigned int *)t5) = 1;
    *((unsigned int *)t20) = 1;
    goto LAB54;

LAB55:    xsi_set_current_line(98, ng0);

LAB58:    xsi_set_current_line(99, ng0);
    t27 = (t0 + 1928);
    t28 = (t27 + 56U);
    t29 = *((char **)t28);
    t30 = *((double *)t29);
    t31 = ((char*)((ng4)));
    t32 = xsi_vlog_convert_to_real(t31, 32, 1);
    t33 = (t30 + t32);
    t34 = (t0 + 1928);
    xsi_vlogvar_assign_value_double(t34, t33, 0);
    xsi_set_current_line(100, ng0);
    xsi_vlogfile_write(1, 0, 0, ng20, 1, t0);
    xsi_set_current_line(101, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    xsi_vlogfile_write(1, 0, 0, ng6, 2, t0, (char)118, t3, 8);
    goto LAB57;

LAB60:    xsi_set_current_line(106, ng0);
    t3 = ((char*)((ng22)));
    t4 = (t0 + 2088);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 3);
    xsi_set_current_line(107, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB61;
    goto LAB1;

LAB61:    xsi_set_current_line(108, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    t3 = ((char*)((ng23)));
    memset(t5, 0, 8);
    t6 = (t4 + 4);
    t7 = (t3 + 4);
    t8 = *((unsigned int *)t4);
    t9 = *((unsigned int *)t3);
    t10 = (t8 ^ t9);
    t11 = *((unsigned int *)t6);
    t12 = *((unsigned int *)t7);
    t13 = (t11 ^ t12);
    t14 = (t10 | t13);
    t15 = *((unsigned int *)t6);
    t16 = *((unsigned int *)t7);
    t17 = (t15 | t16);
    t18 = (~(t17));
    t19 = (t14 & t18);
    if (t19 != 0)
        goto LAB65;

LAB62:    if (t17 != 0)
        goto LAB64;

LAB63:    *((unsigned int *)t5) = 1;

LAB65:    t21 = (t5 + 4);
    t22 = *((unsigned int *)t21);
    t23 = (~(t22));
    t24 = *((unsigned int *)t5);
    t25 = (t24 & t23);
    t26 = (t25 != 0);
    if (t26 > 0)
        goto LAB66;

LAB67:    xsi_set_current_line(112, ng0);

LAB70:    xsi_set_current_line(113, ng0);
    xsi_vlogfile_write(1, 0, 0, ng25, 1, t0);

LAB68:    xsi_set_current_line(116, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB71;
    goto LAB1;

LAB64:    t20 = (t5 + 4);
    *((unsigned int *)t5) = 1;
    *((unsigned int *)t20) = 1;
    goto LAB65;

LAB66:    xsi_set_current_line(108, ng0);

LAB69:    xsi_set_current_line(109, ng0);
    t27 = (t0 + 1928);
    t28 = (t27 + 56U);
    t29 = *((char **)t28);
    t30 = *((double *)t29);
    t31 = ((char*)((ng4)));
    t32 = xsi_vlog_convert_to_real(t31, 32, 1);
    t33 = (t30 + t32);
    t34 = (t0 + 1928);
    xsi_vlogvar_assign_value_double(t34, t33, 0);
    xsi_set_current_line(110, ng0);
    xsi_vlogfile_write(1, 0, 0, ng24, 1, t0);
    xsi_set_current_line(111, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    xsi_vlogfile_write(1, 0, 0, ng6, 2, t0, (char)118, t3, 8);
    goto LAB68;

LAB71:    xsi_set_current_line(116, ng0);
    t3 = ((char*)((ng26)));
    t4 = (t0 + 2088);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 3);
    xsi_set_current_line(117, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB72;
    goto LAB1;

LAB72:    xsi_set_current_line(118, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    t3 = ((char*)((ng27)));
    memset(t5, 0, 8);
    t6 = (t4 + 4);
    t7 = (t3 + 4);
    t8 = *((unsigned int *)t4);
    t9 = *((unsigned int *)t3);
    t10 = (t8 ^ t9);
    t11 = *((unsigned int *)t6);
    t12 = *((unsigned int *)t7);
    t13 = (t11 ^ t12);
    t14 = (t10 | t13);
    t15 = *((unsigned int *)t6);
    t16 = *((unsigned int *)t7);
    t17 = (t15 | t16);
    t18 = (~(t17));
    t19 = (t14 & t18);
    if (t19 != 0)
        goto LAB76;

LAB73:    if (t17 != 0)
        goto LAB75;

LAB74:    *((unsigned int *)t5) = 1;

LAB76:    t21 = (t5 + 4);
    t22 = *((unsigned int *)t21);
    t23 = (~(t22));
    t24 = *((unsigned int *)t5);
    t25 = (t24 & t23);
    t26 = (t25 != 0);
    if (t26 > 0)
        goto LAB77;

LAB78:    xsi_set_current_line(122, ng0);

LAB81:    xsi_set_current_line(123, ng0);
    xsi_vlogfile_write(1, 0, 0, ng29, 1, t0);

LAB79:    xsi_set_current_line(126, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB82;
    goto LAB1;

LAB75:    t20 = (t5 + 4);
    *((unsigned int *)t5) = 1;
    *((unsigned int *)t20) = 1;
    goto LAB76;

LAB77:    xsi_set_current_line(118, ng0);

LAB80:    xsi_set_current_line(119, ng0);
    t27 = (t0 + 1928);
    t28 = (t27 + 56U);
    t29 = *((char **)t28);
    t30 = *((double *)t29);
    t31 = ((char*)((ng4)));
    t32 = xsi_vlog_convert_to_real(t31, 32, 1);
    t33 = (t30 + t32);
    t34 = (t0 + 1928);
    xsi_vlogvar_assign_value_double(t34, t33, 0);
    xsi_set_current_line(120, ng0);
    xsi_vlogfile_write(1, 0, 0, ng28, 1, t0);
    xsi_set_current_line(121, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    xsi_vlogfile_write(1, 0, 0, ng6, 2, t0, (char)118, t3, 8);
    goto LAB79;

LAB82:    xsi_set_current_line(126, ng0);
    t3 = ((char*)((ng30)));
    t4 = (t0 + 2088);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 3);
    xsi_set_current_line(127, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB83;
    goto LAB1;

LAB83:    xsi_set_current_line(128, ng0);
    t3 = (t0 + 1048U);
    t4 = *((char **)t3);
    t3 = ((char*)((ng31)));
    memset(t5, 0, 8);
    t6 = (t4 + 4);
    t7 = (t3 + 4);
    t8 = *((unsigned int *)t4);
    t9 = *((unsigned int *)t3);
    t10 = (t8 ^ t9);
    t11 = *((unsigned int *)t6);
    t12 = *((unsigned int *)t7);
    t13 = (t11 ^ t12);
    t14 = (t10 | t13);
    t15 = *((unsigned int *)t6);
    t16 = *((unsigned int *)t7);
    t17 = (t15 | t16);
    t18 = (~(t17));
    t19 = (t14 & t18);
    if (t19 != 0)
        goto LAB87;

LAB84:    if (t17 != 0)
        goto LAB86;

LAB85:    *((unsigned int *)t5) = 1;

LAB87:    t21 = (t5 + 4);
    t22 = *((unsigned int *)t21);
    t23 = (~(t22));
    t24 = *((unsigned int *)t5);
    t25 = (t24 & t23);
    t26 = (t25 != 0);
    if (t26 > 0)
        goto LAB88;

LAB89:    xsi_set_current_line(132, ng0);

LAB92:    xsi_set_current_line(133, ng0);
    xsi_vlogfile_write(1, 0, 0, ng33, 1, t0);

LAB90:    xsi_set_current_line(136, ng0);
    xsi_vlogfile_write(1, 0, 0, ng34, 1, t0);
    xsi_set_current_line(141, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 6000LL);
    *((char **)t1) = &&LAB93;
    goto LAB1;

LAB86:    t20 = (t5 + 4);
    *((unsigned int *)t5) = 1;
    *((unsigned int *)t20) = 1;
    goto LAB87;

LAB88:    xsi_set_current_line(128, ng0);

LAB91:    xsi_set_current_line(129, ng0);
    t27 = (t0 + 1928);
    t28 = (t27 + 56U);
    t29 = *((char **)t28);
    t30 = *((double *)t29);
    t31 = ((char*)((ng4)));
    t32 = xsi_vlog_convert_to_real(t31, 32, 1);
    t33 = (t30 + t32);
    t34 = (t0 + 1928);
    xsi_vlogvar_assign_value_double(t34, t33, 0);
    xsi_set_current_line(130, ng0);
    xsi_vlogfile_write(1, 0, 0, ng32, 1, t0);
    xsi_set_current_line(131, ng0);
    t2 = (t0 + 1048U);
    t3 = *((char **)t2);
    xsi_vlogfile_write(1, 0, 0, ng6, 2, t0, (char)118, t3, 8);
    goto LAB90;

LAB93:    xsi_set_current_line(142, ng0);
    t3 = ((char*)((ng8)));
    t4 = (t0 + 2248);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 1);
    xsi_set_current_line(143, ng0);
    t2 = ((char*)((ng8)));
    t3 = (t0 + 2408);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 3);
    xsi_set_current_line(144, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 2000LL);
    *((char **)t1) = &&LAB94;
    goto LAB1;

LAB94:    xsi_set_current_line(145, ng0);
    t3 = (t0 + 1208U);
    t4 = *((char **)t3);
    t3 = ((char*)((ng1)));
    memset(t5, 0, 8);
    t6 = (t4 + 4);
    t7 = (t3 + 4);
    t8 = *((unsigned int *)t4);
    t9 = *((unsigned int *)t3);
    t10 = (t8 ^ t9);
    t11 = *((unsigned int *)t6);
    t12 = *((unsigned int *)t7);
    t13 = (t11 ^ t12);
    t14 = (t10 | t13);
    t15 = *((unsigned int *)t6);
    t16 = *((unsigned int *)t7);
    t17 = (t15 | t16);
    t18 = (~(t17));
    t19 = (t14 & t18);
    if (t19 != 0)
        goto LAB98;

LAB95:    if (t17 != 0)
        goto LAB97;

LAB96:    *((unsigned int *)t5) = 1;

LAB98:    t21 = (t5 + 4);
    t22 = *((unsigned int *)t21);
    t23 = (~(t22));
    t24 = *((unsigned int *)t5);
    t25 = (t24 & t23);
    t26 = (t25 != 0);
    if (t26 > 0)
        goto LAB99;

LAB100:    xsi_set_current_line(145, ng0);
    xsi_vlogfile_write(1, 0, 0, ng35, 1, t0);

LAB101:    xsi_set_current_line(146, ng0);
    t2 = (t0 + 1208U);
    t3 = *((char **)t2);
    xsi_vlogfile_write(1, 0, 0, ng36, 2, t0, (char)118, t3, 8);
    xsi_set_current_line(149, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB102;
    goto LAB1;

LAB97:    t20 = (t5 + 4);
    *((unsigned int *)t5) = 1;
    *((unsigned int *)t20) = 1;
    goto LAB98;

LAB99:    xsi_set_current_line(145, ng0);
    t27 = (t0 + 1928);
    t28 = (t27 + 56U);
    t29 = *((char **)t28);
    t30 = *((double *)t29);
    t31 = ((char*)((ng4)));
    t32 = xsi_vlog_convert_to_real(t31, 32, 1);
    t33 = (t30 + t32);
    t34 = (t0 + 1928);
    xsi_vlogvar_assign_value_double(t34, t33, 0);
    goto LAB101;

LAB102:    xsi_set_current_line(150, ng0);
    t3 = ((char*)((ng30)));
    t4 = (t0 + 2408);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 3);
    xsi_set_current_line(151, ng0);
    t2 = ((char*)((ng3)));
    t3 = (t0 + 2728);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 2);
    xsi_set_current_line(152, ng0);
    t2 = ((char*)((ng37)));
    t3 = (t0 + 2568);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 8);
    xsi_set_current_line(153, ng0);
    t2 = ((char*)((ng37)));
    t3 = (t0 + 2888);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 8);
    xsi_set_current_line(154, ng0);
    t2 = ((char*)((ng3)));
    t3 = (t0 + 2248);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(155, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB103;
    goto LAB1;

LAB103:    xsi_set_current_line(156, ng0);
    t3 = ((char*)((ng8)));
    t4 = (t0 + 2248);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 1);
    xsi_set_current_line(157, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB104;
    goto LAB1;

LAB104:    xsi_set_current_line(158, ng0);
    t3 = (t0 + 1208U);
    t4 = *((char **)t3);
    t3 = (t0 + 2568);
    t6 = (t3 + 56U);
    t7 = *((char **)t6);
    memset(t5, 0, 8);
    t20 = (t4 + 4);
    t21 = (t7 + 4);
    t8 = *((unsigned int *)t4);
    t9 = *((unsigned int *)t7);
    t10 = (t8 ^ t9);
    t11 = *((unsigned int *)t20);
    t12 = *((unsigned int *)t21);
    t13 = (t11 ^ t12);
    t14 = (t10 | t13);
    t15 = *((unsigned int *)t20);
    t16 = *((unsigned int *)t21);
    t17 = (t15 | t16);
    t18 = (~(t17));
    t19 = (t14 & t18);
    if (t19 != 0)
        goto LAB108;

LAB105:    if (t17 != 0)
        goto LAB107;

LAB106:    *((unsigned int *)t5) = 1;

LAB108:    t28 = (t0 + 2888);
    t29 = (t28 + 56U);
    t31 = *((char **)t29);
    t22 = *((unsigned int *)t5);
    t23 = *((unsigned int *)t31);
    t24 = (t22 & t23);
    *((unsigned int *)t35) = t24;
    t34 = (t5 + 4);
    t36 = (t31 + 4);
    t37 = (t35 + 4);
    t25 = *((unsigned int *)t34);
    t26 = *((unsigned int *)t36);
    t38 = (t25 | t26);
    *((unsigned int *)t37) = t38;
    t39 = *((unsigned int *)t37);
    t40 = (t39 != 0);
    if (t40 == 1)
        goto LAB109;

LAB110:
LAB111:    t61 = (t35 + 4);
    t62 = *((unsigned int *)t61);
    t63 = (~(t62));
    t64 = *((unsigned int *)t35);
    t65 = (t64 & t63);
    t66 = (t65 != 0);
    if (t66 > 0)
        goto LAB112;

LAB113:    xsi_set_current_line(158, ng0);
    xsi_vlogfile_write(1, 0, 0, ng38, 1, t0);

LAB114:    xsi_set_current_line(159, ng0);
    t2 = (t0 + 1208U);
    t3 = *((char **)t2);
    xsi_vlogfile_write(1, 0, 0, ng36, 2, t0, (char)118, t3, 8);
    xsi_set_current_line(162, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB115;
    goto LAB1;

LAB107:    t27 = (t5 + 4);
    *((unsigned int *)t5) = 1;
    *((unsigned int *)t27) = 1;
    goto LAB108;

LAB109:    t41 = *((unsigned int *)t35);
    t42 = *((unsigned int *)t37);
    *((unsigned int *)t35) = (t41 | t42);
    t43 = (t5 + 4);
    t44 = (t31 + 4);
    t45 = *((unsigned int *)t5);
    t46 = (~(t45));
    t47 = *((unsigned int *)t43);
    t48 = (~(t47));
    t49 = *((unsigned int *)t31);
    t50 = (~(t49));
    t51 = *((unsigned int *)t44);
    t52 = (~(t51));
    t53 = (t46 & t48);
    t54 = (t50 & t52);
    t55 = (~(t53));
    t56 = (~(t54));
    t57 = *((unsigned int *)t37);
    *((unsigned int *)t37) = (t57 & t55);
    t58 = *((unsigned int *)t37);
    *((unsigned int *)t37) = (t58 & t56);
    t59 = *((unsigned int *)t35);
    *((unsigned int *)t35) = (t59 & t55);
    t60 = *((unsigned int *)t35);
    *((unsigned int *)t35) = (t60 & t56);
    goto LAB111;

LAB112:    xsi_set_current_line(158, ng0);
    t67 = (t0 + 1928);
    t68 = (t67 + 56U);
    t69 = *((char **)t68);
    t30 = *((double *)t69);
    t70 = ((char*)((ng4)));
    t32 = xsi_vlog_convert_to_real(t70, 32, 1);
    t33 = (t30 + t32);
    t71 = (t0 + 1928);
    xsi_vlogvar_assign_value_double(t71, t33, 0);
    goto LAB114;

LAB115:    xsi_set_current_line(163, ng0);
    t3 = ((char*)((ng22)));
    t4 = (t0 + 2408);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 3);
    xsi_set_current_line(164, ng0);
    t2 = ((char*)((ng8)));
    t3 = (t0 + 2728);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 2);
    xsi_set_current_line(165, ng0);
    t2 = ((char*)((ng39)));
    t3 = (t0 + 2568);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 8);
    xsi_set_current_line(166, ng0);
    t2 = ((char*)((ng22)));
    t3 = (t0 + 2888);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 8);
    xsi_set_current_line(167, ng0);
    t2 = ((char*)((ng3)));
    t3 = (t0 + 2248);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(168, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 10000LL);
    *((char **)t1) = &&LAB116;
    goto LAB1;

LAB116:    xsi_set_current_line(169, ng0);
    t3 = ((char*)((ng8)));
    t4 = (t0 + 2248);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 1);
    xsi_set_current_line(170, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 10000LL);
    *((char **)t1) = &&LAB117;
    goto LAB1;

LAB117:    xsi_set_current_line(171, ng0);
    t3 = (t0 + 1208U);
    t4 = *((char **)t3);
    t3 = (t0 + 2568);
    t6 = (t3 + 56U);
    t7 = *((char **)t6);
    t20 = (t0 + 2888);
    t21 = (t20 + 56U);
    t27 = *((char **)t21);
    t8 = *((unsigned int *)t7);
    t9 = *((unsigned int *)t27);
    t10 = (t8 | t9);
    *((unsigned int *)t5) = t10;
    t28 = (t7 + 4);
    t29 = (t27 + 4);
    t31 = (t5 + 4);
    t11 = *((unsigned int *)t28);
    t12 = *((unsigned int *)t29);
    t13 = (t11 | t12);
    *((unsigned int *)t31) = t13;
    t14 = *((unsigned int *)t31);
    t15 = (t14 != 0);
    if (t15 == 1)
        goto LAB118;

LAB119:
LAB120:    memset(t35, 0, 8);
    t37 = (t4 + 4);
    t43 = (t5 + 4);
    t41 = *((unsigned int *)t4);
    t42 = *((unsigned int *)t5);
    t45 = (t41 ^ t42);
    t46 = *((unsigned int *)t37);
    t47 = *((unsigned int *)t43);
    t48 = (t46 ^ t47);
    t49 = (t45 | t48);
    t50 = *((unsigned int *)t37);
    t51 = *((unsigned int *)t43);
    t52 = (t50 | t51);
    t55 = (~(t52));
    t56 = (t49 & t55);
    if (t56 != 0)
        goto LAB124;

LAB121:    if (t52 != 0)
        goto LAB123;

LAB122:    *((unsigned int *)t35) = 1;

LAB124:    t61 = (t35 + 4);
    t57 = *((unsigned int *)t61);
    t58 = (~(t57));
    t59 = *((unsigned int *)t35);
    t60 = (t59 & t58);
    t62 = (t60 != 0);
    if (t62 > 0)
        goto LAB125;

LAB126:    xsi_set_current_line(171, ng0);
    xsi_vlogfile_write(1, 0, 0, ng40, 1, t0);

LAB127:    xsi_set_current_line(172, ng0);
    t2 = (t0 + 1208U);
    t3 = *((char **)t2);
    xsi_vlogfile_write(1, 0, 0, ng36, 2, t0, (char)118, t3, 8);
    xsi_set_current_line(175, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB128;
    goto LAB1;

LAB118:    t16 = *((unsigned int *)t5);
    t17 = *((unsigned int *)t31);
    *((unsigned int *)t5) = (t16 | t17);
    t34 = (t7 + 4);
    t36 = (t27 + 4);
    t18 = *((unsigned int *)t34);
    t19 = (~(t18));
    t22 = *((unsigned int *)t7);
    t53 = (t22 & t19);
    t23 = *((unsigned int *)t36);
    t24 = (~(t23));
    t25 = *((unsigned int *)t27);
    t54 = (t25 & t24);
    t26 = (~(t53));
    t38 = (~(t54));
    t39 = *((unsigned int *)t31);
    *((unsigned int *)t31) = (t39 & t26);
    t40 = *((unsigned int *)t31);
    *((unsigned int *)t31) = (t40 & t38);
    goto LAB120;

LAB123:    t44 = (t35 + 4);
    *((unsigned int *)t35) = 1;
    *((unsigned int *)t44) = 1;
    goto LAB124;

LAB125:    xsi_set_current_line(171, ng0);
    t67 = (t0 + 1928);
    t68 = (t67 + 56U);
    t69 = *((char **)t68);
    t30 = *((double *)t69);
    t70 = ((char*)((ng4)));
    t32 = xsi_vlog_convert_to_real(t70, 32, 1);
    t33 = (t30 + t32);
    t71 = (t0 + 1928);
    xsi_vlogvar_assign_value_double(t71, t33, 0);
    goto LAB127;

LAB128:    xsi_set_current_line(176, ng0);
    t3 = ((char*)((ng14)));
    t4 = (t0 + 2408);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 3);
    xsi_set_current_line(177, ng0);
    t2 = ((char*)((ng11)));
    t3 = (t0 + 2728);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 2);
    xsi_set_current_line(178, ng0);
    t2 = ((char*)((ng39)));
    t3 = (t0 + 2568);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 8);
    xsi_set_current_line(179, ng0);
    t2 = ((char*)((ng23)));
    t3 = (t0 + 2888);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 8);
    xsi_set_current_line(180, ng0);
    t2 = ((char*)((ng3)));
    t3 = (t0 + 2248);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(181, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 10000LL);
    *((char **)t1) = &&LAB129;
    goto LAB1;

LAB129:    xsi_set_current_line(182, ng0);
    t3 = ((char*)((ng8)));
    t4 = (t0 + 2248);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 1);
    xsi_set_current_line(183, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 10000LL);
    *((char **)t1) = &&LAB130;
    goto LAB1;

LAB130:    xsi_set_current_line(184, ng0);
    t3 = (t0 + 1208U);
    t4 = *((char **)t3);
    t3 = (t0 + 2568);
    t6 = (t3 + 56U);
    t7 = *((char **)t6);
    t20 = (t0 + 2888);
    t21 = (t20 + 56U);
    t27 = *((char **)t21);
    t8 = *((unsigned int *)t7);
    t9 = *((unsigned int *)t27);
    t10 = (t8 ^ t9);
    *((unsigned int *)t5) = t10;
    t28 = (t7 + 4);
    t29 = (t27 + 4);
    t31 = (t5 + 4);
    t11 = *((unsigned int *)t28);
    t12 = *((unsigned int *)t29);
    t13 = (t11 | t12);
    *((unsigned int *)t31) = t13;
    t14 = *((unsigned int *)t31);
    t15 = (t14 != 0);
    if (t15 == 1)
        goto LAB131;

LAB132:
LAB133:    memset(t35, 0, 8);
    t34 = (t4 + 4);
    t36 = (t5 + 4);
    t18 = *((unsigned int *)t4);
    t19 = *((unsigned int *)t5);
    t22 = (t18 ^ t19);
    t23 = *((unsigned int *)t34);
    t24 = *((unsigned int *)t36);
    t25 = (t23 ^ t24);
    t26 = (t22 | t25);
    t38 = *((unsigned int *)t34);
    t39 = *((unsigned int *)t36);
    t40 = (t38 | t39);
    t41 = (~(t40));
    t42 = (t26 & t41);
    if (t42 != 0)
        goto LAB137;

LAB134:    if (t40 != 0)
        goto LAB136;

LAB135:    *((unsigned int *)t35) = 1;

LAB137:    t43 = (t35 + 4);
    t45 = *((unsigned int *)t43);
    t46 = (~(t45));
    t47 = *((unsigned int *)t35);
    t48 = (t47 & t46);
    t49 = (t48 != 0);
    if (t49 > 0)
        goto LAB138;

LAB139:    xsi_set_current_line(184, ng0);
    xsi_vlogfile_write(1, 0, 0, ng41, 1, t0);

LAB140:    xsi_set_current_line(185, ng0);
    t2 = (t0 + 1208U);
    t3 = *((char **)t2);
    xsi_vlogfile_write(1, 0, 0, ng36, 2, t0, (char)118, t3, 8);
    xsi_set_current_line(188, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 1000LL);
    *((char **)t1) = &&LAB141;
    goto LAB1;

LAB131:    t16 = *((unsigned int *)t5);
    t17 = *((unsigned int *)t31);
    *((unsigned int *)t5) = (t16 | t17);
    goto LAB133;

LAB136:    t37 = (t35 + 4);
    *((unsigned int *)t35) = 1;
    *((unsigned int *)t37) = 1;
    goto LAB137;

LAB138:    xsi_set_current_line(184, ng0);
    t44 = (t0 + 1928);
    t61 = (t44 + 56U);
    t67 = *((char **)t61);
    t30 = *((double *)t67);
    t68 = ((char*)((ng4)));
    t32 = xsi_vlog_convert_to_real(t68, 32, 1);
    t33 = (t30 + t32);
    t69 = (t0 + 1928);
    xsi_vlogvar_assign_value_double(t69, t33, 0);
    goto LAB140;

LAB141:    xsi_set_current_line(189, ng0);
    t3 = ((char*)((ng26)));
    t4 = (t0 + 2408);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 3);
    xsi_set_current_line(190, ng0);
    t2 = ((char*)((ng14)));
    t3 = (t0 + 2728);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 2);
    xsi_set_current_line(191, ng0);
    t2 = ((char*)((ng39)));
    t3 = (t0 + 2568);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 8);
    xsi_set_current_line(192, ng0);
    t2 = ((char*)((ng23)));
    t3 = (t0 + 2888);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 8);
    xsi_set_current_line(193, ng0);
    t2 = ((char*)((ng3)));
    t3 = (t0 + 2248);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(194, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 20000LL);
    *((char **)t1) = &&LAB142;
    goto LAB1;

LAB142:    xsi_set_current_line(195, ng0);
    t3 = ((char*)((ng8)));
    t4 = (t0 + 2248);
    xsi_vlogvar_assign_value(t4, t3, 0, 0, 1);
    xsi_set_current_line(196, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 10000LL);
    *((char **)t1) = &&LAB143;
    goto LAB1;

LAB143:    xsi_set_current_line(197, ng0);
    t3 = (t0 + 1208U);
    t4 = *((char **)t3);
    t3 = (t0 + 2568);
    t6 = (t3 + 56U);
    t7 = *((char **)t6);
    t20 = (t0 + 2888);
    t21 = (t20 + 56U);
    t27 = *((char **)t21);
    t8 = *((unsigned int *)t7);
    t9 = *((unsigned int *)t27);
    t10 = (t8 & t9);
    *((unsigned int *)t35) = t10;
    t28 = (t7 + 4);
    t29 = (t27 + 4);
    t31 = (t35 + 4);
    t11 = *((unsigned int *)t28);
    t12 = *((unsigned int *)t29);
    t13 = (t11 | t12);
    *((unsigned int *)t31) = t13;
    t14 = *((unsigned int *)t31);
    t15 = (t14 != 0);
    if (t15 == 1)
        goto LAB144;

LAB145:
LAB146:    memset(t5, 0, 8);
    t37 = (t5 + 4);
    t43 = (t35 + 4);
    t47 = *((unsigned int *)t35);
    t48 = (~(t47));
    *((unsigned int *)t5) = t48;
    *((unsigned int *)t37) = 0;
    if (*((unsigned int *)t43) != 0)
        goto LAB148;

LAB147:    t55 = *((unsigned int *)t5);
    *((unsigned int *)t5) = (t55 & 255U);
    t56 = *((unsigned int *)t37);
    *((unsigned int *)t37) = (t56 & 255U);
    memset(t72, 0, 8);
    t44 = (t4 + 4);
    t61 = (t5 + 4);
    t57 = *((unsigned int *)t4);
    t58 = *((unsigned int *)t5);
    t59 = (t57 ^ t58);
    t60 = *((unsigned int *)t44);
    t62 = *((unsigned int *)t61);
    t63 = (t60 ^ t62);
    t64 = (t59 | t63);
    t65 = *((unsigned int *)t44);
    t66 = *((unsigned int *)t61);
    t73 = (t65 | t66);
    t74 = (~(t73));
    t75 = (t64 & t74);
    if (t75 != 0)
        goto LAB152;

LAB149:    if (t73 != 0)
        goto LAB151;

LAB150:    *((unsigned int *)t72) = 1;

LAB152:    t68 = (t72 + 4);
    t76 = *((unsigned int *)t68);
    t77 = (~(t76));
    t78 = *((unsigned int *)t72);
    t79 = (t78 & t77);
    t80 = (t79 != 0);
    if (t80 > 0)
        goto LAB153;

LAB154:    xsi_set_current_line(197, ng0);
    xsi_vlogfile_write(1, 0, 0, ng42, 1, t0);

LAB155:    xsi_set_current_line(198, ng0);
    t2 = (t0 + 1208U);
    t3 = *((char **)t2);
    xsi_vlogfile_write(1, 0, 0, ng36, 2, t0, (char)118, t3, 8);
    xsi_set_current_line(201, ng0);
    t2 = (t0 + 4904);
    xsi_process_wait(t2, 2000LL);
    *((char **)t1) = &&LAB156;
    goto LAB1;

LAB144:    t16 = *((unsigned int *)t35);
    t17 = *((unsigned int *)t31);
    *((unsigned int *)t35) = (t16 | t17);
    t34 = (t7 + 4);
    t36 = (t27 + 4);
    t18 = *((unsigned int *)t7);
    t19 = (~(t18));
    t22 = *((unsigned int *)t34);
    t23 = (~(t22));
    t24 = *((unsigned int *)t27);
    t25 = (~(t24));
    t26 = *((unsigned int *)t36);
    t38 = (~(t26));
    t53 = (t19 & t23);
    t54 = (t25 & t38);
    t39 = (~(t53));
    t40 = (~(t54));
    t41 = *((unsigned int *)t31);
    *((unsigned int *)t31) = (t41 & t39);
    t42 = *((unsigned int *)t31);
    *((unsigned int *)t31) = (t42 & t40);
    t45 = *((unsigned int *)t35);
    *((unsigned int *)t35) = (t45 & t39);
    t46 = *((unsigned int *)t35);
    *((unsigned int *)t35) = (t46 & t40);
    goto LAB146;

LAB148:    t49 = *((unsigned int *)t5);
    t50 = *((unsigned int *)t43);
    *((unsigned int *)t5) = (t49 | t50);
    t51 = *((unsigned int *)t37);
    t52 = *((unsigned int *)t43);
    *((unsigned int *)t37) = (t51 | t52);
    goto LAB147;

LAB151:    t67 = (t72 + 4);
    *((unsigned int *)t72) = 1;
    *((unsigned int *)t67) = 1;
    goto LAB152;

LAB153:    xsi_set_current_line(197, ng0);
    t69 = (t0 + 1928);
    t70 = (t69 + 56U);
    t71 = *((char **)t70);
    t30 = *((double *)t71);
    t81 = ((char*)((ng4)));
    t32 = xsi_vlog_convert_to_real(t81, 32, 1);
    t33 = (t30 + t32);
    t82 = (t0 + 1928);
    xsi_vlogvar_assign_value_double(t82, t33, 0);
    goto LAB155;

LAB156:    xsi_set_current_line(202, ng0);
    t3 = (t0 + 1928);
    t4 = (t3 + 56U);
    t6 = *((char **)t4);
    t30 = *((double *)t6);
    *((double *)t5) = t30;
    xsi_vlogfile_write(1, 0, 0, ng43, 2, t0, (char)114, t5, 64);
    xsi_set_current_line(203, ng0);
    xsi_vlog_finish(1);
    goto LAB1;

}


extern void work_m_07907436914831319866_1949178628_init()
{
	static char *pe[] = {(void *)Initial_43_0,(void *)Always_44_1,(void *)Initial_49_2};
	xsi_register_didat("work_m_07907436914831319866_1949178628", "isim/testbench_isim_beh.exe.sim/work/m_07907436914831319866_1949178628.didat");
	xsi_register_executes(pe);
}
