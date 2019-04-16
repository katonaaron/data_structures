#include "ds_queue.h"

DS_ERROR QueueCreate(DS_QUEUE** Queue)
{
	if (NULL == Queue)
		return DS_INVALID_PARAMETER;

	PDS_QUEUE queue = (PDS_QUEUE)malloc(sizeof(DS_QUEUE));
	if (NULL == queue)
		return DS_NO_MEMORY;

	DS_ERROR result = ListCreate(&queue->List);
	if (DS_SUCCESS != result)
		return result;

	*Queue = queue;
	return DS_SUCCESS;
}

void QueueDestroy(DS_QUEUE* Queue)
{
	if (NULL != Queue)
	{
		ListDestroy(Queue->List);
		free(Queue);
	}
}

DS_ERROR QueuePush(DS_QUEUE* Queue, const void* Data, const size_t DataSize)
{
	if (NULL == Queue)
		return DS_INVALID_PARAMETER;

	return ListPushBack(Queue->List, Data, DataSize);
}

DS_ERROR QueuePop(DS_QUEUE* Queue)
{
	if (NULL == Queue)
		return DS_INVALID_PARAMETER;

	return ListPopFront(Queue->List);
}

DS_ERROR QueueFront(const DS_QUEUE* Queue, void** Data)
{
	if (NULL == Queue)
		return DS_INVALID_PARAMETER;

	return ListFront(Queue->List, Data);
}

DS_ERROR QueueBack(const DS_QUEUE* Queue, void** Data)
{
	if (NULL == Queue)
		return DS_INVALID_PARAMETER;

	return ListBack(Queue->List, Data);
}

bool QueueEmpty(const DS_QUEUE* Queue)
{
	return NULL == Queue || ListEmpty(Queue->List);
}

unsigned int QueueSize(const DS_QUEUE* Queue)
{
	if (NULL != Queue)
		return ListSize(Queue->List);
	return 0;
}
