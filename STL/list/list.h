#ifndef LIST_LIST_H
#define LIST_LIST_H

namespace beat {

    // 链表节点结构体
    template<class T>
    struct list_node {
        list_node *_next;   // 指向下一个节点 (Pointer to the next node)
        list_node *_prev;   // 指向前一个节点 (Pointer to the previous node)
        T _data;            // 存储的数据 (Stored data)

        // 默认构造函数，初始化指针为空，数据为默认值
        // Default constructor, initializes pointers to nullptr and data to the default value
        list_node() : _next(nullptr), _prev(nullptr), _data(T()) {}

        // 带参数的构造函数，初始化指针为空，数据为传入的值
        // Constructor with parameters, initializes pointers to nullptr and data to the given value
        explicit list_node(const T &val) : _next(nullptr), _prev(nullptr), _data(val) {}
    };

    // 链表迭代器结构体
    template<class T, class Ref>
    struct list_iterator {
        typedef list_node<T> node;

        // 构造函数，用于初始化迭代器，接受一个指向链表节点的指针
        // Constructor, used to initialize the iterator with a pointer to a list node
        explicit list_iterator(node *pointer) : _pointer(pointer) {}

        // 解引用操作符，返回迭代器当前指向节点的数据引用
        // Dereference operator, returns a reference to the data of the node pointed to by the iterator
        Ref operator*() { return (*_pointer)._data; }

        // 不等于操作符，比较两个迭代器是否不相等
        // Inequality operator, compares two iterators for inequality
        bool operator!=(const list_iterator<T, Ref> &it) { return _pointer != it._pointer; }

        // 前缀递增操作符，使迭代器指向下一个节点，并返回自身引用
        // Prefix increment operator, makes the iterator point to the next node and returns a reference to itself
        list_iterator<T, Ref> &operator++() {
            _pointer = _pointer->_next;
            return *this;
        }

        // 前缀递减操作符，使迭代器指向前一个节点，并返回自身引用
        // Prefix decrement operator, makes the iterator point to the previous node and returns a reference to itself
        list_iterator<T, Ref> operator--() {
            _pointer = _pointer->_prev;
            return *this;
        }

        node *_pointer;
    };

    // 链表类
    template<class T>
    class list {
    public:
        typedef list_node<T> node;
        typedef list_iterator<T, T &> iterator;
        typedef list_iterator<T, const T &> const_iterator;

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
        void push_back(const T &val) { insert(end(), val); }

        // 在链表开头添加元素
        // Adds an element to the beginning of the list
        void push_front(const T &val) { insert(begin(), val); }

        // 移除链表开头的元素
        // Removes the element at the beginning of the list
        void pop_front() { erase(begin()); }

        // 移除链表末尾的元素
        // Removes the element at the end of the list
        void pop_back() { erase(--end()); }

        // 检查链表是否为空
        // Checks if the list is empty
        bool empty() { return _head->_next == _head; }

        // 在指定位置插入元素
        // Inserts an element at the specified position
        iterator insert(iterator pos, const T &val) {
            auto new_node = new node(val);
            node *cur = pos._pointer;
            node *prev = cur->_prev;

            prev->_next = new_node;
            new_node->_prev = prev;
            new_node->_next = cur;
            cur->_prev = new_node;

            return iterator(new_node);
        }

        // 删除指定位置的元素
        // Deletes the element at the specified position
        iterator erase(iterator pos) {
            assert(pos != end());

            node *prev_node = pos._pointer->_prev;
            node *next_node = pos._pointer->_next;

            prev_node->_next = next_node;
            next_node->_prev = prev_node;

            delete pos._pointer;
            return iterator(next_node);
        }

        // 清空整个链表
        // Clears the entire list
        void clear() {
            iterator it = begin();
            while (it != end()) {
                it = erase(it);
            }
        }

        // 初始化一个空链表
        // Initializes an empty list
        void empty_initialize() {
            _head = new node();
            _head->_next = _head;
            _head->_prev = _head;
        }

        // 析构函数，清空链表并释放内存
        // Destructor, clears the list and releases memory
        ~list() {
            clear();
            delete _head;
            _head = nullptr;
        }

        // 复制构造函数，用另一个链表初始化当前链表
        // Copy constructor, initializes the current list with another list
        list(const list<T> &lt) {
            empty_initialize();

            for (const auto &elem: lt) {
                push_back(elem);
            }
        }

        // 赋值运算符，用另一个链表的内容替换当前链表的内容
        // Assignment operator, replaces the content of the current list with the content of another list
        list<T> &operator==(const list<T> &lt) {
            if (this != &lt) {
                clear();
                for (const auto &elem: lt) {
                    push_back(elem);
                }
            }
            return *this;
        }

    private:
        node *_head;
    };
}

#endif //LIST_LIST_H
