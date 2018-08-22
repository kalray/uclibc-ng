/*
 * This file is subject to the terms and conditions of the LGPV V2.1
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2018 Kalray Inc.
 */

	.section .init
	.align 8
	.global	_init
	.type	 _init,@function
	# EPILOGUE
	ld $r0 = 0[$sp]
	;;
	ld $r14 = 8[$sp]
	set $ra = $r0
	addd $sp = $sp, 16
	;;
	ret
	;;

	.section .fini
	.align 8
	.global	_fini
	.type	 _fini,@function
	# EPILOGUE
	ld $r0 = 0[$sp]
	;;
	ld $r14 = 8[$sp]
	set $ra = $r0
	addd $sp = $sp, 16
	;;
	ret
	;;
