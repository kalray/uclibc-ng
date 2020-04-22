/*
 * This file is subject to the terms and conditions of the LGPL V2.1
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2018 Kalray Inc.
 */

	.section .init
	.align 8
	.global	_init
	.type	 _init,@function
_init:
	addd $sp = $sp, -32
	get $r0 = $ra
	;;
	sd 0[$sp] = $r0
	;;
	sd 8[$sp] = $r14
	;;

	.section .fini
	.align 8
	.global	_fini
	.type	 _fini,@function
_fini:
	addd $sp = $sp, -32
	get $r0 = $ra
	;;
	sd 0[$sp] = $r0
	;;
	sd 8[$sp] = $r14
	;;
