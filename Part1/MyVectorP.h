#pragma once

#include <stdexcept> 

template <typename T>
class MyVectorP {
private:
    unsigned int capacity; 
    T** elements; 

public:
    
    MyVectorP(unsigned int size = 0, T init = T())
        : capacity(size)
    {
        elements = new T * [capacity];
        for (size_t i = 0; i < capacity; ++i) {
            elements[i] = new T(init);
        }
    }


    
    ~MyVectorP() {
        for (size_t i = 0; i < capacity; ++i) {
            delete elements[i];
        }
        delete[] elements;
    }

    
    unsigned int GetSize() const {
        return capacity;
    }

    
    void  AdjustSize(unsigned int newSize, T init = T()) {
        T** temp = new T * [newSize];
        for (size_t i = 0; i < newSize; ++i) {
            if (i < capacity) {
                temp[i] = elements[i];
            }
            else {
                temp[i] = new T(init);
            }
        }
        
        for (size_t i = newSize; i < capacity; ++i) {
            delete elements[i];
        }
        delete[] elements;
        elements = temp;
        capacity = newSize;
    }

    void PushBack(T& value) {
        AdjustSize(capacity + 1);
        elements[capacity - 1] = new T(value);
    }

    void InsertElement(unsigned int index, const T& value = T()) {
        if (index >= capacity) {
            throw std::out_of_range("Index out of bounds");
        }
        AdjustSize(capacity + 1);
        delete elements[capacity - 1];
        for (size_t i = capacity - 1; i > index; --i) {
            elements[i] = elements[i - 1];
        }

        elements[index] = new T(value);
    }

    
    void RemoveElement(unsigned int index) {
        if (index >= capacity) {
            throw std::out_of_range("Index out of bounds");
        }
        delete elements[index];
        for (size_t i = index; i < capacity - 1; ++i) {
            elements[i] = elements[i + 1];
        }
        capacity--;
    }

    
    T& operator[](int index) {
        if (index >= static_cast<int>(capacity) || index < 0) {
            throw std::out_of_range("Array index out of bounds");
        }
        return *elements[index];
    }


};
