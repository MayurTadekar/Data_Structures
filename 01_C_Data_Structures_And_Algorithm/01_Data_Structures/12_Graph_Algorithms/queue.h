

/**
 *  @author Mayur Tadekar   
 *  @date   07th May, 2022 
 *  @details    Header file for all interface functions and 
 *              required types definitions for Queue 
 */

#ifndef     _QUEUE_H
#define     _QUEUE_H

//  Headers

#include    "dcll.h"

//  Literals and Typedefs

struct  queue_dummy;

typedef     struct queue_dummy      queue_dummy_t;
typedef     struct queue_dummy*     p_queue_dummy_t;
typedef     struct queue_dummy**    pp_queue_dummy_t;

typedef     void*   queue_t;

typedef     int     status_t;

typedef     dcll_data_t     queue_data_t;

struct queue_dummy
{
    list_t list;
};
#define     SIZE_QUEUE      (sizeof(queue_dummy_t))

//  Queue Auxillary Functions
static  void*   Xcalloc(size_t nr_elements, size_t element_size);

//  List Interface Functions

extern  queue_t         create_queue();

extern  status_t        queue_enqueue(queue_t queue, queue_data_t data);
extern  queue_data_t    queue_dequeue(queue_t queue);

extern  queue_data_t    queue_first(queue_t queue);

extern  queue_data_t    queue_at(queue_t queue, size_t index);

extern  size_t          queue_size(queue_t queue);

extern  void            queue_destroy(queue_t* pqueue);

#endif      /* _QUEUE_H */

