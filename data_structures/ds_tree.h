#ifndef DS_TREE_H_INCLUDED
#define DS_TREE_H_INCLUDED

#include "ds_common.h"
#include "ds_stack.h"

typedef struct _DS_TREE_NODE
{
	void* Key;
	void* Data;
	struct _DS_TREE_NODE* Parent;
	struct _DS_TREE_NODE* Left;
	struct _DS_TREE_NODE* Right;
}DS_TREE_NODE, * PDS_TREE_NODE;

typedef struct _DS_TREE
{
	unsigned int Size;
	DS_TREE_NODE* Root;
	DS_COMPARE_FUNCTION Compare;
}DS_TREE, * PDS_TREE;

typedef struct _DS_TREE_ITERATOR
{
	const DS_TREE* Tree;
	DS_STACK* Stack;
}DS_TREE_ITERATOR, *PDS_TREE_ITERATOR;

DS_ERROR TreeCreate(DS_TREE** Tree, DS_COMPARE_FUNCTION Compare);
void TreeDestroy(DS_TREE* Tree);

DS_ERROR TreeInsert(DS_TREE* Tree, const void* Key, size_t KeySize, const void* Data, size_t DataSize);
DS_ERROR TreeErase(DS_TREE* Tree, const void* Key);
void TreeClear(DS_TREE* Tree);

DS_ERROR TreeFind(const DS_TREE* Tree, const void* Key, void** Data);
//unsigned int TreeCount(const DS_TREE* Tree, const void* Key);

unsigned int TreeSize(const DS_TREE* Tree);
bool TreeEmpty(const DS_TREE* Tree);

DS_ERROR TreeGetMinNode(const DS_TREE* Tree, DS_TREE_NODE** Node);
DS_ERROR TreeGetMaxNode(const DS_TREE* Tree, DS_TREE_NODE** Node);

DS_ERROR TreeCreateIterator(const DS_TREE* Tree, DS_ITERATOR_TYPE Type, DS_TREE_ITERATOR** Iterator);
void TreeDestroyIterator(DS_TREE_ITERATOR* Iterator);
bool TreeHasNext(const DS_TREE_ITERATOR* Iterator);
DS_ERROR TreeNext(DS_TREE_ITERATOR* Iterator, void** Data);


#endif // !DS_TREE_H_INCLUDED

