#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <iostream>
#include <cstddef>
#include <cassert>

namespace Track {
    template<class T>
    class vector {
    public:
        typedef T* iterator; // 定义迭代器类型
        typedef const T* const_iterator; // 定义常量迭代器类型
        typedef T value_type; // 定义元素类型
        typedef size_t size_type; // 定义大小类型

        // 默认构造函数，创建一个空的vector
        vector() : _start(nullptr), _finish(nullptr), _end_of_storage(nullptr) {}

        // 复制构造函数，从另一个vector复制内容
        vector(const vector<value_type>& v)
            : _start(nullptr),
            _finish(nullptr),
            _end_of_storage(nullptr) {
            // 创建一个临时vector，将v的元素复制到临时vector，然后交换指针
            vector<value_type> tmp(v.begin(), v.end());
            swap(tmp);
        }

        // 从迭代器范围构造函数，将[first, last)范围的元素复制到vector
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

        // 指定大小和值的构造函数，创建一个大小为numItems的vector，每个元素都是val
        explicit vector(size_type numItems, const value_type& val = value_type())
            : _start(nullptr),
            _finish(nullptr),
            _end_of_storage(nullptr) {
            // 预留足够的空间，然后将val添加到vector中
            reserve(numItems);

            for (size_type index = 0; index < numItems; ++index)
                push_back(val);
        }

        // 指定大小和值的构造函数，整数版本
        explicit vector(int numItems, const value_type& val = value_type())
            : _start(nullptr),
            _finish(nullptr),
            _end_of_storage(nullptr) {
            // 预留足够的空间，然后将val添加到vector中
            reserve(numItems);

            for (int index = 0; index < numItems; ++index)
                push_back(val);
        }

        // 返回指向首元素的迭代器
        iterator begin() {
            return _start;
        }

        // 返回指向尾元素的迭代器
        iterator end() {
            return _finish;
        }

        // 返回指向首元素的常量迭代器
        const_iterator begin() const {
            return _start;
        }

        // 返回指向尾元素的常量迭代器
        const_iterator end() const {
            return _finish;
        }

        // 在vector尾部添加元素
        void push_back(const value_type& val) {
            // 如果vector已满，则分配更多的内存
            if (_finish == _end_of_storage) {
                size_type newCapacity = (capacity() == 0) ? 4 : capacity() * 2;
                reserve(newCapacity);
            }

            // 将val添加到vector尾部，并更新_finish指针
            *_finish = val;
            ++_finish;
        }

        // 移除vector尾部的元素
        void pop_back() {
            assert(!empty());
            --_finish;
        }

        // 在指定位置插入元素，pos是插入位置的迭代器
        iterator insert(iterator pos, const value_type& val) {
            assert(pos >= _start);
            assert(pos <= _finish);

            // 如果vector已满，则分配更多的内存
            if (_finish == _end_of_storage) {
                // 计算插入位置的偏移
                size_type len = pos - _start;
                // 计算新容量并预留内存
                size_type newCapacity = (capacity() == 0) ? 4 : capacity() * 2;
                reserve(newCapacity);
                // 更新插入位置的迭代器
                pos = _start + len;
            }

            // 将插入位置之后的元素依次向后移动
            iterator last = end();
            while (last != pos) {
                *last = *(last - 1);
                --last;
            }
            // 在插入位置处设置新值，并更新_finish指针
            *pos = val;
            ++_finish;

            return pos;
        }

        // 删除指定位置的元素，pos是要删除元素的迭代器
        iterator erase(iterator pos) {
            assert(pos >= _start);
            assert(pos < _finish);
            assert(!empty());

            // 从pos位置开始，将元素向前移动一个位置
            iterator cur = pos;
            while (cur != _finish - 1) {
                *cur = *(cur + 1);
                ++cur;
            }
            // 更新_finish指针
            --_finish;

            return pos;
        }

        // 预留存储空间，确保vector至少能容纳numItems个元素
        void reserve(size_t numItems) {
            if (numItems > capacity()) {
                // 分配新内存
                auto* tmp = new T[numItems];
                // 复制旧数据到新内存
                size_t oldSize = size();
                if (_start) {
                    for (size_type index = 0; index < size(); ++index)
                        tmp[index] = _start[index];

                    // 释放旧内存
                    delete[] _start;
                }

                // 更新指针和容量信息
                _start = tmp;
                _finish = tmp + oldSize;
                _end_of_storage = _start + numItems;
            }
        }

        // 调整vector的大小为numItems，并用val填充新的元素
        void resize(size_type numItems, value_type val = value_type()) {
            if (numItems > capacity())
                reserve(numItems);

            if (numItems < size()) {
                // 缩小vector，只需更新_finish指针
                _finish = _start + numItems;
            }
            else if (numItems > size()) {
                // 增大vector，不断添加val元素直到达到指定大小
                while (_finish < _end_of_storage)
                    push_back(val);
            }
            else {
                // numItems等于size()，不需要操作
            }
        }

        // 返回vector的大小
        [[nodiscard]] size_type size() const {
            return _finish - _start;
        }

        // 返回vector的容量
        [[nodiscard]] size_type capacity() const {
            return _end_of_storage - _start;
        }

        // 检查vector是否为空
        [[nodiscard]] bool empty() const {
            return _finish == _start;
        }

        // 交换两个vector的内容
        void swap(vector<value_type>& v) {
            std::swap(_start, v._start);
            std::swap(_finish, v._finish);
            std::swap(_end_of_storage, v._end_of_storage);
        }

        // 清空vector，将其大小设置为0
        void clear() {
            _finish = _start;
        }

        // 访问vector的元素，通过下标操作符[]
        value_type& operator[](size_type pos) {
            assert(pos < size());
            return _start[pos];
        }

        // 访问vector的元素，通过下标操作符[]（常量版本）
        const value_type& operator[](size_type pos) const {
            assert(pos < size());
            return _start[pos];
        }

        // 赋值运算符，复制另一个vector的内容
        vector<value_type>& operator=(const vector<value_type>& v) {
            // 检查是否自我赋值
            if (v._start == _start) {
                vector<value_type> tmp(v);
                swap(v);
            }
            return *this;
        }

        // 析构函数，释放vector占用的内存
        ~vector() {
            delete[] _start;
            _start = _finish = _end_of_storage = nullptr;
        }

    private:
        iterator _start; // 指向vector首元素的指针
        iterator _finish; // 指向vector尾元素的下一个位置的指针
        iterator _end_of_storage; // 指向vector内存末尾的下一个位置的指针
    };
}

#endif //VECTOR_VECTOR_H
