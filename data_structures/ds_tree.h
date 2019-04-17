#ifndef DS_TREE_H_INCLUDED
#define DS_TREE_H_INCLUDED

typedef struct _DS_TREE_NODE
{
	void* Key;
	void* Data;
	struct _DS_TREE_NODE* Left;
	struct _DS_TREE_NODE* Right;
}DS_TREE_NODE, *PDS_TREE_NODE;

typedef struct _DS_TREE
{
	unsigned int Size;
	DS_TREE_NODE* Root;
}DS_TREE, *PDS_TREE;

#endif // !DS_TREE_H_INCLUDED

