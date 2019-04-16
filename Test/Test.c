// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdio.h>
#include "ds_list.h"
#include "ds_stack.h"
#include "ds_queue.h"
#include "ds_vector.h"

DS_ERROR TestList();
DS_ERROR TestStack();
DS_ERROR TestQueue();
DS_ERROR TestVector();

DS_ERROR PrintList(DS_LIST* List);
DS_ERROR PrintStack(DS_STACK* Stack);
DS_ERROR PrintQueue(DS_QUEUE* Queue);
DS_ERROR PrintVector(DS_VECTOR* Vector);

int main()
{
	DS_ERROR result = DS_SUCCESS;


	/*result = TestList();
	if (result)
		return result;

	result = TestStack();
	if (result)
		return result;*/

	/*result = TestQueue();
	if (result)
	{
		printf("Error: %s\n", DSErrorGetMessage(result));
		return -1;
	}*/

	result = TestVector();
	if (result)
	{
		printf("Error: %s\n", DSErrorGetMessage(result));
		return -1;
	}

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

	int* front, * back;
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
	return result;
}

DS_ERROR TestStack()
{
	DS_ERROR result = DS_SUCCESS;
	DS_STACK* stack = NULL;
	int val[] = { 9, 2, 4, 6, 8, 13 };

	result = StackCreate(&stack);
	if (result)
		return result;

	for (int i = 0; i < sizeof(val) / sizeof(val[0]); i++)
	{
		result = StackPush(stack, &val[i], sizeof(val[i]));
		if (result)
			return result;
	}

	result = PrintStack(stack);
	if (result)
		return result;

	int i = 0;
	while (!StackEmpty(stack))
	{
		result = StackPop(stack);
		if (result)
			return result;
		result = PrintStack(stack);
		if (result)
			return result;

		if (i == 3)
		{
			result = StackPush(stack, &val[0], sizeof(val[0]));
			if (result)
				return result;
			result = PrintStack(stack);
			if (result)
				return result;
		}
		i++;
	}

	result = StackPush(stack, &val[4], sizeof(val[4]));
	if (result)
		return result;
	result = PrintStack(stack);
	if (result)
		return result;
	return result;
}

DS_ERROR TestQueue()
{
	DS_ERROR result = DS_SUCCESS;
	DS_QUEUE* queue = NULL;
	int val[] = { 9, 2, 4, 6, 8, 13 };

	result = QueueCreate(&queue);
	if (result)
		return result;

	for (int i = 0; i < sizeof(val) / sizeof(val[0]); i++)
	{
		result = QueuePush(queue, &val[i], sizeof(val[i]));
		if (result)
			return result;
	}

	result = PrintQueue(queue);
	if (result)
		return result;

	int i = 0;
	while (!QueueEmpty(queue))
	{
		result = QueuePop(queue);
		if (result)
			return result;
		result = PrintQueue(queue);
		if (result)
			return result;

		if (i == 3 || i == 4)
		{
			result = QueuePush(queue, &val[0], sizeof(val[0]));
			if (result)
				return result;
			result = PrintQueue(queue);
			if (result)
				return result;
		}
		i++;
	}

	result = QueuePush(queue, &val[4], sizeof(val[4]));
	if (result)
		return result;
	result = PrintQueue(queue);
	if (result)
		return result;
	return result;
}

DS_ERROR TestVector()
{
	DS_ERROR result = DS_SUCCESS;
	DS_VECTOR* vector = NULL;
	int val[] = { 9, 2, 4, 6, 8, 13 };

	result = VectorCreate(&vector, sizeof(int));
	if (DS_SUCCESS != result)
		return result;

	for (int i = 0; i < sizeof(val) / sizeof(val[0]); i++)
	{
		result = VectorPushBack(vector, &val[i]);
		if (result)
			return result;
	}
	result = PrintVector(vector);
	if (result)
		return result;

	 VectorClear(vector);
	if (result)
		return result;

	result = PrintVector(vector);
	if (result)
		return result;

	for (int i = 0; i < sizeof(val) / sizeof(val[0]); i++)
	{
		result = VectorPushBack(vector, &val[i]);
		if (result)
			return result;
	}
	result = PrintVector(vector);
	if (result)
		return result;

	int* data = NULL;
	result = VectorAt(vector, 1, &data);
	if (result)
		return result;
	printf("Found data: %d\n", *data);
	*data = 12;
	result = PrintVector(vector);
	if (result)
		return result;

	result = VectorResize(vector, 1);
	if (result)
		return result;
	result = PrintVector(vector);
	if (result)
		return result;

	while (!VectorEmpty(vector))
	{
		result = VectorPopBack(vector);
		if (result)
			return result;
		result = PrintVector(vector);
		if (result)
			return result;
	}

	result = VectorPushBack(vector, &val[2]);
	if (result)
		return result;
	result = PrintVector(vector);
	if (result)
		return result;

	result = VectorReserve(vector, 1000);
	if (result)
		return result;
	result = PrintVector(vector);
	if (result)
		return result;

	VectorDestroy(vector);
	return result;
}

DS_ERROR PrintList(DS_LIST* List)
{
	DS_LIST_ITERATOR* it;
	DS_ERROR result = DS_SUCCESS;
	int* front, * back;

	it = ListIteratorCreate(List);
	printf("List:");
	while (ListHasNext(it))
	{
		printf(" %d", *(int*)ListNext(it));
	}
	printf("\n");
	ListIteratorDestroy(it);

	it = ListReverseIteratorCreate(List);
	printf("List (reverse):");
	while (ListHasNext(it))
	{
		printf(" %d", *(int*)ListNext(it));
	}
	printf("\n");
	ListIteratorDestroy(it);

	printf("List size: %d\n", ListSize(List));

	if (ListEmpty(List))
	{
		printf("List is empty: yes\n");
	}
	else
	{
		result = ListFront(List, &front);
		if (result)
			return result;
		result = ListBack(List, &back);
		if (result)
			return result;
		printf("List is empty: no\n");
		printf("List front: %d\nList back: %d\n", *front, *back);
	}
	return DS_SUCCESS;
}

DS_ERROR PrintStack(DS_STACK* Stack)
{
	DS_LIST_ITERATOR* it;
	DS_ERROR result = DS_SUCCESS;
	int* top;

	it = ListIteratorCreate(Stack->List);
	printf("Stack:");
	while (ListHasNext(it))
	{
		printf(" %d", *(int*)ListNext(it));
	}
	printf("\n");
	ListIteratorDestroy(it);

	it = ListReverseIteratorCreate(Stack->List);
	printf("Stack (reverse):");
	while (ListHasNext(it))
	{
		printf(" %d", *(int*)ListNext(it));
	}
	printf("\n");
	ListIteratorDestroy(it);

	printf("Stack size: %d\n", StackSize(Stack));

	if (StackEmpty(Stack))
	{
		printf("Stack is empty: yes\n");
	}
	else
	{
		result = StackTop(Stack, &top);
		if (result)
			return result;
		printf("Stack is empty: no\n");
		printf("Stack top: %d\n", *top);
	}
	printf("\n");
	return DS_SUCCESS;
}

DS_ERROR PrintQueue(DS_QUEUE* Queue)
{
	if (NULL == Queue)
		return DS_INVALID_PARAMETER;

	DS_LIST_ITERATOR * it;
	DS_ERROR result = DS_SUCCESS;
	int* front, *back;

	it = ListIteratorCreate(Queue->List);
	printf("Queue:");
	while (ListHasNext(it))
	{
		printf(" %d", *(int*)ListNext(it));
	}
	printf("\n");
	ListIteratorDestroy(it);

	it = ListReverseIteratorCreate(Queue->List);
	printf("Queue (reverse):");
	while (ListHasNext(it))
	{
		printf(" %d", *(int*)ListNext(it));
	}
	printf("\n");
	ListIteratorDestroy(it);

	printf("Queue size: %d\n", QueueSize(Queue));

	if (QueueEmpty(Queue))
	{
		printf("Queue is empty: yes\n");
	}
	else
	{
		result = QueueFront(Queue, &front);
		if (result)
			return result;
		result = QueueBack(Queue, &back);
		if (result)
			return result;
		printf("Queue is empty: no\n");
		printf("Queue front: %d\nQueue back: %d\n", *front, *back);
	}
	printf("\n");
	return DS_SUCCESS;
}

DS_ERROR PrintVector(DS_VECTOR* Vector)
{
	if (NULL == Vector)
		return DS_INVALID_PARAMETER;

	DS_ERROR result = DS_SUCCESS;
	DS_VECTOR_ITERATOR* it;
	int* front, *back;

	printf("Vector:");
	it = VectorIteratorCreate(Vector);
	while (VectorHasNext(it))
	{
		printf(" %d", *(int*)VectorNext(it));
	}
	VectorIteratorDestroy(it);
	printf("\n");

	printf("Vector (reverse):");
	it = VectorReverseIteratorCreate(Vector);
	while (VectorHasNext(it))
	{
		printf(" %d", *(int*)VectorNext(it));
	}
	VectorIteratorDestroy(it);
	printf("\n");

	printf("Vector size: %d\n", VectorSize(Vector));
	printf("Vector capacity: %d\n", VectorCapacity(Vector));
	if (VectorEmpty(Vector))
	{
		printf("Vector empty: yes\n");
	}
	else
	{
		printf("Vector empty: no\n");
		result = VectorFront(Vector, &front);
		if (DS_SUCCESS != result)
			return result;
		result = VectorBack(Vector, &back);
		if (DS_SUCCESS != result)
			return result;

		printf("Vector front: %d\nVector back: %d\n", *(int*)front, *(int*)back);
	}

	return DS_SUCCESS;
}
