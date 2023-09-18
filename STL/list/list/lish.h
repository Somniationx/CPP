#pragma once

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
        list_node(const T& val);
    };

    // Iterator for the linked list
    template<class T>
    struct __list_iterator {
        typedef list_node<T> node;

        node* _pnode;       // Pointer to the current node

        /**
         * @brief Constructor to initialize the iterator with a node.
         * @param ptr A pointer to the node to be associated with this iterator.
         */
        __list_iterator(node* ptr);

        /**
         * @brief Overloaded dereference operator (*) to access node data.
         * @return A reference to the data stored in the current node.
         */
        T& operator*();

        /**
         * @brief Overloaded pre-increment operator (++) to move to the next node.
         * @return A reference to the updated iterator.
         */
        __list_iterator<T>& operator++();

        /**
         * @brief Overloaded inequality operator (!=) to compare two iterators.
         * @param it The iterator to be compared with the current iterator.
         * @return True if the iterators are not equal, false otherwise.
         */
        bool operator!=(const __list_iterator<T>& it);
    };

    // Doubly linked list class
    template<class T>
    class list {
    public:
        typedef list_node<T> node;
        typedef __list_iterator<T> iterator;

        /**
         * @brief Constructor to initialize an empty list with a dummy head node.
         */
        list();

        /**
         * @brief Function to add an element to the end of the list.
         * @param val The value to be added to the end of the list.
         */
        void push_back(const T& val);

        /**
         * @brief Function to obtain an iterator pointing to the beginning of the list.
         * @return An iterator pointing to the first element in the list.
         */
        iterator begin();

        /**
         * @brief Function to obtain an iterator pointing to the end of the list.
         * @return An iterator pointing one past the end of the list.
         */
        iterator end();

    private:
        node* _head; // Pointer to the dummy head node of the list
    };

    /**
     * @brief Constructor for the list class.
     */
    template<class T>
    inline list<T>::list() {
        _head = new node(T());
        _head->_next = _head;
        _head->_pre = _head;
    }

    /**
     * @brief Function to add an element to the end of the list.
     * @param val The value to be added to the end of the list.
     */
    template<class T>
    inline void list<T>::push_back(const T& val) {
        node* new_node = new node(val);
        node* tail = _head->_pre;

        tail->_next = new_node;
        new_node->_pre = tail;
        _head->_pre = new_node;
        new_node->_next = _head;
    }

    /**
     * @brief Function to obtain an iterator pointing to the beginning of the list.
     * @return An iterator pointing to the first element in the list.
     */
    template<class T>
    inline typename list<T>::iterator list<T>::begin() {
        return iterator(_head->_next);
    }

    /**
     * @brief Function to obtain an iterator pointing to the end of the list.
     * @return An iterator pointing one past the end of the list.
     */
    template<class T>
    inline typename list<T>::iterator list<T>::end() {
        return iterator(_head);
    }

    /**
     * @brief Constructor for the list_node class.
     * @param val The data to be stored in the node.
     */
    template<class T>
    inline list_node<T>::list_node(const T& val) {
        _next = _pre = nullptr;
        _data = val;
    }

    /**
     * @brief Constructor for the __list_iterator class.
     * @param ptr A pointer to the node to be associated with this iterator.
     */
    template<class T>
    inline __list_iterator<T>::__list_iterator(node* ptr)
        : _pnode(ptr) {}

    /**
     * @brief Overloaded dereference operator (*) to access node data.
     * @return A reference to the data stored in the current node.
     */
    template<class T>
    inline T& __list_iterator<T>::operator*() {
        return ((*_pnode)._data);
    }

    /**
     * @brief Overloaded pre-increment operator (++) to move to the next node.
     * @return A reference to the updated iterator.
     */
    template<class T>
    inline __list_iterator<T>& __list_iterator<T>::operator++() {
        _pnode = _pnode->_next;
        return *this;
    }

    /**
     * @brief Overloaded inequality operator (!=) to compare two iterators.
     * @param it The iterator to be compared with the current iterator.
     * @return True if the iterators are not equal, false otherwise.
     */
    template<class T>
    inline bool __list_iterator<T>::operator!=(const __list_iterator<T>& it) {
        return _pnode != it._pnode;
    }
}
