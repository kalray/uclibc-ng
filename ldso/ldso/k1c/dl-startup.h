/*
 * Architecture specific code used by dl-startup.c
 * Copyright (C) 2016 Waldemar Brodkorb <wbx@uclibc-ng.org>
 * Ported from GNU libc
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

/* Copyright (C) 1995-2016 Free Software Foundation, Inc.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#error Not even close to be ready

#include <features.h>

__asm__("\
.text									\n\
.globl _start								\n\
.type _start, %function							\n\
.globl _dl_start_user							\n\
.type _dl_start_user, %function						\n\
_start:									\n\
    goto 0 \n								\
    ;;\n								\
");

/* Get a pointer to the argv array.  On many platforms this can be just
 * the address of the first argument, on other platforms we need to
 * do something a little more subtle here.  */
#define GET_ARGV(ARGVP, ARGS) ARGVP = (((unsigned long*)ARGS)+1)

/* Handle relocation of the symbols in the dynamic loader. */
static __always_inline
void PERFORM_BOOTSTRAP_RELOC(ELF_RELOC *rpnt, ElfW(Addr) *reloc_addr,
	ElfW(Addr) symbol_addr, ElfW(Addr) load_addr, ElfW(Addr) *sym)
{
	switch (ELF_R_TYPE(rpnt->r_info)) {
		default:
			_dl_exit(1);
	}
}
