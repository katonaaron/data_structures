#ifndef DS_LIST_H_INCLUDED
#define DS_LIST_H_INCLUDED

#include "ds_common.h"

typedef struct _DS_LIST_ENTRY
{
	void* Data;
	struct _DS_LIST_ENTRY* Next;
	struct _DS_LIST_ENTRY* Prev;
} DS_LIST_ENTRY, *PDS_LIST_ENTRY;

typedef struct _DS_LIST
{
	DS_LIST_ENTRY Head;
	unsigned int Size;
} DS_LIST, *PDS_LIST;

typedef struct _DS_LIST_ITERATOR
{
	DS_ITERATOR_TYPE Type;
	const DS_LIST* List;
	DS_LIST_ENTRY* Entry;
}DS_LIST_ITERATOR, *PDS_LIST_ITERATOR;


DS_ERROR ListCreate(DS_LIST** List);
void ListDestroy(DS_LIST* List);
void ListClear(DS_LIST* List);

DS_ERROR ListPushFront(DS_LIST* List, const void* Data, const size_t DataSize);
DS_ERROR ListPopFront(DS_LIST* List);
DS_ERROR ListPushBack(DS_LIST* List, const void* Data, const size_t DataSize);
DS_ERROR ListPopBack(DS_LIST* List);

DS_ERROR ListFront(const DS_LIST* List, void** Data);
DS_ERROR ListBack(const DS_LIST* List, void** Data);

bool ListEmpty(const DS_LIST* List);
unsigned int ListSize(const DS_LIST* List);

DS_ERROR ListInsert(DS_LIST* List, const DS_COMPARE_FUNCTION Compare, const void* Data, const size_t DataSize);
DS_ERROR ListErase(DS_LIST* List, const DS_COMPARE_FUNCTION Compare, const void* Data);
DS_ERROR ListFind(const DS_LIST* List, const DS_COMPARE_FUNCTION Compare, const void* Data, DS_LIST_ENTRY** Entry);

DS_LIST_ITERATOR* ListIteratorCreate(const DS_LIST* List);
DS_LIST_ITERATOR* ListReverseIteratorCreate(const DS_LIST* List);
void ListIteratorDestroy(DS_LIST_ITERATOR* Iterator);
bool ListHasNext(const DS_LIST_ITERATOR * Iterator);
void* ListNext(DS_LIST_ITERATOR* Iterator);

#endif // !DS_LIST_H_INCLUDED
