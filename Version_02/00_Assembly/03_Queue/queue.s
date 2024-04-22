 #
 # S.G.M.P
 # @file: Queue.s
 # @brief: x86 Linux Assembly implementation of DCLL based Queue
 # @author: Mayur S. Tadekar(mrtadekar@gmail.com)
 # @Copyright ©2020-2023 MarshallingVoid
 # @date: 15 April 2024 (Monday) 03:27:56 PM
 #

# Section ROData
.section .rodata
	
	.msg_p_start:
		.string	"{START}-"

	.msg_p_end:
		.string "{END}\n\n"

# Section DATA

# Section BSS

# Section TEXT
.section .text

############# Queue Interface Function ##############

#
# Function: create_queue
# Description: Creates a new queue by initializing a linked list.
# Params: None
# Returns: Pointer to the newly created queue
# Notes: This function internally calls create_list to initialize a new linked list structure.
#         It allocates memory for the queue structure, initializes its properties, and returns a pointer to it.
#         The caller is responsible for managing the memory of the returned queue.
#
# void* create_queue()
	.globl	create_queue
	.type	create_queue, @function
create_queue:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	call	create_list

	# Epilogue
	movl	%ebp, %esp
	popl	%ebp
	ret

#
# Function: queue_enqueue
# Description: Adds a new node with the provided data to the front of the queue.
# Params: 1) queue - pointer to the queue
#         2) data - data to be enqueued
# Returns: None
# Notes: This function internally calls list_insert_front to add a new node at the front of the queue.
#         It ensures that the provided data is added to the queue by inserting it as the first node.
#         The caller is responsible for managing the memory of the data being enqueued.
#
# int queue_enqueue(queue, data)
	.globl	queue_enqueue
	.type	queue_enqueue, @function
queue_enqueue:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	pushl	12(%ebp)
	pushl	8(%ebp)
	call	list_insert_front
	addl	$8, %esp

	# Epilogue
	movl	%ebp, %esp
	popl	%ebp
	ret

#
# Function: queue_dequeue
# Description: Removes and returns the data from the back of the queue.
# Params: queue - pointer to the queue
# Returns: Pointer to the dequeued data
# Notes: This function internally calls list_remove_back to remove and return the last node's data from the queue.
#         It ensures that the data is dequeued from the queue by removing and returning the data from the last node.
#         The caller is responsible for managing the memory of the dequeued data.
#
# void* queue_dequeue(queue)
	.globl	queue_dequeue
	.type	queue_dequeue, @function
queue_dequeue:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	pushl	8(%ebp)
	call	list_remove_back
	addl	$4, %esp

	# Epilogue
	movl	%ebp, %esp
	popl	%ebp
	ret

#
# Function: queue_print
# Description: Prints the data stored in each node of the queue by applying the provided printing function to each node's data.
# Params: 1) queue - pointer to the queue
#         2) print_data - function pointer for printing each data element
# Returns: None
# Notes: This function iterates through each node of the queue, retrieves its data, and applies the provided printing function to print the data.
#         It ensures that the data in each node of the queue is printed using the specified printing function.
#         The caller must provide a valid printing function to correctly print the data stored in each node.
#
# void	queue_print(queue, print_data)
	.globl	queue_print
	.type	queue_print, @function
queue_print:
	
	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code
	subl	$8, %esp
	
	movl	$0, -8(%ebp)

	pushl	8(%ebp)
	call	list_size
	addl	$4, %esp

	movl	%eax, -4(%ebp)

	.loop_qp:
	movl	-4(%ebp), %eax
	movl	-8(%ebp), %ebx
	cmpl	%eax, %ebx
	je	.loop_end_qp

		pushl	-8(%ebp)
		pushl	8(%ebp)
		call	list_data_at
		addl	$8, %esp

		movl	12(%ebp), %ecx
		
		pushl	%eax
		call	*%ecx
		addl	$4, %esp

		incl	-8(%ebp)
		
		jmp	.loop_qp

	.loop_end_qp:

	addl	$8, %esp

	# Epilogue
	movl	%ebp, %esp
	popl	%ebp
	ret

#
# Function: destroy_queue
# Description: Destroys the queue by freeing the memory occupied by the nodes.
# Params: 1) pqueue - pointer to the queue
#         2) delete_data - function pointer for deleting each data element if needed
# Returns: None
# Notes: This function internally calls list_destroy to free the memory occupied by each node in the queue.
#         It ensures that all memory allocated for the nodes in the queue is properly released.
#         If a delete_data function is provided, it will be called for each data element to perform additional cleanup.
#         The caller is responsible for managing the memory of the queue structure itself.
#
# void 	destroy_queue(pqueue, delete_data)
	.globl	destroy_queue
	.type	destroy_queue, @function
destroy_queue:

	# Prologue
	pushl	%ebp
	movl	%esp, %ebp

	# Main Code

	pushl	12(%ebp)
	pushl	8(%ebp)
	call	list_destroy
	addl	$8, %esp

	# Epilogue
	movl	%ebp, %esp
	popl	%ebp
	ret

