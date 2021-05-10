#ifndef CONSTITERATOR_HPP
#define CONSTITERATOR_HPP
#include <constant_iterator.h>

template<typename Type>
Type *const_iterator<Type>::getCurrentPointer() const
{
    std::shared_ptr<Type[]> copied = this->wPointer.lock();
    return copied.get() + current_index;
}

template<typename Type>
const_iterator<Type>::const_iterator(const const_iterator<Type> &iterator) noexcept
{
    this->wPointer = iterator.wPointer;
    this->current_index = iterator.current_index;
    this->vector_size = iterator.vector_size;
}

template<typename Type>
const_iterator<Type>::const_iterator(const vector<Type> &vector) noexcept
{
    this->current_index = 0;
    this->vector_size = vector.size();
    this->wPointer = vector.values;
}

template<typename Type>
const Type &const_iterator<Type>::operator*() const
{
    exceptionCheck(__LINE__);
    validityCheck(__LINE__);

    return *getCurrentPointer();
}

template<typename Type>
const Type *const_iterator<Type>::operator->() const
{
    exceptionCheck(__LINE__);
    validityCheck(__LINE__);

    return getCurrentPointer();
}

template<typename Type>
const_iterator<Type> &const_iterator<Type>::operator=(const const_iterator<Type>& iterator) noexcept
{
    wPointer = iterator.wPointer;
    return *this;
}

template<typename Type>
const_iterator<Type> &const_iterator<Type>::operator+=(size_t number)
{
    exceptionCheck(__LINE__);
    current_index += number;

    return *this;
}

template<typename Type>
const_iterator<Type> const_iterator<Type>::operator+(size_t number) const
{
    exceptionCheck(__LINE__);
    const_iterator<Type> iterator(*this);
    iterator += number;

    return iterator;
}

template <typename Type>
const_iterator<Type> &const_iterator<Type>::operator-=(size_t number)
{
    exceptionCheck(__LINE__);
    current_index -= number;

    return *this;
}

template <typename Type>
const_iterator<Type> const_iterator<Type>::operator-(size_t number) const
{
    exceptionCheck(__LINE__);
    const_iterator<Type> iterator(*this);
    iterator -= number;

    return iterator;
}

template<typename Type>
const_iterator<Type> const_iterator<Type>::operator++(int)
{
    exceptionCheck(__LINE__);
    ++(*this);

    return *this;
}

template<typename Type>
const_iterator<Type> &const_iterator<Type>::operator++()
{
    exceptionCheck(__LINE__);
    ++current_index;

    return *this;
}

template<typename Type>
const_iterator<Type> const_iterator<Type>::operator--(int)
{
    exceptionCheck(__LINE__);
    --(*this);

    return *this;
}

template<typename Type>
const_iterator<Type> &const_iterator<Type>::operator--()
{
    exceptionCheck(__LINE__);
    --current_index;

    return *this;
}

template<typename Type>
bool const_iterator<Type>::operator<(const const_iterator<Type> &compareTo) const
{
    exceptionCheck(__LINE__);

    return this->current_index < compareTo.current_index;
}

template<typename Type>
bool const_iterator<Type>::operator<=(const const_iterator<Type> &compareTo) const
{
    exceptionCheck(__LINE__);

    return this->current_index <= compareTo.current_index;
}

template<typename Type>
bool const_iterator<Type>::operator>(const const_iterator<Type> &compareTo) const
{
    exceptionCheck(__LINE__);

    return this->current_index > compareTo.current_index;
}

template<typename Type>
bool const_iterator<Type>::operator>=(const const_iterator<Type> &compareTo) const
{
    exceptionCheck();

    return this->current_index >= compareTo.current_index;
}

template<typename Type>
bool const_iterator<Type>::operator==(const const_iterator<Type> &compareTo) const
{
    exceptionCheck(__LINE__);

    return this->current_index == compareTo.current_index;
}

template<typename Type>
bool const_iterator<Type>::operator!=(const const_iterator<Type> &compareTo) const
{
    exceptionCheck(__LINE__);

    return this->current_index != compareTo.current_index;
}

template<typename Type>
const_iterator<Type>::operator bool() const
{
    exceptionCheck(__LINE__);

    if (current_index >= vector_size || vector_size == 0)
        return false;
    else
        return true;
}

template<typename Type>
const Type &const_iterator<Type>::operator[](size_t index) const
{
    size_t curLine = __LINE__;
    exceptionCheck(curLine);

    time_t currentTime = time(NULL);
    if (index + this->current_index >= this->vectorLen)
        throw out_of_range_exception(__FILE__, typeid(*this).name(),
                                  curLine, ctime(&currentTime));

    return *(this + index);
}

template<typename Type>
void const_iterator<Type>::exceptionCheck(int currentLine) const
{
    if (wPointer.expired())
    {
        time_t currentTime = time(NULL);
        throw deleted_object_exception(__FILE__, typeid(*this).name(),
                                     currentLine, ctime(&currentTime));
    }
}

template<typename Type>
void const_iterator<Type>::validityCheck(int currentLine) const
{
    if (this->current_index >= this->vector_size)
    {
        time_t currentTime = time(NULL);
        throw invalid_iterator(__FILE__, typeid(*this).name(),
                                     currentLine, ctime(&currentTime));
    }
}
#endif // CONSTITERATOR_HPP
