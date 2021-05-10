#ifndef VECTOR_BASE_H
#define VECTOR_BASE_H

#include <cstddef>

class vector_base
{
public:
    vector_base(size_t vector_size = 0): vector_size(vector_size) { }

    virtual size_t size() const noexcept
    {
        return vector_size;
    };

    virtual operator bool() const noexcept
    {
        return bool(vector_size);
    }

    virtual ~vector_base() = 0;

protected:
    size_t vector_size = 0;
};

vector_base::~vector_base() { }

#endif // VECTOR_BASE_H
