#pragma once
#include <cassert>

namespace Somn {

    // Node structure for the linked list
    template<class T>
    struct list_node {
        list_node* _next;   // Pointer to the next node
        list_node* _pre;    // Pointer to the previous node
        T _data;            // Data stored in the node

        /**
         * @brief Constructor to initialize the node with data.
         * @param val The data to be stored in the node.
         */
        list_node(const T& val) : _next(nullptr), _pre(nullptr), _data(val) {}
    };

    // Iterator for the linked list
    template<class T, class Ref, class Ptr>
    struct __list_iterator {
        typedef list_node<T> node;
        typedef __list_iterator<T, Ref, Ptr> Self;

        node* _pnode;       // Pointer to the current node

        /**
         * @brief Constructor to initialize the iterator with a node.
         * @param ptr A pointer to the node to be associated with this iterator.
         */
        __list_iterator(node* ptr) : _pnode(ptr) {}

        /**
         * @brief Overloaded dereference operator (*) to access node data.
         * @return A reference to the data stored in the current node.
         */
        Ref operator*() {
            return _pnode->_data;
        }

        Ptr operator->() {
            return &_pnode->_data;
        }

        /**
         * @brief Overloaded pre-increment operator (++) to move to the next node.
         * @return A reference to the updated iterator.
         */
        Self& operator++() {
            _pnode = _pnode->_next;
            return *this;
        }

        Self operator++(int) {
            Self temp(*this);
            _pnode = _pnode->_next;
            return temp;
        }

        /**
         * @brief Overloaded pre-decrement operator (--) to move to the previous node.
         * @return A reference to the updated iterator.
         */
        Self& operator--() {
            _pnode = _pnode->_pre;
            return *this;
        }

        Self operator--(int) {
            Self temp(*this);
            _pnode = _pnode->_pre;
            return temp;
        }

        bool operator!=(const Self& it) const {
            return _pnode != it._pnode;
        }

        /**
         * @brief Overloaded inequality operator (!=) to compare two iterators.
         * @param it The iterator to be compared with the current iterator.
         * @return True if the iterators are not equal, false otherwise.
         */
        bool operator!=(const __list_iterator<T, Ref>& it) {
            return _pnode != it._pnode;
        }
    };

    // Doubly linked list class
    template<class T>
    class list {
    public:
        typedef list_node<T> node;
        typedef __list_iterator<T, T&, T*> iterator;
        typedef __list_iterator<T, const T&, const T*> const_iterator;

        /**
         * @brief Initialize an empty list.
         */
        list() {
            empty_initialize();
        }

        /**
         * @brief Copy constructor.
         * @param lt The list to be copied.
         */
        list(const list& lt) {
            empty_initialize();

            /* for (const auto& val : lt) {
                 push_back(val);
             }*/

            empty_initialize();
            list<T> temp(lt.begin(), lt.edn());
            swap(temp);
        }

        template<class InputIterator>
        list(InputIterator first, InputIterator last) {
            empty_initialize();

            while (first != last) {
                push_back(*first);
                first++;
            }
        }

        void swap(list<T>& lt) {
            std::swap(_head, lt._head);
            std::swap(_size, lt._size);
        }

        /**
         * @brief Assignment operator.
         * @param lt The list to be assigned.
         * @return A reference to the assigned list.
         */
        list& operator=(const list<T>& lt) {
            if (this != &lt) {
                this->clear();

                for (const auto& val : lt) {
                    this->push_back(val);
                }
            }
            return *this;
        }

        list<T>& operator=(list<T> lt) {
            swap(lt);
            return *this;
        }

        /**
         * @brief Add an element to the end of the list.
         * @param val The value to be added to the end of the list.
         */
        void push_back(const T& val) {
            // Insert a new node with the given value at the end of the list.
            insert(end(), val);
        }

        /**
         * @brief Add an element to the front of the list.
         * @param val The value to be added to the front of the list.
         */
        void push_front(const T& val) {
            // Insert a new node with the given value at the beginning of the list.
            insert(begin(), val);
        }

        /**
         * @brief Insert an element at a specified position in the list.
         * @param pos The iterator pointing to the position where the element should be inserted.
         * @param val The value to be inserted.
         * @return An iterator pointing to the inserted element.
         */
        iterator insert(iterator pos, const T& val) {
            // Insert a new node with the given value at the specified position.
            node* new_node = new node(val);
            node* cur = pos._pnode;
            node* prev = cur->_pre;

            prev->_next = new_node;
            new_node->_pre = prev;
            new_node->_next = cur;
            cur->_pre = new_node;

            _size++;

            return iterator(new_node);
        }

        /**
         * @brief Erase an element at a specified position in the list.
         * @param pos The iterator pointing to the position of the element to be erased.
         * @return An iterator pointing to the element following the erased element.
         */
        iterator erase(iterator pos) {
            // Erase the node at the specified position.
            assert(pos != end());

            node* prev = pos._pnode->_pre;
            node* next = pos._pnode->_next;

            prev->_next = next;
            next->_pre = prev;

            delete pos._pnode;

            _size--;

            return iterator(next);
        }

        /**
         * @brief Remove the first element of the list.
         */
        void pop_front() {
            // Remove the first element of the list.
            erase(begin());
        }

        /**
         * @brief Remove the last element of the list.
         */
        void pop_back() {
            // Remove the last element of the list.
            erase(end()._pnode->_pre);
        }

        /**
         * @brief Get an iterator pointing to the beginning of the list.
         * @return An iterator pointing to the first element in the list.
         */
        iterator begin() {
            return iterator(_head->_next);
        }

        /**
         * @brief Get a const iterator pointing to the beginning of the list.
         * @return A const iterator pointing to the first element in the list.
         */
        const_iterator begin() const {
            return const_iterator(_head->_next);
        }

        /**
         * @brief Get an iterator pointing to the end of the list.
         * @return An iterator pointing one past the end of the list.
         */
        iterator end() {
            return iterator(_head);
        }

        /**
         * @brief Get a const iterator pointing to the end of the list.
         * @return A const iterator pointing one past the end of the list.
         */
        const_iterator end() const {
            return const_iterator(_head);
        }

        /**
         * @brief Clear the list, removing all elements.
         */
        void clear() {
            iterator cur = begin();
            while (cur != end()) {
                cur = erase(cur);
            }
        }

        size_t size() const {
            return _size;
        }

        bool empty() const {
            return _size == 0;
        }

        /**
         * @brief Destructor to clean up the list.
         */
        ~list() {
            clear();
            delete _head;
            _head = nullptr;
        }

    private:
        node* _head; // Pointer to the dummy head node of the list
        size_t _size;

        inline void empty_initialize() {
            _head = new node(T());
            _head->_next = _head;
            _head->_pre = _head;
            _size = 0;
        }
    };

    // Constant Iterator for the linked list
    template<class T>
    struct __list_const_iterator {
        typedef list_node<T> node;

        const node* _pnode;  // Pointer to the current node

        /**
         * @brief Constructor to initialize the constant iterator with a node.
         * @param ptr A pointer to the node to be associated with this constant iterator.
         */
        __list_const_iterator(const node* ptr) : _pnode(ptr) {}

        /**
         * @brief Overloaded dereference operator (*) to access node data.
         * @return A constant reference to the data stored in the current node.
         */
        const T& operator*() const {
            return _pnode->_data;
        }

        /**
         * @brief Overloaded pre-increment operator (++) to move to the next node.
         * @return A reference to the updated constant iterator.
         */
        __list_const_iterator<T>& operator++() {
            _pnode = _pnode->_next;
            return *this;
        }

        /**
         * @brief Overloaded pre-decrement operator (--) to move to the previous node.
         * @return A reference to the updated constant iterator.
         */
        __list_const_iterator<T>& operator--() {
            _pnode = _pnode->_pre;
            return *this;
        }

        /**
         * @brief Overloaded inequality operator (!=) to compare two constant iterators.
         * @param it The constant iterator to be compared with the current constant iterator.
         * @return True if the constant iterators are not equal, false otherwise.
         */
        bool operator!=(const __list_const_iterator<T>& it) const {
            return _pnode != it._pnode;
        }
    };

}
