#ifndef SORTING_H
#define SORTING_H
#define SORTINGELEMENT int
#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
#include <stdlib.h>
#include <string.h>

typedef int (*SortingCompareFunction)(const void *, const void *);

/**
 * @brief selectionSort 
 * 
 * @param arr list
 * @param base element size
 * @param length list length
 * @param compare compare function
 */
void selectionSort(void * arr,int base,int length,SortingCompareFunction compare);

/**
 * @brief insertionSort 
 * 
 * @param arr list
 * @param base element size
 * @param length list length
 * @param compare compare function
 */
void insertionSort(void * arr,int base, int length,SortingCompareFunction compare);

/**
 * @brief bubbleSort 
 * 
 * @param arr list
 * @param base element size
 * @param length list length
 * @param compare compare function
 */
void bubbleSort(void * arr,int base, int length,SortingCompareFunction compare);

/**
 * @brief shellSort 
 * 
 * @param arr list
 * @param base element size
 * @param length list length
 * @param compare compare function
 */
void shellSort(void * list,int base,int length,SortingCompareFunction compare);

/**
 * @brief mergeSort 
 * 
 * @param arr list
 * @param base element size
 * @param length list length
 * @param compare compare function
 */
void mergeSort(void * list,int base,int length,SortingCompareFunction compare);

/**
 * @brief quickSort 
 * 
 * @param arr list
 * @param base element size
 * @param length list length
 * @param compare compare function
 */
void quickSort(void * list,int base,int length,SortingCompareFunction compare);

#endif


#define SORTING_IMPLEMENTATION
#ifdef SORTING_IMPLEMENTATION

/**
 * @brief to swap void pointer's value
 * 
 * @param A swap desc 1
 * @param B swap desc 2
 * @param temp swap temp
 * @param size element size
 */
inline static void swapValue(void * A, void * B,void * temp,int size){
    memmove(temp,A,size);
    memmove(A,B,size);
    memmove(B,temp,size);
}

void selectionSort(void * arr,int base,int length,SortingCompareFunction compare){
    int min;
    void *temp = malloc(base);
    for (int i = 0; i < length - 1; i++){
        min = i;
        for(int j = i + 1 ;j < length; j++){
            if(compare(arr + (min * base),arr + (j * base)) > 0) min = j;
        }
        swapValue(arr + (min * base),arr + (i * base),temp,base);
    }
    free(temp);
}

void insertionSort(void * arr,int base, int length,SortingCompareFunction compare){
    void * key = malloc(base);
    int i,j;
    for(i = 1; i <length; i++){
        memmove(key,arr + (i * base),base);
        for(j = i -1; i >= 0 && compare(arr + (j * base),key) > 0; j--)
            memmove(arr + ((j+ 1) * base ),arr + (j * base),base);
        memmove(arr + ((j+ 1) * base),key,base);
    }
}

void bubbleSort(void * arr,int base, int length,SortingCompareFunction compare){
    void * temp = malloc(base);
    for (int i = length;i > 0; i--){
        for(int j = 0; j < i; j++){
            if(compare(arr + (j * base),arr +((j + 1) * base)) > 0)
                swapValue(arr + (j * base),arr +((j + 1) * base),temp,base);
        }
    }
    free(temp);
}

void incInsertionShort(void* list,int base,int first,int last,int gap,SortingCompareFunction compare){
    int i,j;
    void * key = malloc(base);
    for(i = first + gap; i <= last;i+=gap){
        memmove(key,list + (i * base),base);
        for(j = i - gap; j>= first&&compare(key,list + (j * base)) < 0;j -=gap)
            memmove(list + (j+gap) * base,list + (j * base),base);
        memmove(list + (j+gap) * base,key,base);
    }
}

void shellSort(void * list,int base,int length,SortingCompareFunction compare){
    int i ,gap;
    for(gap = length / 2; gap > 0; gap /= 2){
        if((gap % 2) == 0) gap++;
        for(i = 0; i< gap;i++)
            incInsertionShort(list,base,i,length -1,gap,compare);
    }
}

void merge(void * list,void * sorted,int base,int left, int mid,int right,SortingCompareFunction compare){
    int i,j,k,l;
    i = left; j = mid + 1; k = left;


    while(i <= mid && j <= right){
        if(compare(list + (i*base),list+(j*base))<=0)
            memmove(sorted+(k++ * base),list+(i++ * base),base);
        else
            memmove(sorted+(k++ * base),list+(j++ * base),base);
    }

    if(i > mid)
        for (l = j; l <= right; l++)
            memmove(sorted+(k++ * base),list+(l * base),base);
    else
        for(l = i; l <= mid; l++)
            memmove(sorted+(k++ * base),list+(l * base),base);
    for(l = left; l <= right; l++){
        memmove(list+(l*base),sorted+(l*base),base);
    }
}



void _mergeSort(void * arr, void * sorted,int base,int left,int right,SortingCompareFunction compare){
    int mid;
    if(left<right){
        mid = (left + right) / 2;
        _mergeSort(arr,sorted,base,left,mid,compare);
        _mergeSort(arr,sorted,base,mid+1,right,compare);
        merge(arr,sorted,base,left,mid,right,compare);
    }
}

void mergeSort(void * list,int base,int length,SortingCompareFunction compare){
    void * sorted = malloc(base * length);
    _mergeSort(list,sorted,base,0,length,compare);
    free(sorted);
}

int partitaion(void * arr,int base,int left,int right,SortingCompareFunction compare){
    int low,high,key;
    void * temp = malloc(base);
    low = left;
    key = left;
    high = right + 1;
    do{
        do{
            low++;
        }while(compare(arr+(key*base),arr+(low*base)) > 0);
        do{
            high--;
        }while(compare(arr+(key*base),arr+(high*base)) < 0);
        if(low < high) swapValue(arr+(low*base),arr+(high*base),temp,base);
    }while(low < high);
    swapValue(arr+(key*base),arr+(high*base),temp,base);
    return high;
}

void _quickSort(void * arr,int base, int left,int right,SortingCompareFunction compare){
    if(left < right){
        int mid = partitaion(arr,base,left,right,compare);
        _quickSort(arr,base,left,mid - 1,compare);
        _quickSort(arr,base,mid + 1,right,compare);
    }
}

void quickSort(void * list,int base,int length,SortingCompareFunction compare){
    _quickSort(list,base,0,length,compare);
}

#endif