/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2018 Kalray Inc.
 */

#ifndef _BITS_SYSCALLS_H
#define _BITS_SYSCALLS_H
#ifndef _SYSCALL_H
# error "Never use <bits/syscalls.h> directly; include <sys/syscall.h> instead."
#endif

#ifndef __ASSEMBLER__

#define INTERNAL_SYSCALL_NCS(name, err, nr, args...)                    \
        ({                                                              \
		register long _a1 __asm__("r0");			\
		unsigned long _scno = name;				\
                LOAD_ARGS_##nr (args);                                  \
                __asm__ __volatile__("scall %[r_scno]"			\
                              : "=r" (_a1)                              \
                              : [r_scno] "r" (_scno) ASM_ARGS_##nr     \
                              : "cc", "memory");                	\
                _a1;                                                    \
        })

#define LOAD_ARGS_0() do { } while(0)
#define ASM_ARGS_0

#define LOAD_ARGS_1(a1)                                 \
	LOAD_ARGS_0();					\
	_a1  = (long) a1;
#define ASM_ARGS_1      ASM_ARGS_0, "r"(_a1)

#define LOAD_ARGS_2(a1, a2)                             \
	LOAD_ARGS_1(a1);				\
	register long _a2 __asm__("r1") = (long) a2;
#define ASM_ARGS_2      ASM_ARGS_1, "r"(_a2)

#define LOAD_ARGS_3(a1, a2, a3)                         \
	LOAD_ARGS_2(a1, a2);				\
	register long _a3 __asm__("r2") = (long) a3;
#define ASM_ARGS_3      ASM_ARGS_2, "r"(_a3)

#define LOAD_ARGS_4(a1, a2, a3, a4)                     \
	LOAD_ARGS_3(a1, a2, a3);			\
	register long _a4 __asm__("r3") = (long) a4;
#define ASM_ARGS_4      ASM_ARGS_3, "r"(_a4)

#define LOAD_ARGS_5(a1, a2, a3, a4, a5)                 \
	LOAD_ARGS_4(a1, a2, a3, a4);			\
	register long _a5 __asm__("r4") = (long) a5;
#define ASM_ARGS_5      ASM_ARGS_4, "r"(_a5)

#define LOAD_ARGS_6(a1, a2, a3, a4, a5, a6)             \
	LOAD_ARGS_5(a1, a2, a3, a4, a5);		\
	register long _a6 __asm__("r5") = (long) a6;
#define ASM_ARGS_6      ASM_ARGS_5, "r"(_a6)

#endif /* __ASSEMBLER__ */
#endif /* _BITS_SYSCALLS_H */
