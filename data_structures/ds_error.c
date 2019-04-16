#include "ds_error.h"

char* DSErrorGetMessage(DS_ERROR Code)
{
	char* message;
	switch (Code)
	{
	case DS_SUCCESS:
		message = "No error";
		break;
	case DS_INVALID_PARAMETER:
		message = "Invalid parameter";
		break;
	case DS_NO_MEMORY:
		message = "No memory";
		break;
	case DS_NOT_FOUND:
		message = "Not found";
		break;
	default:
		message = "Unknown Error";
		break;
	}
	return message;
}