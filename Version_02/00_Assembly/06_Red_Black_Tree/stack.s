 #
 # S.G.M.P
 # @file: stack.s
 # @brief: Assembly source code that implements DCLL based Stack
 # @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 # @Copyright ©2020-2023 MarshallingVoid
 # @date: 14 April 2024 (Sunday) 09:30:58 PM
 #
 
# Section ROData
.section .rodata

	.msg_p_start:
		.string	"  |\n{START}\n\n"

	.msg_p_end:
		.string	"{END}\n"
	
	.msg_p_data:
		.string "  |\n{%d}\n"

# Section Data
.section .data

# Section BSS
.section .bss

# Section Text
.section .text

################# Stack Interface Functions ##################

#
#	Function: To create a Stack (DCLL)
#
#	identifier:	create_stack
#	params: NONE
#	returns: pointer to the DCLL which is represented as Stack
#
# list* create_stack()
	.globl	create_stack
	.type	create_stack, @function
create_stack:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code

	call create_list

	# Epilogue
	movl	%ebp, %esp
	popl	%ebp
	ret

#
#	Function: for insertion of data in stack 
#
#	identifier:	stack_push
#	params: 1) stack
#			2) data
#	returns: status of insertion
#
# ret_t stack_push(stack, data)
	.globl	stack_push
	.type	stack_push, @function
stack_push:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	pushl	12(%ebp)
	pushl	8(%ebp)
	call	list_insert_back
	addl	$8, %esp

	# Epilogue
	movl	%ebp, %esp
	popl	%ebp
	ret

#
#	Function: for removing recently inserted data from stack
#
#	identifier:	stack_pop
#	params: stack
#	returns: Data recently pushed
#
# void* stack_pop(stack)
	.globl	stack_pop
	.type	stack_pop, @function
stack_pop:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code

	pushl	8(%ebp)
	call	list_remove_back
	addl	$8, %esp

	# Epilogue
	movl	%ebp, %esp
	popl	%ebp
	ret

#
#	Function: to iterate every element and print the data in stack
#
#	identifier:	stack_print
#	params: stack
#	returns: NONE
#
# void stack_print(stack)
	.globl	stack_print
	.type	stack_print, @function
stack_print:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	pushl	8(%ebp)
	call	list_size
	addl	$4, %esp

	subl	$4, %esp
	decl	%eax
	movl	%eax, -4(%ebp)
	
	pushl	$.msg_p_end
	call	printf
	addl	$4, %esp

	.loop_sp:
	movl	-4(%ebp), %eax
	cmpl	$0, %eax
	jl	.loop_end_sp

		pushl	-4(%ebp)
		pushl	8(%ebp)
		call	list_data_at
		addl	$8, %esp

		pushl	%eax
		pushl	$.msg_p_data
		call	printf
		addl	$8, %esp

		decl	-4(%ebp)
		jmp	.loop_sp

	.loop_end_sp:

	pushl	$.msg_p_start
	call	printf
	addl	$4, %esp

	# Epilogue
	addl	$4, %esp
	movl	%ebp, %esp
	popl	%ebp
	ret

#
#	Function: to destroy stack and destroy every element with data in it
#
#	identifier:	stack_destroy
#	params: 1) pointer to stack
#			2) destroy_data callback fuction
#	returns: NONE
#
# void stack_destroy(pstack, destroy_data)
	.globl	stack_destroy
	.type	stack_destroy, @function
stack_destroy:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main code
	pushl	12(%ebp)
	pushl	8(%ebp)
	call	list_destroy
	addl	$8, %esp

	# Epilogue
	movl	%ebp, %esp
	popl	%ebp
	ret
