// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdio.h>
#include "ds_list.h"
#include "ds_stack.h"
#include "ds_queue.h"
#include "ds_vector.h"
#include "ds_tree.h"
#include "ds_priority_queue.h"

DS_ERROR TestList();
DS_ERROR TestStack();
DS_ERROR TestQueue();
DS_ERROR TestVector();
DS_ERROR TestTree();
DS_ERROR TestPriorityQueue();

DS_ERROR PrintList(DS_LIST* List);
DS_ERROR PrintStack(DS_STACK* Stack);
DS_ERROR PrintQueue(DS_QUEUE* Queue);
DS_ERROR PrintVector(DS_VECTOR* Vector);
DS_ERROR PrintTree(DS_TREE* Tree);
DS_ERROR PrintPriorityQueue(DS_PRIORITY_QUEUE* Pq);

int main()
{
	DS_ERROR result = DS_SUCCESS;


	/*result = TestList();
	if (result)
	{
		printf("Error: %s\n", DSErrorGetMessage(result));
		return -1;
	}
*/
	/*result = TestStack();
	if (result)
		return result;*/

		/*result = TestQueue();
		if (result)
		{
			printf("Error: %s\n", DSErrorGetMessage(result));
			return -1;
		}*/

		/*result = TestVector();
		if (result)
		{
			printf("Error: %s\n", DSErrorGetMessage(result));
			return -1;
		}*/

	/*result = TestTree();
	if (result)
	{
		printf("Error: %s\n", DSErrorGetMessage(result));
		return -1;
	}*/

	result = TestPriorityQueue();
	if (result)
	{
		printf("Error: %s\n", DSErrorGetMessage(result));
		return -1;
	}

	return 0;
}

int CompareInt(const int* A, const int* B)
{
	return *A > * B ? 1 : *A < *B ? -1 : 0;
}

DS_ERROR TestList()
{
	DS_ERROR result = DS_SUCCESS;
	DS_LIST* list = NULL;

	result = ListCreate(&list);
	if (result)
		return result;

	int val[] = { 34, 10, 96, 0, 2, 3 ,1, 10 };
	for (int i = 0; i < sizeof(val) / sizeof(val[0]); i++)
	{
		result = ListPushFront(list, &val[i], sizeof(val[i]));
		if (result)
			return result;
	}
	result = PrintList(list);
	if (result)
		return result;

	ListClear(list);
	result = PrintList(list);
	if (result)
		return result;

	for (int i = 0; i < sizeof(val) / sizeof(val[0]); i++)
	{
		result = ListPushFront(list, &val[i], sizeof(val[i]));
		if (result)
			return result;
	}

	result = PrintList(list);
	if (result)
		return result;

	result = ListPopBack(list);
	if (result)
		return result;

	result = PrintList(list);
	if (result)
		return result;

	result = ListPopFront(list);
	if (result)
		return result;

	result = PrintList(list);
	if (result)
		return result;

	result = ListPopBack(list);
	if (result)
		return result;

	result = PrintList(list);
	if (result)
		return result;

	ListClear(list);
	result = PrintList(list);
	if (result)
		return result;

	for (int i = 0; i < sizeof(val) / sizeof(val[0]); i++)
	{
		result = ListInsert(list, (DS_COMPARE_FUNCTION)CompareInt, &val[i], sizeof(val[i]));
		if (result)
			return result;
	}
	result = PrintList(list);
	if (result)
		return result;

	result = ListErase(list, (DS_COMPARE_FUNCTION)CompareInt, &val[2]);
	if (result)
		return result;

	result = PrintList(list);
	if (result)
		return result;

	result = ListInsert(list, (DS_COMPARE_FUNCTION)CompareInt, &val[2], sizeof(val[2]));
	if (result)
		return result;
	result = PrintList(list);
	if (result)
		return result;

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

DS_ERROR TestTree()
{
	DS_ERROR result = DS_SUCCESS;
	PDS_TREE tree = NULL;
	char* key[] = { "g", "b", "ahahahhaa", "l", "k" };
	int val[] = { 1, 2, 3, 4, 5 };

	result = TreeCreate(&tree, (DS_COMPARE_FUNCTION)strcmp);
	if (DS_SUCCESS != result)
		return result;

	for (int i = 0; i < sizeof(key) / sizeof(key[0]); i++)
	{
		result = TreeInsert(tree, key[i], (strlen(key[i]) + 1) * sizeof(char), &val[i], sizeof(val[i]));
		if (DS_SUCCESS != result)
			return result;
	}

	result = PrintTree(tree);
	if (DS_SUCCESS != result)
		return result;

	TreeClear(tree);
	result = PrintTree(tree);
	if (DS_SUCCESS != result)
		return result;

	for (int i = 0; i < sizeof(key) / sizeof(key[0]); i++)
	{
		result = TreeInsert(tree, key[i], (strlen(key[i]) + 1) * sizeof(char), &val[i], sizeof(val[i]));
		if (DS_SUCCESS != result)
			return result;
	}
	result = PrintTree(tree);
	if (DS_SUCCESS != result)
		return result;

	int* data;
	result = TreeFind(tree, "k", &data);
	if (DS_SUCCESS != result)
		return result;
	printf("Found data: %d\n\n", *(int*)data);

	/*while (!TreeEmpty(tree))
	{
		result = TreeErase(tree, tree->Root->Key);
		if (DS_SUCCESS != result)
			return result;
		result = PrintTree(tree);
		if (DS_SUCCESS != result)
			return result;
	}*/

	DS_TREE_ITERATOR* it = NULL;
	result = TreeCreateIterator(tree, DS_INORDER_ITERATOR, &it);
	if (DS_SUCCESS != result)
		return result;

	printf("tree: ");
	while (TreeHasNext(it))
	{
		result = TreeNext(it, &data);
		if (DS_SUCCESS != result)
			return result;

		printf(" %d", *data);
	}
	printf("\n");
	TreeDestroyIterator(it);

	TreeDestroy(tree);

	result = TreeCreateIterator(tree, DS_INORDER_ITERATOR, &it);
	if (DS_SUCCESS != result)
		return result;

	/*printf("tree: ");
	while (TreeHasNext(it))
	{
		result = TreeNext(it, &data);
		if (DS_SUCCESS != result)
			return result;

		printf(" %d", *data);
	}
	printf("\n");
	TreeDestroyIterator(it);*/

	PrintTree(tree);

	TreeDestroy(tree);
	return result;
}

DS_ERROR TestPriorityQueue()
{
	DS_ERROR result = DS_SUCCESS;
	DS_PRIORITY_QUEUE* pq = NULL;
	int val[] = { 9, 2, 4, 6, 8, 13 };

	result = PQCreate(&pq, CompareInt);
	if (DS_SUCCESS != result)
		return result;

	for (int i = 0; i < sizeof(val) / sizeof(val[0]); i++)
	{
		result = PQInsert(pq, &val[i], sizeof(val[i]));
		if (result)
			return result;
	}
	result = PrintPriorityQueue(pq);
	if (DS_SUCCESS != result)
		return result;

	for (int i = 0; i < 3; i++)
	{
		result = PQPopMin(pq);
		if (DS_SUCCESS != result)
			return result;
		result = PrintPriorityQueue(pq);
		if (DS_SUCCESS != result)
			return result;

		result = PQPopMax(pq);
		if (DS_SUCCESS != result)
			return result;
		result = PrintPriorityQueue(pq);
		if (DS_SUCCESS != result)
			return result;
	}

	PQDestroy(pq);

	return result;
}

DS_ERROR PrintList(DS_LIST * List)
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

DS_ERROR PrintStack(DS_STACK * Stack)
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

DS_ERROR PrintQueue(DS_QUEUE * Queue)
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

DS_ERROR PrintVector(DS_VECTOR * Vector)
{
	if (NULL == Vector)
		return DS_INVALID_PARAMETER;

	DS_ERROR result = DS_SUCCESS;
	DS_VECTOR_ITERATOR * it;
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

void printRec(DS_TREE_NODE * Root)
{
	if (NULL != Root)
	{
		printf(" (%s,%d)", (char*)Root->Key, *(int*)Root->Data);
		printRec(Root->Left);
		printRec(Root->Right);
	}
}

DS_ERROR PrintTree(DS_TREE * Tree)
{
	if (Tree == NULL)
		return DS_INVALID_PARAMETER;

	DS_ERROR result = DS_SUCCESS;
	DS_TREE_NODE* minNode, * maxNode;

	printf("Tree (preorder):");
	printRec(Tree->Root);
	printf("\n");
	printf("Tree size: %d\n", TreeSize(Tree));

	if (TreeEmpty(Tree))
	{
		printf("Tree empty: yes\n");
	}
	else
	{
		printf("Tree empty: no\n");
		
		result = TreeGetMinNode(Tree, &minNode);
		if (DS_SUCCESS != result)
			return result;
		result = TreeGetMaxNode(Tree, &maxNode);
		if (DS_SUCCESS != result)
			return result;

		printf("Min node: %s\nMax node: %s\n", (char*)minNode->Key, (char*)maxNode->Key);
	}
	printf("\n");

	return DS_SUCCESS;
}

DS_ERROR PrintPriorityQueue(DS_PRIORITY_QUEUE* Pq)
{
	if (NULL == Pq)
		return DS_INVALID_PARAMETER;

	DS_ERROR result = DS_SUCCESS;
	DS_LIST_ITERATOR* it = NULL;
	int* min, * max;

	it = ListIteratorCreate(Pq->List);
	printf("Priority queue:");
	while (ListHasNext(it))
	{
		printf(" %d", *(int*)ListNext(it));
	}
	printf("\n");
	ListIteratorDestroy(it);

	printf("PQ size: %u\n", PQSize(Pq));
	if (PQEmpty(Pq))
	{
		printf("PQ empty: yes\n");
	}
	else
	{
		printf("PQ empty: no\n");

		result = PQGetMin(Pq, &min);
		if (DS_SUCCESS != result)
			return result;

		result = PQGetMax(Pq, &max);
		if (DS_SUCCESS != result)
			return result;

		printf("Min node: %d\nMax node: %d\n", *min, *max);
	}
	return result;
}
