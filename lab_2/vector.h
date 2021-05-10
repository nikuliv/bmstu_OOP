#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <memory>

#include "iterator.h"
#include "constant_iterator.h"
#include "vector_base.h"

// class
template<typename Type>
class vector: public vector_base
{
public:
    friend class iterator<Type>;
    friend class const_iterator<Type>;

    // Constructors
    vector();

    explicit vector(size_t size);
    vector(size_t size, const Type *arrayFrom);
    vector(size_t size, Type &element);
    vector(const std::initializer_list<Type> &elements);


    explicit vector(const vector<Type> &vector);
    vector(vector<Type> &&vector) noexcept;

    // Destructor
    virtual ~vector() = default;


    // Vector bool funcs
    bool is_zero_vector() const noexcept;
    bool is_single_vector() const noexcept;

    // One vector methods
    template<typename TypeOut>
    TypeOut length() const;
    template<typename TypeOut>
    vector<TypeOut> get_unit_vector() const;

    // Two vectors methods
    double angle(const vector<Type> &vector) const;
    bool collinear(const vector<Type> &vector) const;
    bool orthgonal(const vector<Type> &vector) const;

    Type &at(size_t index);
    const Type &at(size_t index) const;
    Type &operator[](size_t index);
    const Type &operator[](size_t index) const;


    // Iterator
    const_iterator<Type> begin() const noexcept;
    const_iterator<Type> end() const noexcept;
    iterator<Type> begin() noexcept;
    iterator<Type> end() noexcept;
    const_iterator<Type> cBegin() const noexcept;
    const_iterator<Type> cEnd() const noexcept;

    // Operators overloads
    vector<Type> &operator=(const vector<Type> &vector);
    vector<Type> &operator=(const std::initializer_list<Type> &arguments);
    vector<Type> &operator=(vector<Type> &&vector);

    vector<Type> &operator+=(const vector<Type> &vector);
    vector<Type> &operator+=(const Type &element);
    vector<Type> operator+(const vector<Type> &vector) const;
    vector<Type> operator+(const Type &element) const;
    vector<Type> vector_sum(const vector<Type> &vector) const;
    vector<Type> elements_sum(const Type &element) const;

    vector<Type> &operator-=(const vector<Type> &vector);
    vector<Type> &operator-=(const Type &element);
    vector<Type> operator-(const vector<Type> &vector) const;
    vector<Type> operator-(const Type &element) const;
    vector<Type> vector_difference(const vector<Type> &vector) const;
    vector<Type> elements_difference(const Type &element) const;

    vector<Type> &operator*=(const vector<Type> &vector);
    vector<Type> &operator*=(const Type &element);
    vector<Type> operator*(const vector<Type> &vector) const;
    vector<Type> operator*(const Type &element) const;
    vector<Type> elements_multiplication(const Type &element) const;

    Type operator&(const vector<Type> &vector) const;

    vector<Type> &operator/=(const vector<Type> &vector);
    vector<Type> &operator/=(const Type &element);
    vector<Type> operator/(const vector<Type> &vector) const;
    vector<Type> operator/(const Type &element) const;
    vector<Type> elements_division(const Type &element) const;

    vector<Type> operator-();

    bool operator==(const vector<Type> &vector) const;
    bool operator!=(const vector<Type> &vector) const;

private:
    std::shared_ptr<Type[]> values;

protected:
    Type summary_value();
    vector<Type> vector_multiplication(const vector<Type> &vector) const;
    vector<Type> vector_division(const vector<Type> &vector) const;

    void check_sizes(const vector<Type> &vector, int lineError) const;
    void check_size_for_vect_mul(const vector<Type> &vector, int lineError) const;
    void alloc_new_vector(size_t itemsAmount);
};

#include "vector.hpp"

#endif // VECTOR_H
