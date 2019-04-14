#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "list.h"

typedef struct _DS_STACK
{
	DS_LIST* List;
}DS_STACK, *PDS_STACK;

DS_ERROR StackCreate(DS_STACK** Stack);
void StackDestroy(DS_STACK* Stack);

DS_ERROR StackPush(DS_STACK* Stack, const void* Data, const size_t DataSize);
DS_ERROR StackPop(DS_STACK* Stack, void** Data);
DS_ERROR StackTop(DS_STACK* Stack, void** Data);

#endif // !STACK_H_INCLUDED
