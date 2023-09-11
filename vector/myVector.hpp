// Created by Dell on 2023/9/11.

#ifndef VECTOR_MYVECTOR_HPP
#define VECTOR_MYVECTOR_HPP

#include <cstddef>
#include <cstring>
#include <cassert>

namespace cocoon {
    template<class T>
    class myVector {
    public:
        typedef T *iterator; // 定义一个迭代器类型
        typedef const T *const_iterator; // 定义一个常量迭代器类型

        myVector(); // 默认构造函数

        void push_back(const T &elem); // 向容器尾部添加元素

        void reserve(size_t newCapacity); // 预分配内存空间

        [[nodiscard]] size_t size() const; // 返回容器的大小

        [[nodiscard]] size_t capacity() const; // 返回容器的容量

        iterator begin(); // 返回容器的起始迭代器

        iterator end(); // 返回容器的结束迭代器

        const_iterator begin() const; // 返回容器的常量起始迭代器

        const_iterator end() const; // 返回容器的常量结束迭代器

        T &operator[](size_t pos); // 重载下标运算符，用于访问指定位置的元素

        [[nodiscard]] bool empty() const; // 检查容器是否为空

        void resize(size_t n, T value = T()); // 调整容器的大小，并填充默认值

        void pop_back(); // 移除容器尾部的元素

        void clear(); // 清空容器

        void insert(iterator pos, const T &val); // 在指定位置插入元素

        void erase(iterator pos); // 移除指定位置的元素

    private:
        iterator _start; // 指向容器起始位置的指针
        iterator _finish; // 指向容器结束位置的指针
        iterator _end_of_storage; // 指向容器分配内存结束位置的指针
    };

    template<class T>
    void myVector<T>::erase(myVector::iterator pos) {
        assert(pos >= _start && pos < _finish);
        assert(!empty());

        iterator cur = pos;
        while (cur < _finish - 1) {
            *(cur) = *(cur + 1);
            cur++;
        }
        _finish--;// 更新_finish指针，表示容器大小减一
    }

    template<class T>
    void myVector<T>::insert(myVector<T>::iterator pos, const T &val) {
        assert(pos >= _start && pos <= _finish);
        size_t len = pos - _start;
        if (_finish == _end_of_storage) {
            // 扩容会导致pos迭代器失效
            size_t newCapacity = capacity() == 0 ? 4 : capacity() * 2;
            reserve(newCapacity);
            pos = _start + len;
        }

        iterator end = _finish - 1;
        while (end >= pos) {
            *(end + 1) = *end;
            end--;
        }
        *pos = val;
        _finish++;
    }

    template<class T>
    void myVector<T>::clear() {
        _finish = _start;
    }

    template<class T>
    void myVector<T>::pop_back() {
        assert(empty());
        _finish--;
    }

    template<class T>
    void myVector<T>::resize(size_t n, T value) {
        if (n > capacity()) {
            reserve(n);
        }

        if (n > size()) {
            while (_finish < _start + n) {
                push_back(value);
            }
        } else {
            _finish = _start + n;
        }
    }


    template<class T>
    bool myVector<T>::empty() const {
        return _start == _finish;
    }

    template<class T>
    typename myVector<T>::const_iterator myVector<T>::end() const {
        return _finish;
    }

    template<class T>
    typename myVector<T>::const_iterator myVector<T>::begin() const {
        return _start;
    }

    template<class T>
    T &myVector<T>::operator[](size_t pos) {
        assert(pos < size());
        return _start[pos];
    }

    template<class T>
    typename myVector<T>::iterator myVector<T>::end() {
        return _finish;
    }

    template<class T>
    typename myVector<T>::iterator myVector<T>::begin() {
        return _start;
    }

    template<class T>
    void myVector<T>::reserve(size_t newCapacity) {
        size_t oldSize = size();
        if (newCapacity > capacity()) {
            T *temp = new T[newCapacity];
            if (_start) {
                memcpy(temp, _start, sizeof(T) * size());
                delete[] _start;
            }
            _start = temp;
            _finish = _start + oldSize;
            _end_of_storage = _start + newCapacity;
        }
    }

    template<class T>
    size_t myVector<T>::capacity() const {
        return _end_of_storage - _start;
    }

    template<class T>
    size_t myVector<T>::size() const {
        return _finish - _start;
    }

    template<class T>
    void myVector<T>::push_back(const T &elem) {
        if (_finish == _end_of_storage) {
            size_t newCapacity = (capacity() == 0) ? 4 : capacity() * 2;
            reserve(newCapacity);
        }
        *_finish = elem;
        _finish++;
    }

    template<class T>
    myVector<T>::myVector():_start(0),
                            _finish(0),
                            _end_of_storage(0) {}

}

#endif //VECTOR_MYVECTOR_HPP
