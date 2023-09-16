/**
 * @file myVector.h
 * This is an internal header file, included by other library headers.
 * Do not attempt to use it directly.
 * @headername{myVector}
 */
#pragma once
#include <cassert>

namespace Somn {

	/**
	 * @brief Template class for a dynamic array-like container.
	 * @tparam T The type of elements in the container.
	 */
	template<class T>
	class myVector {
	public:
		typedef T* iterator;           /**< Iterator type for non-constant access */
		typedef const T* const_iterator; /**< Iterator type for constant access */

		/**
		 * @brief Default constructor
		 */
		myVector();

		/**
		 * @brief Copy constructor, copies elements from another myVector object.
		 * @param v The myVector object to copy from.
		 */
		myVector(const myVector<T>& v);

		/**
		 * @brief Constructs a myVector object from an iterator range.
		 * @param first The beginning of the iterator range.
		 * @param last The end of the iterator range.
		 */
		template<class InputIterator>
		myVector(InputIterator first, InputIterator last);

		/**
		 * @brief Add an element to the back of the vector
		 * @param val The value to be added.
		 */
		void push_back(const T& val);

		/**
		 * @brief Reserve space for a specified number of elements
		 * @param n The number of elements to reserve memory for.
		 */
		void reserve(size_t n);

		/**
		 * @brief Get the current size of the vector
		 * @return The number of elements in the vector.
		 */
		size_t size() const;

		/**
		 * @brief Get the current capacity of the vector
		 * @return The storage capacity of the vector.
		 */
		size_t capacity() const;

		/**
		 * @brief Get an iterator pointing to the beginning of the vector
		 * @return An iterator pointing to the first element.
		 */
		iterator begin();

		/**
		 * @brief Get a constant iterator pointing to the beginning of the vector
		 * @return A constant iterator pointing to the first element.
		 */
		const_iterator begin() const;

		/**
		 * @brief Get a constant iterator pointing to the end of the vector
		 * @return A constant iterator pointing just past the last element.
		 */
		const_iterator end() const;

		/**
		 * @brief Get an iterator pointing to the end of the vector
		 * @return An iterator pointing just past the last element.
		 */
		iterator end();

		/**
		 * @brief Access an element in the vector by index
		 * @param pos The index of the element to access.
		 * @return A reference to the element at the specified index.
		 */
		T& operator[](size_t pos);

		/**
		 * @brief Check if the vector is empty.
		 * @return True if the vector is empty, false otherwise.
		 */
		bool empty() const;

		/**
		 * @brief Resize the vector to contain 'n' elements.
		 * @param n The new size of the vector.
		 * @param val The value used to fill new elements if 'n' is greater than the current size.
		 */
		void resize(size_t n, T val = T());

		/**
		 * @brief Remove the last element from the vector.
		 */
		void pop_back();

		/**
		 * @brief Insert an element at a specified position in the vector.
		 * @param pos The iterator indicating the position to insert the element.
		 * @param val The value to be inserted.
		 * @return An iterator pointing to the inserted element.
		 */
		iterator insert(iterator pos, const T& val);

		/**
		 * @brief Erase an element at a specified position in the vector.
		 * @param pos The iterator indicating the position of the element to be erased.
		 * @return An iterator pointing to the element following the erased element.
		 */
		iterator erase(iterator pos);

		/**
		 * @brief Swaps the elements of this vector with the elements of another vector.
		 * @param v The vector to swap elements with.
		 */
		void swap(myVector<T>& v);

		/**
		 * @brief Removes all elements from the vector, leaving it empty.
		 */
		void clear();

		/**
		 * @brief Copy assignment operator for myVector.
		 * @param v The myVector object to copy from.
		 * @return Reference to this myVector after copying.
		 */
		myVector<T>& operator=(const myVector<T>& v);

		/**
		 * @brief Constructor for creating a myVector with a specified size and initial value.
		 * @param n The size of the vector.
		 * @param val The initial value for elements in the vector.
		 */
		myVector(size_t n, const T& val = T());
		myVector(int n, const T& val = T());

		/**
		 * @brief Destructor for the myVector class.
		 */
		~myVector();

	private:
		iterator _start;          /**< Pointer to the start of the vector */
		iterator _finish;         /**< Pointer to the end of the used elements */
		iterator _end_of_storage; /**< Pointer to the end of the allocated memory */
	};

	// Default constructor
	template<class T>
	inline myVector<T>::myVector() : _start(nullptr), _finish(nullptr), _end_of_storage(nullptr) {}

	template<class T>
	inline myVector<T>::myVector(const myVector<T>& v)
		: _start(nullptr),
		_finish(nullptr),
		_end_of_storage(nullptr)
	{
		// Create a temporary myVector object 'temp' and initialize it with the elements from 'v'
		myVector<T> temp(v.begin(), v.end());

		// Swap the contents of 'temp' with the current object
		swap(temp);
	}


	// Add an element to the back of the vector
	template<class T>
	inline void myVector<T>::push_back(const T& val)
	{
		// Check if space needs to be expanded or opened up when the capacity is full or if it is an initial vector.
		if (_finish == _end_of_storage) {
			size_t newCapacity = (_finish == nullptr) ? 4 : capacity() * 2;
			reserve(newCapacity);
		}

		// Insert val and update the vector pointers.
		*(_finish) = val;
		_finish++;
	}

	// Reserve space for a specified number of elements
	template<class T>
	inline void myVector<T>::reserve(size_t newCapacity)
	{
		// This function cannot perform capacity reduction.
		if (newCapacity > capacity()) {
			// Allocate temporary space for the new capacity.
			T* tempSpace = new T[newCapacity];

			// If the vector is not empty, copy the existing data to the new space.
			if (_start) {
				//memcpy(tempSpace, _start, sizeof(T) * size());
				for (size_t index = 0; index < size(); index++) {
					tempSpace[index] = _start[index];
				}
				delete[] _start;
			}

			// Preserve the size value to avoid errors in the subsequent size() function.
			size_t len = size();

			// Update the vector pointers.
			_start = tempSpace;
			_finish = _start + len;
			_end_of_storage = _start + newCapacity;
		}
	}

	// Get the current size of the vector
	template<class T>
	inline size_t myVector<T>::size() const {
		if (_start == nullptr || _finish == nullptr)
		{
			// Handling the case of an empty object
			return 0;
		}
		return _finish - _start;
	}

	// Get the current capacity of the vector
	template<class T>
	inline size_t myVector<T>::capacity() const
	{
		if (_start == nullptr || _end_of_storage == nullptr) {
			// Handling the case of an empty object
			return 0;
		}
		return _end_of_storage - _start;
	}

	// Get an iterator pointing to the beginning of the vector
	template<class T>
	inline typename myVector<T>::iterator myVector<T>::begin()
	{
		// Return an iterator pointing to the beginning of the vector.
		return _start;
	}

	// Get a constant iterator pointing to the beginning of the vector
	template<class T>
	inline typename myVector<T>::const_iterator myVector<T>::begin() const
	{
		// Return a constant iterator pointing to the beginning of the vector.
		return _start;
	}

	// Get a constant iterator pointing to the end of the vector
	template<class T>
	inline typename myVector<T>::const_iterator myVector<T>::end() const
	{
		// Return a constant iterator pointing to the end of the vector.
		return _finish;
	}

	// Get an iterator pointing to the end of the vector
	template<class T>
	inline typename myVector<T>::iterator myVector<T>::end()
	{
		// Return an iterator pointing to the end of the vector.
		return _finish;
	}

	// Access an element in the vector by index
	template<class T>
	inline T& myVector<T>::operator[](size_t pos)
	{
		// Access the element at the specified position.
		assert(pos < size());
		return _start[pos];
	}

	// Check if the vector is empty.
	template<class T>
	inline bool myVector<T>::empty() const
	{
		// Check if the vector is empty by comparing the start and finish pointers.
		// If they are equal, the vector is empty.
		return _start == _finish;
	}

	// Resize the vector to contain 'n' elements.
	template<class T>
	inline void myVector<T>::resize(size_t n, T val)
	{
		// Check if the requested size 'n' is greater than the current capacity.
		if (n > capacity()) {
			// If 'n' is greater than the current capacity, reserve space for it.
			reserve(n);
		}

		// Check if 'n' is less than or equal to the current size.
		if (n <= size()) {
			// If 'n' is less than or equal to the current size, simply update the finish pointer.
			_finish = _start + n;
		}
		else {
			// If 'n' is greater than the current size, fill the additional elements with 'val'.
			while (_finish < _start + n) {
				*_finish = val;
				_finish++;
			}
		}
	}

	// Remove the last element from the vector.
	template<class T>
	inline void myVector<T>::pop_back()
	{
		assert(!empty());
		_finish--;
	}

	// Insert an element at a specified position in the vector.
	template<class T>
	inline typename myVector<T>::iterator myVector<T>::insert(iterator pos, const T& val)
	{
		assert(pos >= _start && pos <= _finish);
		size_t len = pos - _start;

		if (_finish == _end_of_storage) {
			size_t newCapacity = capacity() == 0 ? 4 : capacity() * 2;
			reserve(newCapacity);
			pos = _start + len;
		}

		iterator end = begin() - 1;
		while (end >= pos) {
			*(end + 1) = *end;
			end--;
		}
		*pos = val;
		_finish++;
		return pos;
	}

	// Erase an element at a specified position in the vector.
	template<class T>
	inline typename myVector<T>::iterator myVector<T>::erase(iterator pos)
	{
		assert(!empty());
		assert(pos >= _start);
		assert(pos < _finish);

		iterator cur = pos;
		while (cur < _finish - 1) {
			*cur = *(cur + 1);
			cur++;
		}
		_finish--;
		return pos;
	}

	template<class T>
	inline void myVector<T>::swap(myVector<T>& v)
	{
		// Swap the pointers to the start, finish, and end of storage with another vector.
		std::swap(_start, v._start);
		std::swap(_finish, v._finish);
		std::swap(_end_of_storage, v._end_of_storage);
	}

	template<class T>
	inline void myVector<T>::clear()
	{
		// Set the finish pointer to the start pointer effectively clearing the vector.
		_finish = _start;
	}

	template<class T>
	inline myVector<T>& myVector<T>::operator=(const myVector<T>& v)
	{
		if (v._start != _start) {
			myVector<T> temp(v);
			swap(v);
		}
		return *this;
	}

	template<class T>
	inline myVector<T>::myVector(size_t n, const T& val)
		: _start(nullptr),
		_finish(nullptr),
		_end_of_storage(nullptr)
	{
		reserve(n);
		for (size_t index = 0; index < n; index++) {
			push_back(val);
		}
	}

	template<class T>
	inline myVector<T>::myVector(int n, const T& val)
		: _start(nullptr),
		_finish(nullptr),
		_end_of_storage(nullptr)
	{
		reserve(n);
		for (size_t index = 0; index < n; index++) {
			push_back(val);
		}
	}

	template<class T>
	inline myVector<T>::~myVector()
	{
		// Deallocate the dynamically allocated memory
		delete[] _start;

		// Set pointers to nullptr to indicate that the object is now empty
		_start = _finish = _end_of_storage = nullptr;
	}

	template<class T>
	template<class InputIterator>
	inline myVector<T>::myVector(InputIterator first, InputIterator last)
		: _start(nullptr),
		_finish(nullptr),
		_end_of_storage(nullptr)
	{
		// Iterate through the input range and add elements to the vector using push_back
		while (first != last) {
			push_back(*first);
			first++;
		}
	}

}