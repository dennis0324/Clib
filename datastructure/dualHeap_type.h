
//요소는 반드시 _ELEMENT로 설정

#ifndef DUALHEAPTYPE_H
#define DUALHEAPTYPE_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef DUALHEAPELEMENT
#define DUALHEAPELEMENT int
#endif

#ifndef DUALHEAPTYPE_ELEMENT
int dualHeapDefaultCompare(const void * A,const void * B){
    int * a = (int *)A; int * b = (int *)B;
    return (*a < *b) - (*a > *b);
}
#define _DUALHEAPTYPE_COMPARE_FUNCTION
#define DUALHEAPTYPE_ELEMENT int
#endif

/**
 * @brief mod of extraction
 * 
 */
enum dualheap_type_enum{
    DUALHEAP_MIN = -1,
    DUALHEAP_MAX = 1
};

/**
 * @brief structure of Heap Element
 * 
 */
typedef struct{
    DUALHEAPTYPE_ELEMENT data; 
    int index;
}HE;

/**
 * @brief structure of Heap
 * 
 */
typedef struct {
    int n;
    HE * d;
}H;

/**
 * @brief to compare different value that user make
 * 
 */
typedef int (*CompareFunction)(const void *, const void *);

/**
 * @brief structure of Flag array
 * 
 */
typedef struct {
    bool flag;
    DUALHEAPTYPE_ELEMENT data;
}Flag;

/**
 * @brief structure of Dual Heap
 * 
 */
typedef struct DualHeapType{
    int size;
    int cindex;
    H * max;
    H * min;
    Flag * flag;
    int * _que;
    int _front, _rear;
    CompareFunction compare;
}DualHeapType;

/**
 * @brief Create a dualheap object
 * 
 * @param size dualheap size;
 * @param compare 
 * @return DualHeapType* 
 */
DualHeapType *create_dualheap(int size,CompareFunction compare);

/**
 * @brief free dualheap object
 * 
 * @param dh DualHeap
 */
void destory_dualheap(DualHeapType * dh);

/**
 * @brief add value to dualheap
 * 
 * @param dh DualHeap
 * @param e insert value
 */
void insertDualheap(DualHeapType * dh,DUALHEAPTYPE_ELEMENT e);


/**
 * @brief delete value from dualheap
 * 
 * @param dh DualHeap
 * @param type DUALHEAP_MIN / DUALHEAP_MAX
 * @return DUALHEAPTYPE_ELEMENT 
 */
DUALHEAPTYPE_ELEMENT deleteDualheap(DualHeapType * dh,int type);
#endif


#ifdef DUALHEAPTYPE_IMPLEMENTATION
static H* _dualheapCreateHeap(int size){
    H * result = malloc(sizeof(*result));
    result->d = malloc(sizeof(*result) * size);
    result->n = 0;

    return result;
}

static void _dualheapDestroyHeap(H* h){
    free(h->d);
    free(h);
}
DualHeapType * create_dualheap(int size,CompareFunction compare){
    DualHeapType * dh = (DualHeapType *)malloc(sizeof(*dh));
    dh->flag = malloc(sizeof(*(dh->flag)) * size);
    dh->cindex = -1;
    dh->size = size;

    dh->_que = malloc(sizeof(*(dh->_que) * (size + 2)));
    dh->_front = 0; dh->_rear = 0;

    dh->min = _dualheapCreateHeap(size);
    dh->max = _dualheapCreateHeap(size);

#ifdef _DUALHEAPTYPE_COMPARE_FUNCTION
    dh->compare = dualHeapDefaultCompare;
#else
    dh->compare = compare;
#endif
}

void destory_dualheap(DualHeapType * dh){
    free(dh->flag);
    _dualheapDestroyHeap(dh->max);
    _dualheapDestroyHeap(dh->min);
    free(dh->_que);

    free(dh);
}

static void _dualheaptype_insert(H * h,CompareFunction compare, HE e,int type){
    int index = ++h->n;
    while(index != 1){
        if(compare(&(h->d[index / 2]),&e) * type <= 0) break;
        h->d[index] = h->d[index /2];
        index /= 2;
    }
    h->d[index] = e;
}

void insertDualheap(DualHeapType * dh,DUALHEAPTYPE_ELEMENT e){
    int currentIndex;
    if(dh->_front == dh->_rear){
        dh->cindex = (dh->cindex + 1) % dh->size;
        currentIndex = dh->cindex;
    }
    else{
        dh->_front = (dh->_front + 1) % (dh->size + 1);
        currentIndex = dh->_que[dh->_front];
    }

    _dualheaptype_insert(dh->max,dh->compare,(HE){e,currentIndex},1);
    _dualheaptype_insert(dh->min,dh->compare,(HE){e,currentIndex},-1);
    dh->flag[currentIndex].data = e;
    dh->flag[currentIndex].flag = 0;
}

DUALHEAPTYPE_ELEMENT _deleteDualheap(DualHeapType * dh,H *h, int type){
    if(!h->n) return;
    HE result = h->d[1];
    int parent = 1,child = 2;
    HE temp = h->d[h->n--];
    while(child <= h->n){
        if(child < h->n && (dh->compare(&(h->d[child + 1].data),&(h->d[child].data)) * type < 0))
            child++;
        if(dh->compare(&temp.data,&(h->d[child].data)) * type <= 0) break;
        h->d[parent] = h->d[child];
        parent = child;
        child *=2;
    }
    h->d[parent] = temp;

    
    if(!dh->compare(&(dh->flag[result.index].data),&(result.data)))
        dh->flag[result.index].flag = 1;
    dh->_rear = (dh->_rear + 1) % (dh->size + 1);
    dh->_que[dh->_rear] = result.index;

    return result.data;
}

DUALHEAPTYPE_ELEMENT deleteDualheap(DualHeapType * dh,int type){
    HE temp;
    DUALHEAPTYPE_ELEMENT result;
    if(type == DUALHEAP_MIN){
        Flag tempFlag = dh->flag[temp.index];
        while(dh->flag[dh->min->d[1].index].flag || dh->compare(&(dh->flag[dh->min->d[1].index].data),&(dh->min->d[1].data))){
            temp = dh->min->d[1];
            Flag tempFlag = dh->flag[temp.index];
            _deleteDualheap(dh,dh->min,type);
        }
        result = _deleteDualheap(dh,dh->min,type);
    }
    else if(type ==DUALHEAP_MAX){
        temp = dh->max->d[1];
        while(dh->flag[temp.index].flag || dh->compare(&(dh->flag[temp.index].data),&(temp.data))) 
            _deleteDualheap(dh,dh->max,type);
        result = _deleteDualheap(dh,dh->max,type);
    }

    return result;
}

#endif