#ifndef DS_PRIORITY_QUEUE_H
#define DS_PRIORITY_QUEUE_H

#include "ds_common.h"
#include "ds_list.h"

typedef struct _DS_PRIORITY_QUEUE
{
	DS_LIST* List;
	DS_COMPARE_FUNCTION Compare;
}DS_PRIORITY_QUEUE, *PDS_PRIORITY_QUEUE;

DS_ERROR PQCreate(DS_PRIORITY_QUEUE** Pq, DS_COMPARE_FUNCTION Compare);
void PQDestory(DS_PRIORITY_QUEUE* Pq);
DS_ERROR PQInsert(DS_PRIORITY_QUEUE* Pq, const void* Data, const size_t DataSize);
DS_ERROR PQGetMin(const DS_PRIORITY_QUEUE* Pq, void** Data);
DS_ERROR PQGetMax(const DS_PRIORITY_QUEUE* Pq, void** Data);
DS_ERROR PQPopMin(DS_PRIORITY_QUEUE* Pq);
DS_ERROR PQPopMax(DS_PRIORITY_QUEUE* Pq);

bool PQEmpty(const DS_PRIORITY_QUEUE* Pq);
unsigned int PQSize(const DS_PRIORITY_QUEUE* Pq);

#endif //DS_PRIORITY_QUEUE_H
