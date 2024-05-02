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
static const char *ng0 = "/home/ise/HW3/part2/lab3_2.v";
static int ng1[] = {10, 0};
static int ng2[] = {15, 0};
static int ng3[] = {0, 0};
static int ng4[] = {20, 0};
static int ng5[] = {1, 0};



static void Initial_26_0(char *t0)
{
    char t3[8];
    char t5[8];
    char *t1;
    char *t2;
    char *t4;
    char *t6;

LAB0:    xsi_set_current_line(26, ng0);

LAB2:    xsi_set_current_line(27, ng0);
    t1 = (t0 + 1048U);
    t2 = *((char **)t1);
    memcpy(t3, t2, 8);
    t1 = (t0 + 3208);
    xsi_vlogvar_assign_value(t1, t3, 0, 0, 6);
    xsi_set_current_line(28, ng0);
    t1 = (t0 + 1368U);
    t2 = *((char **)t1);
    t1 = ((char*)((ng1)));
    memset(t3, 0, 8);
    xsi_vlog_unsigned_multiply(t3, 32, t2, 2, t1, 32);
    t4 = ((char*)((ng1)));
    memset(t5, 0, 8);
    xsi_vlog_unsigned_add(t5, 32, t3, 32, t4, 32);
    t6 = (t0 + 3368);
    xsi_vlogvar_assign_value(t6, t5, 0, 0, 6);
    xsi_set_current_line(29, ng0);
    t1 = ((char*)((ng2)));
    t2 = (t0 + 3528);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 6);
    xsi_set_current_line(30, ng0);
    t1 = ((char*)((ng3)));
    t2 = (t0 + 3688);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 6);
    xsi_set_current_line(31, ng0);
    t1 = ((char*)((ng2)));
    t2 = (t0 + 3848);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 6);
    xsi_set_current_line(32, ng0);
    t1 = ((char*)((ng1)));
    t2 = (t0 + 4008);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 6);
    xsi_set_current_line(33, ng0);
    t1 = ((char*)((ng3)));
    t2 = (t0 + 4168);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 6);
    xsi_set_current_line(34, ng0);
    t1 = ((char*)((ng4)));
    t2 = (t0 + 4328);
    xsi_vlogvar_assign_value(t2, t1, 0, 0, 6);

LAB1:    return;
}

static void Always_37_1(char *t0)
{
    char t6[8];
    char t32[8];
    char t34[8];
    char t46[8];
    char t72[8];
    char t88[8];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    unsigned int t7;
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
    char *t19;
    char *t20;
    unsigned int t21;
    unsigned int t22;
    unsigned int t23;
    unsigned int t24;
    unsigned int t25;
    char *t26;
    char *t27;
    char *t28;
    char *t29;
    char *t30;
    char *t31;
    char *t33;
    char *t35;
    char *t36;
    char *t37;
    char *t38;
    unsigned int t39;
    unsigned int t40;
    unsigned int t41;
    unsigned int t42;
    unsigned int t43;
    char *t44;
    char *t45;
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
    unsigned int t57;
    unsigned int t58;
    unsigned int t59;
    unsigned int t60;
    char *t61;
    char *t62;
    unsigned int t63;
    unsigned int t64;
    unsigned int t65;
    unsigned int t66;
    unsigned int t67;
    char *t68;
    char *t69;
    char *t70;
    char *t71;
    char *t73;
    char *t74;
    char *t75;
    char *t76;
    unsigned int t77;
    unsigned int t78;
    unsigned int t79;
    unsigned int t80;
    unsigned int t81;
    char *t82;
    char *t83;
    char *t84;
    char *t85;
    char *t86;
    char *t87;
    char *t89;
    char *t90;
    unsigned int t91;
    unsigned int t92;
    unsigned int t93;
    unsigned int t94;
    unsigned int t95;
    unsigned int t96;
    unsigned int t97;
    unsigned int t98;
    unsigned int t99;
    unsigned int t100;
    unsigned int t101;
    unsigned int t102;
    char *t103;
    char *t104;
    unsigned int t105;
    unsigned int t106;
    unsigned int t107;
    unsigned int t108;
    unsigned int t109;
    char *t110;
    char *t111;

LAB0:    t1 = (t0 + 5488U);
    t2 = *((char **)t1);
    if (t2 == 0)
        goto LAB2;

LAB3:    goto *t2;

LAB2:    xsi_set_current_line(37, ng0);
    t2 = (t0 + 5808);
    *((int *)t2) = 1;
    t3 = (t0 + 5520);
    *((char **)t3) = t2;
    *((char **)t1) = &&LAB4;

LAB1:    return;
LAB4:    xsi_set_current_line(37, ng0);

LAB5:    xsi_set_current_line(38, ng0);
    t4 = ((char*)((ng3)));
    t5 = (t0 + 1928);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 6);
    xsi_set_current_line(39, ng0);
    t2 = ((char*)((ng3)));
    t3 = (t0 + 2248);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(40, ng0);
    t2 = ((char*)((ng3)));
    t3 = (t0 + 2408);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(41, ng0);
    t2 = ((char*)((ng3)));
    t3 = (t0 + 2568);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(42, ng0);
    t2 = ((char*)((ng3)));
    t3 = (t0 + 2728);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(43, ng0);
    t2 = ((char*)((ng3)));
    t3 = (t0 + 2888);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(44, ng0);
    t2 = ((char*)((ng3)));
    t3 = (t0 + 3048);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    xsi_set_current_line(45, ng0);
    t2 = (t0 + 1368U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng3)));
    memset(t6, 0, 8);
    t4 = (t3 + 4);
    t5 = (t2 + 4);
    t7 = *((unsigned int *)t3);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t4);
    t11 = *((unsigned int *)t5);
    t12 = (t10 ^ t11);
    t13 = (t9 | t12);
    t14 = *((unsigned int *)t4);
    t15 = *((unsigned int *)t5);
    t16 = (t14 | t15);
    t17 = (~(t16));
    t18 = (t13 & t17);
    if (t18 != 0)
        goto LAB9;

LAB6:    if (t16 != 0)
        goto LAB8;

LAB7:    *((unsigned int *)t6) = 1;

LAB9:    t20 = (t6 + 4);
    t21 = *((unsigned int *)t20);
    t22 = (~(t21));
    t23 = *((unsigned int *)t6);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB10;

LAB11:    xsi_set_current_line(66, ng0);
    t2 = (t0 + 1368U);
    t3 = *((char **)t2);
    t2 = ((char*)((ng5)));
    memset(t6, 0, 8);
    t4 = (t3 + 4);
    t5 = (t2 + 4);
    t7 = *((unsigned int *)t3);
    t8 = *((unsigned int *)t2);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t4);
    t11 = *((unsigned int *)t5);
    t12 = (t10 ^ t11);
    t13 = (t9 | t12);
    t14 = *((unsigned int *)t4);
    t15 = *((unsigned int *)t5);
    t16 = (t14 | t15);
    t17 = (~(t16));
    t18 = (t13 & t17);
    if (t18 != 0)
        goto LAB46;

LAB43:    if (t16 != 0)
        goto LAB45;

LAB44:    *((unsigned int *)t6) = 1;

LAB46:    t20 = (t6 + 4);
    t21 = *((unsigned int *)t20);
    t22 = (~(t21));
    t23 = *((unsigned int *)t6);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB47;

LAB48:    xsi_set_current_line(100, ng0);

LAB98:    xsi_set_current_line(101, ng0);
    t2 = (t0 + 4328);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 4168);
    t19 = (t5 + 56U);
    t20 = *((char **)t19);
    memset(t6, 0, 8);
    xsi_vlog_unsigned_add(t6, 32, t4, 6, t20, 6);
    t26 = ((char*)((ng3)));
    memset(t32, 0, 8);
    t27 = (t6 + 4);
    if (*((unsigned int *)t27) != 0)
        goto LAB100;

LAB99:    t28 = (t26 + 4);
    if (*((unsigned int *)t28) != 0)
        goto LAB100;

LAB103:    if (*((unsigned int *)t6) > *((unsigned int *)t26))
        goto LAB101;

LAB102:    t30 = (t32 + 4);
    t7 = *((unsigned int *)t30);
    t8 = (~(t7));
    t9 = *((unsigned int *)t32);
    t10 = (t9 & t8);
    t11 = (t10 != 0);
    if (t11 > 0)
        goto LAB104;

LAB105:    xsi_set_current_line(117, ng0);

LAB128:    xsi_set_current_line(118, ng0);
    t2 = ((char*)((ng5)));
    t3 = (t0 + 2248);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);

LAB106:
LAB49:
LAB12:    goto LAB2;

LAB8:    t19 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t19) = 1;
    goto LAB9;

LAB10:    xsi_set_current_line(45, ng0);

LAB13:    xsi_set_current_line(46, ng0);
    t26 = (t0 + 3688);
    t27 = (t26 + 56U);
    t28 = *((char **)t27);
    t29 = (t0 + 3528);
    t30 = (t29 + 56U);
    t31 = *((char **)t30);
    memset(t32, 0, 8);
    xsi_vlog_unsigned_add(t32, 32, t28, 6, t31, 6);
    t33 = ((char*)((ng3)));
    memset(t34, 0, 8);
    t35 = (t32 + 4);
    if (*((unsigned int *)t35) != 0)
        goto LAB15;

LAB14:    t36 = (t33 + 4);
    if (*((unsigned int *)t36) != 0)
        goto LAB15;

LAB18:    if (*((unsigned int *)t32) > *((unsigned int *)t33))
        goto LAB16;

LAB17:    t38 = (t34 + 4);
    t39 = *((unsigned int *)t38);
    t40 = (~(t39));
    t41 = *((unsigned int *)t34);
    t42 = (t41 & t40);
    t43 = (t42 != 0);
    if (t43 > 0)
        goto LAB19;

LAB20:    xsi_set_current_line(62, ng0);

LAB42:    xsi_set_current_line(63, ng0);
    t2 = ((char*)((ng5)));
    t3 = (t0 + 2248);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);

LAB21:    goto LAB12;

LAB15:    t37 = (t34 + 4);
    *((unsigned int *)t34) = 1;
    *((unsigned int *)t37) = 1;
    goto LAB17;

LAB16:    *((unsigned int *)t34) = 1;
    goto LAB17;

LAB19:    xsi_set_current_line(46, ng0);

LAB22:    xsi_set_current_line(47, ng0);
    t44 = (t0 + 1528U);
    t45 = *((char **)t44);
    t44 = ((char*)((ng5)));
    memset(t46, 0, 8);
    t47 = (t45 + 4);
    t48 = (t44 + 4);
    t49 = *((unsigned int *)t45);
    t50 = *((unsigned int *)t44);
    t51 = (t49 ^ t50);
    t52 = *((unsigned int *)t47);
    t53 = *((unsigned int *)t48);
    t54 = (t52 ^ t53);
    t55 = (t51 | t54);
    t56 = *((unsigned int *)t47);
    t57 = *((unsigned int *)t48);
    t58 = (t56 | t57);
    t59 = (~(t58));
    t60 = (t55 & t59);
    if (t60 != 0)
        goto LAB26;

LAB23:    if (t58 != 0)
        goto LAB25;

LAB24:    *((unsigned int *)t46) = 1;

LAB26:    t62 = (t46 + 4);
    t63 = *((unsigned int *)t62);
    t64 = (~(t63));
    t65 = *((unsigned int *)t46);
    t66 = (t65 & t64);
    t67 = (t66 != 0);
    if (t67 > 0)
        goto LAB27;

LAB28:    xsi_set_current_line(50, ng0);

LAB31:    xsi_set_current_line(51, ng0);
    t2 = (t0 + 3208);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 3368);
    t19 = (t5 + 56U);
    t20 = *((char **)t19);
    memset(t6, 0, 8);
    t26 = (t4 + 4);
    if (*((unsigned int *)t26) != 0)
        goto LAB33;

LAB32:    t27 = (t20 + 4);
    if (*((unsigned int *)t27) != 0)
        goto LAB33;

LAB36:    if (*((unsigned int *)t4) > *((unsigned int *)t20))
        goto LAB35;

LAB34:    *((unsigned int *)t6) = 1;

LAB35:    t29 = (t6 + 4);
    t7 = *((unsigned int *)t29);
    t8 = (~(t7));
    t9 = *((unsigned int *)t6);
    t10 = (t9 & t8);
    t11 = (t10 != 0);
    if (t11 > 0)
        goto LAB37;

LAB38:    xsi_set_current_line(57, ng0);

LAB41:    xsi_set_current_line(58, ng0);
    t2 = ((char*)((ng5)));
    t3 = (t0 + 2408);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);

LAB39:
LAB29:    goto LAB21;

LAB25:    t61 = (t46 + 4);
    *((unsigned int *)t46) = 1;
    *((unsigned int *)t61) = 1;
    goto LAB26;

LAB27:    xsi_set_current_line(47, ng0);

LAB30:    xsi_set_current_line(48, ng0);
    t68 = ((char*)((ng5)));
    t69 = (t0 + 2728);
    xsi_vlogvar_assign_value(t69, t68, 0, 0, 1);
    goto LAB29;

LAB33:    t28 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t28) = 1;
    goto LAB35;

LAB37:    xsi_set_current_line(51, ng0);

LAB40:    xsi_set_current_line(52, ng0);
    t30 = (t0 + 3208);
    t31 = (t30 + 56U);
    t33 = *((char **)t31);
    t35 = (t0 + 3368);
    t36 = (t35 + 56U);
    t37 = *((char **)t36);
    memset(t32, 0, 8);
    xsi_vlog_unsigned_minus(t32, 6, t33, 6, t37, 6);
    t38 = (t0 + 3208);
    xsi_vlogvar_wait_assign_value(t38, t32, 0, 0, 6, 0LL);
    xsi_set_current_line(53, ng0);
    t2 = (t0 + 3528);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng5)));
    memset(t6, 0, 8);
    xsi_vlog_unsigned_minus(t6, 32, t4, 6, t5, 32);
    t19 = (t0 + 3528);
    xsi_vlogvar_wait_assign_value(t19, t6, 0, 0, 6, 0LL);
    xsi_set_current_line(54, ng0);
    t2 = (t0 + 3528);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 2088);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 6);
    xsi_set_current_line(55, ng0);
    t2 = ((char*)((ng5)));
    t3 = (t0 + 3048);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    goto LAB39;

LAB45:    t19 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t19) = 1;
    goto LAB46;

LAB47:    xsi_set_current_line(66, ng0);

LAB50:    xsi_set_current_line(67, ng0);
    t26 = (t0 + 4008);
    t27 = (t26 + 56U);
    t28 = *((char **)t27);
    t29 = (t0 + 3848);
    t30 = (t29 + 56U);
    t31 = *((char **)t30);
    memset(t32, 0, 8);
    xsi_vlog_unsigned_add(t32, 32, t28, 6, t31, 6);
    t33 = ((char*)((ng3)));
    memset(t34, 0, 8);
    t35 = (t32 + 4);
    if (*((unsigned int *)t35) != 0)
        goto LAB52;

LAB51:    t36 = (t33 + 4);
    if (*((unsigned int *)t36) != 0)
        goto LAB52;

LAB55:    if (*((unsigned int *)t32) > *((unsigned int *)t33))
        goto LAB53;

LAB54:    t38 = (t34 + 4);
    t39 = *((unsigned int *)t38);
    t40 = (~(t39));
    t41 = *((unsigned int *)t34);
    t42 = (t41 & t40);
    t43 = (t42 != 0);
    if (t43 > 0)
        goto LAB56;

LAB57:    xsi_set_current_line(96, ng0);

LAB97:    xsi_set_current_line(97, ng0);
    t2 = ((char*)((ng5)));
    t3 = (t0 + 2248);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);

LAB58:    goto LAB49;

LAB52:    t37 = (t34 + 4);
    *((unsigned int *)t34) = 1;
    *((unsigned int *)t37) = 1;
    goto LAB54;

LAB53:    *((unsigned int *)t34) = 1;
    goto LAB54;

LAB56:    xsi_set_current_line(67, ng0);

LAB59:    xsi_set_current_line(68, ng0);
    t44 = (t0 + 1528U);
    t45 = *((char **)t44);
    t44 = ((char*)((ng5)));
    memset(t46, 0, 8);
    t47 = (t45 + 4);
    t48 = (t44 + 4);
    t49 = *((unsigned int *)t45);
    t50 = *((unsigned int *)t44);
    t51 = (t49 ^ t50);
    t52 = *((unsigned int *)t47);
    t53 = *((unsigned int *)t48);
    t54 = (t52 ^ t53);
    t55 = (t51 | t54);
    t56 = *((unsigned int *)t47);
    t57 = *((unsigned int *)t48);
    t58 = (t56 | t57);
    t59 = (~(t58));
    t60 = (t55 & t59);
    if (t60 != 0)
        goto LAB63;

LAB60:    if (t58 != 0)
        goto LAB62;

LAB61:    *((unsigned int *)t46) = 1;

LAB63:    t62 = (t46 + 4);
    t63 = *((unsigned int *)t62);
    t64 = (~(t63));
    t65 = *((unsigned int *)t46);
    t66 = (t65 & t64);
    t67 = (t66 != 0);
    if (t67 > 0)
        goto LAB64;

LAB65:    xsi_set_current_line(84, ng0);

LAB87:    xsi_set_current_line(85, ng0);
    t2 = (t0 + 3208);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 3368);
    t19 = (t5 + 56U);
    t20 = *((char **)t19);
    memset(t6, 0, 8);
    t26 = (t4 + 4);
    t27 = (t20 + 4);
    t7 = *((unsigned int *)t4);
    t8 = *((unsigned int *)t20);
    t9 = (t7 ^ t8);
    t10 = *((unsigned int *)t26);
    t11 = *((unsigned int *)t27);
    t12 = (t10 ^ t11);
    t13 = (t9 | t12);
    t14 = *((unsigned int *)t26);
    t15 = *((unsigned int *)t27);
    t16 = (t14 | t15);
    t17 = (~(t16));
    t18 = (t13 & t17);
    if (t18 != 0)
        goto LAB91;

LAB88:    if (t16 != 0)
        goto LAB90;

LAB89:    *((unsigned int *)t6) = 1;

LAB91:    t29 = (t6 + 4);
    t21 = *((unsigned int *)t29);
    t22 = (~(t21));
    t23 = *((unsigned int *)t6);
    t24 = (t23 & t22);
    t25 = (t24 != 0);
    if (t25 > 0)
        goto LAB92;

LAB93:    xsi_set_current_line(91, ng0);

LAB96:    xsi_set_current_line(92, ng0);
    t2 = ((char*)((ng5)));
    t3 = (t0 + 2568);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);

LAB94:
LAB66:    goto LAB58;

LAB62:    t61 = (t46 + 4);
    *((unsigned int *)t46) = 1;
    *((unsigned int *)t61) = 1;
    goto LAB63;

LAB64:    xsi_set_current_line(68, ng0);

LAB67:    xsi_set_current_line(69, ng0);
    t68 = (t0 + 4008);
    t69 = (t68 + 56U);
    t70 = *((char **)t69);
    t71 = ((char*)((ng3)));
    memset(t72, 0, 8);
    t73 = (t70 + 4);
    if (*((unsigned int *)t73) != 0)
        goto LAB69;

LAB68:    t74 = (t71 + 4);
    if (*((unsigned int *)t74) != 0)
        goto LAB69;

LAB72:    if (*((unsigned int *)t70) > *((unsigned int *)t71))
        goto LAB70;

LAB71:    t76 = (t72 + 4);
    t77 = *((unsigned int *)t76);
    t78 = (~(t77));
    t79 = *((unsigned int *)t72);
    t80 = (t79 & t78);
    t81 = (t80 != 0);
    if (t81 > 0)
        goto LAB73;

LAB74:    xsi_set_current_line(80, ng0);

LAB86:    xsi_set_current_line(81, ng0);
    t2 = ((char*)((ng5)));
    t3 = (t0 + 2888);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);

LAB75:    goto LAB66;

LAB69:    t75 = (t72 + 4);
    *((unsigned int *)t72) = 1;
    *((unsigned int *)t75) = 1;
    goto LAB71;

LAB70:    *((unsigned int *)t72) = 1;
    goto LAB71;

LAB73:    xsi_set_current_line(69, ng0);

LAB76:    xsi_set_current_line(70, ng0);
    t82 = (t0 + 3208);
    t83 = (t82 + 56U);
    t84 = *((char **)t83);
    t85 = (t0 + 3368);
    t86 = (t85 + 56U);
    t87 = *((char **)t86);
    memset(t88, 0, 8);
    t89 = (t84 + 4);
    t90 = (t87 + 4);
    t91 = *((unsigned int *)t84);
    t92 = *((unsigned int *)t87);
    t93 = (t91 ^ t92);
    t94 = *((unsigned int *)t89);
    t95 = *((unsigned int *)t90);
    t96 = (t94 ^ t95);
    t97 = (t93 | t96);
    t98 = *((unsigned int *)t89);
    t99 = *((unsigned int *)t90);
    t100 = (t98 | t99);
    t101 = (~(t100));
    t102 = (t97 & t101);
    if (t102 != 0)
        goto LAB80;

LAB77:    if (t100 != 0)
        goto LAB79;

LAB78:    *((unsigned int *)t88) = 1;

LAB80:    t104 = (t88 + 4);
    t105 = *((unsigned int *)t104);
    t106 = (~(t105));
    t107 = *((unsigned int *)t88);
    t108 = (t107 & t106);
    t109 = (t108 != 0);
    if (t109 > 0)
        goto LAB81;

LAB82:    xsi_set_current_line(76, ng0);

LAB85:    xsi_set_current_line(77, ng0);
    t2 = ((char*)((ng5)));
    t3 = (t0 + 2568);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);

LAB83:    goto LAB75;

LAB79:    t103 = (t88 + 4);
    *((unsigned int *)t88) = 1;
    *((unsigned int *)t103) = 1;
    goto LAB80;

LAB81:    xsi_set_current_line(70, ng0);

LAB84:    xsi_set_current_line(71, ng0);
    t110 = ((char*)((ng3)));
    t111 = (t0 + 3208);
    xsi_vlogvar_assign_value(t111, t110, 0, 0, 6);
    xsi_set_current_line(72, ng0);
    t2 = (t0 + 4008);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng5)));
    memset(t6, 0, 8);
    xsi_vlog_unsigned_minus(t6, 32, t4, 6, t5, 32);
    t19 = (t0 + 4008);
    xsi_vlogvar_assign_value(t19, t6, 0, 0, 6);
    xsi_set_current_line(73, ng0);
    t2 = (t0 + 4008);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 2088);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 6);
    xsi_set_current_line(74, ng0);
    t2 = ((char*)((ng5)));
    t3 = (t0 + 3048);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    goto LAB83;

LAB90:    t28 = (t6 + 4);
    *((unsigned int *)t6) = 1;
    *((unsigned int *)t28) = 1;
    goto LAB91;

LAB92:    xsi_set_current_line(85, ng0);

LAB95:    xsi_set_current_line(86, ng0);
    t30 = ((char*)((ng3)));
    t31 = (t0 + 3208);
    xsi_vlogvar_assign_value(t31, t30, 0, 0, 6);
    xsi_set_current_line(87, ng0);
    t2 = (t0 + 3848);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng5)));
    memset(t6, 0, 8);
    xsi_vlog_unsigned_minus(t6, 32, t4, 6, t5, 32);
    t19 = (t0 + 3848);
    xsi_vlogvar_assign_value(t19, t6, 0, 0, 6);
    xsi_set_current_line(88, ng0);
    t2 = (t0 + 3848);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 2088);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 6);
    xsi_set_current_line(89, ng0);
    t2 = ((char*)((ng5)));
    t3 = (t0 + 3048);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    goto LAB94;

LAB100:    t29 = (t32 + 4);
    *((unsigned int *)t32) = 1;
    *((unsigned int *)t29) = 1;
    goto LAB102;

LAB101:    *((unsigned int *)t32) = 1;
    goto LAB102;

LAB104:    xsi_set_current_line(101, ng0);

LAB107:    xsi_set_current_line(102, ng0);
    t31 = (t0 + 4328);
    t33 = (t31 + 56U);
    t35 = *((char **)t33);
    t36 = ((char*)((ng3)));
    memset(t34, 0, 8);
    t37 = (t35 + 4);
    if (*((unsigned int *)t37) != 0)
        goto LAB109;

LAB108:    t38 = (t36 + 4);
    if (*((unsigned int *)t38) != 0)
        goto LAB109;

LAB112:    if (*((unsigned int *)t35) > *((unsigned int *)t36))
        goto LAB110;

LAB111:    t45 = (t34 + 4);
    t12 = *((unsigned int *)t45);
    t13 = (~(t12));
    t14 = *((unsigned int *)t34);
    t15 = (t14 & t13);
    t16 = (t15 != 0);
    if (t16 > 0)
        goto LAB113;

LAB114:    xsi_set_current_line(113, ng0);

LAB127:    xsi_set_current_line(114, ng0);
    t2 = ((char*)((ng5)));
    t3 = (t0 + 2888);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);

LAB115:    goto LAB106;

LAB109:    t44 = (t34 + 4);
    *((unsigned int *)t34) = 1;
    *((unsigned int *)t44) = 1;
    goto LAB111;

LAB110:    *((unsigned int *)t34) = 1;
    goto LAB111;

LAB113:    xsi_set_current_line(102, ng0);

LAB116:    xsi_set_current_line(103, ng0);
    t47 = (t0 + 3208);
    t48 = (t47 + 56U);
    t61 = *((char **)t48);
    t62 = (t0 + 3368);
    t68 = (t62 + 56U);
    t69 = *((char **)t68);
    memset(t46, 0, 8);
    t70 = (t61 + 4);
    if (*((unsigned int *)t70) != 0)
        goto LAB118;

LAB117:    t71 = (t69 + 4);
    if (*((unsigned int *)t71) != 0)
        goto LAB118;

LAB121:    if (*((unsigned int *)t61) < *((unsigned int *)t69))
        goto LAB120;

LAB119:    *((unsigned int *)t46) = 1;

LAB120:    t74 = (t46 + 4);
    t17 = *((unsigned int *)t74);
    t18 = (~(t17));
    t21 = *((unsigned int *)t46);
    t22 = (t21 & t18);
    t23 = (t22 != 0);
    if (t23 > 0)
        goto LAB122;

LAB123:    xsi_set_current_line(109, ng0);

LAB126:    xsi_set_current_line(110, ng0);
    t2 = ((char*)((ng5)));
    t3 = (t0 + 2408);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);

LAB124:    goto LAB115;

LAB118:    t73 = (t46 + 4);
    *((unsigned int *)t46) = 1;
    *((unsigned int *)t73) = 1;
    goto LAB120;

LAB122:    xsi_set_current_line(103, ng0);

LAB125:    xsi_set_current_line(104, ng0);
    t75 = (t0 + 3208);
    t76 = (t75 + 56U);
    t82 = *((char **)t76);
    t83 = (t0 + 3368);
    t84 = (t83 + 56U);
    t85 = *((char **)t84);
    memset(t72, 0, 8);
    xsi_vlog_unsigned_minus(t72, 6, t82, 6, t85, 6);
    t86 = (t0 + 3208);
    xsi_vlogvar_assign_value(t86, t72, 0, 0, 6);
    xsi_set_current_line(105, ng0);
    t2 = (t0 + 4328);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = ((char*)((ng5)));
    memset(t6, 0, 8);
    xsi_vlog_unsigned_minus(t6, 32, t4, 6, t5, 32);
    t19 = (t0 + 4328);
    xsi_vlogvar_assign_value(t19, t6, 0, 0, 6);
    xsi_set_current_line(106, ng0);
    t2 = (t0 + 4328);
    t3 = (t2 + 56U);
    t4 = *((char **)t3);
    t5 = (t0 + 2088);
    xsi_vlogvar_assign_value(t5, t4, 0, 0, 6);
    xsi_set_current_line(107, ng0);
    t2 = ((char*)((ng5)));
    t3 = (t0 + 3048);
    xsi_vlogvar_assign_value(t3, t2, 0, 0, 1);
    goto LAB124;

}


extern void work_m_02247598409814409835_1338705563_init()
{
	static char *pe[] = {(void *)Initial_26_0,(void *)Always_37_1};
	xsi_register_didat("work_m_02247598409814409835_1338705563", "isim/Board232_isim_beh.exe.sim/work/m_02247598409814409835_1338705563.didat");
	xsi_register_executes(pe);
}
