	.file	"bench.c"
	.text
	.p2align 4,,15
	.globl	multiply
	.type	multiply, @function
multiply:
.LFB22:
	.cfi_startproc
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L3:
	movzwl	(%rsi,%rax,2), %ecx
	imulw	(%rdi,%rax,2), %cx
	movw	%cx, (%rdx,%rax,2)
	addq	$1, %rax
	cmpq	$32768, %rax
	jne	.L3
	rep ret
	.cfi_endproc
.LFE22:
	.size	multiply, .-multiply
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB23:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	movl	$65536, %edi
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	call	malloc
	movl	$65536, %edi
	movq	%rax, %rbx
	call	malloc
	movl	$65536, %edi
	movq	%rax, %rbp
	call	malloc
	testq	%rbx, %rbx
	je	.L6
	testq	%rbp, %rbp
	je	.L6
	testq	%rax, %rax
	movq	%rax, %r12
	je	.L6
	movl	$42, %edi
	xorl	%r13d, %r13d
	call	srand
	.p2align 4,,10
	.p2align 3
.L10:
	call	rand
	movw	%ax, (%rbx,%r13,2)
	call	rand
	movw	%ax, 0(%rbp,%r13,2)
	addq	$1, %r13
	cmpq	$32768, %r13
	jne	.L10
	movl	$100000, %eax
	.p2align 4,,10
	.p2align 3
.L9:
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L13:
	movzwl	0(%rbp,%rdx,2), %ecx
	imulw	(%rbx,%rdx,2), %cx
	movw	%cx, (%r12,%rdx,2)
	addq	$1, %rdx
	cmpq	$32768, %rdx
	jne	.L13
	subq	$1, %rax
	jne	.L9
	movswl	32768(%r12), %edx
	movl	$.LC0, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
.L6:
	.cfi_restore_state
	call	abort
	.cfi_endproc
.LFE23:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
