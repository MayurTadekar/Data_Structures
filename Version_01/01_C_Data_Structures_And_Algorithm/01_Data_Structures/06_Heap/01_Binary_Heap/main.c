

#include	<stdio.h>
#include	<stdlib.h>

#include	"heap.h"

heap_t 	heap = NULL;
heap_t 	heap2 = NULL;

bool_t inequality(data_t d1, data_t d2)
{
	if( (int)d1 > (int)d2 )
		return(SUCCESS);

	return(FAILURE);
}

bool_t inequality2(data_t d1, data_t d2)
{
	if( (int)d1 < (int)d2 )
		return(SUCCESS);

	return(FAILURE);
}

bool_t compare(data_t d1, data_t d2)
{
	if( (int)d1 == (int)d2 )
		return(SUCCESS);

	return(FAILURE);
}

void show(data_t data)
{
	printf("%d->", (int)data);
}

int main(void)
{

	heap = heap_create();
	heap2 = heap_create();

	srand(time(0));

	int iArr = (rand() % 10 + 1);
	int *arr = (int*)malloc( sizeof(int) * iArr);

	for(int i = 0 ; i < iArr; ++i)
	{	
		arr[i] = (rand() % 1000 + 1);
		heap_insert_key(heap, (data_t)arr[i], compare, inequality);
	}
	heap_show(heap, show);
	printf("Maximum = %d\n", (int)heap_peek(heap));
	printf("\n");

	printf("Deleted Data = %d\n", (int)heap_delete_root(heap, inequality, compare));
	heap_show(heap, show);
	printf("Maximum = %d\n", (int)heap_peek(heap));
	printf("\n");
	printf("\n");

	printf("Deleted Data = %d\n", (int)heap_delete_key(heap,  (data_t)arr[ (rand() % 10) ], compare, inequality));
	heap_show(heap, show);
	
	int rep = (rand() % 1000 + 1);
	printf("Replacing Root = %d with %d\n", (int)heap_replace_root(heap, (data_t)rep, compare, inequality), rep);
	heap_show(heap, show);

	/*for(int i = 0 ; i < (rand() % 100 + 1); ++i)
	{
		heap_insert_key(heap2, (data_t) (rand() % 1000 + 1), compare, inequality2);
		//printf("\n");
	}
	heap_show(heap2, show);
	printf("Maximum = %d\n", (int)heap_peek(heap2));
	printf("\n");

	printf("Deleted Data = %d\n", (int)heap_delete_root(heap2, compare));
	heap_heapify(heap2, inequality2, compare);
	heap_show(heap2, show);
	printf("Minimum = %d\n", (int)heap_peek(heap2));*/


	return(0);
}

