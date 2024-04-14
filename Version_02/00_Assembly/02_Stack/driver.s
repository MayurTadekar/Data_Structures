

# Section ROData
.section .rodata

	.msg_p_data:
		.string "Address = %p\n"

	.msg_p_ddata:
		.string	"Deleting = %d\n"

# Section Data
.section .data

	.globl	stack
	.type	stack, @object
	.size	stack, 4
	.align	4
stack:
	.zero	4

# Section BSS

# Section Text
.section .text
	
#
#	Function: An entry point function to the Stack Program
#
#	identifier:	_start
#	params: NONE
#	returns: NONE
#

	.globl	_start
	.type	_start, @function
_start:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code

	call	create_stack	
	movl	%eax, stack

	subl	$4, %esp
	movl	$0, -4(%ebp)
	
	.loop_pd:
	movl	-4(%ebp), %eax
	cmpl	$5, %eax
	jge	.loop_end_pd

		movl	-4(%ebp), %eax
		incl	%eax
		movl	$11, %ebx
		mull	%ebx

		pushl	%eax
		pushl	stack
		call	stack_push
		addl	$8, %esp
		
		incl	-4(%ebp)
		jmp	.loop_pd
	
	.loop_end_pd:

	addl	$4, %esp

	pushl	stack
	call	stack_print
	addl	$4, %esp

	push	stack
	call	stack_pop
	addl	$4, %esp

	pushl	stack
	call	stack_print
	addl	$4, %esp
	
	pushl	$delete_data
	pushl	$stack
	call	stack_destroy
	addl	$8, %esp

	pushl	stack
	call	stack_print
	addl	$4, %esp

	# Epilogue
	pushl	$0
	call	exit

#
#	Function: to delete data inserted in stack
#
#	identifier:	delete_data
#	params: data
#	returns: NONE
#
# void delete_data(data)
	.globl	delete_data
	.type	delete_data, @function
delete_data:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code

	pushl	8(%ebp)
	pushl	$.msg_p_ddata
	call	printf
	addl	$8, %esp

	# Epilogue
	movl	%ebp, %esp
	popl	%ebp
	ret

