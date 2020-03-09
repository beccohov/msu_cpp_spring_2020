#pragma once
class LinearAllocator {
    size_t size;
    size_t offset;
    void* base;
public:
    void initAllocator(size_t);
    char* alloc(size_t);
    void reset(void);
    LinearAllocator() {
        size = offset = 0;
        base = nullptr;
    };
    ~LinearAllocator() {
        free(base);
    }
};
void LinearAllocator::initAllocator(size_t max_size)
{
    size = max_size;
    if (max_size) base = malloc(max_size);// base == NULL in case of exception
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
