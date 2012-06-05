	.section	__TEXT,__text,regular,pure_instructions
	.globl	_getMuNum
	.align	4, 0x90
_getMuNum:                              ## @getMuNum
	.cfi_startproc
## BB#0:
	subq	$24, %rsp
Ltmp1:
	.cfi_def_cfa_offset 32
	leaq	L_.str(%rip), %rdi
	callq	_getenv
	movq	%rax, 16(%rsp)
	movl	$0, 12(%rsp)
	cmpq	$0, 16(%rsp)
	je	LBB0_2
## BB#1:
	movq	16(%rsp), %rdi
	callq	_atoi
	movl	%eax, 12(%rsp)
LBB0_2:
	movl	12(%rsp), %eax
	addq	$24, %rsp
	ret
	.cfi_endproc

	.globl	_pthread_mutex_lock_ov
	.align	4, 0x90
_pthread_mutex_lock_ov:                 ## @pthread_mutex_lock_ov
	.cfi_startproc
## BB#0:
	subq	$24, %rsp
Ltmp3:
	.cfi_def_cfa_offset 32
	movq	%rdi, 16(%rsp)
	movl	%esi, 12(%rsp)
	callq	_getMuNum
	movl	%eax, 8(%rsp)
	cmpl	12(%rsp), %eax
	jne	LBB1_2
## BB#1:
	movl	8(%rsp), %esi
	leaq	L_.str1(%rip), %rdi
	xorb	%al, %al
	callq	_printf
LBB1_2:
	movq	16(%rsp), %rdi
	callq	_pthread_mutex_lock
	addq	$24, %rsp
	ret
	.cfi_endproc

	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	subq	$24, %rsp
Ltmp5:
	.cfi_def_cfa_offset 32
	movl	$0, 20(%rsp)
	leaq	8(%rsp), %rdi
	leaq	_functionCount1(%rip), %rdx
	xorl	%esi, %esi
	xorl	%ecx, %ecx
	callq	_pthread_create
	leaq	(%rsp), %rdi
	leaq	_functionCount2(%rip), %rdx
	xorl	%esi, %esi
	xorl	%ecx, %ecx
	callq	_pthread_create
	movq	8(%rsp), %rdi
	xorl	%esi, %esi
	callq	_pthread_join
	movq	(%rsp), %rdi
	xorl	%esi, %esi
	callq	_pthread_join
	leaq	L_.str2(%rip), %rdi
	movl	_count(%rip), %esi
	xorb	%al, %al
	callq	_printf
	xorl	%edi, %edi
	callq	_exit
	.cfi_endproc

	.globl	_functionCount1
	.align	4, 0x90
_functionCount1:                        ## @functionCount1
	.cfi_startproc
## BB#0:
	pushq	%r15
Ltmp10:
	.cfi_def_cfa_offset 16
	pushq	%r14
Ltmp11:
	.cfi_def_cfa_offset 24
	pushq	%rbx
Ltmp12:
	.cfi_def_cfa_offset 32
Ltmp13:
	.cfi_offset %rbx, -32
Ltmp14:
	.cfi_offset %r14, -24
Ltmp15:
	.cfi_offset %r15, -16
	leaq	_count_mutex(%rip), %rbx
	leaq	_condition_var(%rip), %r14
	leaq	L_.str13(%rip), %r15
	.align	4, 0x90
LBB3_1:                                 ## =>This Inner Loop Header: Depth=1
	movq	%rbx, %rdi
	movl	$1, %esi
	callq	_pthread_mutex_lock_ov
	movq	%r14, %rdi
	movq	%rbx, %rsi
	callq	_pthread_cond_wait
	movl	_count(%rip), %esi
	incl	%esi
	movl	%esi, _count(%rip)
	movq	%r15, %rdi
	xorb	%al, %al
	callq	_printf
	movq	%rbx, %rdi
	callq	_pthread_mutex_unlock
	cmpl	$10, _count(%rip)
	jl	LBB3_1
## BB#2:
	xorl	%eax, %eax
	popq	%rbx
	popq	%r14
	popq	%r15
	ret
	.cfi_endproc

	.globl	_functionCount2
	.align	4, 0x90
_functionCount2:                        ## @functionCount2
	.cfi_startproc
## BB#0:
	pushq	%r15
Ltmp20:
	.cfi_def_cfa_offset 16
	pushq	%r14
Ltmp21:
	.cfi_def_cfa_offset 24
	pushq	%rbx
Ltmp22:
	.cfi_def_cfa_offset 32
Ltmp23:
	.cfi_offset %rbx, -32
Ltmp24:
	.cfi_offset %r14, -24
Ltmp25:
	.cfi_offset %r15, -16
	leaq	_count_mutex(%rip), %rbx
	leaq	_condition_var(%rip), %r14
	leaq	L_.str24(%rip), %r15
	.align	4, 0x90
LBB4_1:                                 ## =>This Inner Loop Header: Depth=1
	movq	%rbx, %rdi
	movl	$2, %esi
	callq	_pthread_mutex_lock_ov
	cmpl	$3, _count(%rip)
	jl	LBB4_3
## BB#2:                                ##   in Loop: Header=BB4_1 Depth=1
	cmpl	$7, _count(%rip)
	jl	LBB4_4
LBB4_3:                                 ##   in Loop: Header=BB4_1 Depth=1
	movq	%r14, %rdi
	callq	_pthread_cond_signal
	jmp	LBB4_5
LBB4_4:                                 ##   in Loop: Header=BB4_1 Depth=1
	movl	_count(%rip), %esi
	incl	%esi
	movl	%esi, _count(%rip)
	movq	%r15, %rdi
	xorb	%al, %al
	callq	_printf
LBB4_5:                                 ##   in Loop: Header=BB4_1 Depth=1
	movq	%rbx, %rdi
	callq	_pthread_mutex_unlock
	cmpl	$10, _count(%rip)
	jl	LBB4_1
## BB#6:
	xorl	%eax, %eax
	popq	%rbx
	popq	%r14
	popq	%r15
	ret
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	 "MUNUM"

L_.str1:                                ## @.str1
	.asciz	 "Mutating %d\n"

	.section	__DATA,__data
	.globl	_count_mutex            ## @count_mutex
	.align	3
_count_mutex:
	.quad	850045863               ## 0x32aaaba7
	.space	56

	.globl	_condition_var          ## @condition_var
	.align	3
_condition_var:
	.quad	1018212795              ## 0x3cb0b1bb
	.space	40

	.globl	_count                  ## @count
.zerofill __DATA,__common,_count,4,2
	.section	__TEXT,__cstring,cstring_literals
L_.str2:                                ## @.str2
	.asciz	 "Final count: %d\n"

L_.str13:                               ## @.str13
	.asciz	 "Counter value functionCount1: %d\n"

L_.str24:                               ## @.str24
	.asciz	 "Counter value functionCount2: %d\n"


.subsections_via_symbols
