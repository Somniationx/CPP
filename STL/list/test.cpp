#include <iostream>
#include "list_en.h"

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
    for (int & iter : myList) {
        std::cout << iter << " ";
    }
    std::cout << std::endl;

    // Remove elements from the list
    myList.pop_front();
    myList.pop_back();

    // Print the remaining elements
    for (int & iter : myList) {
        std::cout << iter << " ";
    }
    std::cout << std::endl;

    return 0;
}
