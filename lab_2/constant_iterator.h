#ifndef CONSTITERATOR_H
#define CONSTITERATOR_H

#include "exceptions.h"

#include <memory>
#include <time.h>

template<typename Type>
class vector;

template<typename Type>
class const_iterator: public std::iterator<std::random_access_iterator_tag, int>
{
public:
    const_iterator(const const_iterator<Type> &iterator) noexcept;
    const_iterator(const vector<Type> &vector) noexcept;

    const Type &operator*() const;
    const Type *operator->() const;
    operator bool() const;

    const_iterator<Type> &operator=(const const_iterator<Type> &iterator) noexcept;

    const_iterator<Type> &operator-=(size_t number);
    const_iterator<Type> operator-(size_t number) const;
    const_iterator<Type> &operator--();
    const_iterator<Type> operator--(int);

    const_iterator<Type> &operator+=(size_t number);
    const_iterator<Type> operator+(size_t number) const;
    const_iterator<Type> &operator++();
    const_iterator<Type> operator++(int);

    bool operator<=(const const_iterator<Type> &compareTo) const;
    bool operator<(const const_iterator<Type> &compareTo) const;
    bool operator>=(const const_iterator<Type> &compareTo) const;
    bool operator>(const const_iterator<Type> &compareTo) const;
    bool operator==(const const_iterator<Type> &compareTo) const;
    bool operator!=(const const_iterator<Type> &compareTo) const;

    const Type &operator[](const size_t index) const;

private:
    std::weak_ptr<Type[]> wPointer;

protected:
    Type *getCurrentPointer() const;
    void exceptionCheck(int currentLine) const;
    void validityCheck(int currentLine) const;
    size_t current_index = 0;
    size_t vector_size = 0;
};

#include "constant_iterator.hpp"


#endif // CONSTITERATOR_H
