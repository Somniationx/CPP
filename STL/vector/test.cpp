#include <iostream>
#include "myVector.h" // Include your header file based on your filename and path

void test_vector1() {
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
}

void test_vector2() {
    using namespace Somn;

    myVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3); 
    v.push_back(4); 

    myVector<int>::iterator it = std::find(v.begin(), v.end(), 3);

    if (it != v.end()) {
        v.erase(it);   // Erase the element pointed to by it
        // After erasing, it is invalidated and should not be used.
    }

    // Now, you can't use it1 here because it's invalidated.
    // *it = 5; or std::cout << *it << std::endl;

    std::cout << "myVector elements: ";
    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";  // Print the elements in myVector
    }
}

void test_vector3() {
    using namespace Somn;

    myVector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(2);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);

    myVector<int>::iterator it = v.begin();  // Initialize an iterator pointing to the beginning of the vector

    // wrong writing
    while (it != v.end()) {  // Loop until the iterator reaches the end of the vector
        if (*it % 2 == 0) {  // Check if the element pointed to by the iterator is even
            v.erase(it);     // Erase the even element from the vector
            // Warning: After erasing, the iterator 'it' is invalidated and should not be used.
        }
        else {
            it++;  // Move the iterator to the next element
        }
    }
    
    // Correct writing
    //while (it != v.end()) {  // Loop until the iterator reaches the end of the vector
    //    if (*it % 2 == 0) {  // Check if the element pointed to by the iterator is even
    //        it = v.erase(it);  // Erase the even element from the vector and get the new iterator
    //    }
    //    else {
    //        ++it;  // Move the iterator to the next element
    //    }
    //}

    // WARNING: You should not use 'it' here as it may be invalidated by the erase operation.

    std::cout << "myVector elements: ";
    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";  // Print the elements in myVector
    }
}

int main() {
    test_vector3();
    return 0;
}
