#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <stdlib.h>

#ifndef SORTINGELEMENT
#define SORTINGELEMENT int
#endif


enum INT_RANDOMIZER_TYPE{
    INT_RANDOMIZER_NORMAL,
    INT_RANDOMIZER_UNIQUE
};
/**
 * @brief randomizer
 * 
 * @param size 
 */
int randomIntFromZero(int to);

int randomInt(int from ,int to);

int * randomizer(int size,int type);

#endif

// #define RANDOMIZER_IMPLEMENTATION
#ifdef RANDOMIZER_IMPLEMENTATION

int * randomizer(int size,int type){
    SORTINGELEMENT * result = (SORTINGELEMENT *) malloc(sizeof(SORTINGELEMENT) * size);
    int flag[32767] ={0};
    int temp;
    int index = 0;
    while(index < size){
        temp = rand() % size;
        if(type == 0 ){
            result[index++] = temp;
        }
        else{
            if(!flag[temp]){
                flag[temp] =1;
                result[index] = temp;
                index++;
            }
        }
    }

    return result;
}

#endif