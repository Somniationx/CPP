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
         * @brief Overloaded pre-decrement operator (--) to move to the previous node.
         * @return A reference to the updated iterator.
         */
        __list_iterator<T>& operator--();

        /**
         * @brief Overloaded inequality operator (!=) to compare two iterators.
         * @param it The iterator to be compared with the current iterator.
         * @return True if the iterators are not equal, false otherwise.
         */
        bool operator!=(const __list_iterator<T>& it);
    };

    template<class T>
    struct __list_const_iterator {
        typedef list_node<T> node;

        node* _pnode;       // Pointer to the current node

        /**
         * @brief Constructor to initialize the iterator with a node.
         * @param ptr A pointer to the node to be associated with this iterator.
         */
        __list_const_iterator(node* ptr);

        /**
         * @brief Overloaded dereference operator (*) to access node data.
         * @return A reference to the data stored in the current node.
         */
        const T& operator*() const;

        /**
         * @brief Overloaded pre-increment operator (++) to move to the next node.
         * @return A reference to the updated iterator.
         */
        __list_const_iterator<T>& operator++();

        /**
         * @brief Overloaded pre-decrement operator (--) to move to the previous node.
         * @return A reference to the updated iterator.
         */
        __list_const_iterator<T>& operator--();

        /**
         * @brief Overloaded inequality operator (!=) to compare two iterators.
         * @param it The iterator to be compared with the current iterator.
         * @return True if the iterators are not equal, false otherwise.
         */
        bool operator!=(const __list_const_iterator<T>& it);
    };

    // Doubly linked list class
    template<class T>
    class list {
    public:
        typedef list_node<T> node;
        typedef __list_iterator<T> iterator;
        typedef __list_const_iterator<T> const_iterator;

        /**
         * @brief Initialize an empty list.
         */
        void empty_initialize();

        /**
         * @brief Constructor to initialize an empty list with a dummy head node.
         */
        list();

        /**
         * @brief Copy constructor.
         * @param lt The list to be copied.
         */
        list(const list& lt);

        /**
         * @brief Assignment operator.
         * @param lt The list to be assigned.
         * @return A reference to the assigned list.
         */
        list& operator=(const list<T>& lt);

        /**
         * @brief Add an element to the end of the list.
         * @param val The value to be added to the end of the list.
         */
        void push_back(const T& val);

        /**
         * @brief Add an element to the front of the list.
         * @param val The value to be added to the front of the list.
         */
        void push_front(const T& val);

        /**
         * @brief Insert an element at a specified position in the list.
         * @param pos The iterator pointing to the position where the element should be inserted.
         * @param val The value to be inserted.
         * @return An iterator pointing to the inserted element.
         */
        iterator insert(iterator pos, const T& val);

        /**
         * @brief Erase an element at a specified position in the list.
         * @param pos The iterator pointing to the position of the element to be erased.
         * @return An iterator pointing to the element following the erased element.
         */
        iterator erase(iterator pos);

        /**
         * @brief Remove the first element of the list.
         */
        void pop_front();

        /**
         * @brief Remove the last element of the list.
         */
        void pop_back();

        /**
         * @brief Get an iterator pointing to the beginning of the list.
         * @return An iterator pointing to the first element in the list.
         */
        iterator begin();

        /**
         * @brief Get a const iterator pointing to the beginning of the list.
         * @return A const iterator pointing to the first element in the list.
         */
        const_iterator begin() const;

        /**
         * @brief Get an iterator pointing to the end of the list.
         * @return An iterator pointing one past the end of the list.
         */
        iterator end();

        /**
         * @brief Get a const iterator pointing to the end of the list.
         * @return A const iterator pointing one past the end of the list.
         */
        const_iterator end() const;

        /**
         * @brief Clear the list, removing all elements.
         */
        void clear();

        /**
         * @brief Destructor to clean up the list.
         */
        ~list();

    private:
        node* _head; // Pointer to the dummy head node of the list
    };

    template<class T>
    inline void list<T>::empty_initialize()
    {
        _head = new node(T());
        _head->_next = _head;
        _head->_pre = _head;
    }

    template<class T>
    inline list<T>::list() {
        empty_initialize();
    }

    template<class T>
    inline list<T>::list(const list& lt)
    {
        empty_initialize();

        for (const auto& val : lt) {
            push_back(val);
        }
    }

    template<class T>
    inline list<T>& list<T>::operator=(const list<T>& lt)
    {
        if (this != &lt) {
            this->clear();

            for (const auto& val : lt) {
                this->push_back(val);
            }
        }
        return *this;
    }

    template<class T>
    inline void list<T>::push_back(const T& val) {
        // Insert a new node with the given value at the end of the list.
        insert(end(), val);
    }

    template<class T>
    inline void list<T>::push_front(const T& val)
    {
        // Insert a new node with the given value at the beginning of the list.
        insert(begin(), val);
    }

    template<class T>
    inline typename list<T>::iterator list<T>::insert(iterator pos, const T& val)
    {
        // Insert a new node with the given value at the specified position.
        node* new_node = new node(val);
        node* cur = pos._pnode;
        node* prev = cur->_pre;

        prev->_next = new_node;
        new_node->_pre = prev;
        new_node->_next = cur;
        cur->_pre = new_node;

        return iterator(new_node);
    }

    template<class T>
    inline typename list<T>::iterator list<T>::erase(iterator pos)
    {
        // Erase the node at the specified position.
        assert(pos != end());

        node* prev = pos._pnode->_pre;
        node* next = pos._pnode->_next;

        prev->_next = next;
        next->_pre = prev;

        delete pos._pnode;

        return iterator(next);
    }

    template<class T>
    inline void list<T>::pop_front()
    {
        // Remove the first element of the list.
        erase(begin());
    }

    template<class T>
    inline void list<T>::pop_back()
    {
        // Remove the last element of the list.
        erase(end()._pnode->_pre);
    }

    template<class T>
    inline typename list<T>::iterator list<T>::begin() {
        return iterator(_head->_next);
    }

    template<class T>
    inline typename list<T>::const_iterator list<T>::begin() const
    {
        return const_iterator(_head->_next);
    }

    template<class T>
    inline typename list<T>::iterator list<T>::end() {
        return iterator(_head);
    }

    template<class T>
    inline typename list<T>::const_iterator list<T>::end() const
    {
        return const_iterator(_head);
    }

    template<class T>
    inline void list<T>::clear()
    {
        iterator cur = begin();
        while (cur != end()) {
            cur = erase(cur);
        }
    }

    template<class T>
    inline list<T>::~list()
    {
        clear();
        delete _head;
        _head = nullptr;
    }

    template<class T>
    inline list_node<T>::list_node(const T& val) {
        _next = _pre = nullptr;
        _data = val;
    }

    template<class T>
    inline __list_iterator<T>::__list_iterator(node* ptr)
        : _pnode(ptr) {}

    template<class T>
    inline T& __list_iterator<T>::operator*() {
        return _pnode->_data;
    }

    template<class T>
    inline __list_iterator<T>& __list_iterator<T>::operator++() {
        _pnode = _pnode->_next;
        return *this;
    }

    template<class T>
    inline __list_iterator<T>& __list_iterator<T>::operator--()
    {
        _pnode = _pnode->_pre;
        return *this;
    }

    template<class T>
    inline bool __list_iterator<T>::operator!=(const __list_iterator<T>& it) {
        return _pnode != it._pnode;
    }

    template<class T>
    inline __list_const_iterator<T>::__list_const_iterator(node* ptr)
        :_pnode(ptr)
    {}

    template<class T>
    inline const T& __list_const_iterator<T>::operator*() const
    {
        return _pnode->_data;
    }

    template<class T>
    inline __list_const_iterator<T>& __list_const_iterator<T>::operator++()
    {
        _pnode = _pnode->_next;
        return *this;
    }

    template<class T>
    inline __list_const_iterator<T>& __list_const_iterator<T>::operator--()
    {
        _pnode = _pnode->_pre;
        return *this;
    }

    template<class T>
    inline bool __list_const_iterator<T>::operator!=(const __list_const_iterator<T>& it)
    {
        return _pnode != it._pnode;
    }

}
