

#ifndef     _ARRAY_3D
#define     _ARRAY_3D

typedef     void*   data_t;
#define     SIZE_DATA   (sizeof(data_t))

struct dummy;

typedef     struct dummy    dummy_t;
typedef     struct dummy*   p_dummy_t;
typedef     struct dummy**  pp_dummy_t;

typedef     p_dummy_t   array_t;
typedef     pp_dummy_t  p_array_t;

typedef     void(*DESTROYDATA_PROC)(data_t);
typedef     void(*SHOWDATA_PROC)(data_t);

struct dummy
{
    data_t* arr;
    size_t  dimen_1;
    size_t  dimen_2;
    size_t  dimen_3;
};
#define     SIZE_DUMMY  (sizeof(dummy_t))

//  Array Interface Functions

array_t     create_array(size_t dimen1, size_t dimen2, size_t dimen3);

void        assign_value_at(array_t arr, long index1, long index2, long index3, data_t ndata);
data_t      get_value_at(array_t arr, long index1, long index2, long index3);

void        array_traversal(array_t parr, SHOWDATA_PROC pshowdata);

void        destroy_array(p_array_t parr, DESTROYDATA_PROC pdestroydata);

#endif      /* _ARRAY_3D */

