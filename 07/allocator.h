#pragma once
#include <cstddef>
template <typename EType>
class allocator {
public:
    EType * space;
    size_t size;
    allocator() { space = nullptr; size = 0; };
    ~allocator() { if (space) delete [] space; };
    EType* reshape(size_t newsize) {
        EType* new_space = new EType[newsize];
        int min_l = (size < newsize ? size : newsize);
        for (int i = 0; i < min_l;  i++) {
            new_space[i] = space[i];
        }
        delete[] space;
        space = new_space; //(EType*)realloc(space, sizeof(EType)*size);
        size = newsize;
        return space;
    }
    EType* allocate(size_t newsize) {
        if (!space) {
            space = new EType[newsize]; //(EType*)malloc(sizeof(EType)*newsize);
            size = newsize;
        }
        else {
            space = reshape(newsize);
        }
        return space;
    };
    void GoBack() {
        if (!space) free(space);
    }
};