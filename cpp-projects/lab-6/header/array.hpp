#pragma once

#include "..\header\utils.hpp"

template<typename T>
class Array {
private:
    T* data_;
    int size_;

public:
    class Iterator {
        T* ptr;

    public:
        Iterator(T* start);
        T& GetValue();
        void Next();
        void Previous();
        bool IsEnd(Iterator end);

    };

    Array(int size);
    ~Array();

    int GetSize() const;
    int Find(const T& value);
    bool IsEmpty();
    void Insert(int position, const T& value);

    Iterator Begin();
    Iterator End();
};