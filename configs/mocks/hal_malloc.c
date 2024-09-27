#include <stddef.h>
#include <stdlib.h>

extern void *hal_malloc(size_t bytes_quantity) {
	return malloc(bytes_quantity);
}
