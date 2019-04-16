#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include "ds_list.h"

typedef struct _DS_QUEUE
{
	DS_LIST* List;
}DS_QUEUE, *PDS_QUEUE;

DS_ERROR QueueCreate(DS_QUEUE** Queue);
void QueueDestroy(DS_QUEUE* Queue);

DS_ERROR QueuePush(DS_QUEUE* Queue, const void* Data, const size_t DataSize);
DS_ERROR QueuePop(DS_QUEUE* Queue);
DS_ERROR QueueFront(const DS_QUEUE* Queue, void** Data);
DS_ERROR QueueBack(const DS_QUEUE* Queue, void** Data);

bool QueueEmpty(const DS_QUEUE* Queue);
unsigned int QueueSize(const DS_QUEUE* Queue);

#endif // !QUEUE_H_INCLUDED
