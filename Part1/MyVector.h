#pragma once
#include <stdexcept>

template <class T>
class MyVector {
private:
    unsigned int capacity;
    T* elements;

public:

    MyVector(unsigned int initialCapacity = 0, T initialValue = T())
        : capacity(initialCapacity), elements(new T[initialCapacity])
    {
        for (size_t i = 0; i < capacity; ++i) {
            elements[i] = initialValue;
        }
    }

    
    ~MyVector() {
        delete[] elements;
    }


    void Pushback(const T& value) {
        AdjustSize(capacity + 1);
        elements[capacity - 1] = value;
    }

    
    void InsertElement(unsigned int position, const T& value) {
        if (position > capacity) {
            throw std::out_of_range("Position out of bounds");
        }
        AdjustSize(capacity + 1);
        for (size_t i = capacity - 1; i > position; --i) {
            elements[i] = elements[i - 1];
        }
        elements[position] = value;
    }

    
    void RemoveElement(unsigned int position) {
        if (position >= capacity) {
            throw std::out_of_range("Position out of bounds");
        }
        for (size_t i = position; i < capacity - 1; ++i) {
            elements[i] = elements[i + 1];
        }
        AdjustSize(capacity - 1);
    }

    T& operator[](int index) {
        if (index < 0 || index >= static_cast<int>(capacity)) {
            throw std::out_of_range("Index out of bounds");
        }
        return elements[index];
    }

    
    void AdjustSize(unsigned int newSize) {
        T* temp = new T[newSize];
        for (size_t i = 0; i < newSize; ++i) {
            if (i < capacity) {
                temp[i] = elements[i];
            }
        }
        delete[] elements;
        elements = temp;
        capacity = newSize;
    }
};
