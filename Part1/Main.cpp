#include <iostream>
#include <vector>
#include <ctime>
#include "MyVector.h"
#include "MyVectorP.h"

#define SAMPLE_COUNT 10
#define OBJECT_SIZE_MB 5
#define ARRAY_SIZE 100

// Helper function to generate a large object
struct LargeObject {
    std::vector<char> data;
    LargeObject(size_t size_in_mb = 1) : data(size_in_mb * 1024 * 1024) {}
};

int main() {
    // Create a LargeObject
    LargeObject testObject(OBJECT_SIZE_MB);

    // Variables to store total clock times
    std::clock_t vector_insert_total = 0;
    std::clock_t vector_remove_total = 0;
    std::clock_t vector_pointer_insert_total = 0;
    std::clock_t vector_pointer_remove_total = 0;

    // Run test cases
    for (int i = 1; i <= SAMPLE_COUNT; ++i) {
        // Vector tests
        MyVector<LargeObject> vec(ARRAY_SIZE, testObject);

        std::clock_t start = std::clock();
        vec.InsertElement(0, testObject);
        std::clock_t end = std::clock();
        vector_insert_total += (end - start);

        start = std::clock();
        vec.RemoveElement(0);
        end = std::clock();
        vector_remove_total += (end - start);

        // VectorPointer tests
        MyVectorP<LargeObject> vecPointer(ARRAY_SIZE, testObject);

        start = std::clock();
        vecPointer.InsertElement(0, testObject);
        end = std::clock();
        vector_pointer_insert_total += (end - start);

        start = std::clock();
        vecPointer.RemoveElement(0);
        end = std::clock();
        vector_pointer_remove_total += (end - start);
    }

    // Calculate average times in milliseconds
    double vector_insert_avg = (vector_insert_total / (double)CLOCKS_PER_SEC) * 1000 / SAMPLE_COUNT;
    double vector_remove_avg = (vector_remove_total / (double)CLOCKS_PER_SEC) * 1000 / SAMPLE_COUNT;
    double vector_pointer_insert_avg = (vector_pointer_insert_total / (double)CLOCKS_PER_SEC) * 1000 / SAMPLE_COUNT;
    double vector_pointer_remove_avg = (vector_pointer_remove_total / (double)CLOCKS_PER_SEC) * 1000 / SAMPLE_COUNT;

    // Output results
    std::cout << "Average insert time for Vector: " << vector_insert_avg << " ms\n";
    std::cout << "Average remove time for Vector: " << vector_remove_avg << " ms\n";
    std::cout << "Average insert time for VectorPointer: " << vector_pointer_insert_avg << " ms\n";
    std::cout << "Average remove time for VectorPointer: " << vector_pointer_remove_avg << " ms\n";
    std::cout << "Press any key to close\n";
    std::getchar();
    return 0;
}
