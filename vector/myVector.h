#pragma once
#include <cassert>

namespace Somn {

	/// <summary>
	/// Template class for a dynamic array-like container.
	/// </summary>
	template<class T>
	class myVector {
	public:
		typedef T* iterator;           // Iterator type for non-constant access
		typedef const T* const_iterator; // Iterator type for constant access

		/// <summary>
		/// Default constructor
		/// </summary>
		myVector();

		/// <summary>
		/// Add an element to the back of the vector
		/// </summary>
		/// <param name="val">The value to be added.</param>
		void push_back(const T& val);

		/// <summary>
		/// Reserve space for a specified number of elements
		/// </summary>
		/// <param name="n">The number of elements to reserve memory for.</param>
		void reserve(size_t n);

		/// <summary>
		/// Get the current size of the vector
		/// </summary>
		/// <returns>The number of elements in the vector.</returns>
		size_t size() const;

		/// <summary>
		/// Get the current capacity of the vector
		/// </summary>
		/// <returns>The storage capacity of the vector.</returns>
		size_t capacity() const;

		/// <summary>
		/// Get an iterator pointing to the beginning of the vector
		/// </summary>
		/// <returns>An iterator pointing to the first element.</returns>
		iterator begin();

		/// <summary>
		/// Get a constant iterator pointing to the beginning of the vector
		/// </summary>
		/// <returns>A constant iterator pointing to the first element.</returns>
		const_iterator begin() const;

		/// <summary>
		/// Get a constant iterator pointing to the end of the vector
		/// </summary>
		/// <returns>A constant iterator pointing just past the last element.</returns>
		const_iterator end() const;

		/// <summary>
		/// Get an iterator pointing to the end of the vector
		/// </summary>
		/// <returns>An iterator pointing just past the last element.</returns>
		iterator end();

		/// <summary>
		/// Access an element in the vector by index
		/// </summary>
		/// <param name="pos">The index of the element to access.</param>
		/// <returns>A reference to the element at the specified index.</returns>
		T& operator[](size_t pos);

		/// <summary>
		/// Check if the vector is empty.
		/// </summary>
		/// <returns>True if the vector is empty, false otherwise.</returns>
		bool empty() const;

		/// <summary>
		/// Resize the vector to contain 'n' elements.
		/// </summary>
		/// <param name="n">The new size of the vector.</param>
		/// <param name="val">The value used to fill new elements if 'n' is greater than the current size.</param>
		void resize(size_t n, T val = T());

		/// <summary>
		/// Remove the last element from the vector.
		/// </summary>
		void pop_back();

		/// <summary>
		/// Insert an element at a specified position in the vector.
		/// </summary>
		/// <param name="pos">The iterator indicating the position to insert the element.</param>
		/// <param name="val">The value to be inserted.</param>
		/// <returns>An iterator pointing to the inserted element.</returns>
		iterator insert(iterator pos, const T& val);

		/// <summary>
		/// Erase an element at a specified position in the vector.
		/// </summary>
		/// <param name="pos">The iterator indicating the position of the element to be erased.</param>
		/// <returns>An iterator pointing to the element following the erased element.</returns>
		iterator erase(iterator pos);

	private:
		iterator _start;          // Pointer to the start of the vector
		iterator _finish;         // Pointer to the end of the used elements
		iterator _end_of_storage; // Pointer to the end of the allocated memory
	};

	// Default constructor
	template<class T>
	inline myVector<T>::myVector() : _start(nullptr), _finish(nullptr), _end_of_storage(nullptr) {}

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
				memcpy(tempSpace, _start, sizeof(T) * size());
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
}
