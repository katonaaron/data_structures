// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdio.h>
#include "list.h"
#include "stack.h"

DS_ERROR TestList();
DS_ERROR TestStack();

int main()
{
	DS_ERROR result = DS_SUCCESS;
	

	/*result = TestList();
	if (result)
		return result;*/

	result = TestStack();
	if (result)
		return result;

	return 0;
}

DS_ERROR TestList()
{
	DS_ERROR result = DS_SUCCESS;
	DS_LIST* list = NULL;
	DS_LIST_ITERATOR* it;

	result = ListCreate(&list);
	if (result)
		return result;

	int val[] = { 1, 2, 3 };
	for (int i = 0; i < sizeof(val) / sizeof(val[0]); i++)
	{
		result = ListPushFront(list, &val[i], sizeof(val[i]));
		if (result)
			return result;
	}
	
	int *front, *back;
	result = ListFront(list, &front);
	if (result)
		return result;
	result = ListBack(list, &back);
	if (result)
		return result;
	printf("List front: %d\nList back: %d\n", *front, *back);
	printf("List size: %d\n", ListSize(list));
	printf("List is empty: %s\n", ListEmpty(list) ? "yes" : "no");

	it = ListIteratorCreate(list);
	printf("List:");
	while (ListHasNext(it))
	{
		printf(" %d", *(int*)ListNext(it));
	}
	printf("\n");
	ListIteratorDestroy(it);

	it = ListReverseIteratorCreate(list);
	printf("-List:");
	while (ListHasNext(it))
	{
		printf(" %d", *(int*)ListNext(it));
	}
	printf("\n");
	ListIteratorDestroy(it);

	ListClear(list);
	printf("List size: %d\n", ListSize(list));
	printf("List is empty: %s\n", ListEmpty(list) ? "yes" : "no");

	it = ListIteratorCreate(list);
	printf("List:");
	while (ListHasNext(it))
	{
		printf(" %d", *(int*)ListNext(it));
	}
	printf("\n");
	ListIteratorDestroy(it);

	it = ListReverseIteratorCreate(list);
	printf("-List:");
	while (ListHasNext(it))
	{
		printf(" %d", *(int*)ListNext(it));
	}
	printf("\n");
	ListIteratorDestroy(it);

	for (int i = 0; i < sizeof(val) / sizeof(val[0]); i++)
	{
		result = ListPushFront(list, &val[i], sizeof(val[i]));
		if (result)
			return result;
	}

	result = ListPopBack(list);
	if (result)
		return result;

	result = ListFront(list, &front);
	if (result)
		return result;
	result = ListBack(list, &back);
	if (result)
		return result;
	printf("List front: %d\nList back: %d\n", *front, *back); 
	printf("List size: %d\n", ListSize(list));
	printf("List is empty: %s\n", ListEmpty(list) ? "yes" : "no");

	it = ListIteratorCreate(list);
	printf("List:");
	while (ListHasNext(it))
	{
		printf(" %d", *(int*)ListNext(it));
	}
	printf("\n");
	ListIteratorDestroy(it);

	it = ListReverseIteratorCreate(list);
	printf("-List:");
	while (ListHasNext(it))
	{
		printf(" %d", *(int*)ListNext(it));
	}
	printf("\n");
	ListIteratorDestroy(it);
	
	result = ListPopFront(list);
	if (result)
		return result;

	result = ListFront(list, &front);
	if (result)
		return result;
	result = ListBack(list, &back);
	if (result)
		return result;
	printf("List front: %d\nList back: %d\n", *front, *back); 
	printf("List size: %d\n", ListSize(list));
	printf("List is empty: %s\n", ListEmpty(list) ? "yes" : "no");

	it = ListIteratorCreate(list);
	printf("List:");
	while (ListHasNext(it))
	{
		printf(" %d", *(int*)ListNext(it));
	}
	printf("\n");
	ListIteratorDestroy(it);

	it = ListReverseIteratorCreate(list);
	printf("-List:");
	while (ListHasNext(it))
	{
		printf(" %d", *(int*)ListNext(it));
	}
	printf("\n");
	ListIteratorDestroy(it);

	result = ListPopBack(list);
	if (result)
		return result;

	printf("List size: %d\n", ListSize(list));
	printf("List is empty: %s\n", ListEmpty(list) ? "yes" : "no");

	it = ListIteratorCreate(list);
	printf("List:");
	while (ListHasNext(it))
	{
		printf(" %d", *(int*)ListNext(it));
	}
	printf("\n");
	ListIteratorDestroy(it);

	it = ListReverseIteratorCreate(list);
	printf("-List:");
	while (ListHasNext(it))
	{
		printf(" %d", *(int*)ListNext(it));
	}
	printf("\n");
	ListIteratorDestroy(it);

	ListDestroy(list);
	return DS_SUCCESS;
}

DS_ERROR TestStack()
{
	return DS_SUCCESS;
}
