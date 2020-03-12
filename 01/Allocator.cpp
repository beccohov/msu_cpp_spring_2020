#include "allocator.h"
#include <iostream>
#include <stddef.h>
using namespace std;
void* LinearAllocator::initAllocator(size_t max_size)
{
	size = max_size;
	if (max_size) {
		base = malloc(max_size);// base == NULL in case of exception
		if (!base) {
			return NULL; // return error code into call process
		}
	}
	else return NULL;  // return error code into call process in case of void allocation
}

char * LinearAllocator::alloc(size_t request)
{
    if (request + offset > size) return nullptr; // Проверка достаточности свободного пространства
    if (request == 0) return nullptr;
    char* space = (char*)base + offset;
    offset += request;
    return space;
}

void LinearAllocator::reset(void)
{
   offset = 0;
}
LinearAllocator::LinearAllocator() {
    size = offset = 0;
    base = nullptr;
};
LinearAllocator::~LinearAllocator(void) {
    free(base);
}