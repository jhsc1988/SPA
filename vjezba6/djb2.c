#include "djb2.h"

size_t djb2(const char *s) {

	size_t hash = 5381;

	while (*s) 
		hash = ((hash << 5) + hash) + *s++;
	
	return hash;

}
