#ifndef CIR_QUE_H
#define CIR_QUE_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct CirQue_struct CirQue;
/* create circular queue */
CirQue *CirQue_create(int capacity);

/* release circular queue */
void CirQue_free(CirQue *Cque);

/* get value from circular queue */
void *CirQue_get(CirQue *Cque, int index);

/* insert values in circualr queue */
bool CirQue_enqueue(CirQue *Cque, void *i);
/* insert values in circualr queue */
bool CirQue_dequeue(CirQue *q, void *i);

bool CirQue_empty(CirQue *q);

bool CirQue_full(CirQue *q);
#endif

#ifdef CIR_QUE_IMPLEMENTATION

struct CirQue_struct {
  void **ptr;
  int capacity;
  int start, end;
};

CirQue *CirQue_create(int capacity) {
  CirQue *q = malloc(sizeof(*q));
  q->capacity = capacity + 1;
  q->ptr = malloc(sizeof(void *) * q->capacity);
  q->start = q->end = 0;
  return q;
}

void CirQue_free(CirQue *Cque) {
  free(Cque->ptr);
  free(Cque);
}

void *CirQue_get(CirQue *Cque, int index) {
  if (index >= Cque->capacity)
    return NULL;
  return Cque->ptr[(Cque->start + index) % Cque->capacity];
}

/* insert values in circurlar queue */
bool CirQue_enqueue(CirQue *Cque, void *i) {
  if (Cque == NULL || CirQue_full(Cque))
    return false;

  Cque->ptr[Cque->end] = i;
  Cque->end = (Cque->end + 1) % Cque->capacity;

  return true;
}

/* get first element in circular queue */
bool CirQue_dequeue(CirQue *q, void *i) {
  if (CirQue_empty(q) || i == NULL)
    return false;

  i = q->ptr[q->start];
  q->start = (q->start + 1) % q->capacity;

  return true;
}

/* check cirque is empty */
bool CirQue_empty(CirQue *q) {
  return (q == NULL) || (q->start == q->end);
}

/* 링 버퍼가 포화 상태인지 확인한다. */
bool CirQue_full(CirQue *q) {
  return (q != NULL) && (q->start == (q->end + 1) % q->capacity);
}
#endif
