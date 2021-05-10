#ifndef ITERATOR_H
#define ITERATOR_H

#include "exceptions.h"

#include <memory>
#include <time.h>

template<typename Type>
class vector;

template<typename Type>
class iterator: public std::iterator<std::random_access_iterator_tag, int>
{
public:
    iterator(const iterator<Type> &iterator) noexcept;
    iterator(const vector<Type> &vector) noexcept;

    Type &operator*();
    const Type &operator*() const;
    Type *operator->();
    const Type *operator->() const;
    operator bool() const;

    iterator<Type> &operator=(const iterator<Type> &iterator) noexcept;

    iterator<Type> &operator-=(size_t number);
    iterator<Type> operator-(size_t number) const;
    iterator<Type> &operator--();
    iterator<Type> operator--(int);

    iterator<Type> &operator+=(size_t number);
    iterator<Type> operator+(size_t number) const;
    iterator<Type> &operator++();
    iterator<Type> operator++(int);

    bool operator<=(const iterator<Type> &compareTo) const;
    bool operator<(const iterator<Type> &compareTo) const;
    bool operator>=(const iterator<Type> &compareTo) const;
    bool operator>(const iterator<Type> &compareTo) const;
    bool operator==(const iterator<Type> &compareTo) const;
    bool operator!=(const iterator<Type> &compareTo) const;

    Type &operator[](const size_t index);
    const Type &operator[](const size_t index) const;

private:
    std::weak_ptr<Type[]> wPointer;

protected:
    Type *get_current_pointer() const;
    void exception_check(int currentLine) const;
    void validity_check(int currentLine) const;
    size_t current_index = 0;
    size_t vector_size = 0;
};

#include "Iterator.hpp"

#endif // ITERATOR_H
