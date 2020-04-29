#pragma once
#include <cstddef>
template <typename EType>
class allocator {
public:
    size_t size;
    allocator() { size = 0; };
    EType* reshape(EType* space,size_t newsize) {
        if (!space) space = (EType*)calloc(newsize, sizeof(EType));
        else space = (EType*)realloc(space, sizeof(EType)*newsize);
        size = newsize;
        return space;
    }
    EType* allocate(size_t newsize) {
        if (!newsize) return NULL;
        EType* space = (EType*)calloc(newsize,sizeof(EType));
        return space;
    };
    void deallocate(EType* space) {
        if (space) free(space);
    }
};