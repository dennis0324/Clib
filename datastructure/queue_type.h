#ifndef QUEUETYPE_H
#define QUEUETYPE_H
#include <stdlib.h>

// typedef struct Queue_node{
//     int num;
// }QueueNode;
#ifndef QUEUEELEMENT
#define QUEUEELEMENT int
#endif

typedef struct queue_type{
    int front;
    int rear;
    int total;
    QUEUEELEMENT * data;
}QueueType;

/**
 * @brief 큐를 동적할당으로 생성하는 함수이다.
 * 
 * @param n 큐의 크기
 * @return QueueType* 
 */
QueueType * create_queue(int n);

/**
 * @brief 큐를 동적할당 해제하는 함수이다.
 * 
 * @param q 동적할당할 큐
 */
void destroy_queue(QueueType * q);

/**
 * @brief 큐가 다 차있는지 확인하는 함수
 * 
 * @param queue 확인할 큐
 * @return int 
 */
int queue_is_full(QueueType * queue);

/**
 * @brief 큐가 비었는지 확인하는 함수
 * 
 * @param queue 확인할 큐
 * @return int 
 */
int queue_is_empty(QueueType * queue);

/**
 * @brief 큐에 삽입하는 함수
 * 
 * @param queue 변수를 삽입할 큐
 * @param data 삽입을 할 변수
 * @return int 삽입 성공 여부
 */
int queue_enque(QueueType * queue,QUEUEELEMENT data);

/**
 * @brief 큐에 삭제하는 함수
 * 
 * @param queue 변수를 제거할 큐
 * @param resultValue 제거하고 반환 받을 포인터 변수
 * @return int 제거 성공 여부
 */
int queue_deque(QueueType * queue,QUEUEELEMENT * resultValue);

/**
 * @brief 큐를 배열로 변환하는 함수
 * 
 * @param queue 변환할 함수
 * @param ob 동적할당할 포인터 변수의 주소
 * @return int 배열의 크기
 */
int toArray(QueueType * queue,QUEUEELEMENT ** ob);
#endif

#ifdef QUEUETYPE_IMPLEMENTATION
QueueType * create_queue(int n){
    QueueType * result = (QueueType *)malloc(sizeof(QueueType));
    result->data = (QUEUEELEMENT *)malloc(sizeof(QUEUEELEMENT) * n);
    result->total = n;
    result->front = 0;
    result->rear = 0;
    return result;
}

void destroy_queue(QueueType * q){
    free(q->data);
    free(q);
}

int queue_is_full(QueueType * queue){
    return (queue->rear + 1 % queue->total ) == queue->front;
}

int queue_is_empty(QueueType * queue){
    return queue->front == queue->rear;
}

int queue_enque(QueueType * queue,QUEUEELEMENT data){
    if(queue_is_full(queue)){
        return 0;
    }
    queue->data[queue->rear] = data;
    queue->rear = (queue->rear+1)%queue->total;
    return 1;
}

int queue_deque(QueueType * queue,QUEUEELEMENT * resultValue){
    if(queue_is_empty(queue)) return 0;
    if(resultValue != NULL)
        *resultValue = queue->data[queue->front];
    queue->front = (queue->front+1)%queue->total;
    return 1;
}

int toArray(QueueType * queue,QUEUEELEMENT ** resultValue){
    int n = (queue->rear + queue->total - queue->front) % queue->total;
    int tfront = queue->front; int trear = queue->rear;
    if(n == 0) {
        *ob = NULL;
        return 0;
    }
    QUEUEELEMENT * result = (QUEUEELEMENT *)malloc(sizeof(QUEUEELEMENT) * n);
    int i = 0;

    while(i != n){
        result[i++] = queue->data[tfront]; 
        tfront = (tfront + 1) % queue->total;

    }
    *ob = result;
    return n; 
}
#endif