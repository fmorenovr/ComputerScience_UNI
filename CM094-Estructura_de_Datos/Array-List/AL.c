/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Dinamic Array List Functions              ###
########################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include "AL.h"


// ------------------------------------------------//

ArrayListPtr Create_arrayList() {
  return Create_arrayList_with_parent_and_chunck_size(NULL, ARRAY_LIST_CHUNK_SIZE);
}

ArrayListPtr Create_arrayList_initial_size(size_t capacity) {
  return Create_arrayList_with_parent_and_chunck_size(NULL, capacity);
}

// en vez de "aumentar" la capacidad, se crea un nuevo vector que le sigue al original con un tamano dado
ArrayListPtr Create_arrayList_with_parent_and_chunck_size(ArrayListPtr parent,size_t chunck_size) {
  ArrayListPtr result = (ArrayListPtr)calloc(sizeof(ArrayList), 1);
  result->parent = parent;
  result->child = NULL;
  result->capacity = chunck_size;
  result->data = (float*)malloc(sizeof(float) * chunck_size);
  return result;
}

// en vez de "aumentar" la capacidad, se crea un nuevo vector que le sigue al original con tamano por defecto
ArrayListPtr Create_arrayList_with_parent(ArrayListPtr parent) {
  return Create_arrayList_with_parent_and_chunck_size(parent, ARRAY_LIST_CHUNK_SIZE);
}

// inserta por el final un valor
void arrayList_push_back(ArrayListPtr list, float value) {
  if (list->size >= list->capacity) {
    if (!list->child) {
      list->child = Create_arrayList_with_parent(list);
    }
    arrayList_push_back(list->child, value);
  } else {
      list->data[list->size] = value;
      list->size+=1;
  }
}

// retorna el valor de indice dado
float* arrayList_get_value_by_index(ArrayListPtr list, size_t index) {
  if (index >= list->capacity || index >= list->size) {
    if (list->child) {
      return arrayList_get_value_by_index(list->child,index - list->size);
    } else {
      return NULL;
    }
  }
  return list->data + index;
}

void arrayList_set_value_by_index(ArrayListPtr list, size_t index,float value){
  if (index >= list->capacity || index >= list->size) {
    if (list->child) {
      arrayList_set_value_by_index(list->child,index - list->size,value);
    } else {
      printf("\nFuera de rango, Overflow !!\n");
    }
  } else {
    list->data[index] = value;
  }
}

float arrayList_prom(ArrayListPtr list){
  float prom=0.;
  size_t len=1;
  if(list==NULL){
    printf("\nArray Empty\n");
    return prom;
  }
  else{
    ArrayListPtr aux = list;
    len = arrayList_length(aux);
    size_t i;
    for (i = 0; i < aux->size; ++i) {
      float* result = arrayList_get_value_by_index(aux, i);
      if (result) {
          prom = prom + (*result);
      } else {
          printf("Can't get value by index %ld\n", i);
          break;
      }
    }
    if(aux->child != NULL){ // el seguido de un vector
      float prom_child = arrayList_prom(aux->child);
      prom = prom + prom_child;
    } else {
      prom = prom;
    }
    if(aux->parent==NULL){
      return prom/len;
    } else {
      return prom;
    }
  }
}

size_t arrayList_length(ArrayListPtr list){
  size_t length = 0;
  if(list==NULL){
    printf("\nArray Empty\n");
    return length;
  } else{
    ArrayListPtr aux = list;
    length = aux->size;
    if(aux->child == NULL){ // solo un unico vector
      return length;
    }
    if(aux->child != NULL){ // el seguido de un vector
      size_t length_child = arrayList_length(aux->child);
      length = length + length_child;
      return length;
    }
  }
}

void arrayList_print(ArrayListPtr list){
  if(list==NULL){
    printf("\nArray Empty\n");
    return ;
  }
  else{
    ArrayListPtr aux = list;
    size_t i;
    printf("array[");
    for (i = 0; i < aux->size; ++i) {
      float* result = arrayList_get_value_by_index(aux, i);
      if (result) {
          //printf("array[%ld] = %d\n", i, *result);
          printf("%f  ,",*result);
      } else {
          printf("Can't get value by index %ld\n", i);
          break;
      }
    }
    printf("]\n");
    if(aux->child == NULL){
      printf("\nEnd Array\n");
      return;
    }
    else  arrayList_print(aux->child);
  }
  return ;
}

void ALmain()
{
  int i;
  ArrayListPtr list = Create_arrayList_initial_size(15);
  for (i = 0; i < 100; i++) {
    //printf("%d,", i);
    arrayList_push_back(list, i);
  }
  size_t test[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,31,32,33,63,64,65,97,100};

  for (i = 0; i < sizeof(test) / sizeof(size_t); ++i) {
    float* result = arrayList_get_value_by_index(list, test[i]);
    if (result) {
        printf("array[%ld] = %f\n", test[i], *result);
    } else {
        printf("Can't get value by index %ld\n", test[i]);
    }
  }
  arrayList_print(list);
  arrayList_set_value_by_index(list,10,1.5);
  arrayList_print(list);
  arrayList_set_value_by_index(list,66,0.379777);
  arrayList_print(list);
  return ;
}
