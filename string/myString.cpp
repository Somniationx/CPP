// Created by cocoon on 2023/9/9.

#include "myString.h"

cocoon::myString::myString(const char *str) {
    _size = strlen(str);
    _capacity = _size;
    _str = new char[_capacity + 1];
    strcpy(_str, str);
}

const char *cocoon::myString::c_str() {
    return _str;
}

size_t cocoon::myString::size() {
    return _size;
}

char &cocoon::myString::operator[](size_t pos) {
    // 检验pos合法性
    assert(pos < _size);
    return _str[pos];
}

cocoon::myString::iterator cocoon::myString::begin() {
    return _str;
}

cocoon::myString::iterator cocoon::myString::end() {
    return _str + _size;
}

cocoon::myString::const_iterator cocoon::myString::begin() const {
    return _str;
}

cocoon::myString::const_iterator cocoon::myString::end() const {
    return _str + _size;
}

cocoon::myString::reverse_iterator cocoon::myString::rbegin() {
    return cocoon::myString::reverse_iterator(end());
}

cocoon::myString::reverse_iterator cocoon::myString::rend() {
    return cocoon::myString::reverse_iterator(begin());
}

cocoon::myString::const_reverse_iterator cocoon::myString::rbegin() const {
    return cocoon::myString::const_reverse_iterator(end());
}

cocoon::myString::const_reverse_iterator cocoon::myString::rend() const {
    return cocoon::myString::const_reverse_iterator(begin());
}

void cocoon::myString::reserve(size_t n) {
    // 开辟新空间
    char *temp = new char[n + 1];
    // 挪动数据
    strcpy(temp, _str);
    delete[] _str;
    _str = temp;
    _capacity = n;
}

void cocoon::myString::push_back(char ch) {
    // 容量满时需要扩容插入数据
    // TODO
    // bug 初始capacity与size问题 空字符串问题
    if (_size == _capacity) {
        if (_capacity == 0) {
            reserve(4);
        } else {
            reserve(_capacity * 2);
        }
    }
    _str[_size++] = ch;
    _str[_size] = '\0';
}

void cocoon::myString::append(const char *str) {
    size_t len = strlen(str);
    if (_size + len > _capacity) {
        reserve(_size + len);
    }
    strcpy(_str + _size, str);
    _size += len;
}

cocoon::myString &cocoon::myString::operator+=(const char *str) {
    append(str);
    return *this;
}

cocoon::myString &cocoon::myString::operator+=(char ch) {
    push_back(ch);
    return *this;
}

cocoon::myString::myString() {
    _size = 0;
    _capacity = 0;
    _str = new char[1];
    _str[0] = '\0';
}

cocoon::myString::~myString() {
    delete[] _str;
    _str = nullptr;
    _size = 0;
    _capacity = 0;
}

size_t cocoon::myString::capacity() {
    return _capacity;
}

cocoon::myString::myString(const cocoon::myString &str) {
    _size = str._size;
    _capacity = str._capacity;
    _str = new char[_capacity + 1];
    strcpy(_str, str._str);
}

cocoon::myString &cocoon::myString::operator=(const cocoon::myString &str) {
    if (this != &str) {  // 检查自赋值
        // 释放当前对象的资源
        delete[] _str;

        // 复制新字符串的内容
        _size = str._size;
        _capacity = _size;
        _str = new char[_capacity + 1];
        strcpy(_str, str._str);
    }
    return *this;
}

void cocoon::myString::clear() {
    _size = 0;
}

bool cocoon::myString::empty() {
    return _size == 0;
}

void cocoon::myString::resize(size_t n, char c) {
    if (n < _size) {
        _str[n] = '\0';
        _size = n;
    } else if (n > _size) {
        if (n > _capacity) {
            reserve(n);
        }
        for (size_t index = _size; index < n; index++) {
            push_back(c);
        }
        _str[n] = '\0';
        _size = n;
    } else {
        //n == _size不处理
    }
}

void cocoon::myString::shrink_to_fit() {
    if (_size != _capacity) {
        char *temp = new char[_size + 1];
        for (size_t index = 0; index < _size; index++) {
            temp[index] = _str[index];
        }
        temp[_size] = '\0';
        delete[] _str;
        _str = temp;
        _capacity = _size;
    }
}

cocoon::myString &cocoon::myString::insert(size_t pos, char ch) {
    assert(pos <= _size);
    if (_size == _capacity) {
        if (_capacity == 0) {
            reserve(4);
        } else {
            reserve(_capacity * 2);
        }
        for (size_t index = _size + 1; index > pos; index--) {
            _str[index] = _str[index - 1];
        }
        _str[pos] = ch;
        _size++;
    }
    return *this;
}

cocoon::myString &cocoon::myString::insert(size_t pos, const char *str) {
    assert(pos <= _size);
    size_t len = strlen(str);
    if (_size + len > _capacity) {
        reserve(_size + len);
    }
    // 挪动数据
    for (size_t index = _size + 1; index > pos; index--) {
        _str[index + len - 1] = _str[index - 1];
    }

    // 插入数据
    for (size_t index = pos, count = 0; count < len; count++, index++) {
        _str[index] = str[count];
    }

    _size += len;
    return *this;
}

std::ostream &cocoon::operator<<(std::ostream &in, cocoon::myString &str) {
    in << str.c_str();
    return in;
}