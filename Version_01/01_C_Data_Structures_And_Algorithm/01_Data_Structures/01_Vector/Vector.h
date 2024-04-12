

#ifndef     _VECTOR
#define     _VECTOR 

typedef     void*   data_t;
#define     SIZE_DATA   (sizeof(data_t))

struct dummy;

typedef     struct dummy    dummy_t;
typedef     struct dummy*   p_dummy_t;
typedef     struct dummy**  pp_dummy_t;

struct dummy
{
    data_t*     data;
    size_t      size;
    size_t      capacity;
};
#define     SIZE_DUMMY  (sizeof(dummy_t))

typedef     p_dummy_t   vector_t;

//  Vector Auxillary Functions
vector_t    create_vector();

void        vector_push_back(vector_t vec, data_t data);
data_t      vector_pop_back(vector_t vec);
data_t      vector_at(vector_t vec, size_t index);
size_t      vector_size(vector_t vec);

data_t      vector_front(vector_t vec);
data_t      vector_back(vector_t vec);

size_t      vector_capacity(vector_t vec);

int         vector_empty();

#endif     /* _VECTOR */


