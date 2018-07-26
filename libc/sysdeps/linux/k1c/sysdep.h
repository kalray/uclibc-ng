/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2018 Kalray Inc.
 */

#ifndef _LINUX_K1C_SYSDEP_H
#define _LINUX_K1C_SYSDEP_H 1

#include <common/sysdep.h>

#define SYS_ify(syscall_name)  (__NR_##syscall_name)

#endif //_LINUX_K1C_SYSDEP_H
