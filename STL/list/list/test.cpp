#include <iostream>
#include "lish.h"

int main() {
    // Create a linked list of integers
    Somn::list<int> myLinkedList;

    // Add some elements to the list
    myLinkedList.push_back(10);
    myLinkedList.push_back(20);
    myLinkedList.push_back(30);

    // Create an iterator to traverse the list
    Somn::list<int>::iterator it = myLinkedList.begin();

    // Print the elements of the list using the iterator
    std::cout << "Elements in the list: ";
    while (it != myLinkedList.end()) {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << std::endl;

    // Output should be: Elements in the list: 10 20 30

    return 0;
}
