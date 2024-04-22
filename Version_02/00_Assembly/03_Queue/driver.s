#
# S.G.M.P
# @file: driver.s
# @brief: Implementation of driver code in assembly for queue
# @author: Mayur S. Tadekar(mrtadekar@gmail.com)
# @Copyright ©2020-2023 MarshallingVoid
# @date: 22 April 2024 (Monday) 11:14:55 AM
#

# Section ROData
.section .rodata

	.msg_p_data:
		.string	"{%d}->"

	.msg_p_start:
		.string "{START}->"

	.msg_p_end:
		.string	"{END}\n"

	.msg_p_ddata:
		.string "Deleting: %d\n"

# Section Data
.section .data

	.globl	queue
	.type	queue, @object
	.size	queue, 4
	.align	4
queue:
	.zero	4

# Section BSS

# Section Text
.section .text

#
# Function: _start
# Description: Entry point of the program, responsible for executing the main logic.
# Params: None
# Returns: None
# Notes: This function initializes a queue, enqueues a series of integers, prints the queue, dequeues an element, prints the updated queue, 
#        destroys the queue, prints the empty queue, and exits the program.
#
# _start
	.globl	_start
	.type	_start, @function
_start:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	call	create_queue
	movl	%eax, queue

	subl	$4, %esp
	movl	$0, -4(%ebp)

	.loop_eq:
	movl	-4(%ebp), %eax
	cmpl	$5, %eax
	jge	.loop_end_eq

		movl	-4(%ebp), %eax
		incl	%eax
		movl	$21, %ebx
		mull	%ebx

		pushl	%eax
		pushl	queue
		call	queue_enqueue
		addl	$8, %esp

		incl	-4(%ebp)

		jmp	.loop_eq

	.loop_end_eq:
	addl	$4, %esp

	pushl	queue
	call	print_queue
	addl	$4, %esp
	
	pushl	queue
	call	queue_dequeue
	addl	$4, %esp

	pushl	queue
	call	print_queue
	addl	$4, %esp
	
	pushl	$delete_data
	pushl	$queue
	call	destroy_queue
	addl	$8, %esp

	pushl	queue
	call	print_queue
	addl	$4, %esp
	
	# Epilogue
	pushl	$0
	call	exit

#
# Function: print_queue
# Description: Prints the contents of the queue by calling queue_print.
# Params: 1) queue - pointer to the queue
# Returns: None
# Notes: This function prints the start message, then prints the content of the queue using queue_print, and finally prints the end message.
#
# void print_queue(queue)
	.globl	print_queue
	.type	print_queue, @function
print_queue:
	
	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	pushl	$.msg_p_start
	call	printf
	addl	$4, %esp
	
	pushl	$print_data
	pushl	8(%ebp)
	call	queue_print
	addl	$8, %esp

	pushl	$.msg_p_end
	call	printf
	addl	$4, %esp

	# Epilogue
	movl	%ebp, %esp
	popl	%ebp
	ret

#
# Function: print_data
# Description: Prints the provided data.
# Params: 1) data - data to be printed
# Returns: None
# Notes: This function prints the provided data along with a message.
#
# void print_data(data)
	.globl	print_data
	.type	print_data, @function
print_data:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	pushl	8(%ebp)
	pushl	$.msg_p_data
	call	printf
	addl	$8, %esp

	# Epilogue
	movl	%ebp, %esp
	popl	%ebp
	ret

#
# Function: delete_data
# Description: Prints a message indicating the deletion of provided data.
# Params: 1) data - data to be deleted
# Returns: None
# Notes: This function prints a message indicating the deletion of the provided data.
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

