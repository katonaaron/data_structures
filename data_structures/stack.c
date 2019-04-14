#include "stack.h"

DS_ERROR StackCreate(DS_STACK** Stack)
{
	if (NULL == Stack)
		return DS_INVALID_PARAMETER;

	PDS_STACK stack = (PDS_STACK)malloc(sizeof(DS_STACK));
	if (NULL == stack)
		return DS_NO_MEMORY;

	DS_ERROR result = ListCreate(&stack->List);
	if (DS_SUCCESS != result)
		return result;

	*Stack = stack;
	return DS_SUCCESS;
}

void StackDestroy(DS_STACK* Stack)
{
	if (Stack)
	{
		ListDestroy(Stack->List);
		free(Stack);
	}
}

DS_ERROR StackPush(DS_STACK* Stack, const void* Data, const size_t DataSize)
{
	if (NULL == Stack)
		return DS_INVALID_PARAMETER;

	return ListPushFront(Stack->List, Data, DataSize);
}

DS_ERROR StackPop(DS_STACK* Stack)
{
	if (NULL == Stack)
		return DS_INVALID_PARAMETER;

	return ListPopFront(Stack->List);
}

DS_ERROR StackTop(const DS_STACK* Stack, void** Data)
{
	if (NULL == Stack)
		return DS_INVALID_PARAMETER;

	return ListFront(Stack->List, Data);
}

bool StackEmpty(const DS_STACK* Stack)
{
	return NULL == Stack || ListEmpty(Stack->List);
}

unsigned int StackSize(const DS_STACK* Stack)
{
	if (Stack)
		return ListSize(Stack->List);
	return 0;
}
