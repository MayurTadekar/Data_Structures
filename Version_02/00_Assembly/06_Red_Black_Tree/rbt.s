#
# S.G.M.P
# @file: rbt.s
# @brief: 
# @author: Mayur S. Tadekar(mrtadekar@gmail.com)
# @Copyright ©2020-2023 MarshallingVoid
# @date: 08 May 2024 (Wednesday) 03:31:18 PM
#

#
# struct Node
# {
# 	void*	data
#	Node*	left
#	Node*	right
#	Node*	parent
#	int 	color
# };
# #define SIZE_NODE (sizeof(Node))
.equ	n_data, 0
.equ	n_left, 4
.equ	n_right, 8
.equ	n_parent, 12
.equ	n_color, 16
.equ	SIZE_NODE, 20

#
# struct Tree
# {
# 	Node*	root
#	int	size
# };
# #define SIZE_AVL (sizeof(Tree))
.equ	t_root, 0
.equ	t_size, 4
.equ	SIZE_AVL, 8

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

.equ	RED, 0
.equ	BLACK, 1

.equ	CMP_SAME, 1
.equ	CMP_LESS, 2

# Section ROData
.section .rodata

	.msg_p_oom:
		.string	"ERROR: Out of memory\n"

	.msg_p_dap:
		.string	"ERROR: Data Already Present\n"

	.msg_p_1:
		.string	"--1\n"

	.msg_p_2:
		.string	"\n2\n"

	.msg_p_data:
		.string "%d\n"

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
	jne		.return_address

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
# @brief Locates a node containing specific data in a AVL Tree.
# @details This function searches for a node containing the specified data in the AVL Tree.
#          It uses a comparison function to determine the direction of search.
# @param tree Pointer to the AVL Tree.
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
# @brief Finds the minimum value node in a AVL Tree.
# @details This function traverses the left child of each node until reaching the leftmost leaf, which contains the minimum value.
# @param node The root node of the AVL Tree (or subtree).
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
		movl	n_left(%ebx), %eax
		movl	%eax, 8(%ebp)
		jmp	.loop_min
	
	.loop_end_min:

	movl 	8(%ebp), %eax

	# Epilogue
	movl	%ebp, %esp
	popl	%ebp
	ret

##
# @brief Finds the maximum value node in a AVL Tree.
# @details This function traverses the right child of each node until reaching the rightmost leaf, which contains the maximum value.
# @param node The root node of the AVL Tree (or subtree).
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
		movl	n_right(%ebx), %eax
		movl	%eax, 8(%ebp)
		jmp	.loop_max
	
	.loop_end_max:

	movl 	8(%ebp), %eax

	# Epilogue
	movl	%ebp, %esp
	popl	%ebp
	ret

##
# @brief Finds the successor node of a given node in a AVL Tree.
# @details This function finds the successor node of the given node in the AVL Tree.
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
	je	.get_parent_successor
		
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
# @brief Finds the predecessor node of a given node in a AVL Tree.
# @details This function finds the predecessor node of the given node in the AVL Tree.
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

##
# @brief Performs an inorder traversal of the AVL Tree rooted at the given node.
# @details This function traverses the AVL Tree in an inorder manner and applies the provided
#          printing function to each node's data.
# @param node Pointer to the root of the subtree to traverse.
# @param printdata Pointer to the function used to print the data of each node.
# @return None
##
# static void inorder(void* node, PRINTDATAPROC printdata)
	.type	inorder, @function
inorder:
	
	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	# if(node->left)
	movl	8(%ebp), %ebx
	cmpl	$0, n_left(%ebx)
	jne		.call_inorder_left
	jmp		.print_data

	.call_inorder_left:
		movl	8(%ebp), %ebx

		pushl	12(%ebp)
		pushl	n_left(%ebx)
		call	inorder
		addl	$8, %esp

	.print_data:

	movl	8(%ebp), %ebx
	movl	12(%ebp), %ecx
	pushl	n_data(%ebx)
	call	*%ecx
	addl	$4, %esp

	# if(node->right)
	movl	8(%ebp), %ebx
	cmpl	$0, n_right(%ebx)
	jne		.call_inorder_right
	jmp		.epilogue_in

	.call_inorder_right:
	movl	8(%ebp), %ebx
	pushl	12(%ebp)
	pushl	n_right(%ebx)
	call	inorder
	addl	$8, %esp

	# Epilogue
	.epilogue_in:
	movl	%ebp, %esp
	popl	%ebp
	ret
##
# @brief Performs a left rotation operation on the Red-Black Tree.
#
# This function rotates the given node and its right child to the left, 
#	maintaining the Red-Black Tree properties.
#
# @param node Pointer to the node around which the left rotation is performed.
# @return Pointer to the node that is the new root after the left rotation.
#

# static Node* left_rotate(Node* node)
	.type	left_rotate, @function
left_rotate:

	# Prologue
	pushl	%ebp
	movl 	%esp, %ebp

	pushl	$.msg_p_1
	call 	printf
	addl	$4, %esp

	# Main Code
	subl	$4, %esp
	movl 	8(%ebp), %ebx
	movl 	n_right(%ebx), %eax
	movl 	%eax, -4(%ebp)

	movl 	-4(%ebp), %ebx
	movl 	n_left(%ebx), %eax
	movl 	8(%ebp), %ebx
	movl 	%eax, n_right(%ebx)

	cmpl 	$0, %eax
	jne 	.set_right_parent
	jmp 	.set_left_node

	.set_right_parent:
		movl 	8(%ebp), %ebx
		movl 	n_right(%ebx), %eax
		movl 	%ebx, n_parent(%eax)

	.set_left_node:
		movl 	8(%ebp), %eax
		movl 	-4(%ebp), %ebx
		movl 	%eax, n_left(%ebx)

	movl 	8(%ebp), %ebx
	movl 	n_parent(%ebx), %eax
	movl 	-4(%ebp), %ebx
	movl 	%eax, n_parent(%ebx)
	cmpl 	$0, %eax
	je 		.set_node_parent_lr

		movl 	8(%ebp), %ebx
		movl 	n_parent(%ebx), %ebx
		movl 	8(%ebp), %eax
		cmpl 	%eax, n_left(%ebx)
		jne 	.set_right_of_parent_lr

			movl 	8(%ebp), %ebx
			movl 	n_parent(%ebx), %ebx
			movl 	-4(%ebp), %eax
			movl 	%eax, n_left(%ebx)
			jmp 	.set_node_parent_lr

		.set_right_of_parent_lr:

			movl 	8(%ebp), %ebx
			movl 	n_parent(%ebx), %ebx
			movl 	-4(%ebp), %eax
			movl 	%eax, n_right(%ebx)

	.set_node_parent_lr:
		movl 	-4(%ebp), %eax
		movl 	8(%ebp), %ebx
		movl 	n_parent(%ebx), %eax

	# Epilogue
	movl 	-4(%ebp), %eax
	addl	$4, %esp

	movl 	%ebp, %esp
	popl 	%ebp
	ret

##
# @brief Performs a right rotation operation on the Red-Black Tree.
#
# This function rotates the given node and its left child to the right, maintaining the Red-Black Tree properties.
#
# @param node Pointer to the node around which the right rotation is performed.
# @return Pointer to the node that is the new root after the right rotation.
#
# static right_rotate(Node* node)
	.type	right_rotate, @function
right_rotate:

	# Prologue
	pushl	%ebp
	movl 	%esp, %ebp

	# Main Code
	subl	$4, %esp
	movl 	8(%ebp), %ebx
	movl 	n_left(%ebx), %eax
	movl 	%eax, -4(%ebp)

	movl 	-4(%ebp), %ebx
	movl 	n_right(%ebx), %eax
	movl 	8(%ebp), %ebx
	movl 	%eax, n_left(%ebx)

	cmpl 	$0, %eax
	jne 	.set_left_parent
	jmp 	.set_right_node

	.set_left_parent:
		movl 	8(%ebp), %ebx
		movl 	n_left(%ebx), %eax
		movl 	%ebx, n_parent(%eax)

	.set_right_node:
		movl 	8(%ebp), %eax
		movl 	-4(%ebp), %ebx
		movl 	%eax, n_right(%ebx)

	movl 	8(%ebp), %ebx
	movl 	n_parent(%ebx), %eax
	movl 	-4(%ebp), %ebx
	movl 	%eax, n_parent(%ebx)
	cmpl 	$0, %eax
	je 		.set_node_parent_rr

		movl 	8(%ebp), %ebx
		movl 	n_parent(%ebx), %ebx
		movl 	8(%ebp), %eax
		cmpl 	%eax, n_left(%ebx)
		jne 	.set_right_of_parent_rr

			movl 	8(%ebp), %ebx
			movl 	n_parent(%ebx), %ebx
			movl 	-4(%ebp), %eax
			movl 	%eax, n_left(%ebx)
			jmp 	.set_node_parent_rr

		.set_right_of_parent_rr:

			movl 	8(%ebp), %ebx
			movl 	n_parent(%ebx), %ebx
			movl 	-4(%ebp), %eax
			movl 	%eax, n_right(%ebx)

	.set_node_parent_rr:
		movl 	-4(%ebp), %eax
		movl 	8(%ebp), %ebx
		movl 	n_parent(%ebx), %eax

	# Epilogue
	movl 	-4(%ebp), %eax
	addl	$4, %esp

	movl 	%ebp, %esp
	popl 	%ebp
	ret

##
# @brief Fix-up procedure to maintain Red-Black Tree properties after insertion.
#
# This function adjusts the Red-Black Tree structure to ensure that it conforms to the Red-Black Tree properties
# after the insertion of a new node. It checks and corrects violations such as consecutive red nodes or invalid
# rotations.
#
# @param tree Pointer to the Red-Black Tree structure.
# @param node Pointer to the node that may violate Red-Black Tree properties after insertion.
#
# static insert_fixup(tree, node)
	.type	insert_fixup, @funciton
insert_fixup:

	# Prologue
	pushl	%ebp
	movl 	%esp, %ebp
	
	# Main Code 
	subl	$4, %esp

	.loop_if:
	movl	12(%ebp), %ebx
	cmpl 	$0, n_parent(%ebx)
	je 		.loop_end_if
	movl 	12(%ebp), %ebx
	movl 	n_parent(%ebx), %ebx
	cmpl 	$RED, n_color(%ebx)
	jne 	.loop_end_if
	movl	12(%ebp), %ebx
	movl	n_parent(%ebx), %ebx
	cmpl	$0, n_parent(%ebx)
	je 		.loop_end_if

		movl 	12(%ebp), %ebx
		movl 	n_parent(%ebx), %edx

		movl 	n_parent(%ebx), %ebx
		movl 	n_paren(%ebx), %ebx
		cmpl 	%edx, n_left(%ebx)
		je 		.process_left_parent
		jmp 	.process_right_parent

		.process_left_parent:

			movl 	12(%ebp), %ebx
			movl 	n_parent(%ebx), %ebx
			movl 	n_parent(%ebx), %ebx
			movl 	n_right(%ebx), %eax
			movl 	%eax, -4(%ebp)

			# if (uncle && RED == uncle->color)
			movl	-4(%ebp), %ecx
			test	%ecx, %ecx
			je 		.else_condition_plp
			cmpl 	$RED, n_color(%ecx)
			jne 	.else_condition_plp

			movl 	12(%ebp), %ebx
			movl 	n_parent(%ebx), %ebx
			movl 	$BLACK, n_color(%ebx)

			movl 	-4(%ebp), %ebx
			movl 	$BLACK, n_color(%ebx)

			movl 	12(%ebp), %ebx
			movl 	n_parent(%ebx), %ebx
			movl 	n_parent(%ebx), %ebx
			movl 	$RED, n_color(%ebx)

			movl 	12(%ebp), %ebx
			movl 	n_parent(%ebx), %ebx
			movl 	n_parent(%ebx), %eax
			movl 	%eax, 12(%ebp)

			.else_condition_plp:
			movl 	12(%ebp), %eax
			movl 	12(%ebp), %ebx
			movl 	n_parent(%ebx), %ebx
			cmpl 	%eax, n_right(%ebx)
			jne 	.set_colors_parent_left

			movl 	12(%ebp), %ebx
			movl 	n_parent(%ebx), %eax
			movl 	%eax, 12(%ebp)

			pushl	12(%ebp)
			call 	left_rotate
			addl	$4, %esp

			.set_colors_parent_left:
			movl 	12(%ebp), %ebx
			movl 	n_parent(%ebx), %ebx
			movl 	$BLACK, n_color(%ebx)

			movl 	12(%ebp), %ebx
			movl 	n_parent(%ebx), %ebx
			movl 	n_parent(%ebx), %ebx
			movl 	$RED, n_color(%ebx)

			pushl	%ebx
			call 	right_rotate
			addl	$4, %esp

			movl 	%eax, 12(%ebp)
			jmp 	.loop_if

		.process_right_parent:

			movl 	12(%ebp), %ebx
			movl 	n_parent(%ebx), %ebx
			movl 	n_parent(%ebx), %ebx
			movl 	n_left(%ebx), %eax
			movl 	%eax, -4(%ebp)

			# if (uncle && RED == uncle->color)
			movl	-4(%ebp), %ecx
			test	%ecx, %ecx
			je 		.else_condition_prp
			cmpl 	$RED, n_color(%ecx)
			jne 	.else_condition_prp

			movl 	12(%ebp), %ebx
			movl 	n_parent(%ebx), %ebx
			movl 	$BLACK, n_color(%ebx)

			movl 	-4(%ebp), %ebx
			movl 	$BLACK, n_color(%ebx)

			movl 	12(%ebp), %ebx
			movl 	n_parent(%ebx), %ebx
			movl 	n_parent(%ebx), %ebx
			movl 	$RED, n_color(%ebx)

			movl 	12(%ebp), %ebx
			movl 	n_parent(%ebx), %ebx
			movl 	n_parent(%ebx), %eax
			movl 	%eax, 12(%ebp)

			.else_condition_prp:
			movl 	12(%ebp), %eax
			movl 	12(%ebp), %ebx
			movl 	n_parent(%ebx), %ebx
			cmpl 	%eax, n_right(%ebx)
			jne 	.set_colors_parent_right

			movl 	12(%ebp), %ebx
			movl 	n_parent(%ebx), %eax
			movl 	%eax, 12(%ebp)

			pushl	12(%ebp)
			call 	right_rotate
			addl	$4, %esp

			.set_colors_parent_right:
			movl 	12(%ebp), %ebx
			movl 	n_parent(%ebx), %ebx
			movl 	$BLACK, n_color(%ebx)

			movl 	12(%ebp), %ebx
			movl 	n_parent(%ebx), %ebx
			movl 	n_parent(%ebx), %ebx
			movl 	$RED, n_color(%ebx)

			pushl	%ebx
			call 	left_rotate
			addl	$4, %esp

			movl 	%eax, 12(%ebp)
			jmp 	.loop_if
	.loop_end_if:

	movl 	12(%ebp), %ebx
	cmpl 	$0, n_parent(%ebx)
	je 		.set_root_black_if

		movl 	8(%ebp), %ebx
		movl 	12(%ebp), %eax
		movl 	%eax, t_root(%ebx)

	.set_root_black_if:
	movl 	8(%ebp), %ebx
	movl 	t_root(%ebx), %ebx
	movl 	$BLACK, n_color(%ebx)

	addl 	$4, %esp

	# Epilogue
	movl 	%ebp, %esp
	popl 	%esp
	ret

################### Interface Function ###############
##
# @brief Creates a new AVL Tree.
# @details This function allocates memory for a new AVL Tree structure and initializes its fields.
# @return Returns a pointer to the newly created AVL Tree.
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

	pushl	$SIZE_AVL
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
# @brief Inserts a new node containing specified data into the AVL Tree.
# @details This function inserts a new node with the provided data into the AVL Tree.
#          It uses a comparison function to determine the insertion point.
# @param tree Pointer to the AVL Tree.
# @param data The data to be inserted into the tree.
# @param pcompareproc Pointer to the comparison function used to determine the insertion point.
# @return Returns 1 if insertion is successful, 0 otherwise.
##
# extern int avl_insert(void* tree, void* data, COMPAREPROC pcompareproc)
	.globl	avl_insert
	.type	avl_insert, @function
avl_insert:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	movl	8(%ebp), %ebx
	cmpl	$0, t_root(%ebx)
	je		.insert_root
	jmp		.insert_node

	.insert_root:
		pushl	12(%ebp)
		call	create_node
		addl	$4, %esp

		movl	8(%ebp), %ebx
		movl	%eax, t_root(%ebx)
		jmp		.increase_elmcount

	.insert_node:
		subl	$8, %esp
		movl	$0, -4(%ebp)
		movl	$0, -8(%ebp)

		movl	8(%ebp), %ebx
		movl	t_root(%ebx), %eax
		movl	%eax, -4(%ebp)

		.loop_in:
			movl	-4(%ebp), %ebx
			pushl	n_data(%ebx)
			pushl	12(%ebp)
			movl	16(%ebp), %ecx
			call	*%ecx
			addl	$8, %esp

			movl	%eax, -8(%ebp)

			cmpl	$CMP_SAME, %eax
			je	.ret_error_dap
			movl	-8(%ebp), %eax
			cmpl	$CMP_LESS, %eax
			je	.check_left_bi
			jmp	.check_right_bi

			.ret_error_dap:
				pushl	$.msg_p_dap
				call	printf
				addl	$4, %esp
				addl	$8, %esp
				jmp	.loop_end_in

			.check_left_bi:
				movl	-4(%ebp), %ebx
				cmpl	$0, n_left(%ebx)
				jne	.go_left_bi
				jmp	.insert_left_bi

				.go_left_bi:
					movl	-4(%ebp), %ebx
					movl	n_left(%ebx), %eax
					movl	%eax, -4(%ebp)
					jmp	.loop_in

				.insert_left_bi:
					pushl	12(%ebp)
					call	create_node
					addl	$4, %esp
					
					movl	-4(%ebp), %ebx
					movl	%eax, n_left(%ebx)

					movl	-4(%ebp), %eax
					movl	n_left(%eax), %ebx
					movl	%eax, n_parent(%ebx)
					addl	$8, %esp

					movl 	-4(%ebp), %ebx
					pushl	n_left(%ebx)
					pushl 	8(%ebp)
					call 	AVL
					addl 	$8, %esp
					jmp		.increase_elmcount

			.check_right_bi:
				movl	-4(%ebp), %ebx
				cmpl	$0, n_right(%ebx)
				jne	.move_right_bi
				jmp	.insert_right_bi

				.move_right_bi:
					movl	-4(%ebp), %ebx
					movl	n_right(%ebx), %eax
					movl	%eax, -4(%ebp)
					jmp	.loop_in

				.insert_right_bi:
					pushl	12(%ebp)
					call	create_node
					addl	$4, %esp

					movl	-4(%ebp), %ebx
					movl	%eax, n_right(%ebx)

					movl	-4(%ebp), %eax
					movl	n_right(%eax), %ebx
					movl	%eax, n_parent(%ebx)
					addl	$8, %esp

					movl 	-4(%ebp), %ebx
					pushl	n_right(%ebx)
					pushl 	8(%ebp)
					call 	AVL
					addl 	$8, %esp
					jmp		.increase_elmcount
	
		.loop_end_in:
		movl	$1, %eax
		jmp	.epilogue_bi

		.increase_elmcount:

		movl	8(%ebp), %ebx
		incl	t_size(%ebx)

	# Epilogue
	.epilogue_bi:
	movl	%ebp, %esp
	popl	%ebp
	ret
	
##
# @brief Removes a node containing specified data from the AVL Tree.
# @details This function removes a node containing the specified data from the AVL Tree.
#          It uses a comparison function to locate the node to be removed.
# @param tree Pointer to the AVL Tree.
# @param data The data to be removed from the tree.
# @param pcompareproc Pointer to the comparison function used to locate the node to be removed.
# @return Returns the data removed from the tree, or NULL if data is not found.
##
# extern void* avl_remove(void* tree, void* data, COMPAREPROC pcompareproc)
	.globl	avl_remove
	.type	avl_remove, @function
avl_remove:

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
		jne		.replace_succ
		jmp		.check_left

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
		cmpl	$0, n_left(%ebx)
		je		.remove_node

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

##
# @brief Performs an inorder traversal of the AVL Tree.
# @details This function initiates an inorder traversal of the AVL Tree rooted at the given node,
#          applying the provided printing function to each node's data.
# @param tree Pointer to the AVL Tree.
# @param printdata Pointer to the function used to print the data of each node.
# @return None
##
#  extern void avl_inorder(void* tree, PRINTDATAPROC printdata)
	.globl	avl_inorder
	.type	avl_inorder, @function
avl_inorder:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	movl	8(%ebp), %ebx
	pushl	12(%ebp)
	pushl	t_root(%ebx)
	call	inorder
	addl	$4, %esp

	# Epilogue
	movl	%ebp, %esp
	popl	%ebp
	ret


