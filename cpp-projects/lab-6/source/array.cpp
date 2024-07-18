#include "..\header\array.hpp"

template <typename T>
Array<T>::Array(int size) : size_(size)
{
    data_ = new T[size];
    for (int i = 0; i < size_; i++)
    {
        data_[i] = T();
    }
}

template <typename T>
Array<T>::~Array()
{
    delete[] data_;
}

template <typename T>
int Array<T>::GetSize() const
{
    return size_;
}

template <typename T>
int Array<T>::Find(const T &value)
{
    for (int i = 0; i < size_; i++)
    {
        if (data_[i] == value)
        {
            return i;
        }
    }
    return 0;
}

template <typename T>
bool Array<T>::IsEmpty()
{
    return size_ == 0;
}

template <typename T>
void Array<T>::Insert(int position, const T &value)
{
    if (position >= 0 && position < size_)
    {
        data_[position] = value;
    }
    else
    {
        throw std::out_of_range("Index out of bounds");
    }
}

template <class T>
Array<T>::Iterator::Iterator(T *start) : ptr(start) {}

template <typename T>
T &Array<T>::Iterator::GetValue()
{
    return *ptr;
}

template <typename T>
void Array<T>::Iterator::Next()
{
    ptr++;
}

template <typename T>
void Array<T>::Iterator::Previous()
{
    ptr--;
}

template <typename T>
bool Array<T>::Iterator::IsEnd(Iterator end)
{
    return ptr == end.ptr;
}

template <typename T>
typename Array<T>::Iterator Array<T>::Begin()
{
    return Iterator(data_);
}

template <typename T>
typename Array<T>::Iterator Array<T>::End()
{
    return Iterator(data_ + size_);
}

template class Array<bool>;
template class Array<int>;
template class Array<float>;
template class Array<double>;
template class Array<char>;
template class Array<std::string>;