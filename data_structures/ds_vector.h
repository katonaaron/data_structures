#ifndef DS_VECTOR_H_INCLUDED
#define DS_VECTOR_H_INCLUDED

#include "ds_common.h"

#define DS_VECTOR_UP_RATIO 1
#define DS_VECTOR_UP_NEW_SIZE 2
#define DS_VECTOR_DOWN_RATIO 0.25
#define DS_VECTOR_DOWN_NEW_SIZE 0.5

typedef struct _DS_VECTOR
{
	unsigned int Size;
	unsigned int Capacity;
	size_t DataSize;
	void** Data;
}DS_VECTOR, * PDS_VECTOR;

typedef struct _DS_VECTOR_ITERATOR
{
	DS_ITERATOR_TYPE Type;
	const DS_VECTOR* Vector;
	void** Entry;
}DS_VECTOR_ITERATOR, * PDS_VECTOR_ITERATOR;

DS_ERROR VectorCreate(DS_VECTOR** Vector, size_t DataSize);
void VectorDestroy(DS_VECTOR* Vector);

DS_ERROR VectorAssign(DS_VECTOR* Vector, unsigned int newSize, const void* Data);
DS_ERROR VectorPushBack(DS_VECTOR* Vector, const void* Data);
DS_ERROR VectorPopBack(DS_VECTOR* Vector);
DS_ERROR VectorInsert(DS_VECTOR* Vector, const void* Data, unsigned int Position);
DS_ERROR VectorErase(DS_VECTOR* Vector, unsigned int Position);
void VectorClear(DS_VECTOR* Vector);

DS_ERROR VectorAt(const DS_VECTOR* Vector, unsigned int Position, void** Data);
DS_ERROR VectorFront(const DS_VECTOR* Vector, void** Data);
DS_ERROR VectorBack(const DS_VECTOR* Vector, void** Data);

unsigned int VectorSize(const DS_VECTOR* Vector);
unsigned int VectorCapacity(const DS_VECTOR* Vector);
bool VectorEmpty(const DS_VECTOR* Vector);

DS_ERROR VectorResize(DS_VECTOR* Vector, unsigned int newCapacity);
DS_ERROR VectorReserve(DS_VECTOR* Vector, unsigned int newSize);


DS_VECTOR_ITERATOR* VectorIteratorCreate(const DS_VECTOR* Vector);
DS_VECTOR_ITERATOR* VectorReverseIteratorCreate(const DS_VECTOR* Vector);
void VectorIteratorDestroy(DS_VECTOR_ITERATOR* Iterator);
bool VectorHasNext(const DS_VECTOR_ITERATOR* Iterator);
void* VectorNext(DS_VECTOR_ITERATOR* Iterator);

#endif // !DS_VECTOR_H_INCLUDED
