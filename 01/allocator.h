//#pragma once
#include <stddef.h>
class LinearAllocator {
    size_t size;
    size_t offset;
    void* base;
public:
    void* initAllocator(size_t);
    char* alloc(size_t);
    void reset(void);
    LinearAllocator(void);
    ~LinearAllocator(void);
};