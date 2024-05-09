 #
 # S.G.M.P
 # @file: driver.s
 # @brief: 
 # @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 # @Copyright ©2020-2023 MarshallingVoid
 # @date: 08 May 2024 (Wednesday) 04:10:56 PM
 #
 
# Section RODATA
.section	.rodata
	.msg_p_start:
		.string		"{START}|"

	.msg_p_data:
		.string		"{%d}|"

	.msg_p_end:
		.string		"{END}\n\n"

	.msg_p_1:
		.string		"1\n"

# Section DATA
.section	.data
	
	.globl	tree
	.type	tree, @object
	.size	tree, 4
	.align	4
tree:
	.zero	4

# Section BSS


# Section Text
##
# @brief The main entry point for the program.
# @details This function serves as the main entry point for the program. It initializes a binary search tree,
#          inserts three elements into the tree, prints the contents of the tree, and then exits the program.
# @return None
##
.section	.text
	.globl	_start
	.type	_start, @function
_start:

	#Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code

	call	create_tree

	movl	%eax, tree

	pushl	$compare
	pushl	$1
	pushl	tree
	call	avl_insert
	addl	$12, %esp

	pushl	$compare
	pushl	$2
	pushl	tree
	call	avl_insert
	addl	$12, %esp

	pushl	$compare
	pushl	$3
	pushl	tree
	call	avl_insert
	addl	$12, %esp

	pushl	$compare
	pushl	$4
	pushl	tree
	call	avl_insert
	addl	$12, %esp

	pushl	$compare
	pushl	$5
	pushl	tree
	call	avl_insert
	addl	$12, %esp

	pushl	tree
	call	print_tree
	addl	$4, %esp

	pushl	$compare
	pushl	$50
	pushl	tree
	call	avl_remove
	addl	$12, %esp

	pushl	tree
	call	print_tree
	addl	$4, %esp

	#Epilogue
	pushl	$0
	call	exit

##
# @brief Compare function for binary search tree nodes.
# @details This function compares two data elements and returns an integer indicating their relationship.
#          It follows the convention:
#          - If data1 == data2, returns 1
#          - If data1 < data2, returns 2
#          - If data1 > data2, returns 3
# @param data1 The first data element to compare.
# @param data2 The second data element to compare.
# @return An integer indicating the relationship between the two data elements.
##
# int compare(data1, data1)
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
	je 		.return_same
	jl		.return_less
	jmp		.return_greater

	.return_same:
		movl	$1, %eax
		jmp		.epilogue_cmp

	.return_less:
		movl	$2, %eax
		jmp		.epilogue_cmp

	.return_greater:
		movl	$3, %eax

	# Epilogue
	.epilogue_cmp:
	movl	%ebp, %esp
	popl	%ebp
	ret

##
# @brief Prints a data element.
# @details This function prints the given data element to the standard output.
# @param data The data element to be printed.
# @return This function does not return a value.
##
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

##
# @brief Prints the elements of a binary search tree in ascending order.
# @details This function prints the elements of a binary search tree in ascending order.
#          It first prints a start message, then traverses the tree in inorder fashion,
#          printing each element using the provided print_data function, and finally
#          prints an end message.
# @param tree The binary search tree to be printed.
# @return This function does not return a value.
##
# void print_tree(tree)
	.globl	print_tree
	.type	print_tree, @function
print_tree:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code

	pushl	$.msg_p_start
	call	printf
	addl	$4, %esp

	pushl	$print_data
	pushl	tree
	call	avl_inorder
	addl	$8, %esp

	pushl	$.msg_p_end
	call	printf
	addl	$4, %esp

	# Epilogue
	movl	%ebp, %esp
	popl	%ebp
	ret
