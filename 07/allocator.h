#pragma once
#include <cstddef>
#include <memory>
template <typename EType>
class allocator {
public:
    size_t size;
    std::allocator<EType> alloc;
    allocator() { size = 0; };
    EType* reshape(EType* space,size_t newsize,const EType& val = EType()) {
        if (!space) {
            space = alloc.allocate(newsize);
            return space;
        }
        EType *tarr = alloc.allocate(newsize);
        for (int i = 0; i < (size < newsize ? size : newsize); i++) alloc.construct(tarr+i,space[i]); // initiolize
        if (size < newsize) {
            for (int i = size; i < newsize; i++) alloc.construct(tarr + i, val);
        }
        alloc.deallocate(space,size);
        size = newsize;
        return tarr;
    }
    EType* allocate(size_t newsize, const EType& val = EType ()) {
        if (!newsize) return NULL;
        size = newsize;
        EType* space = alloc.allocate(newsize);
        for (int i = 0;i < newsize;i++)  alloc.construct(space + i, val); // Init
        return space;
    };
    void deallocate(EType* space) {
        for (int i = 0; i < size; i++) alloc.destroy(space+ i);
        if (space) alloc.deallocate(space,size);
        size = 0;
    }
};