#include <iostream>
#include "myVector.h" // Include your header file based on your filename and path

int main() {
    using namespace Somn;

    // Create an empty myVector object
    myVector<int> myVec;

    // Add some elements to myVector
    for (int i = 0; i < 10; ++i) {
        myVec.push_back(i * 2);
    }

    // Output the elements in myVector
    std::cout << "myVector elements: ";
    for (auto it = myVec.begin(); it != myVec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Test the size() and capacity() functions
    std::cout << "Size of myVector: " << myVec.size() << std::endl;
    std::cout << "Capacity of myVector: " << myVec.capacity() << std::endl;

    // Test the operator[] function
    std::cout << "Element at index 3: " << myVec[3] << std::endl;

    return 0;
}
