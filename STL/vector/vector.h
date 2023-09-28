#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <iostream>
#include <cstddef>
#include <cassert>

namespace Track {
    template<class T>
    class vector {
    public:
        typedef T *iterator;
        typedef const T *const_iterator;
        typedef T value_type;
        typedef size_t size_type;

        vector() : _start(nullptr), _finish(nullptr), _end_of_storage(nullptr) {}

        vector(const vector<value_type> &v)
                : _start(nullptr),
                  _finish(nullptr),
                  _end_of_storage(nullptr) {
            vector<value_type> tmp(v.begin(), v.end());
            swap(tmp);
        }

        template<class InputIterator>
        vector(InputIterator first, InputIterator last)
                : _start(nullptr),
                  _finish(nullptr),
                  _end_of_storage(nullptr) {
            while (first != last) {
                push_back(*first);
                ++first;
            }
        }

        explicit vector(size_type numItems, const value_type &val = value_type())
                : _start(nullptr),
                  _finish(nullptr),
                  _end_of_storage(nullptr) {
            reserve(numItems);

            for (size_type index = 0; index < numItems; ++index)
                push_back(val);
        }

        explicit vector(int numItems, const value_type &val = value_type())
                : _start(nullptr),
                  _finish(nullptr),
                  _end_of_storage(nullptr) {
            reserve(numItems);

            for (int index = 0; index < numItems; ++index)
                push_back(val);
        }

        iterator begin() {
            return _start;
        }

        iterator end() {
            return _finish;
        }

        const_iterator begin() const {
            return _start;
        }

        const_iterator end() const {
            return _finish;
        }

        void push_back(const value_type &val) {
            if (_finish == _end_of_storage) {
                size_type newCapacity = (capacity() == 0) ? 4 : capacity() * 2;
                reserve(newCapacity);
            }

            *_finish = val;
            ++_finish;
        }

        void pop_back() {
            assert(!empty());
            --_finish;
        }

        // TODO 注意野指针问题 pos 为什么不用&传递呢
        iterator insert(iterator pos, const value_type &val) {
            assert(pos >= _start);
            assert(pos <= _finish);

            if (_finish == _end_of_storage) {
                size_type len = pos - _start;
                size_type newCapacity = (capacity() == 0) ? 4 : capacity() * 2;
                reserve(newCapacity);
                pos = _start + len;
            }

            iterator last = end();
            while (last != pos) {
                *last = *(last - 1);
                --last;
            }
            *pos = val;
            ++_finish;

            return pos;
        }

        iterator erase(iterator pos) {
            assert(pos >= _start);
            assert(pos < _finish);
            assert(!empty());

            iterator cur = pos;
            while (cur != _finish - 1) {
                *cur = *(cur + 1);
                ++cur;
            }
            --_finish;

            return pos;
        }

        void reserve(size_t numItems) {
            if (numItems > capacity()) {
                auto *tmp = new T[numItems];
                size_t oldSize = size();
                if (_start) {
//                    memcpy(tmp, _start, sizeof(value_type) * size());
                    for (size_type index = 0; index < size(); ++index)
                        tmp[index] = _start[index];

                    delete[] _start;
                }

                _start = tmp;
                _finish = tmp + oldSize;
                _end_of_storage = _start + numItems;
            }
        }

        void resize(size_type numItems, value_type val = value_type()) {
            if (numItems > capacity())
                reserve(numItems);

            if (numItems < size()) {
                _finish = _start + numItems;
            } else if (numItems > size()) {
                while (_finish < _end_of_storage)
                    push_back(val);
            } else {
                // numItems == size() do nothing
            }
        }

        [[nodiscard]] size_type size() const {
            return _finish - _start;
        }

        [[nodiscard]] size_type capacity() const {
            return _end_of_storage - _start;
        }

        [[nodiscard]] bool empty() const {
            return _finish == _start;
        }

        void swap(vector<value_type> &v) {
            std::swap(_start, v._start);
            std::swap(_finish, v._finish);
            std::swap(_end_of_storage, v._end_of_storage);
        }

        void clear() {
            _finish = _start;
        }

        value_type &operator[](size_type pos) {
            assert(pos < size());
            return _start[pos];
        }

        const value_type &operator[](size_type pos) const {
            assert(pos < size());
            return _start[pos];
        }

        vector<value_type> &operator=(const vector<value_type> &v) {
            if (v._start == _start) {
                vector<value_type> tmp(v);
                swap(v);
            }
            return *this;
        }

        ~vector() {
            delete[] _start;
            _start = _finish = _end_of_storage = nullptr;
        }

    private:
        iterator _start;
        iterator _finish;
        iterator _end_of_storage;
    };
}

#endif //VECTOR_VECTOR_H
