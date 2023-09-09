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
        char *_str;         //c字符串存储数据
        size_t _size;       //有效字符个数
        size_t _capacity;   //有效容量
    public:
        // 模拟迭代器
        typedef char *iterator;
        typedef const char *const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        // 返回正向迭代器的起始和结束位置
        iterator begin();

        iterator end();

        [[nodiscard]] const_iterator begin() const;

        [[nodiscard]] const_iterator end() const;

        // 返回反向迭代器的起始和结束位置
        reverse_iterator rbegin();

        reverse_iterator rend();

        [[nodiscard]] const_reverse_iterator rbegin() const;

        [[nodiscard]] const_reverse_iterator rend() const;

        // 构造函数（使用c类型字符串构造myString对象）
        explicit myString(const char *str);

        // 构造函数空字符串
        myString();

        // 拷贝构造函数
        myString(const myString &str);

        // 析构函数
        ~myString();

        // 返回myString对象中成员变量_str（c类型字符串）
        [[nodiscard]] const char *c_str();

        // 返回_size（有效字符个数）
        size_t size();

        // 返回容量
        size_t capacity();

        // 运算符重载使其可使用[]访问_str数据
        char &operator[](size_t pos);

        // 空间扩容
        void reserve(size_t n);

        // 尾插字符
        void push_back(char ch);

        // 尾插字符串
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

        // 重新设置_size
        void resize(size_t n, char c);

        // 缩容
        void shrink_to_fit();

        // 插入字符
        myString &insert(size_t pos, char ch);

        // 插入字符串
        myString &insert(size_t pos, const char *str);

    };

    std::ostream &operator<<(std::ostream &in, myString &str);
}

#endif //STRING_MYSTRING_H
