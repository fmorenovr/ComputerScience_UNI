/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Dinamic Array List Functions              ###
########################################################
*/

#define ARRAY_LIST_CHUNK_SIZE 64

typedef struct arrayList ArrayList;
typedef struct arrayList* ArrayListPtr;

// Define a array type
struct arrayList{
  size_t size;      // tamano usado
  size_t capacity;  // tamano total
  float *data;     // array
  ArrayListPtr parent; // array padre
  ArrayListPtr child; // array que le sigue
};

extern ArrayListPtr Create_arrayList();
extern ArrayListPtr Create_arrayList_initial_size(size_t);
extern ArrayListPtr Create_arrayList_with_parent_and_chunck_size(ArrayListPtr,size_t);
extern ArrayListPtr Create_arrayList_with_parent(ArrayListPtr);
extern void arrayList_push_back(ArrayListPtr, float);
extern float* arrayList_get_value_by_index(ArrayListPtr, size_t);
extern void arrayList_set_value_by_index(ArrayListPtr, size_t,float);
extern float arrayList_prom(ArrayListPtr);
extern size_t arrayList_length(ArrayListPtr);
extern void arrayList_print(ArrayListPtr);

extern void ALmain();
