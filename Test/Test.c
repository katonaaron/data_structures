// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdio.h>
#include "list.h"

int main()
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

	result = ListPopFront(list);
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
	return 0;
}