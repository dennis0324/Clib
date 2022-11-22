#ifndef HEAPTYPE_H
#define HEAPTYPE_H
#include <stdlib.h>

// typedef struct heaptype_element{
//     int key;
// }HT_element;

#ifndef HEAPTYPE_ELEMENT
int heapDefaultCompare(const void * A,const void * B){
    int * a = (int *)A; int * b = (int *)B;
    return (*a < *b) - (*a > *b);
}
#define _HEAPTYPE_COMPARE_FUNCTION
#define HEAPTYPE_ELEMENT int
#endif

enum InsertType{
    min =-1,
    max = 1
};

typedef int (*CompareFunction)(const void *, const void *);

typedef struct heap_type{
    int size;
    int total;
    HEAPTYPE_ELEMENT * data;
    CompareFunction compare;
}HeapType;

/**
 * @brief Create a heap object
 * 
 * @param size 
 * @return HeapType* 
 */
HeapType * create_heap(int size);

/**
 * @brief insert value to heap
 * 
 * @param insertType min / max
 * @param heap heaptype
 * @param element value that is going to inserted in heap
 */
void insert_heap(int insertType,HeapType * heap,HEAPTYPE_ELEMENT element);

/**
 * @brief delete value from heap
 * 
 * @param insertType min / max
 * @param heap heaptype
 * @return HEAPTYPE_ELEMENT value that deleted from heap
 */
HEAPTYPE_ELEMENT delete_heap(int insertType,HeapType * heap);


/**
 * @brief free the heap
 * 
 */
void destory_heap(HeapType * heap);
#endif

#ifdef HEAPTYPE_IMPLEMENTATION
HeapType * create_heap(int size,CompareFunction compare){
    HeapType * result = (HeapType*)malloc(sizeof(HeapType));
    if(!result) return NULL;
    result->compare = compare;
    result->total = size;
    result->size = 0;
    result->data = (HEAPTYPE_ELEMENT *)malloc(sizeof(HEAPTYPE_ELEMENT) * size);
    if(!result->data) return NULL;
    return result;
}


void insert_heap(int insertType,HeapType * heap,HEAPTYPE_ELEMENT element){
    int index = ++heap->size;
    while(index != 1){
        if(heap->compare(&(heap->data[index /2]),&element) * insertType <= 0) break;
        heap->data[index] = heap->data[index/2];
        index /= 2;
    }
    heap->data[index] = element;
}

HEAPTYPE_ELEMENT delete_heap(int insertType,HeapType * heap){
    int parent = 1;
    int child = 2;
    HEAPTYPE_ELEMENT result = heap->data[1];
    HEAPTYPE_ELEMENT element = heap->data[heap->size--];
    while(child <= heap->size){
        if(child < heap->size && (heap->compare(&(heap->data[child + 1]),&(heap->data[child])) * insertType < 0))
            child++;
        if(heap->compare(&element,&(heap->data[child])) * insertType <= 0) break;
        heap->data[parent] = heap->data[child];
        parent = child;
        child *=2;
    }
    heap->data[parent] = element;
    
    return result;
}

void destory_heap(HeapType * heap){
    free(heap->data);
    free(heap);
}

#endif