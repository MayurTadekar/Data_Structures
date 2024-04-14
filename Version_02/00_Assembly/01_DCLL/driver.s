 #
 # S.G.M.P
 # @file: driver.s
 # @brief: Implementation of the driver code for DCLL in x86 Linux Assembly
 # @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 # @Copyright ©2020-2023 MarshallingVoid
 # @date: 13 April 2024 (Saturday) 12:55:24 PM
 #

# Section ROData
.section .rodata
	
	.msg_p_start:
		.string	"List: {START}->"

	.msg_p_data:
		.string	"{%d}->"

	.msg_p_end:
		.string "{END}\n\n"

	.msg_p_delete:
		.string "Deleting: %d\n"

# Section Data
.section .data
	
	.type	list, @object
	.size	list, 4
	.align	4
list:
	.zero	4

# Section BSS

# Section Text
.section .text


#	
#	Function: Entry point function of the program
#
# 	identifier: _start
#

	.globl	_start
	.type	_start, @function
_start:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	call	create_list
	movl	%eax, list

	subl	$4, %esp
	movl	$0, -4(%ebp)

	# Loop to insert elements in front of list
	.loop_if:
	movl	-4(%ebp), %ebx
	cmpl	$5, %ebx
	jge	.loop_if_end
	
		movl	-4(%ebp), %eax
		incl	%eax
		movl	$10, %ebx
		mull	%ebx

		pushl	%eax
		pushl	list
		call	list_insert_front
		addl	$8, %esp
		
		incl	-4(%ebp)
		jmp	.loop_if

	.loop_if_end:
	addl	$4, %esp

	# Print list
	pushl	list
	call	print_list
	addl	$4, %esp

	subl	$4, %esp
	movl	$0, -4(%ebp)

	# Loop to insert elements at end of list
	.loop_ib:
	movl	-4(%ebp), %ebx
	cmpl	$5, %ebx
	jge	.loop_ib_end
	
		movl	-4(%ebp), %eax
		incl	%eax
		movl	$22, %ebx
		mull	%ebx

		pushl	%eax
		pushl	list
		call	list_insert_front
		addl	$8, %esp
		
		incl	-4(%ebp)
		jmp	.loop_ib

	.loop_ib_end:
	addl	$4, %esp

	# Print list
	pushl	list
	call	print_list
	addl	$4, %esp

	# function call to insert data after existing data
	pushl	$compare
	pushl	$22
	pushl	$2121
	pushl	list
	call	list_insert_after
	addl	$12, %esp

	# function call to insert data before existing data
	pushl	$compare
	pushl	$22
	pushl	$2121
	pushl	list
	call	list_insert_before
	addl	$12, %esp

	# function call to print list
	pushl	list
	call	print_list
	addl	$4, %esp

	# function call to insert data at specific index
	pushl	$0
	pushl	$1212
	pushl	list
	call	list_insert_at
	addl	$12, %esp

	# function call to print list
	pushl	list
	call	print_list
	addl	$4, %esp

	# function call to remove element from front
	pushl	list
	call	list_remove_front
	addl	$4, %esp

	# function call to print list
	pushl	list
	call	print_list
	addl	$4, %esp

	# function call to remove element from end
	pushl	list
	call	list_remove_back
	addl	$4, %esp

	# function call to print list
	pushl	list
	call	print_list
	addl	$4, %esp

	# function call to remove element after a specific data
	pushl	$compare
	pushl	$22
	pushl	list
	call	list_remove_after
	addl	$4, %esp

	# function call to print list
	pushl	list
	call	print_list
	addl	$4, %esp

	# function call to remove element before a specific data
	pushl	$compare
	pushl	$22
	pushl	list
	call	list_remove_before
	addl	$4, %esp

	# function call to print list
	pushl	list
	call	print_list
	addl	$4, %esp

	# function call to remove element at a specific index
	pushl	$0
	pushl	list
	call	list_remove_at
	addl	$8, %esp

	# function call to print list
	pushl	list
	call	print_list
	addl	$4, %esp

	# function call to destroy list
	pushl	$delete_data
	pushl	$list
	call	list_destroy
	addl	$8, %esp

	# function call to print list
	pushl	list
	call	print_list
	addl	$4, %esp

	# Epilogue
	pushl	$0
	call	exit

#
#	function : The function that iterates each data and print the data of list
#
#	identifier:	print_list
#	param : list
#	returns: None
#

# void print_list(list)
	.globl	print_list
	.type	print_list, @function
print_list:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	subl	$8, %esp
	movl	$0, -4(%ebp)
	movl	$0, -8(%ebp)

	pushl	8(%ebp)
	call	list_size
	addl	$4, %esp

	movl	%eax, -8(%ebp)
	
	# print the START message
	pushl	$.msg_p_start
	call	printf
	addl	$4, %esp

	# loop to print all the elements of list
	.loop_pl:
	movl	-4(%ebp), %eax
	movl	-8(%ebp), %ebx
	cmpl	%ebx, %eax
	jge	.loop_end_pl

		pushl	-4(%ebp)
		pushl	8(%ebp)
		call	list_data_at
		addl	$8, %esp
	
		pushl	%eax
		pushl	$.msg_p_data
		call	printf
		addl	$8, %esp

		movl	-4(%ebp), %eax
		incl	%eax
		movl	%eax, -4(%ebp)
		jmp	.loop_pl

	.loop_end_pl:

	addl	$8, %esp

	# print the END message
	pushl	$.msg_p_end
	call	printf
	addl	$4, %esp

	# Epilogue
	movl	%ebp, %esp
	popl	%ebp
	ret

#
#	function : The function that compares 2 data 
#
#	identifier:	compare
#	param : 1) data1
#			2) data2
#	returns: SUCCESS if data same and FAILURE is data not same
#

# int compare(data1, data2)
	.globl	compare
	.type	compare, @function
compare:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code

	movl	8(%ebp), %eax
	movl	12(%ebp), %ebx
	cmpl	%eax, %ebx
	jne	.return_failure

		movl	$0, %eax
		jmp	.epilogue_cmp

	.return_failure:
	movl	$1, %eax

	# Epilogue
	.epilogue_cmp:
	movl	%ebp, %esp
	popl	%ebp
	ret


#
#	function : The function that deletes data while destroying list nodes 
#
#	identifier:	delete_data
#	param : data
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
	pushl	$.msg_p_delete
	call	printf
	addl	$8, %esp

	# Epilogue
	movl	%ebp, %esp
	popl	%ebp
	ret

