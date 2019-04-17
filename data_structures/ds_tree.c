#include "ds_tree.h"

static DS_ERROR TreeNodeCreate(DS_TREE_NODE** Node, const void* Key, size_t KeySize, const void* Data, size_t DataSize);
static void TreeNodeDestroy(DS_TREE_NODE* Node, bool Recursively);
static DS_ERROR TreeFindNode(const DS_TREE* Tree, const void* Key, DS_TREE_NODE** Node);
static DS_ERROR TreeNodeGetMin(DS_TREE_NODE* Root, DS_TREE_NODE** Node);
static DS_ERROR TreeNodeGetMax(DS_TREE_NODE* Root, DS_TREE_NODE** Node);

DS_ERROR TreeCreate(DS_TREE** Tree, DS_COMPARE_FUNCTION Compare)
{
	if (NULL == Tree || NULL == Compare)
		return DS_INVALID_PARAMETER;

	PDS_TREE tree = (PDS_TREE)malloc(sizeof(DS_TREE));
	if (NULL == tree)
		return DS_NO_MEMORY;

	tree->Size = 0;
	tree->Root = NULL;
	tree->Compare = Compare;

	*Tree = tree;
	return DS_SUCCESS;
}

void TreeDestroy(DS_TREE * Tree)
{
	if (NULL != Tree)
	{
		TreeClear(Tree);
		free(Tree);
	}
}

DS_ERROR TreeInsert(DS_TREE * Tree, const void* Key, size_t KeySize, const void* Data, size_t DataSize)
{
	if (NULL == Tree || NULL == Key || 0 == KeySize)
		return DS_INVALID_PARAMETER;

	PDS_TREE_NODE node = NULL, it;
	DS_ERROR result = DS_SUCCESS;

	result = TreeNodeCreate(&node, Key, KeySize, Data, DataSize);
	if (DS_SUCCESS != result)
		return result;

	if (NULL == Tree->Root)
	{
		Tree->Root = node;
	}
	else
	{
		it = Tree->Root;
		while (NULL == node->Parent)
		{
			if (Tree->Compare(it->Key, Key) >= 0)
			{
				if (it->Left == NULL)
				{
					node->Parent = it;
					it->Left = node;
				}
				else
				{
					it = it->Left;
				}
			}
			else
			{
				if (it->Right == NULL)
				{
					node->Parent = it;
					it->Right = node;
				}
				else
				{
					it = it->Right;
				}
			}
		}
	}

	Tree->Size++;
	return result;
}

DS_ERROR TreeErase(DS_TREE * Tree, const void* Key)
{
	if (NULL == Tree || NULL == Key)
		return DS_INVALID_PARAMETER;

	DS_ERROR result = DS_SUCCESS;
	PDS_TREE_NODE node = NULL;

	result = TreeFindNode(Tree, Key, &node);
	if (DS_SUCCESS != result)
		return result;

	if (NULL == node->Left || NULL == node->Right)
	{
		PDS_TREE_NODE child = NULL == node->Left ? node->Right : node->Left;

		if (NULL == node->Parent)
		{
			Tree->Root = child;
		}
		else
		{
			if (node->Parent->Left == node)
			{
				node->Parent->Left = child;
			}
			else
			{
				node->Parent->Right = child;
			}
		}
		if (NULL != child)
		{
			child->Parent = node->Parent;
		}

		TreeNodeDestroy(node, false);
		Tree->Size--;
		return result;
	}
	else
	{
		PDS_TREE_NODE minNode = NULL, root = Tree->Root;
		result = TreeNodeGetMin(node->Right, &minNode);
		if (DS_SUCCESS != result)
			return result;

		void* tmp = node->Key;
		node->Key = minNode->Key;
		minNode->Key = tmp;
		tmp = node->Data;
		node->Data = minNode->Data;
		minNode->Data = node->Data;

		Tree->Root = minNode;
		result = TreeErase(Tree, Key);
		Tree->Root = root;
		if (DS_SUCCESS != result)
			return result;
	}
	return result;
}

void TreeClear(DS_TREE * Tree)
{
	if (Tree)
	{
		TreeNodeDestroy(Tree->Root, true);
		Tree->Size = 0;
		Tree->Root = NULL;
	}
}

DS_ERROR TreeFind(const DS_TREE * Tree, const void* Key, void** Data)
{
	if (NULL == Tree || NULL == Key || NULL == Data)
		return DS_INVALID_PARAMETER;

	if (Tree->Size == 0 || NULL == Tree->Root)
		return DS_NOT_FOUND;

	PDS_TREE_NODE node = NULL;
	DS_ERROR result = TreeFindNode(Tree, Key, &node);

	if (DS_SUCCESS != result)
		return result;

	*Data = node->Data;
	return result;
}

unsigned int TreeSize(const DS_TREE * Tree)
{
	if (NULL != Tree)
		return Tree->Size;
	return 0;
}

bool TreeEmpty(const DS_TREE * Tree)
{
	return TreeSize(Tree) == 0 || Tree->Root == NULL;
}

DS_ERROR TreeGetMinNode(const DS_TREE * Tree, DS_TREE_NODE * *Node)
{
	if (NULL == Tree || NULL == Node)
		return DS_INVALID_PARAMETER;

	return TreeNodeGetMin(Tree->Root, Node);
}

DS_ERROR TreeGetMaxNode(const DS_TREE * Tree, DS_TREE_NODE * *Node)
{
	if (NULL == Tree || NULL == Node)
		return DS_INVALID_PARAMETER;

	return TreeNodeGetMax(Tree->Root, Node);
}

DS_ERROR TreeNodeCreate(DS_TREE_NODE * *Node, const void* Key, size_t KeySize, const void* Data, size_t DataSize)
{
	if (NULL == Node || NULL == Key || 0 == KeySize)
		return DS_INVALID_PARAMETER;

	PDS_TREE_NODE node = (PDS_TREE_NODE)malloc(sizeof(DS_TREE_NODE));
	if (NULL == node)
		return DS_NO_MEMORY;

	void* data = NULL, *key = NULL;
	if (DataSize != 0 && Data != NULL)
	{
		data = malloc(DataSize);
		if (NULL == data)
			return DS_NO_MEMORY;
		memcpy(data, Data, DataSize);
		node->Data = data;
	}

	key = malloc(KeySize);
	if (NULL == key)
		return DS_NO_MEMORY;
	memcpy(key, Key, KeySize);

	node->Key = key;
	node->Data = data;
	node->Parent = NULL;
	node->Left = NULL;
	node->Right = NULL;

	*Node = node;
	return DS_SUCCESS;
}

void TreeNodeDestroy(DS_TREE_NODE * Node, bool Recursively)
{
	if (Node)
	{
		if (Recursively)
		{
			TreeNodeDestroy(Node->Left, true);
			TreeNodeDestroy(Node->Right, true);
		}
		//free(Node->Data);
		//free(Node->Key);
		free(Node);
	}
}

DS_ERROR TreeFindNode(const DS_TREE * Tree, const void* Key, DS_TREE_NODE * *Node)
{
	if (NULL == Tree || NULL == Key || NULL == Node)
		return DS_INVALID_PARAMETER;

	if (Tree->Size == 0 || NULL == Tree->Root)
		return DS_NOT_FOUND;

	PDS_TREE_NODE node = Tree->Root;
	bool stop = false;
	int cmp = 0;

	while (!stop)
	{
		cmp = Tree->Compare(node->Key, Key);
		if (cmp == 0)
		{
			stop = true;
		}
		else if (cmp > 0)
		{
			if (node->Left == NULL)
			{
				return DS_NOT_FOUND;
			}
			else
			{
				node = node->Left;
			}
		}
		else
		{
			if (node->Right == NULL)
			{
				return DS_NOT_FOUND;
			}
			else
			{
				node = node->Right;
			}
		}
	}

	*Node = node;
	return DS_SUCCESS;
}

DS_ERROR TreeNodeGetMin(DS_TREE_NODE * Root, DS_TREE_NODE * *Node)
{
	if (NULL == Root || NULL == Node)
		return DS_INVALID_PARAMETER;

	if (Root->Left != NULL)
		return TreeNodeGetMin(Root->Left, Node);

	*Node = Root;
	return DS_SUCCESS;
}

DS_ERROR TreeNodeGetMax(DS_TREE_NODE * Root, DS_TREE_NODE * *Node)
{
	if (NULL == Root || NULL == Node)
		return DS_INVALID_PARAMETER;

	if (Root->Right != NULL)
		return TreeNodeGetMin(Root->Right, Node);

	*Node = Root;
	return DS_SUCCESS;
}