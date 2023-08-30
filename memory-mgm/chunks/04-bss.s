	.file	"04-bss.c"
	.text
	.globl	global_var1
	.bss
	.align 4
	.type	global_var1, @object
	.size	global_var1, 4
global_var1:
	.zero	4
	.globl	global_var2
	.align 4
	.type	global_var2, @object
	.size	global_var2, 4
global_var2:
	.zero	4
	.globl	global_var3
	.align 4
	.type	global_var3, @object
	.size	global_var3, 4
global_var3:
	.zero	4
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Debian 10.2.1-6) 10.2.1 20210110"
	.section	.note.GNU-stack,"",@progbits
