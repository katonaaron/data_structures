#ifndef DS_COMMON_H_INCLUDED
#define DS_COMMON_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ds_error.h"

typedef int (*DS_COMPARE_FUNCTION)(const void*, const void*);
typedef enum _DS_ITERATOR_TYPE
{
	DS_ITERATOR,
	DS_REVERSE_ITERATOR
}DS_ITERATOR_TYPE;
typedef enum _DS_DIRECTION
{
	DS_UP,
	DS_DOWN
}DS_DIRECTION;

#endif // !DS_COMMON_H_INCLUDED

