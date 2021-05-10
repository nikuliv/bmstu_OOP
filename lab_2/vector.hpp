#include "vector.h"
#include <limits>
#include <stdlib.h>
#include <cmath>
#include <math.h>
#include <exception>


// Iterator
template<typename Type>
iterator<Type> vector<Type>::begin() noexcept
{
    iterator<Type> iterator(*this);
    return iterator;
}

template<typename Type>
iterator<Type> vector<Type>::end() noexcept
{
    iterator<Type> iterator(*this);
    return iterator + this->vector_size;
}

template<typename Type>
const_iterator<Type> vector<Type>::begin() const noexcept
{
    const_iterator<Type> cIterator(*this);
    return cIterator;
}

template<typename Type>
const_iterator<Type> vector<Type>::end() const noexcept
{
    const_iterator<Type> cIterator(*this);
    return cIterator + this->vector_size;
}

template<typename Type>
const_iterator<Type> vector<Type>::cBegin() const noexcept
{
    const_iterator<Type> cIterator(*this);
    return cIterator;
}

template<typename Type>
const_iterator<Type> vector<Type>::cEnd() const noexcept
{
    const_iterator<Type> cIterator(*this);
    return cIterator + this->vector_size;
}


//Constructors
template<typename Type>
vector<Type>::vector()
{
    this->vector_size = 0;
    this->alloc_new_vector(vector_size);
}

template<typename Type>
vector<Type>::vector(size_t size)
{
    time_t currentTime = time(NULL);

    this->alloc_new_vector(size);
    if (!this->values)
        throw memory_exception(__FILE__, typeid(*this).name(),
                              __LINE__, ctime(&currentTime));

    this->vector_size = size;

    iterator<Type> iterator = this->begin();
    for (; iterator; iterator++)
        *iterator = 0;
}

template<typename Type>
vector<Type>::vector(size_t size, Type element)
{
    time_t currentTime = time(NULL);
    if (size == 0)
        throw empty_vector_exception(__FILE__, typeid(*this).name(),
                                   __LINE__, ctime(&currentTime));

    this->alloc_new_vector(size);
    if (!values)
        throw memory_exception(__FILE__, typeid(*this).name(),
                              __LINE__, ctime(&currentTime));

    this->vector_size = size;

    iterator<Type> iterator = this->begin();
    for (; iterator; iterator++)
        *iterator = element;
}

template<typename Type>
vector<Type>::vector(size_t size, const Type *arrayFrom)
{
    if (size == 0)
    {
        time_t currentTime = time(NULL);
        throw empty_vector_exception(__FILE__, typeid(*this).name(),
                                   __LINE__, ctime(&currentTime));
    }
    if (!arrayFrom)
    {
        time_t currentTime = time(NULL);
        throw invalid_copy_array_pointer(__FILE__, typeid(*this).name(),
                                      __LINE__, ctime(&currentTime));
    }
    this->alloc_new_vector(size);
    this->vector_size = size;

    iterator<Type> iterator = this->begin();
    for (size_t i = 0; iterator; iterator++, i++)
        *iterator = arrayFrom[i];
}

template<typename Type>
vector<Type>::vector(const std::initializer_list<Type> &arguments)
{
    this->vector_size = arguments.size();
    this->alloc_new_vector(vector_size);

    iterator<Type> iterator = this->begin();
    for (auto &currentItem : arguments)
    {
        *iterator = currentItem;
        iterator++;
    }
}

template<typename Type>
vector<Type>::vector(vector<Type> &&vector) noexcept: vector_base(vector.vector_size)
{
    this->values = vector.values;
    vector.values = nullptr;
}

template<typename Type>
vector<Type>::vector(const vector<Type> &vector): vector_base(vector.vector_size)
{
    *this = vector;
}

// Methods
template<typename Type>
vector<Type> vector<Type>::vector_sum(const vector<Type> &vect) const
{
    vector<Type> result(*this);
    iterator<Type> resultIterator = result.begin();
    const_iterator<Type> iterFrom = vect.begin();

    for (; resultIterator; resultIterator++, iterFrom++)
        *resultIterator = *resultIterator + *iterFrom;
    return result;
}

template<typename Type>
vector<Type> vector<Type>:: elements_sum(const Type &element) const
{
    vector<Type> result(*this);

    const_iterator<Type> iterFrom = this->begin();
    iterator<Type> iterTo = result.begin();

    for (; iterFrom; iterFrom++, iterTo++)
        *iterTo = *iterFrom + element;

    return result;
}

template<typename Type>
vector<Type> vector<Type>::vector_difference(const vector<Type> &vect) const
{
    vector<Type> result(*this);
    iterator<Type> resultIterator = result.begin();
    const_iterator<Type> iterFrom = vect.begin();

    for (; resultIterator; resultIterator++, iterFrom++)
        *resultIterator = *resultIterator - *iterFrom;
    return result;
}

template<typename Type>
vector<Type> vector<Type>::elements_difference(const Type &element) const
{
    vector<Type> result(*this);

    const_iterator<Type> iterFrom = this->begin();
    iterator<Type> iterTo = result.begin();

    for (; iterFrom; iterFrom++, iterTo++)
        *iterTo = *iterFrom - element;

    return result;
}

template<typename Type>
vector<Type> vector<Type>::vector_multiplication(const vector<Type> &vect) const
{
    vector<Type> result(*this);
    iterator<Type> resultIterator = result.begin();
    const_iterator<Type> iterFrom = vect.begin();

    for (; resultIterator; resultIterator++, iterFrom++)
        *resultIterator = *resultIterator * *iterFrom;
    return result;
}

template<typename Type>
vector<Type> vector<Type>:: elements_multiplication(const Type &element) const
{
    vector<Type> result(*this);
    const_iterator<Type> iterFrom = this->begin();
    iterator<Type> iterTo = result.begin();

    for (; iterFrom; iterFrom++, iterTo++)
        *iterTo = *iterFrom * element;

    return result;
}

template<typename Type>
vector<Type> vector<Type>::vector_division(const vector<Type> &vect) const
{
    vector<Type> result(*this);
    iterator<Type> resultIterator = result.begin();
    const_iterator<Type> iterFrom = vect.begin();

    for (; resultIterator; resultIterator++, iterFrom++)
        *resultIterator = *resultIterator / *iterFrom;

    return result;
}

template<typename Type>
vector<Type> vector<Type>::elements_division(const Type &element) const
{
    time_t currentTime = time(NULL);
    if (this->vector_size == 0)
        throw empty_vector_exception(__FILE__, typeid(*this).name(),
                                   __LINE__, ctime(&currentTime));
    if (!element)
        throw zero_division_exception(__FILE__, typeid(*this).name(),
                                    __LINE__, ctime(&currentTime));

    vector<Type> result(this->vector_size);

    const_iterator<Type> iterFrom = this->begin();
    iterator<Type> iterTo = result.begin();

    for (; iterFrom; iterFrom++, iterTo++)
        *iterTo = *iterFrom / element;

    return result;
}

// Additive
template<typename Type>
double vector<Type>::angle(const vector<Type> &vector) const
{
    time_t currentTime = time(NULL);
    if (!this->length<Type>() || !vector.length<Type>())
        throw zero_division_exception(__FILE__, typeid(*this).name(),
                                    __LINE__, ctime(&currentTime));

    double angle = (*this & vector) / (this->length<Type>() * vector.length<Type>());
    return acos(angle) * 180 / M_PI;
}

template<typename Type>
bool vector<Type>::collinear(const vector<Type> &vector) const
{
    if (this->angle(vector) < __FLT_EPSILON__)
        return true;
    return false;
}

template<typename Type>
bool vector<Type>::orthgonal(const vector<Type> &vector) const
{
    if (this->angle(vector) - 90 < __DBL_EPSILON__)
        return true;
    return false;
}

template<typename Type>
template<typename TypeOut>
vector<TypeOut> vector<Type>::get_unit_vector() const
{
    vector<TypeOut> unitVector(this->vector_size);
    Type len = this->length<Type>();

    iterator<TypeOut> iteratorTo = unitVector.begin();
    const_iterator<Type> iteratorFrom = this->begin();
    for (; iteratorFrom; iteratorFrom++, iteratorTo++)
        *iteratorTo = *iteratorFrom / len;

    return unitVector;
}

template<>
template<>
vector<double> vector<int>::get_unit_vector() const
{
    vector<double> unitVector(this->vector_size);
    float len = this->length<float>();

    iterator<double> iteratorTo = unitVector.begin();
    const_iterator<int> iteratorFrom = this->begin();
    for (; iteratorFrom; iteratorFrom++, iteratorTo++)
        *iteratorTo = *iteratorFrom / len;

    return unitVector;
}

// Get item func
template<typename Type>
Type &vector<Type>::at(size_t index)
{
    time_t currentTime = time(NULL);
    if (index >= vector_size)
        throw out_of_range_exception(__FILE__, typeid(*this).name(),
                                  __LINE__, ctime(&currentTime));

    iterator<Type> iterator = this->begin();
    for (size_t i = 0; i < index; i++, iterator++) { }

    return *iterator;
}

// Get item const
template<typename Type>
const Type &vector<Type>::at(size_t index) const
{
    if (index >= this->vector_size)
    {
        time_t currentTime = time(NULL);
        throw out_of_range_exception(__FILE__, typeid(*this).name(),
                                  __LINE__, ctime(&currentTime));
    }

    const_iterator<Type> iterator = this->begin();
    for (size_t i = 0; i < index; i++, iterator++) { }

    return *iterator;
}

// Overload
template<typename Type>
bool vector<Type>::operator==(const vector<Type> &vector) const
{
    bool areEqual = false;
    if (this->vector_size != vector.vector_size)
        return areEqual;

    areEqual = true;
    const_iterator<Type> firstIterator = this->begin();
    for (const_iterator<Type> secondIterator = vector.begin(); firstIterator && areEqual;
         secondIterator++)
        if (*firstIterator != *secondIterator)
            areEqual = false;
    return areEqual;
}

template<typename Type>
bool vector<Type>::operator!=(const vector<Type> &vector) const
{
    bool areNotEqual = true;
    if (this->vector_size != vector.vector_size)
        return areNotEqual;

    areNotEqual = false;
    const_iterator<Type> firstIterator = this->begin();
    for (const_iterator<Type> secondIterator = vector.begin(); firstIterator && !areNotEqual;
         secondIterator++)
        if (*firstIterator != *secondIterator)
            areNotEqual = true;
    return areNotEqual;
}

template<typename Type>
vector<Type> &vector<Type>::operator+=(const vector<Type> &vector)
{
    time_t currentTime = time(NULL);
    if (this->vector_size == 0 || vector.vector_size == 0)
        throw empty_vector_exception(__FILE__, typeid(*this).name(),
                                   __LINE__, ctime(&currentTime));
    this->check_sizes(vector, __LINE__);

    *this = this->vector_sum(vector);

    return *this;
}

template<typename Type>
vector<Type> &vector<Type>::operator-=(const vector<Type> &vector)
{
    time_t currentTime = time(NULL);
    if (this->vector_size == 0 || vector.vector_size == 0)
        throw empty_vector_exception(__FILE__, typeid(*this).name(),
                                   __LINE__, ctime(&currentTime));
    this->check_sizes(vector, __LINE__);

    *this = this->vector_difference(vector);

    return *this;
}

template<typename Type>
vector<Type> &vector<Type>::operator*=(const vector<Type> &vector)
{
    time_t currentTime = time(NULL);
    if (this->vector_size == 0)
        throw empty_vector_exception(__FILE__, typeid(*this).name(),
                                   __LINE__, ctime(&currentTime));
    this->check_sizes(vector, __LINE__);

    *this = this->vector_multiplication(vector);
    return *this;
}

template<typename Type>
vector<Type> &vector<Type>::operator*=(const Type &element)
{
    time_t currentTime = time(NULL);
    if (this->vector_size == 0)
        throw empty_vector_exception(__FILE__, typeid(*this).name(),
                                   __LINE__, ctime(&currentTime));

    *this = this->elements_multiplication(element);

    return *this;
}

template<typename Type>
vector<Type> &vector<Type>::operator/=(const vector<Type> &vector)
{
    time_t currentTime = time(NULL);
    if (this->vector_size == 0)
        throw empty_vector_exception(__FILE__, typeid(*this).name(),
                                   __LINE__, ctime(&currentTime));
    this->check_sizes(vector, __LINE__);

    *this = this->vector_division(vector);
    return *this;
}

template<typename Type>
vector<Type> &vector<Type>::operator/=(const Type &element)
{
    time_t currentTime = time(NULL);
    if (this->vector_size == 0)
        throw empty_vector_exception(__FILE__, typeid(*this).name(),
                                   __LINE__, ctime(&currentTime));

    *this = this->elements_division(element);

    return *this;
}

template<typename Type>
vector<Type> vector<Type>::operator+(const vector<Type> &vector) const
{
    time_t currentTime = time(NULL);
    if (this->vector_size == 0 || vector.vector_size == 0)
        throw empty_vector_exception(__FILE__, typeid(*this).name(),
                                   __LINE__, ctime(&currentTime));
    this->check_sizes(vector, __LINE__);

    return this->vector_sum(vector);
}

template<typename Type>
vector<Type> vector<Type>::operator+(const Type &element) const
{
    time_t currentTime = time(NULL);
    if (this->vector_size == 0)
        throw empty_vector_exception(__FILE__, typeid(*this).name(),
                                   __LINE__, ctime(&currentTime));

    return this->elements_sum(element);
}

template<typename Type>
vector<Type> vector<Type>::operator-(const vector<Type> &vector) const
{
    time_t currentTime = time(NULL);
    if (this->vector_size == 0 || vector.vector_size == 0)
        throw empty_vector_exception(__FILE__, typeid(*this).name(),
                                   __LINE__, ctime(&currentTime));
    this->check_sizes(vector, __LINE__);

    return this->vector_difference(vector);
}

template<typename Type>
vector<Type> vector<Type>::operator-(const Type &element) const
{
    time_t currentTime = time(NULL);
    if (this->vector_size == 0)
        throw empty_vector_exception(__FILE__, typeid(*this).name(),
                                   __LINE__, ctime(&currentTime));

    return this->elements_difference(element);
}

template<typename Type>
vector<Type> vector<Type>::operator*(const vector<Type> &vector) const
{
    time_t currentTime = time(NULL);
    if (this->vector_size == 0 || vector.vector_size == 0)
        empty_vector_exception(__FILE__, typeid(*this).name(),
                             __LINE__, ctime(&currentTime));
    this->check_sizes(vector, __LINE__);

    return this->vector_multiplication(vector);
}

template<typename Type>
vector<Type> vector<Type>::operator*(const Type &element) const
{
    time_t currentTime = time(NULL);
    if (this->vector_size == 0)
        throw empty_vector_exception(__FILE__, typeid(*this).name(),
                                   __LINE__, ctime(&currentTime));

    return this->elements_multiplication(element);
}

template<typename Type>
Type vector<Type>::operator&(const vector<Type> &vector) const
{
    time_t currentTime = time(NULL);
    if (this->vector_size == 0 || vector.vector_size == 0)
        empty_vector_exception(__FILE__, typeid(*this).name(),
                             __LINE__, ctime(&currentTime));
    this->check_sizes(vector, __LINE__);

    return this->vector_multiplication(vector).summary_value();
}

template<typename Type>
vector<Type> vector<Type>::operator/(const vector<Type> &vector) const
{
    time_t currentTime = time(NULL);
    if (this->vector_size == 0 || vector.vector_size == 0)
        empty_vector_exception(__FILE__, typeid(*this).name(),
                             __LINE__, ctime(&currentTime));
    this->check_sizes(vector, __LINE__);

    return this->vector_division(vector);
}

template<typename Type>
vector<Type> vector<Type>::operator/(const Type &element) const
{
    return this->elements_division(element);
}
//< End

template<typename Type>
Type &vector<Type>::operator[](size_t index)
{
    return at(index);
}

template<typename Type>
const Type &vector<Type>::operator[](size_t index) const
{
    return at(index);
}

template<typename Type>
vector<Type> vector<Type>::operator-()
{
    vector<Type> newVector(*this);
    iterator<Type> iterator = newVector.begin();
    for (; iterator; iterator++)
        *iterator = -*iterator;

    return newVector;
}

template<typename Type>
vector<Type> &vector<Type>::operator=(const vector<Type> &vector)
{
    this->vector_size = vector.vector_size;
    this->alloc_new_vector(vector_size);

    iterator<Type> iteratorTo(*this);
    iterator<Type> iteratorFrom(vector);
    for (; iteratorTo; iteratorTo++, iteratorFrom++)
        *iteratorTo = *iteratorFrom;
    return *this;
}

template<typename Type>
vector<Type> &vector<Type>::operator=(const std::initializer_list<Type> &arguments)
{
    this->vector_size = arguments.size();
    this->alloc_new_vector(vector_size);

    iterator<Type> iterator = this->begin();
    for (auto &currentItem : arguments)
    {
        *iterator = currentItem;
        iterator++;
    }
    return *this;
}

template<typename Type>
vector<Type> &vector<Type>::operator=(vector<Type> &&vector)
{
    this->vector_size = vector.vector_size;
    this->alloc_new_vector(vector_size);
    this->values = vector.values;
    vector.values.reset();

    return *this;
}

// Allocation for Vector
template<typename Type>
void vector<Type>::alloc_new_vector(size_t amount)
{
    time_t currentTime = time(NULL);
    try
    {
        this->values.reset(new Type[amount]);
    }
    catch (std::bad_alloc &exception)
    {
        throw memory_exception(__FILE__, typeid(*this).name(),
                              __LINE__, ctime(&currentTime));
    }
}

template<typename Type>
bool vector<Type>::is_single_vector() const noexcept
{
    bool retOut = false;
    if (fabs(this->length<Type>() - 1) < __FLT_EPSILON__)
        retOut = true;
    return retOut;
}

template<>
bool vector<long double>::is_single_vector() const noexcept
{
    bool retOut = false;
    if (fabs(this->length<long double>() - 1) < __DBL_EPSILON__)
        retOut = true;
    return retOut;
}

template<typename Type>
bool vector<Type>::is_zero_vector() const noexcept
{
    bool retOut = false;
    if (this->length<Type>() < __FLT_EPSILON__)
        retOut = true;
    return retOut;
}

template<typename Type>
Type vector<Type>::summary_value()
{
    time_t currentTime = time(NULL);
    if (this->vector_size == 0)
        throw empty_vector_exception(__FILE__, typeid(*this).name(),
                                   __LINE__, ctime(&currentTime));

    iterator<Type> iterator = this->begin();
    Type summary = 0;
    for (; iterator; iterator++)
        summary += *iterator;

    return summary;
}

template<typename Type>
template<typename TypeOut>
TypeOut vector<Type>::length(void) const
{
    time_t currentTime = time(NULL);
    if (this->vector_size == 0)
        throw empty_vector_exception(__FILE__, typeid(*this).name(),
                                   __LINE__, ctime(&currentTime));

    const_iterator<Type> iterator = this->begin();
    Type sum = 0;
    for (; iterator; iterator++)
        sum += *iterator * *iterator;
    return sqrt(sum);
}

template<>
template<>
double vector<int>::length(void) const
{
    time_t currentTime = time(NULL);
    if (this->vector_size == 0)
        throw empty_vector_exception(__FILE__, typeid(*this).name(),
                                   __LINE__, ctime(&currentTime));

    const_iterator<int> iterator = this->begin();
    int sum = 0;
    for (; iterator; iterator++)
        sum += *iterator * *iterator;
    return sqrt(sum);
}

// Check
template<typename Type>
void vector<Type>::check_sizes(const vector<Type> &vector, int lineError) const
{
    time_t currentTime = time(NULL);
    if (this->vector_size != vector.vector_size)
        throw invalid_vectors_sizes(__FILE__, typeid(*this).name(),
                                  lineError, ctime(&currentTime));
}

template<typename Type>
void vector<Type>::check_size_for_vect_mul(const vector<Type> &vector, int lineError) const
{
    time_t currentTime = time(NULL);
    if (this->vector_size != 3 || vector.vector_size != 3)
        throw invalid_vectors_sizes(__FILE__, typeid(*this).name(),
                                  lineError, ctime(&currentTime));
}


template<typename Type>
vector<Type> operator+(const Type &element, const vector<Type> &vector)
{
    return vector + element;
}

template<typename Type>
vector<Type> operator-(const Type &element, const vector<Type> &vector)
{
    return vector - element;
}

template<typename Type>
vector<Type> operator*(const Type &element, const vector<Type> &vector)
{
    return vector * element;
}

template<typename Type>
vector<Type> operator/(const Type &element, const vector<Type> &vector)
{
    return vector / element;
}

template<typename Type>
std::ostream &operator<<(std::ostream &os, const vector<Type> &vector)
{
    const_iterator<Type> iterator = vector.begin();
    if (!iterator) {
        os<< "Empty mVector";
        return os;
    }

    os<< "{";
    os<< *iterator;
    for (iterator++; iterator; iterator++)
            os<< ", "<< *iterator;
    os<< "}";

    return os;
}
