/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Dinamic Array List Functions              ###
########################################################
*/

#define ARRAY_LIST_CHUNK_SIZE 64

typedef struct maf_t maf_t;
typedef struct maf_t* maf_tPtr;

// Define a array type
struct maf_t{
  size_t size;      // tamano usado
  size_t capacity;  // tamano total
  float *data;     // array
  maf_tPtr parent; // array padre
  maf_tPtr child; // array que le sigue
};

extern maf_tPtr Create_maf_t();
extern maf_tPtr Create_maf_t_initial_size(size_t);
extern maf_tPtr Create_maf_t_with_parent_and_chunck_size(maf_tPtr,size_t);
extern maf_tPtr Create_maf_t_with_parent(maf_tPtr);
extern void maf_t_push_back(maf_tPtr, float);
extern float* maf_t_get_value_by_index(maf_tPtr, size_t);
extern void maf_t_set_value_by_index(maf_tPtr, size_t,float);
extern float maf_t_prom(maf_tPtr);
extern size_t maf_t_length(maf_tPtr);
extern void maf_t_print(maf_tPtr);
