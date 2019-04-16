#include "ds_list.h"

static DS_ERROR ListEntryCreate(
	DS_LIST_ENTRY** Entry,
	const void* Data, 
	const size_t DataSize, 
	DS_LIST_ENTRY * Next, 
	DS_LIST_ENTRY * Prev
);
static void ListEntryDestroy(DS_LIST_ENTRY* Entry);


DS_ERROR ListCreate(DS_LIST** List)
{
	if (NULL == List)
		return DS_INVALID_PARAMETER;

	PDS_LIST list = (PDS_LIST)malloc(sizeof(DS_LIST));
	if (NULL == list)
		return DS_NO_MEMORY;

	list->Head.Data = NULL;
	list->Head.Next = &list->Head;
	list->Head.Prev = &list->Head;
	list->Size = 0;

	*List = list;
	return DS_SUCCESS;
}

void ListDestroy(DS_LIST* List)
{
	if (List)
	{
		ListClear(List);
		free(List);
	}
}

void ListClear(DS_LIST* List)
{
	if (List)
	{
		PDS_LIST_ENTRY entry = List->Head.Next, tmp;
		while (entry != &List->Head)
		{
			tmp = entry;
			entry = entry->Next;
			ListEntryDestroy(tmp);
		}
		List->Size = 0;
		List->Head.Next = List->Head.Prev = &List->Head;
	}
}

DS_ERROR ListPushFront(DS_LIST* List, const void* Data, const size_t DataSize)
{
	if (NULL == List)
		return DS_INVALID_PARAMETER;

	PDS_LIST_ENTRY entry = NULL;
	DS_ERROR result = DS_SUCCESS;

	result = ListEntryCreate(&entry, Data, DataSize, List->Head.Next, &List->Head);
	if (result)
		return result;

	entry->Prev->Next = entry;
	entry->Next->Prev = entry;

	List->Size++;
	return DS_SUCCESS;
}

DS_ERROR ListPopFront(DS_LIST* List)
{
	if (NULL == List)
		return DS_INVALID_PARAMETER;
	if (List->Size == 0)
		return DS_NOT_FOUND;

	PDS_LIST_ENTRY entry = List->Head.Next;
	List->Head.Next = entry->Next;
	List->Head.Next->Prev = &List->Head;
	ListEntryDestroy(entry);

	List->Size--;
	return DS_SUCCESS;
}

DS_ERROR ListPushBack(DS_LIST* List, const void* Data, const size_t DataSize)
{
	if (NULL == List)
		return DS_INVALID_PARAMETER;

	PDS_LIST_ENTRY entry = NULL;
	DS_ERROR result = DS_SUCCESS;

	result = ListEntryCreate(&entry, Data, DataSize, &List->Head, List->Head.Prev);
	if (result)
		return result;

	entry->Prev->Next = entry;
	entry->Next->Prev = entry;

	List->Size++;
	return DS_SUCCESS;
}

DS_ERROR ListPopBack(DS_LIST* List)
{
	if (NULL == List)
		return DS_INVALID_PARAMETER;
	if (List->Size == 0)
		return DS_NOT_FOUND;

	PDS_LIST_ENTRY entry = List->Head.Prev;
	List->Head.Prev = entry->Prev;
	List->Head.Prev->Next = &List->Head;
	ListEntryDestroy(entry);

	List->Size--;
	return DS_SUCCESS;
}

DS_ERROR ListFront(const DS_LIST* List, void** Data)
{
	if (NULL == List || NULL == Data)
		return DS_INVALID_PARAMETER;
	if (List->Size == 0)
		return DS_NOT_FOUND;

	*Data = List->Head.Next->Data;

	return DS_SUCCESS;
}

DS_ERROR ListBack(const DS_LIST* List, void** Data)
{
	if (NULL == List || NULL == Data)
		return DS_INVALID_PARAMETER;
	if (List->Size == 0)
		return DS_NOT_FOUND;

	*Data = List->Head.Prev->Data;

	return DS_SUCCESS;
}

bool ListEmpty(const DS_LIST* List)
{
	return NULL == List || 0 == List->Size;
}

unsigned int ListSize(const DS_LIST* List)
{
	if (List)
		return List->Size;
	return 0;
}

DS_ERROR ListEntryCreate(
	DS_LIST_ENTRY** Entry,
	const void* Data,
	const size_t DataSize,
	DS_LIST_ENTRY * Next,
	DS_LIST_ENTRY * Prev
)
{
	if (NULL == Entry)
		return DS_INVALID_PARAMETER;

	PDS_LIST_ENTRY entry = (PDS_LIST_ENTRY)malloc(sizeof(DS_LIST_ENTRY));
	if (NULL == entry)
		return DS_NO_MEMORY;
	
	entry->Data = malloc(DataSize);
	if (NULL == entry->Data)
	{
		free(entry);
		return DS_NO_MEMORY;
	}

	memcpy(entry->Data, Data, DataSize);
	entry->Next = Next;
	entry->Prev = Prev;

	*Entry = entry;
	return DS_SUCCESS;
}

void ListEntryDestroy(DS_LIST_ENTRY* Entry)
{
	if (Entry)
	{
		free(Entry->Data);
		free(Entry);
	}
}

DS_LIST_ITERATOR* ListIteratorCreate(const DS_LIST* List)
{
	DS_LIST_ITERATOR* it = (DS_LIST_ITERATOR*)malloc(sizeof(DS_LIST_ITERATOR));
	if (it != NULL)
	{
		it->List = List;
		if (List)
		{
			it->Entry = List->Head.Next;
		}
		else
		{
			it->Entry = NULL;
		}
		it->Type = DS_ITERATOR;
	}		
	return it;
}

DS_LIST_ITERATOR* ListReverseIteratorCreate(const DS_LIST* List)
{
	DS_LIST_ITERATOR* it = (DS_LIST_ITERATOR*)malloc(sizeof(DS_LIST_ITERATOR));
	if (it != NULL)
	{
		it->List = List;
		if (List)
		{
			it->Entry = List->Head.Prev;
		}
		else
		{
			it->Entry = NULL;
		}
		it->Type = DS_REVERSE_ITERATOR;
	}
	return it;
}

void ListIteratorDestroy(DS_LIST_ITERATOR* Iterator)
{
	free(Iterator);
}

bool ListHasNext(const DS_LIST_ITERATOR * Iterator)
{
	return NULL != Iterator && NULL != Iterator->List && Iterator->Entry != &Iterator->List->Head;
}

void* ListNext(DS_LIST_ITERATOR* Iterator)
{
	if (NULL == Iterator || NULL == Iterator->Entry)
		return NULL;

	if (Iterator->Type == DS_ITERATOR)
	{
		Iterator->Entry = Iterator->Entry->Next;
		return Iterator->Entry->Prev->Data;
	}

	Iterator->Entry = Iterator->Entry->Prev;
	return Iterator->Entry->Next->Data;
}
