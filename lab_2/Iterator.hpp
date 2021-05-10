#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include "iterator.h"

template<typename Type>
Type *iterator<Type>::get_current_pointer() const
{
    std::shared_ptr<Type[]> copied = this->wPointer.lock();
    return copied.get() + current_index;
}

template<typename Type>
iterator<Type>::iterator(const iterator<Type> &iterator) noexcept
{
    this->wPointer = iterator.wPointer;
    this->current_index = iterator.current_index;
    this->vector_size = iterator.vector_size;
}

template<typename Type>
iterator<Type>::iterator(const vector<Type> &vector) noexcept
{
    this->current_index = 0;
    this->vector_size = vector.size();
    this->wPointer = vector.values;
}

template<typename Type>
Type &iterator<Type>::operator*()
{
    exception_check(__LINE__);
    validity_check(__LINE__);

    return *get_current_pointer();
}

template<typename Type>
const Type &iterator<Type>::operator*() const
{
    exception_check(__LINE__);
    validity_check(__LINE__);

    return *get_current_pointer();
}

template<typename Type>
Type *iterator<Type>::operator->()
{
    exception_check(__LINE__);
    validity_check(__LINE__);

    return get_current_pointer();
}

template<typename Type>
const Type *iterator<Type>::operator->() const
{
    exception_check(__LINE__);
    validity_check(__LINE__);

    return get_current_pointer();
}

template<typename Type>
iterator<Type> &iterator<Type>::operator=(const iterator<Type>& iterator) noexcept
{
    wPointer = iterator.wPointer;
    return *this;
}

template<typename Type>
iterator<Type> &iterator<Type>::operator+=(size_t number)
{
    exception_check(__LINE__);
    current_index += number;

    return *this;
}

template<typename Type>
iterator<Type> iterator<Type>::operator+(size_t number) const
{
    exception_check(__LINE__);
    iterator<Type> iterator(*this);
    iterator += number;

    return iterator;
}

template <typename Type>
iterator<Type> &iterator<Type>::operator-=(size_t number)
{
    exception_check(__LINE__);
    current_index -= number;

    return *this;
}

template <typename Type>
iterator<Type> iterator<Type>::operator-(size_t number) const
{
    exception_check(__LINE__);
    iterator<Type> iterator(*this);
    iterator -= number;

    return iterator;
}

template<typename Type>
iterator<Type> iterator<Type>::operator++(int)
{
    exception_check(__LINE__);
    ++(*this);

    return *this;
}

template<typename Type>
iterator<Type> &iterator<Type>::operator++()
{
    exception_check(__LINE__);
    ++current_index;

    return *this;
}

template<typename Type>
iterator<Type> iterator<Type>::operator--(int)
{
    exception_check(__LINE__);
    --(*this);

    return *this;
}

template<typename Type>
iterator<Type> &iterator<Type>::operator--()
{
    exception_check(__LINE__);
    --current_index;

    return *this;
}

template<typename Type>
bool iterator<Type>::operator<(const iterator<Type> &compareTo) const
{
    exception_check(__LINE__);

    return this->current_index < compareTo.current_index;
}

template<typename Type>
bool iterator<Type>::operator<=(const iterator<Type> &compareTo) const
{
    exception_check(__LINE__);

    return this->current_index <= compareTo.current_index;
}

template<typename Type>
bool iterator<Type>::operator>(const iterator<Type> &compareTo) const
{
    exception_check(__LINE__);

    return this->current_index > compareTo.current_index;
}

template<typename Type>
bool iterator<Type>::operator>=(const iterator<Type> &compareTo) const
{
    exception_check();

    return this->current_index >= compareTo.current_index;
}

template<typename Type>
bool iterator<Type>::operator==(const iterator<Type> &compareTo) const
{
    exception_check(__LINE__);

    return this->current_index == compareTo.current_index;
}

template<typename Type>
bool iterator<Type>::operator!=(const iterator<Type> &compareTo) const
{
    exception_check(__LINE__);

    return this->current_index != compareTo.current_index;
}

template<typename Type>
iterator<Type>::operator bool() const
{
    exception_check(__LINE__);

    if (current_index >= vector_size || vector_size == 0)
        return false;
    else
        return true;
}

template<typename Type>
Type &iterator<Type>::operator[](size_t index)
{
    size_t curLine = __LINE__;
    exception_check(curLine);

    time_t currentTime = time(NULL);
    if (index + this->currentIndex >= this->vectorLen)
        throw out_of_range_exception(__FILE__, typeid(*this).name(),
                                  curLine, ctime(&currentTime));

    return *(this + index);
}

template<typename Type>
const Type &iterator<Type>::operator[](size_t index) const
{
    size_t curLine = __LINE__;
    exception_check(curLine);

    time_t currentTime = time(NULL);
    if (index + this->currentIndex >= this->vectorLen)
        throw out_of_range_exception(__FILE__, typeid(*this).name(),
                                  curLine, ctime(&currentTime));

    return *(this + index);
}

template<typename Type>
void iterator<Type>::exception_check(int currentLine) const
{
    if (wPointer.expired())
    {
        time_t currentTime = time(NULL);
        throw deleted_object_exception(__FILE__, typeid(*this).name(),
                                     currentLine, ctime(&currentTime));
    }
}

template<typename Type>
void iterator<Type>::validity_check(int currentLine) const
{
    if (this->current_index >= this->vector_size)
    {
        time_t currentTime = time(NULL);
        throw invalid_iterator(__FILE__, typeid(*this).name(),
                              currentLine, ctime(&currentTime));
    }
}

#endif // ITERATOR_HPP
