#include <iostream>
#include "your_list_header.h"  // Replace with the actual header file name

int main() {
    Somn::list<int> myList;

    // Add elements to the list
    myList.push_back(1);
    myList.push_back(2);
    myList.push_front(0);

    // Insert an element at a specific position
    Somn::list<int>::iterator it = myList.begin();
    ++it;  // Move to the second element
    myList.insert(it, 100);

    // Print the elements using an iterator
    for (Somn::list<int>::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    // Remove elements from the list
    myList.pop_front();
    myList.pop_back();

    // Print the remaining elements
    for (Somn::list<int>::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    return 0;
}
