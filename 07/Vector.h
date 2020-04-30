#pragma once
#include "allocator.h"
#include "iterators.h"
template<class T>
class Vector {
public:
    Vector();
    inline Vector(size_t, const T& = T{});
    Vector(const Vector& arg);   
    ~Vector();
    iterator_<T> begin() { 
        iterator_<T> x(&_elements[0]);
        return  x;
    }
    const iterator_<T> begin() const { return iterator_<T>(&_elements[0]); }
    iterator_<T> end() { return iterator_<T>(&_elements[_size > 0 ? _size -1:0]); }
    const iterator_<T> end() const { return iterator_<T>(&_elements[_size > 0 ? _size - 1 : 0]); }
    riterator<T> rbegin() { return riterator<T>(&_elements[_size > 0 ? _size - 1 : 0] ); }
    const riterator<T> rbegin() const { return riterator<T>(&_elements[_size > 0 ? _size - 1 : 0], &_elements[0]); }
    riterator<T> rend() {
        return riterator<T>(&_elements[0]); 
    }
    const riterator<T> rend() const { return riterator<T>(&_elements[0], &_elements[0]); }
    bool empty() const { return _size == 0; }
    void reserve(int newmalloc);
    void resize(size_t newsize, const T& val = T()); 
    size_t size() const { return _size; }
    void clear();
    void push_back(const T& d);
    void pop_back();
    T& operator[](int i);
    const T& operator[](int i) const;
    T& back();
    const T& back() const;    
private:
    size_t	_size;		
    T*		_elements;	
    size_t	_space;	
    allocator<T> Allocator;
};









template<class T>
Vector<T>::Vector()
{
    _size = 0;
    _elements = nullptr;
    _space = 0;
}
template<class T>
inline Vector<T>::Vector(size_t size, T const & val )
{
    _elements = Allocator.allocate(size);
    _size = size;
    for (int index = 0; index < _size; ++index)
        _elements[index] = val;
}
template<class T>
Vector<T>::Vector(const Vector & arg)
{
    _size = arg._size;
    _elements = Allocator.allocate(arg._size);
    for (int index = 0; index < arg._size; ++index)
        _elements[index] = arg._elements[index];
}
template<class T>
Vector<T>::~Vector()
{
    Allocator.deallocate(_elements);
}

template<class T>
void Vector<T>::resize(size_t newsize, const T& val)
{
    if (newsize > _size)
    {
        if (newsize > _space)  {
            size_t reserved_size = newsize + newsize / 2 + 1;
            Allocator.reshape(_elements,reserved_size);
        }
        for (size_t i = _size; i < newsize; i++)
            _elements[i] = val;
    }
    else
    {
        for (size_t i = newsize; i < _size; i++)
            _elements[i].~T();
    }
    _size = newsize;
}

template<class T>
inline void Vector<T>::reserve(int newalloc)
{
    if (newalloc <= _space) return;
    _elements = Allocator.reshape(_elements,newalloc);
    _space = newalloc;
}

template<class T>
void Vector<T>::clear()
{
    _size = 0;
}
template<class T>
void Vector<T>::push_back(const T & d)
{
    if (_space == 0)
        reserve(8);
    else if (_size == _space)
        reserve(2 * _space);

    _elements[_size] = d;

    ++_size;
}
template<class T>
void Vector<T>::pop_back()
{
    if (_size) --_size;
}

template<class T>
T & Vector<T>::operator[](int i)
{
    return _elements[i];
}
template<class T>
const T & Vector<T>::operator[](int i) const
{
    return _elements[i];
}
template<class T>
const T & Vector<T>::back() const
{
    if (_size>0) return _elements[size - 1];
    return nullptr;
}
template<class T>
T & Vector<T>::back()
{
    return _elements[_size - 1];
}