#include <iostream>
#include <vector>

class Stack {
public:
    // Push operation
    void push(int value) {
        stackData.push_back(value);
    }

    // Pop operation
    int pop() {
        if (isEmpty()) {
            std::cerr << "The stack is empty, cannot pop." << std::endl;
            return -1; // You can return a special value for error as needed
        } else {
            int topValue = stackData.back();
            stackData.pop_back();
            return topValue;
        }
    }

    // Get the top element
    int top() {
        if (isEmpty()) {
            std::cerr << "The stack is empty, cannot retrieve the top element." << std::endl;
            return -1; // You can return a special value for error as needed
        } else {
            return stackData.back();
        }
    }

    // Check if the stack is empty
    bool isEmpty() {
        return stackData.empty();
    }

    // Get the size of the stack
    size_t size() {
        return stackData.size();
    }

private:
    std::vector<int> stackData;
};

int main() {
    Stack myStack;

    myStack.push(1);
    myStack.push(2);
    myStack.push(3);

    std::cout << "Stack size: " << myStack.size() << std::endl;
    std::cout << "Top element: " << myStack.top() << std.endl;

    while (!myStack.isEmpty()) {
        std::cout << "Popped element: " << myStack.pop() << std::endl;
    }

    std::cout << "Stack size: " << myStack.size() << std::endl;

    return 0;
}
