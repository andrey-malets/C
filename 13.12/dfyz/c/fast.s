	.file	"bench.c"
	.text
	.p2align 4,,15
	.globl	multiply
	.type	multiply, @function
multiply:
.LFB22:
	.cfi_startproc
	leaq	16(%rdx), %rax
	leaq	16(%rdi), %rcx
	cmpq	%rax, %rdi
	setae	%r8b
	cmpq	%rcx, %rdx
	setae	%cl
	orb	%cl, %r8b
	je	.L2
	cmpq	%rax, %rsi
	leaq	16(%rsi), %rax
	setae	%cl
	cmpq	%rax, %rdx
	setae	%al
	orb	%al, %cl
	je	.L2
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L4:
	movdqu	(%rsi,%rax), %xmm1
	movdqu	(%rdi,%rax), %xmm0
	pmullw	%xmm1, %xmm0
	movdqu	%xmm0, (%rdx,%rax)
	addq	$16, %rax
	cmpq	$65536, %rax
	jne	.L4
	rep ret
	.p2align 4,,10
	.p2align 3
.L2:
	xorl	%eax, %eax
	.p2align 4,,10
	.p2align 3
.L5:
	movzwl	(%rsi,%rax,2), %ecx
	imulw	(%rdi,%rax,2), %cx
	movw	%cx, (%rdx,%rax,2)
	addq	$1, %rax
	cmpq	$32768, %rax
	jne	.L5
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
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movl	$65536, %edi
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$8, %rsp
	.cfi_def_cfa_offset 64
	call	malloc
	movl	$65536, %edi
	movq	%rax, %rbx
	call	malloc
	movl	$65536, %edi
	movq	%rax, %rbp
	call	malloc
	testq	%rbx, %rbx
	je	.L20
	testq	%rbp, %rbp
	je	.L20
	testq	%rax, %rax
	movq	%rax, %r12
	je	.L20
	movl	$42, %edi
	xorl	%r13d, %r13d
	call	srand
	.p2align 4,,10
	.p2align 3
.L24:
	call	rand
	movw	%ax, (%rbx,%r13,2)
	call	rand
	movw	%ax, 0(%rbp,%r13,2)
	addq	$1, %r13
	cmpq	$32768, %r13
	jne	.L24
	movq	%rbx, %r9
	movl	$100000, %r10d
	andl	$15, %r9d
	shrq	%r9
	negq	%r9
	andl	$7, %r9d
	subq	%r9, %r13
	leaq	(%r9,%r9), %rsi
	movq	%r13, %rax
	shrq	$3, %rax
	leaq	(%rbx,%rsi), %r8
	leaq	0(%rbp,%rsi), %rdi
	leaq	0(,%rax,8), %r11
	addq	%r12, %rsi
	.p2align 4,,10
	.p2align 3
.L23:
	testq	%r9, %r9
	je	.L33
	movzwl	0(%rbp), %edx
	imulw	(%rbx), %dx
	cmpq	$1, %r9
	movw	%dx, (%r12)
	je	.L34
	movzwl	2(%rbp), %edx
	imulw	2(%rbx), %dx
	cmpq	$2, %r9
	movw	%dx, 2(%r12)
	je	.L35
	movzwl	4(%rbp), %edx
	imulw	4(%rbx), %dx
	cmpq	$3, %r9
	movw	%dx, 4(%r12)
	je	.L36
	movzwl	6(%rbp), %edx
	imulw	6(%rbx), %dx
	cmpq	$4, %r9
	movw	%dx, 6(%r12)
	je	.L37
	movzwl	8(%rbp), %edx
	imulw	8(%rbx), %dx
	cmpq	$5, %r9
	movw	%dx, 8(%r12)
	je	.L38
	movzwl	10(%rbp), %edx
	imulw	10(%rbx), %dx
	cmpq	$7, %r9
	movw	%dx, 10(%r12)
	jne	.L39
	movzwl	12(%rbx), %edx
	movl	$32761, %r14d
	movl	$7, %r15d
	imulw	12(%rbp), %dx
	movw	%dx, 12(%r12)
.L30:
	xorl	%edx, %edx
	xorl	%ecx, %ecx
	.p2align 4,,10
	.p2align 3
.L32:
	movdqu	(%rdi,%rdx), %xmm0
	addq	$1, %rcx
	pmullw	(%r8,%rdx), %xmm0
	movdqu	%xmm0, (%rsi,%rdx)
	addq	$16, %rdx
	cmpq	%rax, %rcx
	jb	.L32
	movq	%r14, %rcx
	leaq	(%r15,%r11), %rdx
	subq	%r11, %rcx
	cmpq	%r11, %r13
	je	.L27
	movzwl	(%rbx,%rdx,2), %r14d
	imulw	0(%rbp,%rdx,2), %r14w
	cmpq	$1, %rcx
	movw	%r14w, (%r12,%rdx,2)
	leaq	1(%rdx), %r14
	je	.L27
	movzwl	0(%rbp,%r14,2), %r15d
	imulw	(%rbx,%r14,2), %r15w
	cmpq	$2, %rcx
	movw	%r15w, (%r12,%r14,2)
	leaq	2(%rdx), %r14
	je	.L27
	movzwl	0(%rbp,%r14,2), %r15d
	imulw	(%rbx,%r14,2), %r15w
	cmpq	$3, %rcx
	movw	%r15w, (%r12,%r14,2)
	leaq	3(%rdx), %r14
	je	.L27
	movzwl	0(%rbp,%r14,2), %r15d
	imulw	(%rbx,%r14,2), %r15w
	cmpq	$4, %rcx
	movw	%r15w, (%r12,%r14,2)
	leaq	4(%rdx), %r14
	je	.L27
	movzwl	0(%rbp,%r14,2), %r15d
	imulw	(%rbx,%r14,2), %r15w
	cmpq	$5, %rcx
	movw	%r15w, (%r12,%r14,2)
	leaq	5(%rdx), %r14
	je	.L27
	movzwl	0(%rbp,%r14,2), %r15d
	addq	$6, %rdx
	imulw	(%rbx,%r14,2), %r15w
	cmpq	$6, %rcx
	movw	%r15w, (%r12,%r14,2)
	je	.L27
	movzwl	0(%rbp,%rdx,2), %ecx
	imulw	(%rbx,%rdx,2), %cx
	movw	%cx, (%r12,%rdx,2)
.L27:
	subq	$1, %r10
	jne	.L23
	movswl	32768(%r12), %edx
	movl	$.LC0, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L33:
	.cfi_restore_state
	movl	$32768, %r14d
	xorl	%r15d, %r15d
	jmp	.L30
	.p2align 4,,10
	.p2align 3
.L35:
	movl	$32766, %r14d
	movl	$2, %r15d
	jmp	.L30
	.p2align 4,,10
	.p2align 3
.L34:
	movl	$32767, %r14d
	movl	$1, %r15d
	jmp	.L30
	.p2align 4,,10
	.p2align 3
.L39:
	movl	$32762, %r14d
	movl	$6, %r15d
	jmp	.L30
	.p2align 4,,10
	.p2align 3
.L38:
	movl	$32763, %r14d
	movl	$5, %r15d
	jmp	.L30
	.p2align 4,,10
	.p2align 3
.L37:
	movl	$32764, %r14d
	movl	$4, %r15d
	jmp	.L30
	.p2align 4,,10
	.p2align 3
.L36:
	movl	$32765, %r14d
	movl	$3, %r15d
	jmp	.L30
.L20:
	call	abort
	.cfi_endproc
.LFE23:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
