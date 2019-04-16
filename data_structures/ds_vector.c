#include "ds_vector.h"

static unsigned int VectorGetNewCapacity(const DS_VECTOR* Vector, DS_DIRECTION Direction);
static DS_ERROR VectorCopyData(DS_VECTOR* Vector, const void* SrcData, void** DestData);

DS_ERROR VectorCreate(DS_VECTOR** Vector, size_t DataSize)
{
	if (NULL == Vector || 0 == DataSize)
		return DS_INVALID_PARAMETER;

	PDS_VECTOR vector = (PDS_VECTOR)malloc(sizeof(DS_VECTOR));
	if (NULL == vector)
		return DS_NO_MEMORY;

	vector->Capacity = 0;
	vector->Data = NULL;
	vector->DataSize = DataSize;
	vector->Size = 0;

	*Vector = vector;
	return DS_SUCCESS;
}

void VectorDestroy(DS_VECTOR * Vector)
{
	if (NULL != Vector)
	{
		if (!VectorEmpty(Vector))
			VectorClear(Vector);
		free(Vector);
	}
}

DS_ERROR VectorAssign(DS_VECTOR * Vector, unsigned int newSize, const void* Data)
{
	return DS_SUCCESS;
}

DS_ERROR VectorPushBack(DS_VECTOR * Vector, const void* Data)
{
	if (NULL == Vector || NULL == Data)
		return DS_INVALID_PARAMETER;

	return VectorInsert(Vector, Data, Vector->Size);
}

DS_ERROR VectorPopBack(DS_VECTOR * Vector)
{
	if (NULL == Vector || 0 == Vector->Size)
		return DS_INVALID_PARAMETER;

	return VectorErase(Vector, Vector->Size - 1);
}

DS_ERROR VectorInsert(DS_VECTOR * Vector, const void* Data, unsigned int Position)
{
	if (NULL == Vector || NULL == Data || Position > Vector->Size)
		return DS_INVALID_PARAMETER;

	DS_ERROR result = DS_SUCCESS;

	if (Vector->Capacity * DS_VECTOR_UP_RATIO == Vector->Size)
	{
		result = VectorResize(Vector, VectorGetNewCapacity(Vector, DS_UP));
		if (DS_SUCCESS != result)
			return result;
	}

	for (unsigned int i = Vector->Size; i > Position; i--)
	{
		Vector->Data[i] = Vector->Data[i - 1];
	}


	result = VectorCopyData(Vector, Data, Vector->Data + Position);
	if (DS_SUCCESS != result)
		return result;

	Vector->Size++;
	return result;
}

DS_ERROR VectorErase(DS_VECTOR * Vector, unsigned int Position)
{
	if (NULL == Vector || Position >= Vector->Size)
		return DS_INVALID_PARAMETER;

	DS_ERROR result = DS_SUCCESS;

	free(Vector->Data[Position]);

	for (unsigned int i = Position; i < Vector->Size - 1; i++)
	{
		Vector->Data[i] = Vector->Data[i + 1];
	}

	Vector->Size--;

	if (Vector->Capacity * DS_VECTOR_DOWN_RATIO == Vector->Size)
	{
		result = VectorResize(Vector, VectorGetNewCapacity(Vector, DS_DOWN));
		if (DS_SUCCESS != result)
			return result;
	}

	return result;
}

void VectorClear(DS_VECTOR * Vector)
{
	if (Vector)
	{
		for (unsigned int i = 0; i < Vector->Size; i++)
		{
			free(Vector->Data[i]);
		}
		free(Vector->Data);
		Vector->Data = NULL;
		Vector->Capacity = 0;
		Vector->Size = 0;
	}
}

DS_ERROR VectorAt(const DS_VECTOR * Vector, unsigned int Position, void** Data)
{
	if (NULL == Vector || NULL == Data || Position >= Vector->Size)
		return DS_INVALID_PARAMETER;

	*Data = Vector->Data[Position];
	return DS_SUCCESS;
}

DS_ERROR VectorFront(const DS_VECTOR * Vector, void** Data)
{
	if (NULL == Vector || NULL == Data)
		return DS_INVALID_PARAMETER;

	return VectorAt(Vector, 0, Data);
}

DS_ERROR VectorBack(const DS_VECTOR * Vector, void** Data)
{
	if (NULL == Vector || NULL == Data)
		return DS_INVALID_PARAMETER;

	return VectorAt(Vector, Vector->Size - 1, Data);
}

unsigned int VectorSize(const DS_VECTOR * Vector)
{
	if (NULL != Vector)
		return Vector->Size;
	return 0;
}

DS_ERROR VectorResize(DS_VECTOR * Vector, unsigned int newCapacity)
{
	if (NULL == Vector)
		return DS_INVALID_PARAMETER;

	if (NULL != Vector->Data)
	{
		if (Vector->Size > 0 && newCapacity < Vector->Size)
		{
			for (unsigned int i = Vector->Size - 1; i >= newCapacity; i--)
			{
				free(Vector->Data[i]);
			}
			Vector->Size = newCapacity;
		}
	}

	void** data = (void**)realloc(Vector->Data, newCapacity * sizeof(void*));
	if (NULL == data)
		return DS_NO_MEMORY;

	Vector->Data = data;
	Vector->Capacity = newCapacity;

	return DS_SUCCESS;
}

unsigned int VectorCapacity(const DS_VECTOR * Vector)
{
	if (NULL != Vector)
		return Vector->Capacity;
	return 0;
}

bool VectorEmpty(const DS_VECTOR * Vector)
{
	return VectorSize(Vector) == 0;
}

DS_ERROR VectorReserve(DS_VECTOR * Vector, unsigned int newSize)
{
	if (NULL == Vector)
		return DS_INVALID_PARAMETER;

	if (newSize > Vector->Size)
		return VectorResize(Vector, newSize);
	return DS_SUCCESS;
}

DS_VECTOR_ITERATOR* VectorIteratorCreate(const DS_VECTOR * Vector)
{
	DS_VECTOR_ITERATOR* it = (DS_VECTOR_ITERATOR*)malloc(sizeof(DS_VECTOR_ITERATOR));
	if (it != NULL)
	{
		it->Vector = Vector;
		if (Vector)
		{
			it->Entry = Vector->Data;
		}
		else
		{
			it->Entry = NULL;
		}
		it->Type = DS_ITERATOR;
	}
	return it;
}

DS_VECTOR_ITERATOR* VectorReverseIteratorCreate(const DS_VECTOR * Vector)
{
	DS_VECTOR_ITERATOR* it = (DS_VECTOR_ITERATOR*)malloc(sizeof(DS_VECTOR_ITERATOR));
	if (it != NULL)
	{
		it->Vector = Vector;
		if (Vector)
		{
			it->Entry = Vector->Data + (Vector->Size - 1);
		}
		else
		{
			it->Entry = NULL;
		}
		it->Type = DS_REVERSE_ITERATOR;
	}
	return it;
}

void VectorIteratorDestroy(DS_VECTOR_ITERATOR * Iterator)
{
	free(Iterator);
}

bool VectorHasNext(const DS_VECTOR_ITERATOR * Iterator)
{
	if (NULL == Iterator || NULL == Iterator->Vector || NULL == Iterator->Entry)
		return false;

	if (Iterator->Type == DS_ITERATOR)
		return Iterator->Entry - 1 != Iterator->Vector->Data + (Iterator->Vector->Size - 1);
	else
		return Iterator->Entry + 1 != Iterator->Vector->Data;
}

void* VectorNext(DS_VECTOR_ITERATOR * Iterator)
{
	if (NULL == Iterator || NULL == Iterator->Entry)
		return NULL;

	if (Iterator->Type == DS_ITERATOR)
		return *Iterator->Entry++;
	return *Iterator->Entry--;
}

unsigned int VectorGetNewCapacity(const DS_VECTOR * Vector, DS_DIRECTION Direction)
{
	if (NULL == Vector)
		return 0;

	unsigned int newCapacity = Vector->Capacity;

	switch (Direction)
	{
	case DS_UP:
		newCapacity = Vector->Capacity == 0 ? 1 : (unsigned int)(DS_VECTOR_UP_NEW_SIZE * Vector->Capacity);
		break;
	case DS_DOWN:
		newCapacity = (unsigned int)(DS_VECTOR_DOWN_NEW_SIZE * Vector->Capacity);
	default:
		break;
	}
	return newCapacity;
}

DS_ERROR VectorCopyData(DS_VECTOR * Vector, const void* SrcData, void** DestData)
{
	if (NULL == Vector || NULL == SrcData || NULL == DestData)
		return DS_INVALID_PARAMETER;

	void* data = malloc(Vector->DataSize);
	if (NULL == data)
		return DS_NO_MEMORY;

	memcpy(data, SrcData, Vector->DataSize);

	*DestData = data;
	return DS_SUCCESS;
}
