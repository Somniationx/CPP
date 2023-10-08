#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <iostream>

namespace beat {

    // 链表节点结构体 (Structure for Linked List Node)
    template<class T>
    struct list_node {
        list_node* _next;   // 指向下一个节点 (Pointer to the next node)
        list_node* _prev;   // 指向前一个节点 (Pointer to the previous node)
        T _data;            // 存储的数据 (Stored data)

        // 默认构造函数，初始化指针为空，数据为默认值
        // Default constructor, initializes pointers to nullptr and data to the default value
        list_node() : _next(nullptr), _prev(nullptr), _data(T()) {}

        // 带参数的构造函数，初始化指针为空，数据为传入的值
        // Constructor with parameters, initializes pointers to nullptr and data to the given value
        explicit list_node(const T& val) : _next(nullptr), _prev(nullptr), _data(val) {}
    };

    // 链表迭代器结构体 (Structure for Linked List Iterator)
    template<class T, class Ref, class Ptr>
    struct list_iterator {
        typedef T val_type;
        typedef list_node<T>* node_ptr;
        typedef list_iterator<T, Ref, Ptr> Self;

        // 构造函数，用于初始化迭代器，接受一个指向链表节点的指针
        // Constructor, used to initialize the iterator with a pointer to a list node
        explicit list_iterator(node_ptr pointer) : _pointer(pointer) {}

        // 解引用操作符，返回迭代器当前指向节点的数据引用
        // Dereference operator, returns a reference to the data of the node pointed to by the iterator
        Ref operator*() { return _pointer->_data; }

        Ptr operator->() { return &_pointer->_data; }

        // 不等于操作符，比较两个迭代器是否不相等
        // Inequality operator, compares two iterators for inequality
        bool operator!=(const Self& it) const { return _pointer != it._pointer; }

        bool operator==(const Self& it) const { return _pointer == it._pointer; }

        // 前缀递增操作符，使迭代器指向下一个节点，并返回自身引用
        // Prefix increment operator, makes the iterator point to the next node and returns a reference to itself
        Self& operator++() {
            _pointer = _pointer->_next;
            return *this;
        }

        // 后置递增操作符，使迭代器指向下一个节点，并返回自身引用
        // Postfix increment operator, makes the iterator point to the next node and returns a reference to itself
        Self operator++(int) {
            Self temp(*this);
            _pointer = _pointer->_next;
            return temp;
        }

        // 前缀递减操作符，使迭代器指向前一个节点，并返回自身引用
        // Prefix decrement operator, makes the iterator point to the previous node and returns a reference to itself
        Self& operator--() {
            _pointer = _pointer->_prev;
            return *this;
        }

        // 后置递减操作符，使迭代器指向前一个节点，并返回自身引用
        // Postfix decrement operator, makes the iterator point to the previous node and returns a reference to itself
        Self operator--(int) {
            Self temp(*this);
            _pointer = _pointer->_prev;
            return temp;
        }

        node_ptr _pointer;
    };

    // 链表类 (Linked List Class)
    template<class T>
    class list {
    public:
        typedef list_node<T> node;
        typedef list_iterator<T, T&, T*> iterator;
        typedef list_iterator<T, const T&, const T*> const_iterator;

        // 默认构造函数，初始化一个空链表
        // Default constructor, initializes an empty list
        list() { empty_initialize(); }

        // 返回链表的起始迭代器
        // Returns an iterator pointing to the beginning of the list
        iterator begin() { return iterator(_head->_next); }

        // 返回链表的起始迭代器（常量版本）
        // Returns a constant iterator pointing to the beginning of the list
        const_iterator begin() const { return const_iterator(_head->_next); }

        // 返回链表的结束迭代器
        // Returns an iterator pointing to the end of the list
        iterator end() { return iterator(_head); }

        // 返回链表的结束迭代器（常量版本）
        // Returns a constant iterator pointing to the end of the list
        const_iterator end() const { return const_iterator(_head); }

        // 在链表末尾添加元素
        // Adds an element to the end of the list
        void push_back(const T& val) { insert(end(), val); }

        // 在链表开头添加元素
        // Adds an element to the beginning of the list
        void push_front(const T& val) { insert(begin(), val); }

        // 移除链表开头的元素
        // Removes the element at the beginning of the list
        void pop_front() { erase(begin()); }

        // 移除链表末尾的元素
        // Removes the element at the end of the list
        void pop_back() { erase(--end()); }

        // 检查链表是否为空
        // Checks if the list is empty
        [[nodiscard]] bool empty() const { return _head->_next == _head; }

        // 返回链表的大小
        // Returns the size of the list
        [[nodiscard]] size_t size() const { return _size; }

        // 在指定位置插入元素
        // Inserts an element at the specified position
        iterator insert(iterator pos, const T& val) {
            auto new_node = new node(val);
            node* cur = pos._pointer;
            node* prev = cur->_prev;

            prev->_next = new_node;
            new_node->_prev = prev;
            new_node->_next = cur;
            cur->_prev = new_node;

            ++_size;
            return iterator(new_node);
        }

        // 删除指定位置的元素
        // Deletes the element at the specified position
        iterator erase(iterator pos) {
            assert(pos != end());

            node* prev_node = pos._pointer->_prev;
            node* next_node = pos._pointer->_next;

            prev_node->_next = next_node;
            next_node->_prev = prev_node;

            delete pos._pointer;

            --_size;
            return iterator(next_node);
        }

        // 清空整个链表
        // Clears the entire list
        void clear() {
            iterator it = begin();
            while (it != end()) {
                it = erase(it);
            }
            _size = 0;
        }

        // 复制构造函数，用另一个链表初始化当前链表
        // Copy constructor, initializes the current list with another list
        list(const list<T>& lt) {
            empty_initialize();
            list<T> tmp = (lt.begin(), lt.end());
            swap(tmp);
        }

        // 赋值运算符，将一个链表对象的内容赋值给另一个链表对象
        // Assignment operator, assigns the content of one list object to another
        list<T>& operator=(const list<T>& lt) {
            if (this != &lt) { // 检查自赋值
                clear(); // 清空当前链表

                // 创建一个临时链表副本，然后交换它们
                list<T> tmp = lt;
                swap(tmp);
            }
            return *this;
        }

        // 交换两个链表的内容
        // Swaps the content of two lists
        void swap(list<T>& lt) {
            std::swap(_head, lt._head);
            std::swap(_size, lt._size);
        }

        // 析构函数，清空链表并释放内存
        // Destructor, clears the list and releases memory
        ~list() {
            clear();
            delete _head;
            _head = nullptr;
            _size = 0;
        }

    private:
        node* _head;
        size_t _size{};
    };
}

#endif //LIST_LIST_H
