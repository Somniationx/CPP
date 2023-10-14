#include <list>

template<class T>
class Queue {
public:
    Queue() {}

    // 向队列尾部插入元素
    void push(const T& x) {
        _c.push_back(x);
    }

    // 从队列头部删除元素
    void pop() {
        _c.pop_front();
    }

    // 返回队列尾部元素的引用
    T& back() {
        return _c.back();
    }

    // 返回队列尾部元素的常量引用
    const T& back() const {
        return _c.back();
    }

    // 返回队列头部元素的引用
    T& front() {
        return _c.front();
    }

    // 返回队列头部元素的常量引用
    const T& front() const {
        return _c.front();
    }

    // 返回队列的大小
    size_t size() const {
        return _c.size();
    }

    // 检查队列是否为空
    bool empty() const {
        return _c.empty();
    }

private:
    std::list<T> _c;
};

int main() {
    Queue<int> myQueue;

    myQueue.push(1);
    myQueue.push(2);
    myQueue.push(3);

    std::cout << "Front element: " << myQueue.front() << std::endl;
    myQueue.pop();
    std::cout << "Front element after pop: " << myQueue.front() << std::endl;
    std::cout << "Queue size: " << myQueue.size() << std::endl;

    return 0;
}
