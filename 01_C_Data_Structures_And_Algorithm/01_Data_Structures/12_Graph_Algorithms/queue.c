

/**
 * @file queue.c
 * @author Mayur Tadekar
 * @brief Source Code of Helper Queue Data Structure for Graph
 * @version 0.1
 * @date 2022-05-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include    <stdio.h>
#include    <stdlib.h>

#include    "queue.h"

//  Queue Auxillary Functions

/**
 * @brief Allocate 'nr_elements' * 'element_size' memory
 * 
 * @return void* returning address of the allocated memory
 */
static  void*   Xcalloc(size_t nr_elements, size_t element_size)
{
    void* p = calloc(nr_elements, element_size);
    if( NULL == p)
    {
        fprintf(stderr, "ERROR: Out Of Memory\n");
        exit(1);
    }
    return(p);
}

//  List Interface Functions

/**
 * @brief Create a queue object
 * 
 * @return queue_t Address of create queue object
 */
extern  queue_t         create_queue()
{
    p_queue_dummy_t pq = (p_queue_dummy_t)Xcalloc(1, SIZE_QUEUE);
    pq->list = create_list();
    return(pq);
}

/**
 * @brief Insertion of data in queue
 * 
 * @param queue Queue to insert data
 * @param data data to insert in queue
 * @return status_t returning status of insertion
 */
extern  status_t        queue_enqueue(queue_t queue, queue_data_t data)
{
    return( list_insert_back(((p_queue_dummy_t)queue)->list, data) );
}

/**
 * @brief Removing Data from queue
 * 
 * @param queue queue to remove data
 * @return queue_data_t returning remove data from queue 
 */
extern  queue_data_t    queue_dequeue(queue_t queue)
{
    return( list_remove_first(((p_queue_dummy_t)queue)->list) );
}

/**
 * @brief Retriving the first element
 * 
 * @param queue queue to retrive data from
 * @return queue_data_t returning retrived data
 */
extern  queue_data_t    queue_first(queue_t queue)
{
    return( list_at(((p_queue_dummy_t)queue)->list, 0));
}

/**
 * @brief Retriving data at particular index.
 * 
 * @param queue Queue to retrive data
 * @param index index in qeueue to get data
 * @return queue_data_t retuning retrive data from queue
 */
extern  queue_data_t    queue_at(queue_t queue, size_t index)
{
    return(list_at(((p_queue_dummy_t)queue)->list, index));
}

/**
 * @brief Acquiring size of queue
 * 
 * @param queue Queue to get size of
 * @return size_t retuning the size
 */
extern  size_t          queue_size(queue_t queue)
{
    return(list_size( ((p_queue_dummy_t)queue)->list));
}

/**
 * @brief Destroying the queue
 * 
 * @param pqueue Pointer to queue to destroy
 */
extern  void            queue_destroy(queue_t* pqueue)
{
    list_destroy( &( ((p_queue_dummy_t)*pqueue)->list), NULL);
    free(*pqueue);
    *pqueue = NULL;
}
