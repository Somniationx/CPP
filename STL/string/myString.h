// Created by cocoon on 2023/9/9.

#ifndef STRING_MYSTRING_H
#define STRING_MYSTRING_H

#include <cstddef>
#include <cassert>
#include <cstring>
#include <iterator>
#include <iostream>

namespace cocoon {
    class myString {
    private:
        char *_str;         // 存储字符串数据的字符数组
        size_t _size;       // 有效字符个数
        size_t _capacity;   // 存储容量

    public:
        const static size_t npos = -1;

        // 模拟迭代器
        typedef char *iterator;
        typedef const char *const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        // 构造函数（使用C风格字符串构造myString对象）
        explicit myString(const char *str);

        // 构造函数（创建空字符串）
        myString();

        // 拷贝构造函数
        myString(const myString &str);

        // 现代写法
//        myString(const myString &str)
//                : _str(nullptr),
//                  _size(0),
//                  _capacity(0) {
//            myString temp(str._str);
//            std::swap(_str, temp._str);
//            std::swap(_size, temp._size);
//            std::swap(_capacity, temp._capacity);
//        }


        // 析构函数
        ~myString();

        // 交换对象函数
        void swap(myString& str);

        // 返回C风格字符串
        [[nodiscard]] const char *c_str();

        // 返回字符串长度
        size_t size();

        // 返回字符串容量
        size_t capacity();

        // 运算符重载使其可使用[]访问字符串数据
        char &operator[](size_t pos);

        const char &operator[](size_t pos) const;

        // 返回正向迭代器的起始和结束位置
        iterator begin();

        iterator end();

        // 返回常量正向迭代器的起始和结束位置
        [[nodiscard]] const_iterator begin() const;

        [[nodiscard]] const_iterator end() const;

        // 返回反向迭代器的起始和结束位置
        reverse_iterator rbegin();

        reverse_iterator rend();

        // 返回常量反向迭代器的起始和结束位置
        [[nodiscard]] const_reverse_iterator rbegin() const;

        [[nodiscard]] const_reverse_iterator rend() const;

        // 空间扩容
        void reserve(size_t n);

        // 尾部插入字符
        void push_back(char ch);

        // 尾部插入字符串
        void append(const char *str);

        // +=运算符重载
        myString &operator+=(const char *str);

        myString &operator+=(char ch);

        // =运算符重载
        myString &operator=(const myString &str);

        // 清空字符串
        void clear();

        // 判空
        bool empty();

        // 重新设置_size并填充字符c
        void resize(size_t n, char ch = '\0');

        // 缩容
        void shrink_to_fit();

        // 在指定位置插入字符
        myString &insert(size_t pos, char ch);

        // 在指定位置插入字符串
        myString &insert(size_t pos, const char *str);

        // 删除
        myString &erase(size_t pos, size_t len = npos);

        // 查找
        size_t find(char ch, size_t pos = 0);

        size_t find(const char *str, size_t pos = 0);
    };

    // 重载输出运算符以便于输出字符串
    std::ostream &operator<<(std::ostream &out, myString &str);
}

#endif //STRING_MYSTRING_H
