/*
########################################################
###       @Copyright Moreno Vera, Felipe Adrian      ###
###        Dinamic Array List Functions              ###
########################################################
*/

#include <stdio.h>
#include <stdlib.h>
#include "maf.h"


// ------------------------------------------------//

maf_tPtr Create_maf_t() {
  return Create_maf_t_with_parent_and_chunck_size(NULL, ARRAY_LIST_CHUNK_SIZE);
}

maf_tPtr Create_maf_t_initial_size(size_t capacity) {
  return Create_maf_t_with_parent_and_chunck_size(NULL, capacity);
}

// en vez de "aumentar" la capacidad, se crea un nuevo vector que le sigue al original con un tamano dado
maf_tPtr Create_maf_t_with_parent_and_chunck_size(maf_tPtr parent,size_t chunck_size) {
  maf_tPtr result = (maf_tPtr)calloc(sizeof(maf_t), 1);
  result->parent = parent;
  result->child = NULL;
  result->capacity = chunck_size;
  result->data = (float*)malloc(sizeof(float) * chunck_size);
  return result;
}

// en vez de "aumentar" la capacidad, se crea un nuevo vector que le sigue al original con tamano por defecto
maf_tPtr Create_maf_t_with_parent(maf_tPtr parent) {
  return Create_maf_t_with_parent_and_chunck_size(parent, ARRAY_LIST_CHUNK_SIZE);
}

// inserta por el final un valor
void maf_t_push_back(maf_tPtr list, float value) {
  if (list->size >= list->capacity) {
    if (!list->child) {
      list->child = Create_maf_t_with_parent(list);
    }
    maf_t_push_back(list->child, value);
  } else {
      list->data[list->size] = value;
      list->size+=1;
  }
}

// retorna el valor de indice dado
float* maf_t_get_value_by_index(maf_tPtr list, size_t index) {
  if (index >= list->capacity || index >= list->size) {
    if (list->child) {
      return maf_t_get_value_by_index(list->child,index - list->size);
    } else {
      return NULL;
    }
  }
  return list->data + index;
}

void maf_t_set_value_by_index(maf_tPtr list, size_t index,float value){
  if (index >= list->capacity || index >= list->size) {
    if (list->child) {
      maf_t_set_value_by_index(list->child,index - list->size,value);
    } else {
      printf("\nFuera de rango, Overflow !!\n");
    }
  } else {
    list->data[index] = value;
  }
}

float maf_t_prom(maf_tPtr list){
  float prom=0.;
  size_t len=1;
  if(list==NULL){
    printf("\nArray Empty\n");
    return prom;
  }
  else{
    maf_tPtr aux = list;
    len = maf_t_length(aux);
    size_t i;
    for (i = 0; i < aux->size; ++i) {
      float* result = maf_t_get_value_by_index(aux, i);
      if (result) {
          prom = prom + (*result);
      } else {
          printf("Can't get value by index %ld\n", i);
          break;
      }
    }
    if(aux->child != NULL){ // el seguido de un vector
      float prom_child = maf_t_prom(aux->child);
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

size_t maf_t_length(maf_tPtr list){
  size_t length = 0;
  if(list==NULL){
    printf("\nArray Empty\n");
    return length;
  } else{
    maf_tPtr aux = list;
    length = aux->size;
    if(aux->child == NULL){ // solo un unico vector
      return length;
    }
    if(aux->child != NULL){ // el seguido de un vector
      size_t length_child = maf_t_length(aux->child);
      length = length + length_child;
      return length;
    }
  }
}

void maf_t_print(maf_tPtr list){
  if(list==NULL){
    printf("\nArray Empty\n");
    return ;
  }
  else{
    maf_tPtr aux = list;
    size_t i;
    printf("data[");
    for (i = 0; i < aux->size; ++i) {
      float* result = maf_t_get_value_by_index(aux, i);
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
    else  maf_t_print(aux->child);
  }
  return ;
}
