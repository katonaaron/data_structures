#include "ds_priority_queue.h"

DS_ERROR PQCreate(DS_PRIORITY_QUEUE** Pq, DS_COMPARE_FUNCTION Compare)
{
	if (NULL == Pq || NULL == Compare)
		return DS_INVALID_PARAMETER;
	PDS_PRIORITY_QUEUE pq = (PDS_PRIORITY_QUEUE)malloc(sizeof(DS_PRIORITY_QUEUE));
	if (NULL == pq)
		return DS_NO_MEMORY;

	DS_ERROR result = ListCreate(&pq->List);
	if (DS_SUCCESS != result)
	{
		free(pq);
		return result;
	}

	pq->Compare = Compare;
	*Pq = pq;
	return DS_SUCCESS;
}

void PQDestroy(DS_PRIORITY_QUEUE* Pq)
{
	if(NULL != Pq)
	{
		ListDestroy(Pq->List);
		free(Pq);
	}
}

DS_ERROR PQInsert(DS_PRIORITY_QUEUE* Pq, const void* Data, const size_t DataSize)
{
	if (NULL == Pq)
		return DS_INVALID_PARAMETER;
	return ListInsert(Pq->List, Pq->Compare, Data, DataSize);
}

DS_ERROR PQGetMin(const DS_PRIORITY_QUEUE* Pq, void** Data)
{
	if (NULL == Pq)
		return DS_INVALID_PARAMETER;
	return ListFront(Pq->List, Data);
}

DS_ERROR PQGetMax(const DS_PRIORITY_QUEUE* Pq, void** Data)
{
	if (NULL == Pq)
		return DS_INVALID_PARAMETER;
	return ListBack(Pq->List, Data);
}

DS_ERROR PQPopMin(DS_PRIORITY_QUEUE* Pq)
{
	if (NULL == Pq)
		return DS_INVALID_PARAMETER;
	return ListPopFront(Pq->List);
}

DS_ERROR PQPopMax(DS_PRIORITY_QUEUE* Pq)
{
	if (NULL == Pq)
		return DS_INVALID_PARAMETER;
	return ListPopBack(Pq->List);
}

bool PQEmpty(const DS_PRIORITY_QUEUE* Pq)
{
	return NULL == Pq || ListEmpty(Pq->List);
}

unsigned int PQSize(const DS_PRIORITY_QUEUE* Pq)
{
	if(NULL == Pq)
		return 0;
	return ListSize(Pq->List);
}
