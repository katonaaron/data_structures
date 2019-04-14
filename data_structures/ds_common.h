#ifndef DS_COMMON_H_INCLUDED
#define DS_COMMON_H_INCLUDED

#include "error.h"

typedef int (*DS_COMPARE_FUNCTION)(void*, void*);
typedef enum _DS_ITERATOR_TYPE
{
	DS_ITERATOR,
	DS_REVERSE_ITERATOR
}DS_ITERATOR_TYPE;

#endif // !DS_COMMON_H_INCLUDED

