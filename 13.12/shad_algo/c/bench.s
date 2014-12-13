	.file	"bench.c"
	.text
	.p2align 4,,15
	.globl	multiply
	.type	multiply, @function
multiply:
.LFB22:
	.cfi_startproc
	leaq	16(%rdx), %rax
	leaq	16(%rsi), %rcx
	cmpq	%rax, %rsi
	setae	%r8b
	cmpq	%rcx, %rdx
	setae	%cl
	orb	%cl, %r8b
	je	.L2
	cmpq	%rax, %rdi
	leaq	16(%rdi), %rax
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
	subq	$24, %rsp
	.cfi_def_cfa_offset 80
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
	movq	%rbx, %rax
	movl	$100000, %r14d
	andl	$15, %eax
	shrq	%rax
	negq	%rax
	andl	$7, %eax
	subq	%rax, %r13
	leaq	(%rax,%rax), %r8
	movq	%r13, %rdi
	movq	%r13, 8(%rsp)
	movl	$32767, %r13d
	shrq	$3, %rdi
	leaq	(%rbx,%r8), %r10
	leaq	0(%rbp,%r8), %r9
	leaq	0(,%rdi,8), %r15
	addq	%r12, %r8
	.p2align 4,,10
	.p2align 3
.L23:
	testq	%rax, %rax
	je	.L33
	xorl	%edx, %edx
	jmp	.L31
	.p2align 4,,10
	.p2align 3
.L38:
	movq	%rsi, %rdx
.L31:
	movzwl	0(%rbp,%rdx,2), %ecx
	leaq	1(%rdx), %rsi
	movq	%r13, %r11
	imulw	(%rbx,%rdx,2), %cx
	subq	%rdx, %r11
	cmpq	%rax, %rsi
	movw	%cx, (%r12,%rdx,2)
	jne	.L38
.L30:
	xorl	%edx, %edx
	xorl	%ecx, %ecx
	.p2align 4,,10
	.p2align 3
.L32:
	movdqu	(%r9,%rdx), %xmm0
	addq	$1, %rcx
	pmullw	(%r10,%rdx), %xmm0
	movdqu	%xmm0, (%r8,%rdx)
	addq	$16, %rdx
	cmpq	%rcx, %rdi
	ja	.L32
	addq	%r15, %rsi
	subq	%r15, %r11
	cmpq	%r15, 8(%rsp)
	leaq	(%rsi,%r11), %rcx
	je	.L27
	.p2align 4,,10
	.p2align 3
.L28:
	movzwl	0(%rbp,%rsi,2), %edx
	imulw	(%rbx,%rsi,2), %dx
	movw	%dx, (%r12,%rsi,2)
	addq	$1, %rsi
	cmpq	%rcx, %rsi
	jne	.L28
.L27:
	subq	$1, %r14
	jne	.L23
	movswl	32768(%r12), %edx
	movl	$.LC0, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk
	addq	$24, %rsp
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
	movl	$32768, %r11d
	xorl	%esi, %esi
	jmp	.L30
.L20:
	call	abort
	.cfi_endproc
.LFE23:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
