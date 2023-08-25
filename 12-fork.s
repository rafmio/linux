	.file	"12-fork.c"
	.text
	.section	.rodata
	.align 8
.LC0:
	.string	"Too few arguments. Usage: %s <fileName>\n"
.LC1:
	.string	"cmd: %s\n"
.LC2:
	.string	"openat()"
.LC3:
	.string	"\nfd directory for PID %d:\n"
.LC4:
	.string	"Child PID: %d\n"
.LC5:
	.string	"fstat()"
.LC6:
	.string	"st_ino: %ld\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$208, %rsp
	movl	%edi, -196(%rbp)
	movq	%rsi, -208(%rbp)
	cmpl	$1, -196(%rbp)
	jg	.L2
	movq	-208(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$1, %edi
	call	exit@PLT
.L2:
	movabsq	$3395821236278817644, %rax
	movabsq	$7810775776112898672, %rdx
	movq	%rax, -48(%rbp)
	movq	%rdx, -40(%rbp)
	movl	$1684418406, -32(%rbp)
	movb	$0, -28(%rbp)
	leaq	-48(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-208(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movl	$524288, %edx
	movq	%rax, %rsi
	movl	$-100, %edi
	movl	$0, %eax
	call	openat@PLT
	movl	%eax, -4(%rbp)
	cmpl	$-1, -4(%rbp)
	jne	.L3
	leaq	.LC2(%rip), %rdi
	call	perror@PLT
	movl	$1, %edi
	call	exit@PLT
.L3:
	call	getpid@PLT
	movl	%eax, %esi
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	system@PLT
	call	fork@PLT
	movl	%eax, -8(%rbp)
	movl	-8(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC4(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	call	getpid@PLT
	movl	%eax, %esi
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	system@PLT
	movl	$10, %edi
	call	putchar@PLT
	leaq	-192(%rbp), %rdx
	movl	-4(%rbp), %eax
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	fstat@PLT
	movl	%eax, -12(%rbp)
	cmpl	$-1, -12(%rbp)
	jne	.L4
	leaq	.LC5(%rip), %rdi
	call	perror@PLT
	movl	$1, %eax
	jmp	.L6
.L4:
	movq	-184(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC6(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
.L6:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	main, .-main
	.ident	"GCC: (Debian 10.2.1-6) 10.2.1 20210110"
	.section	.note.GNU-stack,"",@progbits
