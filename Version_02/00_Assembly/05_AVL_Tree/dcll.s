 #
 # S.G.M.P
 # @file: dcll.s
 # @brief: Implementation of Doubly Circular Linked List in x86 Linux Assembly
 # @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 # @Copyright ©2020-2023 MarshallingVoid
 # @date: 12 April 2024 (Friday) 07:43:37 PM
 #


# Constant Definitions
.equ	SUCCESS, 0
.equ	FAILURE, 1

.equ	LCFE_LISTNOTFOUND, 0x01
.equ	LCFE_LISTEMPTY, 0x02

.equ	E_NONE, 	0x00
.equ	E_OUTOFMEMORY,	0x01
.equ	E_LISTEMPTY,	0x02
.equ	E_LISTNOTFOUND,	0x04
.equ	E_INDEXOUTOFBOUND, 0x08
.equ	E_DATANOTFOUND,	0x10

# Struct Node
# {
#	void* data
#	Node* next
#	Node* prev
# }
# SIZE_NODE = 12
.equ	n_data, 0
.equ	n_next, 4
.equ	n_prev, 8
.equ	SIZE_NODE, 12

# struct LIST
# {
#	Node* head
#	size_t	size
# }
# SIZE_LIST = 8
.equ	l_head, 0
.equ	l_size, 4
.equ	SIZE_LIST, 8

# Section RODATA
.section .rodata

	.msg_p_oom:
		.string	"ERROR: Out Of Memory\n"

	.msg_p_lnf:
		.string	"ERROR: List Not Found\n"

	.msg_p_le:
		.string	"ERROR: List is Empty\n"

	.msg_p_dnf:
		.string	"ERROR: Data not found\n"

	.msg_p_ioob:
		.string "ERROR: Index out of bound\n"

	.msg_p_ne:
		.string	"ERROR: No Error Found\n"

# Section Data
.section .data
	.type	d_ecode, @object
	.size	d_ecode, 4
	.align	4
d_ecode:
	.zero	4

# Section BSS
.section .bss

# Section Text
.section .text

########### Helper Function ###########

#
#	Function: Function to allocate memory and check for Out Of Memory 
#
#	identifier:	xmalloc
#	params: nr_bytes
#	returns: address to allocated memory
#
# static void* xmalloc(nr_bytes)
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

	cmpl	$0, %eax
	je	.xm_oom_handler
	jmp	.xm_return_address

	.xm_oom_handler:
		movl	$E_OUTOFMEMORY, d_ecode
		movl	$0, %eax
		jmp	.xm_epilogue

	.xm_return_address:
		movl	-4(%ebp), %eax

	# Epilogue
	.xm_epilogue:
	addl	$4, %esp

	movl	%ebp, %esp
	popl	%ebp
	ret

#
#	Function: This function adds the mid node between first and last node
#
#	identifier:	generic_insert
#	params: 1) list
#			2) first
# 			3) mid
# 			4) last
#	returns: Insert Status
#
# static ret_t	generic_insert(list, first, mid, last)
	.type	generic_insert, @function
generic_insert:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	
	# first->next = mid
	movl	16(%ebp), %eax
	movl	12(%ebp), %ebx
	movl	%eax, n_next(%ebx)
	
	# mid->next = last
	movl	20(%ebp), %eax
	movl	16(%ebp), %ebx
	movl	%eax, n_next(%ebx)

	# mid->prev = first
	movl	12(%ebp), %eax
	movl	16(%ebp), %ebx
	movl	%eax, n_prev(%ebx)
	
	# last->prev = mid
	movl	16(%ebp), %eax
	movl	20(%ebp), %ebx
	movl	%eax, n_prev(%ebx)

	movl	8(%ebp), %ebx
	movl	l_size(%ebx), %eax
	incl	%eax
	movl	%eax, l_size(%ebx)

	movl	$SUCCESS, %eax

	# Epilogue
	movl	%ebp, %esp
	popl	%ebp
	ret

#
#	Function: This function remove the node from the list 
#
#	identifier:	generic_remove
#	params: 1) list
# 			2) node
#	returns: Data of the deleted node
#
# static ret_t	generic_remove(list, node)
	.type	generic_remove, @function
generic_remove:
	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	subl	$12, %esp
	movl	$0, -4(%ebp)
	movl	$0, -8(%ebp)
	movl	$0, -12(%ebp)

	# first = node->prev
	# last = node->next
	movl	12(%ebp), %ebx
	movl	n_prev(%ebx), %eax
	movl	%eax, -4(%ebp)
	movl	n_next(%ebx), %eax
	movl	%eax, -8(%ebp)

	# first->next = last
	movl	-4(%ebp), %ebx
	movl	-8(%ebp), %eax
	movl	%eax, n_next(%ebx)

	# last->prev = first
	movl	-4(%ebp), %eax
	movl	-8(%ebp), %ebx
	movl	%eax, n_prev(%ebx)

	# to_return_data = node->data
	movl	12(%ebp), %ebx
	movl	n_data(%ebx), %eax
	movl	%eax, -12(%ebp)

	# free(node)
	movl	12(%ebp), %eax
	pushl	%eax
	call	free
	addl	$4, %esp

	# list->size--
	movl	8(%ebp), %ebx
	decl	l_size(%ebx)

	movl	-12(%ebp), %eax

	# Epilogue
	addl	$12, %esp

	movl	%ebp, %esp
	popl	%ebp
	ret

#
#	Function: Locating node containing the required data by comparing each data from the node of list 
#
#	identifier:	locate_node
#	params: 1) list
#			2) e_data
# 			3) compare_proc
#	returns: data of the found node OR NULL if data not found
#
# static node*	locate_node(list, e_data, compare_proc)
	.type	locate_node, @function
locate_node:
	
	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	subl	$4, %esp
	movl	$0, -4(%ebp)

	# runner = list->head->next
	movl	8(%ebp), %ebx
	movl	l_head(%ebx), %eax
	movl	%eax, %ebx
	movl	n_next(%ebx), %eax
	movl	%eax, -4(%ebp)


	# while(1)
	.loop_ln:
		
		# if(SUCCESS == pcompare(e_data, runner->data)
		movl	16(%ebp), %ecx
		movl	12(%ebp), %eax
		movl	-4(%ebp), %ebx
		movl	n_data(%ebx), %ebx
		pushl	%ebx
		pushl	%eax
		call	*%ecx
		addl	$8, %esp
		cmpl	$SUCCESS, %eax
		jne	.check_list_end_ln

			movl	-4(%ebp), %eax
			jmp	.loop_end_ln

		.check_list_end_ln:
		movl	-4(%ebp), %eax
		movl	8(%ebp), %ebx
		movl	l_head(%ebx), %ebx
		cmpl	%eax, %ebx
		jne	.move_to_next_ln

			movl	$0, %eax
			jmp	.loop_end_ln

		.move_to_next_ln:
			movl	-4(%ebp), %ebx
			movl	n_next(%ebx), %ebx
			movl	%ebx, -4(%ebp)
			jmp	.loop_ln
	.loop_end_ln:

	# Epilogue
	addl	$4, %esp
	
	movl	%ebp, %esp
	popl	%ebp
	ret

#
#	Function: that create a new node and assigns a data to the node
#
#	identifier:	create_node
#	params: data
#	returns: address of the newly created node
#
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
	
	movl	-4(%ebp), %ebx
	movl	-4(%ebp), %eax
	movl	%eax, n_next(%ebx)
	movl	%eax, n_prev(%ebx)

	movl	-4(%ebp), %eax
	addl	$4, %esp

	# Epilogue
	movl	%ebp, %esp
	popl	%ebp
	ret

#
#	Function: that checks list for error
#
#	identifier:	is_error
#	params: 1) list
#			2) Error Code
#	returns: SUCCESS if error present and FAILURE is error not found
#
# static ret_t is_error(list, ecode)
	.type	is_error, @function
is_error:
	
	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	movl	12(%ebp), %eax
	andl	$LCFE_LISTNOTFOUND, %eax
	cmpl	$0, %eax
	je	.check_list_empty

		movl	8(%ebp), %ebx
		cmpl	$0, %ebx
		jne	.check_list_empty

			movl	$E_LISTNOTFOUND, %eax
			movl	%eax, d_ecode
			movl	$SUCCESS, %eax
			jmp	.epilogue_ie

	
	.check_list_empty:
	movl	12(%ebp), %eax
	andl	$LCFE_LISTEMPTY, %eax
	cmpl	$0, %eax
	je	.return_failure_ie

		movl	8(%ebp), %ebx
		movl	l_head(%ebx), %ebx
		movl	n_next(%ebx), %eax
		cmpl	%eax, %ebx
		jne	.return_failure_ie

			movl	$E_LISTEMPTY, %eax
			movl	%eax, d_ecode
			movl	$SUCCESS, %eax
			jmp	.epilogue_ie

	
	.return_failure_ie:
		movl	$FAILURE, %eax

	# Epilogue
	.epilogue_ie:
		movl	%ebp, %esp
		popl	%ebp
		ret


################# Interface Functions #################

#
#	Function: that creates new list
#
#	identifier:	create_list
#	params: NONE
#	returns: Pointer to the newly created list object
#
# extern list* create_list()
	.globl	create_list
	.type	create_list, @function
create_list:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code

	subl	$4, %esp
	movl	$0, -4(%ebp)

	pushl	$SIZE_LIST
	call	xmalloc
	addl	$4, %esp
	movl	%eax, -4(%ebp)

	pushl	$-1
	call	create_node
	addl	$4, %esp

	movl	-4(%ebp), %ebx
	movl	%eax, l_head(%ebx)
	movl	$0, l_size(%ebx)

	movl	-4(%ebp), %eax

	addl	$4, %esp

	# Epilogue
	movl	%ebp, %esp
	popl	%ebp
	ret

#
#	Function: that returns the size of the list
#
#	identifier:	list_size
#	params: list
#	returns: No of elements of list
#
# extern long long list_size(list)
	.globl	list_size
	.type	list_size, @function
list_size:
	
	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	movl	$LCFE_LISTNOTFOUND, %eax
	
	pushl	%eax
	pushl	8(%ebp)
	call	is_error
	addl	$8, %esp
	
	cmpl	$SUCCESS, %eax
	jne	.return_size_ls

		movl	$0, %eax
		jmp	.epilogue_ls

	.return_size_ls:

	movl	8(%ebp), %ebx
	movl	l_size(%ebx), %eax

	# Epilogue
	.epilogue_ls:
	movl	%ebp, %esp
	popl	%ebp
	ret

#
#	Function: Gets the data of node present an index
#
#	identifier:	list_data_at
#	params: 1) list
#			2) index
#	returns: data of the node present at index OR NULL if node not found 
#
# extern void* list_data_at(list, index)
	.globl	list_data_at
	.type	list_data_at, @function
list_data_at:
	
	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	movl	$LCFE_LISTNOTFOUND, %eax
	orl	$LCFE_LISTEMPTY, %eax

	pushl	%eax
	pushl	8(%ebp)
	call	is_error
	addl	$8, %esp

	cmpl	$SUCCESS, %eax
	jne	.check_index_lda

		movl	$0, %eax
		jmp	.epilogue_lda
	
	.check_index_lda:
	movl	12(%ebp), %eax

	cmpl	$0, %eax
	jge	.check_index_less

		movl	$0, %eax
		jmp	.epilogue_lda

	.check_index_less:
	movl	12(%ebp), %eax
	movl	8(%ebp), %ebx
	movl	l_size(%ebx), %ebx
	cmpl	%ebx, %eax
	jl	.return_data_lda

		movl	$0, %eax
		jmp	.epilogue_lda

	.return_data_lda:

	subl	$8, %esp
	movl	$0, -4(%ebp)
	movl	$0, -8(%ebp)

	movl	8(%ebp), %ebx
	movl	l_head(%ebx), %ebx
	movl	n_next(%ebx), %ebx
	movl	%ebx, -4(%ebp)

	.loop_lda:
	movl	-8(%ebp), %eax
	movl	12(%ebp), %ebx
	cmpl	%ebx, %eax
	je	.loop_end_lda

		movl	-4(%ebp), %ebx
		movl	n_next(%ebx), %ebx
		movl	%ebx, -4(%ebp)

		movl	-8(%ebp), %eax
		incl	%eax
		movl	%eax, -8(%ebp)
		jmp	.loop_lda

	.loop_end_lda:

	movl	-4(%ebp), %ebx
	movl	n_data(%ebx), %eax

	addl	$8, %esp
	
	# Epilogue
	.epilogue_lda:
	movl	%ebp, %esp
	popl	%ebp
	ret

#
#	Function: to insert data at start of list
#
#	identifier:	list_insert_front
#	params: 1) list
#			2) data
#	returns: Insertion status
#
# extern ret_t list_insert_front(list, data)
	.globl	list_insert_front
	.type	list_insert_front, @function
list_insert_front:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	
	movl	$E_LISTNOTFOUND, %eax

	pushl	%eax
	pushl	8(%ebp)
	call	is_error
	addl	$8, %esp

	cmpl	$SUCCESS, %eax
	jne	.insert_front_lif

		movl	$0, %eax
		jmp	.epilogue_lif

	.insert_front_lif:
	
	movl	12(%ebp), %ebx
	pushl	%ebx
	call	create_node
	addl	$4, %esp

	movl	8(%ebp), %ebx
	movl	l_head(%ebx), %ecx

	pushl	n_next(%ecx)
	pushl	%eax
	pushl	l_head(%ebx)
	pushl	8(%ebp)
	call	generic_insert
	addl	$12, %esp
	
	# Epilogue
	.epilogue_lif:
	movl	%ebp, %esp
	popl	%ebp
	ret

#
#	Function: to insert data at end of list
#
#	identifier:	list_insert_back
#	params: 1) list
#			2) data
#	returns: Insertion status
#

# extern ret_t list_insert_back(list, data)
	.globl	list_insert_back
	.type	list_insert_back, @function
list_insert_back:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	movl	$E_LISTNOTFOUND, %eax

	pushl	%eax
	pushl	8(%ebp)
	call	is_error
	addl	$8, %esp

	cmpl	$SUCCESS, %eax
	jne	.insert_back_lib

		movl	$0, %eax
		jmp	.epilogue_lib

	.insert_back_lib:
	movl	12(%ebp), %ebx
	pushl	%ebx
	call	create_node
	addl	$4, %esp

	movl	8(%ebp), %ebx
	movl	l_head(%ebx), %ecx

	pushl	l_head(%ebx)
	pushl	%eax
	pushl	n_prev(%ecx)
	pushl	8(%ebp)
	call	generic_insert
	addl	$12, %esp

	# Epilogue
	.epilogue_lib:
	movl	%ebp, %esp
	popl	%ebp
	ret

#
#	Function: to insert data just after e_data in list
#
#	identifier:	list_insert_after
#	params: 1) list
#			2) data
#			3) e_data
# 			4) compare function callback
#	returns: Insertion status
#
# extern ret_t list_insert_after(list, data, e_data, compare)
	.globl	list_insert_after
	.type	list_insert_after, @function
list_insert_after:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	subl	$8, %esp
	movl	$0, -4(%ebp)
	movl	$0, -8(%ebp)

	pushl	20(%ebp)
	pushl	16(%ebp)
	pushl	8(%ebp)
	call	locate_node
	addl	$12, %esp

	movl	%eax, -4(%ebp)

	movl	-4(%ebp), %eax
	cmpl	$0, %eax
	jne	.insert_data_lia

		movl	$FAILURE, %eax
		jmp	.epilogue_lia

	.insert_data_lia:

	pushl	12(%ebp)
	call	create_node
	addl	$4, %esp

	movl	%eax, -8(%ebp)

	movl	-4(%ebp), %ebx

	pushl	n_next(%ebx)
	pushl	-8(%ebp)
	pushl	%ebx
	pushl	8(%ebp)
	call	generic_insert
	addl	$12, %esp

	movl	$SUCCESS, %eax

	# Epilogue
	.epilogue_lia:
	addl	$8, %esp

	movl	%ebp, %esp
	popl	%ebp
	ret

#
#	Function: to insert data just before e_data in list
#
#	identifier:	list_insert_before
#	params: 1) list
#			2) data
#			3) e_data
# 			4) compare function callback
#	returns: Insertion status
#
# extern ret_t list_insert_before(list, data, e_data, compare)
	.globl	list_insert_before
	.type	list_insert_before, @function
list_insert_before:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	subl	$8, %esp
	movl	$0, -4(%ebp)
	movl	$0, -8(%ebp)

	pushl	20(%ebp)
	pushl	16(%ebp)
	pushl	8(%ebp)
	call	locate_node
	addl	$12, %esp

	movl	%eax, -4(%ebp)

	movl	-4(%ebp), %eax
	cmpl	$0, %eax
	jne	.insert_data_lib

		movl	$FAILURE, %eax
		jmp	.epilogue_libe

	.insert_data_lib:

	pushl	12(%ebp)
	call	create_node
	addl	$4, %esp

	movl	%eax, -8(%ebp)

	movl	-4(%ebp), %ebx

	pushl	%ebx
	pushl	-8(%ebp)
	pushl	n_prev(%ebx)
	pushl	8(%ebp)
	call	generic_insert
	addl	$12, %esp

	movl	$SUCCESS, %eax

	# Epilogue
	.epilogue_libe:
	addl	$8, %esp

	movl	%ebp, %esp
	popl	%ebp
	ret

#
#	Function: to insert data at specific index
#
#	identifier:	list_insert_at
#	params: 1) list
#			2) data
#			3) index
#	returns: Insertion status
#
# extern void* list_insert_at(list, data, index)
	.globl	list_insert_at
	.type	list_insert_at, @function
list_insert_at:
	
	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	movl	$LCFE_LISTNOTFOUND, %eax
	orl	$LCFE_LISTEMPTY, %eax

	pushl	%eax
	pushl	8(%ebp)
	call	is_error
	addl	$8, %esp

	cmpl	$SUCCESS, %eax
	jne	.check_index_lia

		movl	$0, %eax
		jmp	.epilogue_liat
	
	.check_index_lia:
	movl	16(%ebp), %eax

	cmpl	$0, %eax
	jge	.check_index_less_liat

		movl	$0, %eax
		jmp	.epilogue_lia

	.check_index_less_liat:
	movl	16(%ebp), %eax
	movl	8(%ebp), %ebx
	movl	l_size(%ebx), %ebx
	cmpl	%ebx, %eax
	jl	.return_data_lia

		movl	$0, %eax
		jmp	.epilogue_liat

	.return_data_lia:

	subl	$8, %esp
	movl	$0, -4(%ebp)
	movl	$0, -8(%ebp)

	movl	8(%ebp), %ebx
	movl	l_head(%ebx), %ebx
	movl	%ebx, -4(%ebp)

	.loop_lia:
	movl	-8(%ebp), %eax
	movl	16(%ebp), %ebx
	cmpl	%ebx, %eax
	je	.loop_end_lia

		movl	-4(%ebp), %ebx
		movl	n_next(%ebx), %ebx
		movl	%ebx, -4(%ebp)

		movl	-8(%ebp), %eax
		incl	%eax
		movl	%eax, -8(%ebp)
		jmp	.loop_lda

	.loop_end_lia:

	movl	-4(%ebp), %ebx

	pushl	12(%ebp)
	call	create_node
	addl	$4, %esp

	movl	-4(%ebp), %ebx

	pushl	n_next(%ebx)
	pushl	%eax
	pushl	%ebx
	pushl	8(%ebp)
	call	generic_insert
	addl	$16, %esp

	addl	$8, %esp
	
	# Epilogue
	.epilogue_liat:
	movl	%ebp, %esp
	popl	%ebp
	ret

#
#	Function: to remove data from start of list
#
#	identifier:	list_remove_front
#	params: list
#	returns: Data of remove node
#
# extern void* list_remove_front(list)
	.globl	list_remove_front
	.type	list_remove_front, @function
list_remove_front:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	movl	$LCFE_LISTNOTFOUND, %eax
	orl	$LCFE_LISTEMPTY, %eax

	pushl	%eax
	pushl	8(%ebp)
	call	is_error
	addl	$8, %esp

	cmpl	$SUCCESS, %eax
	jne	.remove_front

		movl	$0, %eax
		jmp	.epilogue_lrf

	.remove_front:
	movl	8(%ebp), %ebx

	movl	l_head(%ebx), %ebx
	pushl	n_next(%ebx)
	pushl	8(%ebp)
	call	generic_remove
	addl	$8, %esp

	# Epilogue
	.epilogue_lrf:
	movl	%ebp, %esp
	popl	%ebp
	ret

#
#	Function: to remove data from end of list
#
#	identifier:	list_remove_back
#	params: list
#	returns: Data of remove node
#
# extern void* list_remove_back(list)
	.globl	list_remove_back
	.type	list_remove_back, @function
list_remove_back:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	movl	$LCFE_LISTNOTFOUND, %eax
	orl	$LCFE_LISTEMPTY, %eax

	pushl	%eax
	pushl	8(%ebp)
	call	is_error
	addl	$8, %esp

	cmpl	$SUCCESS, %eax
	jne	.remove_back

		movl	$0, %eax
		jmp	.epilogue_lrb

	.remove_back:
	movl	8(%ebp), %ebx

	movl	l_head(%ebx), %ebx
	pushl	n_prev(%ebx)
	pushl	8(%ebp)
	call	generic_remove
	addl	$8, %esp

	# Epilogue
	.epilogue_lrb:
	movl	%ebp, %esp
	popl	%ebp
	ret

#
#	Function: to remove data just after the e_data
#
#	identifier:	list_remove_after
#	params: 1) list
#			2) e_data
#			3) compare
#	returns: Data of remove node
#
# extern void* list_remove_after(list, e_data, compare)
	.globl	list_remove_after
	.type	list_remove_after, @function
list_remove_after:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	movl	$LCFE_LISTNOTFOUND, %eax
	orl	$LCFE_LISTEMPTY, %eax

	pushl	%eax
	pushl	8(%ebp)
	call	is_error
	addl	$8, %esp

	cmpl	$SUCCESS, %eax
	jne	.remove_after

		movl	$0, %eax
		jmp	.epilogue_lraf

	.remove_after:
	
	pushl	16(%ebp)
	pushl	12(%ebp)
	pushl	8(%ebp)
	call	locate_node
	addl	$12, %esp
	
	cmpl	$0, %eax
	jne	.call_gr_lra

		movl	$0, %eax
		jmp	.epilogue_lraf

	.call_gr_lra:
	movl	%eax, %ebx

	pushl	n_next(%ebx)
	pushl	8(%ebp)
	call	generic_remove
	addl	$8, %esp

	# Epilogue
	.epilogue_lraf:
	movl	%ebp, %esp
	popl	%ebp
	ret

#
#	Function: to remove data just before the e_data
#
#	identifier:	list_remove_before
#	params: 1) list
#			2) e_data
#			3) compare
#	returns: Data of remove node
#
# extern void* list_remove_before(list, e_data, compare)
	.globl	list_remove_before
	.type	list_remove_before, @function
list_remove_before:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	movl	$LCFE_LISTNOTFOUND, %eax
	orl	$LCFE_LISTEMPTY, %eax

	pushl	%eax
	pushl	8(%ebp)
	call	is_error
	addl	$8, %esp

	cmpl	$SUCCESS, %eax
	jne	.remove_before

		movl	$0, %eax
		jmp	.epilogue_lrbe

	.remove_before:
	
	pushl	16(%ebp)
	pushl	12(%ebp)
	pushl	8(%ebp)
	call	locate_node
	addl	$12, %esp
	
	cmpl	$0, %eax
	jne	.call_gr_lrbe

		movl	$0, %eax
		jmp	.epilogue_lrbe

	.call_gr_lrbe:
	movl	%eax, %ebx

	pushl	n_prev(%ebx)
	pushl	8(%ebp)
	call	generic_remove
	addl	$8, %esp

	# Epilogue
	.epilogue_lrbe:
	movl	%ebp, %esp
	popl	%ebp
	ret

#
#	Function: to remove data at a specific index
#
#	identifier:	list_remove_at
#	params: 1) list
#			2) index
#	returns: Data of remove node
#
# extern void* list_remove_at(list, index)
	.globl	list_remove_at
	.type	list_remove_at, @function
list_remove_at:
	
	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	movl	$LCFE_LISTNOTFOUND, %eax
	orl	$LCFE_LISTEMPTY, %eax

	pushl	%eax
	pushl	8(%ebp)
	call	is_error
	addl	$8, %esp

	cmpl	$SUCCESS, %eax
	jne	.check_index_lrat

		movl	$0, %eax
		jmp	.epilogue_lrat
	
	.check_index_lrat:
	movl	12(%ebp), %eax

	cmpl	$0, %eax
	jge	.check_index_less_lrat

		movl	$0, %eax
		jmp	.epilogue_lrat

	.check_index_less_lrat:
	movl	12(%ebp), %eax
	movl	8(%ebp), %ebx
	movl	l_size(%ebx), %ebx
	cmpl	%ebx, %eax
	jl	.return_data_lra

		movl	$0, %eax
		jmp	.epilogue_lrat

	.return_data_lra:

	subl	$8, %esp
	movl	$0, -4(%ebp)
	movl	$0, -8(%ebp)

	movl	8(%ebp), %ebx
	movl	l_head(%ebx), %ebx
	movl	n_next(%ebx), %ebx
	movl	%ebx, -4(%ebp)

	.loop_lra:
	movl	-8(%ebp), %eax
	movl	12(%ebp), %ebx
	cmpl	%ebx, %eax
	je	.loop_end_lra

		movl	-4(%ebp), %ebx
		movl	n_next(%ebx), %ebx
		movl	%ebx, -4(%ebp)

		movl	-8(%ebp), %eax
		incl	%eax
		movl	%eax, -8(%ebp)
		jmp	.loop_lra

	.loop_end_lra:

	movl	-4(%ebp), %ebx

	pushl	%ebx
	push	8(%ebp)
	call	generic_remove
	addl	$8, %esp

	addl	$8, %esp
	
	# Epilogue
	.epilogue_lrat:
	movl	%ebp, %esp
	popl	%ebp
	ret

#
#	Function: to print the description of error
#
#	identifier:	list_error_description
#	params: NONE
#	returns: NONE
#
# extern void list_error_description()
	.globl	list_error_description
	.type	list_error_description, @function
list_error_description:

	# Prologue
	pushl	%ebp
	movl 	%esp, %ebp

	# Main Code
	
	movl	d_ecode, %eax
	cmpl	$E_OUTOFMEMORY, %eax
	je	.handle_oom
	movl	d_ecode, %eax
	cmpl	$E_LISTNOTFOUND, %eax
	je	.handle_lnf
	movl	d_ecode, %eax
	cmpl	$E_LISTEMPTY, %eax
	je	.handle_le
	movl	d_ecode, %eax
	cmpl	$E_DATANOTFOUND, %eax
	je	.handle_dnf
	movl	d_ecode, %eax
	cmpl	$E_INDEXOUTOFBOUND, %eax
	je	.handle_ioob
	jmp	.handle_noerror

	.handle_oom:
		pushl	$.msg_p_oom
		call	printf
		addl	$4, %esp
		jmp	.epilogue_led

	.handle_lnf:
		pushl	$.msg_p_lnf
		call	printf
		addl	$4, %esp
		jmp	.epilogue_led

	.handle_le:
		pushl	$.msg_p_le
		call	printf
		addl	$4, %esp
		jmp	.epilogue_led

	.handle_dnf:
		pushl	$.msg_p_dnf
		call	printf
		addl	$4, %esp
		jmp	.epilogue_led

	.handle_ioob:
		pushl	$.msg_p_ioob
		call	printf
		addl	$4, %esp
		jmp	.epilogue_led

	.handle_noerror:
		pushl	$.msg_p_ne
		call	printf
		addl	$4, %esp

	# Epilogue
	.epilogue_led:
	movl	$E_NONE, d_ecode
	movl	%ebp, %esp
	popl	%ebp
	ret

#
#	Function: to destroy the list
#
#	identifier:	list_destroy
#	params: 1) pointer to list
#			2) deletedataproc callback function
#	returns: Status
#
# extern ret_t list_destroy(plist, deletedataproc)
	.globl	list_destroy
	.type	list_destroy, @function
list_destroy:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	cmpl	$0, 8(%ebp)
	jne	.get_list_ld

		movl	$0, %eax
		jmp	.epilogue_ld

	.get_list_ld:
	subl	$4, %esp
	movl	8(%ebp), %ebx
	movl	(%ebx), %eax
	movl	%eax, -4(%ebp)

	movl	$LCFE_LISTNOTFOUND, %eax

	pushl	%eax
	pushl	-4(%ebp)
	call	is_error
	addl	$8, %esp

	cmpl	$0, %eax
	jne	.destroy_ld

		addl	$4, %esp
		movl	$0, %eax
		jmp	.epilogue_ld

	.destroy_ld:
	
	subl	$4, %esp
	movl	-4(%ebp), %ebx
	movl	l_head(%ebx), %eax
	movl	%eax, -8(%ebp)

	movl	-8(%ebp), %ebx
	movl	n_prev(%ebx), %ebx
	movl	$0, n_next(%ebx)

	movl	-8(%ebp), %ebx
	movl	n_next(%ebx), %eax
	movl	%eax, -8(%ebp)

	.loop_ld:
	movl	-8(%ebp), %ebx
	movl	n_next(%ebx), %eax
	cmpl	$0, %eax
	je	.loop_end_ld

		movl	-8(%ebp), %ebx
		pushl	n_prev(%ebx)
		call	free
		addl	$4, %esp

		movl	-8(%ebp), %ebx
		
		movl	12(%ebp), %ecx

		pushl	n_data(%ebx)
		call	*%ecx
		addl	$4, %esp

		movl	-8(%ebp), %ebx
		movl	n_next(%ebx), %eax
		movl	%eax, -8(%ebp)
		jmp	.loop_ld

	.loop_end_ld:

	movl	-8(%ebp), %ebx
	pushl	n_data(%ebx)
	movl	12(%ebp), %ecx
	call	*%ecx
	addl	$4, %esp

	pushl	-8(%ebp)
	call	free
	addl	$4, %esp

	pushl	-4(%ebp)
	call	free
	addl	$4, %esp

	movl	8(%ebp), %ebx
	movl	$0, (%ebx)

	addl	$8, %esp

	# Epilogue
	.epilogue_ld:
	movl	%ebp, %esp
	popl	%ebp
	ret

