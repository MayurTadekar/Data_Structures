#
# S.G.M.P
# @file: bst.s
# @brief: 
# @author: Mayur S. Tadekar(mrtadekar@gmail.com)
# @Copyright ©2020-2023 MarshallingVoid
# @date: 27 April 2024 (Saturday) 10:12:39 PM
#

#
# struct Node
# {
# 	void*	data
#	Node*	left
#	Node*	right
#	Node*	parent
# };
# #define SIZE_NODE (sizeof(Node))
.equ	n_data, 0
.equ	n_left, 4
.equ	n_right, 8
.equ	n_parent, 12
.equ	SIZE_NODE, 16

#
# struct Tree
# {
# 	Node*	root
#	int	size
# };
# #define SIZE_BST (sizeof(Tree))
.equ	t_root, 0
.equ	t_size, 4
.equ	SIZE_BST, 8

#
# struct Iterator
# {
# 	Node* itr
# 	void* stack
# }
# #define SIZE_ITERATOR (sizeof(Iterator))
.equ	i_itr, 0
.equ	i_stack, 4
.equ	SIZE_ITERATOR, 8

.equ	CMP_SAME, 1
.equ	CMP_LESS, 2

# Section ROData
.section .rodata

# Section Data
.section .data

# Section BSS
.section .bss

# Section Text
.section .text

################### Helper Function ###############
##
# @brief This function dynamically allocates memory.
# @details It allocates memory using the malloc function and handles the case where memory allocation fails by printing an error message to stderr.
# @param nr_bytes The number of bytes to allocate.
# @return Returns a pointer to the allocated memory or NULL if allocation fails.
##
	.type	xmalloc, @function
xmalloc:
	
	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	subl	$4, %esp
	movl	$0, -4(%ebp)

	pushl	8(%ebp)
	call	malloc
	addl	$4, %esp

	movl	%eax, -4(%ebp)

	movl	-4(%ebp), %eax
	cmpl	$0, %eax
	jne	.return_address

	pushl	$.msg_p_oom
	pushl	stderr
	call	fprintf
	addl	$8, %esp
	
	movl	$0, %eax
	jmp	.epilogue_xm

	.return_address:
	movl	-4(%ebp), %eax
	
	# Epilogue
	.epilogue_xm:
	addl	$4, %esp

	movl	%ebp, %esp
	popl	%ebp
	ret

##
# @brief Allocates memory for a new node.
# @details This function allocates memory for a new node structure and initializes its fields.
# @param data The data to be stored in the node.
# @return Returns a pointer to the newly created node.
##
# static node* create_node(data)
	.type	create_node, @function
create_node:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	subl	$4, %esp
	movl	$0, -4(%ebp)
	
	pushl	$SIZE_NODE
	call	xmalloc
	addl	$4, %esp
	
	movl	%eax, -4(%ebp)

	movl	-4(%ebp), %ebx
	movl	8(%ebp), %eax
	movl	%eax, n_data(%ebx)
	movl	$0, n_left(%ebx)
	movl	$0, n_right(%ebx)
	movl	$0, n_parent(%ebx)

	movl	-4(%ebp), %eax

	# Epilogue
	addl	$4, %esp
	
	movl	%ebp, %esp
	popl	%ebp
	ret

##
# @brief Locates a node containing specific data in a binary search tree.
# @details This function searches for a node containing the specified data in the binary search tree.
#          It uses a comparison function to determine the direction of search.
# @param tree Pointer to the binary search tree.
# @param data The data to search for.
# @param compare Pointer to the comparison function.
# @return Returns a pointer to the located node if found, otherwise returns NULL.
##
# static Node* locate_node(tree, data, compare)
	.type	locate_node, @function
locate_node:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	subl 	$8, %esp
	movl	$0, -4(%ebp)
	movl	$0, -8(%ebp)
	
	movl	8(%ebp), %ebx
	movl	t_root(%ebx), %eax
	movl	%eax, -4(%ebp)
	
	.loop_ln:
		
		movl	-4(%ebp), %ebx
	
		pushl	12(%ebp)
		pushl	n_data(%ebx)
		movl	16(%ebp), %ecx
		call	*%ecx
		addl	$8, %esp

		movl	%eax, -8(%ebp)

		movl	-8(%ebp), %eax
		cmpl	$CMP_SAME, %eax
		jne	.compare_less

			movl	-4(%ebp), %eax
			jmp	.epilogue_ln

		.compare_less:
		movl	-8(%ebp), %eax
		cmpl	$CMP_LESS, %eax
		jne	.move_right

			# Move Left
			movl	-4(%ebp), %ebx
			movl	n_left(%ebx), %eax
			movl	%eax, -4(%ebp)
			jmp	.compare_null

		.move_right:
		movl	-4(%ebp), %ebx
		movl	n_right(%ebx), %eax
		movl	%eax, -4(%ebp)

		.compare_null:
		movl	-4(%ebp), %eax
		cmpl	$0, %eax
		jne	.loop_ln
		
			movl	$0, %eax

	.loop_end_ln:

	# Epilogue
	.epilogue_ln:
	addl	$8, %esp
	movl	%ebp, %esp
	popl	%ebp
	ret

##
# @brief Finds the minimum value node in a binary search tree.
# @details This function traverses the left child of each node until reaching the leftmost leaf, which contains the minimum value.
# @param node The root node of the binary search tree (or subtree).
# @return Returns a pointer to the node containing the minimum value.
##
# static Node* minimum(node)
	.type	minimum, @function
minimum:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	.loop_min:
	movl	8(%ebp), %ebx
	movl	n_left(%ebx), %eax
	cmpl	$0, %eax
	je	.loop_end_min

		movl	8(%ebp), %ebx
		movl	m_left(%ebx), %eax
		movl	%eax, 8(%ebp)
		jmp	.loop_min
	
	.loop_end_min:

	# Epilogue
	movl	%ebp, %esp
	popl	%ebp
	ret

##
# @brief Finds the maximum value node in a binary search tree.
# @details This function traverses the right child of each node until reaching the rightmost leaf, which contains the maximum value.
# @param node The root node of the binary search tree (or subtree).
# @return Returns a pointer to the node containing the maximum value.
##
# static Node* maximum(node)
	.type	maximum, @function
maximum:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	.loop_max:
	movl	8(%ebp), %ebx
	movl	n_right(%ebx), %eax
	cmpl	$0, %eax
	je	.loop_end_max

		movl	8(%ebp), %ebx
		movl	m_right(%ebx), %eax
		movl	%eax, 8(%ebp)
		jmp	.loop_max
	
	.loop_end_max:

	# Epilogue
	movl	%ebp, %esp
	popl	%ebp
	ret

##
# @brief Finds the successor node of a given node in a binary search tree.
# @details This function finds the successor node of the given node in the binary search tree.
#          If the node has a right child, the successor is the minimum node in the right subtree.
#          Otherwise, it traverses up the tree to find the first ancestor whose left child is also an ancestor of the given node.
# @param node Pointer to the node for which the successor is to be found.
# @return Returns a pointer to the successor node.
##
# static Node* successor(node)
	.type	successor, @function
successor:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	subl	$4, %esp
	movl	$0, -4(%ebp)
	
	movl	8(%ebp), %ebx
	movl	n_right(%ebx), %ebx
	cmpl	$0, %ebx
	je	.get_parent_succssor
		
		movl	8(%ebp), %ebx
		pushl	n_right(%ebx)
		call	minimum
		addl	$4, %esp
		movl	%eax, -4(%ebp)
		jmp	.epilogue_succ

	.get_parent_successor:
	movl	8(%ebp), %ebx
	movl	n_parent(%ebx), %eax
	movl	%eax, -4(%ebp)

	.loop_succ:
	movl	-4(%ebp), %eax
	cmpl	$0, %eax
	je	.loop_end_succ
	movl	-4(%ebp), %eax
	movl	n_right(%eax), %eax
	movl	8(%ebp), %eax
	jne	.loop_end_succ

		movl	-4(%ebp), %eax
		movl	%eax, 8(%ebp)

		movl	-4(%ebp), %ebx
		movl	n_parent(%ebx), %eax
		movl	%eax, -4(%ebp)
		jmp	.loop_succ

	.loop_end_succ:

	# Epilogue
	.epilogue_succ:
	movl	-4(%ebp), %eax
	addl	$4, %esp

	movl	%ebp, %esp
	popl	%ebp
	ret

##
# @brief Finds the predecessor node of a given node in a binary search tree.
# @details This function finds the predecessor node of the given node in the binary search tree.
#          If the node has a left child, the predecessor is the maximum node in the left subtree.
#          Otherwise, it traverses up the tree to find the first ancestor whose right child is also an ancestor of the given node.
# @param node Pointer to the node for which the predecessor is to be found.
# @return Returns a pointer to the predecessor node.
##
# static Node* predecessor(node)
	.type	predecessor, @function
predeceessor:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	subl	$4, %esp
	movl	$0, -4(%ebp)
	
	movl	8(%ebp), %ebx
	movl	n_left(%ebx), %ebx
	cmpl	$0, %ebx
	je	.get_parent_pred
		
		movl	8(%ebp), %ebx
		pushl	n_left(%ebx)
		call	maximum
		addl	$4, %esp
		movl	%eax, -4(%ebp)
		jmp	.epilogue_pred

	.get_parent_pred:
	movl	8(%ebp), %ebx
	movl	n_parent(%ebx), %eax
	movl	%eax, -4(%ebp)

	.loop_pred:
	movl	-4(%ebp), %eax
	cmpl	$0, %eax
	je	.loop_end_pred
	movl	-4(%ebp), %eax
	movl	n_left(%eax), %eax
	movl	8(%ebp), %eax
	jne	.loop_end_pred

		movl	-4(%ebp), %eax
		movl	%eax, 8(%ebp)

		movl	-4(%ebp), %ebx
		movl	n_parent(%ebx), %eax
		movl	%eax, -4(%ebp)
		jmp	.loop_pred

	.loop_end_pred:

	# Epilogue
	.epilogue_pred:
	movl	-4(%ebp), %eax
	addl	$4, %esp

	movl	%ebp, %esp
	popl	%ebp
	ret

################### Interface Function ###############
##
# @brief Creates a new binary search tree.
# @details This function allocates memory for a new binary search tree structure and initializes its fields.
# @return Returns a pointer to the newly created binary search tree.
##
# extern void* create_tree
	.globl	create_tree
	.type	create_tree, @function
create_tree:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	subl	$4, %esp
	movl	$0, -4(%ebp)

	pushl	$SIZE_BST
	call	xmalloc
	addl	$4, %esp

	movl	%eax, -4(%ebp)

	movl	-4(%ebp), %ebx
	movl	$0, t_root(%ebx)
	movl	$0, t_size(%ebx)

	movl	-4(%ebp), %eax

	# Epilogue
	addl	$4, %esp
	movl	%ebp, %esp
	popl	%ebp
	ret

##
# @brief Inserts a new node containing specified data into the binary search tree.
# @details This function inserts a new node with the provided data into the binary search tree.
#          It uses a comparison function to determine the insertion point.
# @param tree Pointer to the binary search tree.
# @param data The data to be inserted into the tree.
# @param pcompareproc Pointer to the comparison function used to determine the insertion point.
# @return Returns 1 if insertion is successful, 0 otherwise.
##
# extern int bst_insert(void* tree, void* data, COMPAREPROC pcompareproc)
	.globl	bst_insert
	.type	bst_insert, @function
bst_insert:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	movl	8(%ebp), %ebx
	cmpl	$0, t_root(%ebx)
	je	.insert_root
	jmp	.insert_node

	.insert_root:
		pushl	12(%ebp)
		call	create_node
		addl	$4, %esp

		movl	8(%ebp), %ebx
		movl	%eax, t_root(%ebx)
		jmp	.increase_elmcount

	.insert_node:
		subl	$8, %esp
		movl	$0, -4(%ebp)
		movl	$0, -8(%ebp)

		mobl	8(%ebp), %ebx
		movl	t_root(%ebx), %eax
		movl	%eax, -4(%ebp)

		.loop_in:
			movl	-4(%ebp), %ebx
			pushl	n_data(%ebx)
			pushl	12(%ebp)
			movl	%16(%ebp), %ecx
			call	*%ecx
			addl	$8, %esp

			movl	%eax, -8(%ebp)

			cmpl	$CMP_SAME, %eax
			je	.ret_error_dap
			movl	-8(%ebp), %eax
			cmpl	$CMP_LESS, %eax
			je	.check_left
			jmp	.check_right

			.ret_error_dap:
				pushl	$.msg_p_dap
				call	printf
				addl	$4, %esp
				addl	$8, %esp
				jmp	.loop_end_in

			.check_left:
				movl	-4(%ebp), %ebx
				cmpl	$0, n_left(%ebx)
				jne	.move_left
				jmp	.insert_left

				.move_left:
					movl	-4(%ebp), %ebx
					movl	n_left(%ebx), %eax
					movl	%eax, -4(%ebp)
					jmp	.loop_in

				.insert_left:
					pushl	12(%ebp)
					call	create_node
					addl	$4, %esp
					
					movl	-4(%ebp), %ebx
					movl	%eax, n_left(%ebx)

					movl	-4(%ebp), %eax
					movl	n_left(%eax), %ebx
					movl	%eax, n_parent(%ebx)
					jmp	.increase_elmcount

			.check_right:
				movl	-4(%ebp), %ebx
				cmpl	$0, n_right(%ebx)
				jne	.move_right
				jmp	.insert_right

				.move_right:
					movl	-4(%ebp), %ebx
					movl	n_right(%ebx), %eax
					movl	%eax, -4(%ebp)
					jmp	.loop_in

				.insert_right:
					pushl	12(%ebp)
					call	create_node
					addl	$4, %esp

					movl	-4(%ebp), %ebx
					movl	%eax, n_right(%ebx)

					movl	-4(%ebp), %eax
					movl	n_right(%eax), %ebx
					movl	%eax, n_parent(%ebx)
					jmp	.increase_elmcount
	
		.loop_end_in:
		movl	$1, %eax
		jmp	.epilogue_bi

		.increase_elmcount:
		addl	$8, %esp

		movl	8(%ebp), %ebx
		incl	t_size(%ebx)

	# Epilogue
	.epilogue_bi:
	movl	%ebp, %esp
	popl	%ebp
	ret
	
##
# @brief Removes a node containing specified data from the binary search tree.
# @details This function removes a node containing the specified data from the binary search tree.
#          It uses a comparison function to locate the node to be removed.
# @param tree Pointer to the binary search tree.
# @param data The data to be removed from the tree.
# @param pcompareproc Pointer to the comparison function used to locate the node to be removed.
# @return Returns the data removed from the tree, or NULL if data is not found.
##
# extern void* bst_remove(void* tree, void* data, COMPAREPROC pcompareproc)
	.globl	bst_remove
	.type	bst_remove, @function
bst_remove:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	subl	$8, %esp
	movl	$0, -4(%ebp)
	movl	$0, -8(%ebp)

	pushl	16(%ebp)
	pushl	12(%ebp)
	pushl	8(%ebp)
	call	locate_node
	addl	$12, %esp

	movl	%eax, -4(%ebp)
	
	movl	-4(%ebp), %ebx
	movl	n_data(%ebx), %eax
	movl	%eax, -8(%ebp)

	.loop_br:

		# Check Right
		movl	-4(%ebp), %ebx
		cmpl	$0, n_right(%ebx)
		jne	.replace_succ
		jmp	.check_left

		.replace_succ:
		subl	$4, %esp
		movl	-4(%ebp), %ebx
		pushl	n_right(%ebx)
		call	minimum
		addl	$4, %esp
		movl	%eax, -12(%ebp)

		movl	-12(%ebp), %ebx
		movl	n_data(%ebx), %eax
		movl	-4(%ebp), %ebx
		movl	%eax, n_data(%ebx)

		movl	-12(%ebp), %eax
		movl	%eax, -4(%ebp)

		addl	$4, %esp
		jmp	.loop_br

		# Check Left
		.check_left:
		movl	-4(%ebp), %ebx
		cmpl	$0, n_left(%ebx
		je	.remove_node

		# Replace with Predecessor
		addl	$4, %esp
		movl	-4(%ebp), %ebx
		pushl	n_left(%ebx)
		call	maximum
		addl	$4, %esp
		movl	%eax, -12(%ebp)
	
		movl	-12(%ebp), %ebx
		movl	n_data(%ebx), %eax
		movl	-4(%ebp), %ebx
		movl	%eax, n_data(%ebx)

		movl	-12(%ebp), %eax
		movl	%eax, -4(%ebp)

		addl	$4, %esp
		jmp	.loop_br

		.remove_node:
		movl	-4(%ebp), %ebx
		cmpl	$0, n_parent(%ebx)
		je	.root_null
		jmp	.check_parent_left

		.root_null:
			movl	8(%ebp), %ebx
			movl	$0, t_root(%ebx)
			jmp	.loop_end_br

		.check_parent_left:
		movl	-4(%ebp), %eax
		movl	n_parent(%eax), %ebx
		movl	n_left(%ebx), %ebx
		cmpl	%eax, %ebx
		je	.parent_left_null
		jmp	.parent_right_null

		.parent_left_null:
			movl	-4(%ebp), %ebx
			movl	n_parent(%ebx), %ebx
			movl	$0, n_left(%ebx)
			jmp	.loop_end_br

		.parent_right_null:
			movl	-4(%ebp), %ebx
			movl	n_parent(%ebx), %ebx
			movl	$0, n_right(%ebx)

	.loop_end_br:

	pushl	-4(%ebp)
	call	free
	addl	$4, %esp

	movl	8(%ebp), %ebx
	decl	t_size(%ebx)

	# Epilogue
	movl	-8(%ebp), %eax
	addl	$8, %esp

	movl	%ebp, %esp
	popl	%ebp
	ret


