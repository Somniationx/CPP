#include "myString.h"

namespace cocoon {
    // 构造函数（使用C风格字符串构造myString对象）
    myString::myString(const char *str) {
        _size = strlen(str);
        _capacity = _size;
        _str = new char[_capacity + 1];
        strcpy(_str, str);
    }

    // 返回C风格字符串
    const char *myString::c_str() {
        return _str;
    }

    // 返回字符串长度
    size_t myString::size() {
        return _size;
    }

    // 重载[]运算符以访问字符串数据
    char &myString::operator[](size_t pos) {
        // 检验pos合法性
        assert(pos < _size);
        return _str[pos];
    }

    // 返回正向迭代器的起始位置
    myString::iterator myString::begin() {
        return _str;
    }

    // 返回正向迭代器的结束位置
    myString::iterator myString::end() {
        return _str + _size;
    }

    // 返回常量正向迭代器的起始位置
    myString::const_iterator myString::begin() const {
        return _str;
    }

    // 返回常量正向迭代器的结束位置
    myString::const_iterator myString::end() const {
        return _str + _size;
    }

    // 返回反向迭代器的起始位置
    myString::reverse_iterator myString::rbegin() {
        return myString::reverse_iterator(end());
    }

    // 返回反向迭代器的结束位置
    myString::reverse_iterator myString::rend() {
        return myString::reverse_iterator(begin());
    }

    // 返回常量反向迭代器的起始位置
    myString::const_reverse_iterator myString::rbegin() const {
        return myString::const_reverse_iterator(end());
    }

    // 返回常量反向迭代器的结束位置
    myString::const_reverse_iterator myString::rend() const {
        return myString::const_reverse_iterator(begin());
    }

    // 空间扩容
    void myString::reserve(size_t n) {
        // 开辟新空间
        char *temp = new char[n + 1];
        // 拷贝数据
        strcpy(temp, _str);
        delete[] _str;
        _str = temp;
        _capacity = n;
    }

    // 尾部插入字符
    void myString::push_back(char ch) {
        // 当容量已满时需要扩容并插入数据
        if (_size == _capacity) {
            if (_capacity == 0) {
                reserve(4);
            } else {
                reserve(_capacity * 2);
            }
        }
        _str[_size++] = ch;
        _str[_size] = '\0'; // 添加null终止符
    }

    // 尾部插入字符串
    void myString::append(const char *str) {
        size_t len = strlen(str);
        if (_size + len > _capacity) {
            reserve(_size + len);
        }
        strcpy(_str + _size, str);
        _size += len;
    }

    // +=运算符重载
    myString &myString::operator+=(const char *str) {
        append(str);
        return *this;
    }

    // +=运算符重载
    myString &myString::operator+=(char ch) {
        push_back(ch);
        return *this;
    }

    // 构造函数（创建空字符串）
    myString::myString() {
        _size = 0;
        _capacity = 0;
        _str = new char[1];
        _str[0] = '\0'; // 空字符串
    }

    // 析构函数
    myString::~myString() {
        delete[] _str;
        _str = nullptr;
        _size = 0;
    }

    // 返回字符串容量
    size_t myString::capacity() {
        return _capacity;
    }

    // 拷贝构造函数
    myString::myString(const myString &str) {
        _size = str._size;
        _capacity = str._capacity;
        _str = new char[_capacity + 1];
        strcpy(_str, str._str);
    }

    // =运算符重载
    myString &myString::operator=(const myString &str) {
        if (this != &str) { // 检查自赋值
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

    // 清空字符串
    void myString::clear() {
        _size = 0;
    }

    // 判空
    bool myString::empty() {
        return _size == 0;
    }

    // 重新设置_size并填充字符c
    void myString::resize(size_t n, char ch) {
        if (n < _size) {
            _str[n] = '\0'; // 截断字符串
            _size = n;
        } else if (n > _size) {
            if (n > _capacity) {
                reserve(n);
            }
            for (size_t index = _size; index < n; index++) {
                _str[index] = ch;
            }
            _size = n;
            _str[_size] = '\0';
        } else {
            // n == _size，不进行操作
        }
    }

    // 缩容
    void myString::shrink_to_fit() {
        if (_size != _capacity) {
            char *temp = new char[_size + 1];
            for (size_t index = 0; index < _size; index++) {
                temp[index] = _str[index];
            }
            temp[_size] = '\0'; // 添加null终止符
            delete[] _str;
            _str = temp;
            _capacity = _size;
        }
    }

    // 在指定位置插入字符
    myString &myString::insert(size_t pos, char ch) {
        assert(pos <= _size);
        if (_size == _capacity) {
            if (_capacity == 0) {
                reserve(4);
            } else {
                reserve(_capacity * 2);
            }
        }
        for (size_t index = _size + 1; index > pos; index--) {
            _str[index] = _str[index - 1];
        }
        _str[pos] = ch;
        _size++;
        return *this;
    }

    // 在指定位置插入字符串
    myString &myString::insert(size_t pos, const char *str) {
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

    myString &myString::erase(size_t pos, size_t len) {
        assert(pos < _size);

        if (len == npos || pos + len >= _size) {
            _str[pos] = '\0';
            _size = pos;
        } else {
            for (size_t index = pos + len; index <= _size; index++) {
                _str[index - len] = _str[index];
            }
            _size -= len;
//            strcpy(_str + pos, _str + pos + len);
//            _size -= len;
        }
        return *this;
    }

    size_t myString::find(char ch, size_t pos) {
        assert(pos < _size);
        while (pos < _size) {
            if (_str[pos] == ch) {
                return pos;
            }
            pos++;
        }
        return npos;
    }

    size_t myString::find(const char *str, size_t pos) {
        const char *ptr = strstr(_str + pos, str);
        if (ptr) {
            return ptr - _str;
        } else {
            return npos;
        }
    }

    const char &myString::operator[](size_t pos) const {
        return _str[pos];
    }

    void myString::swap(myString &str) {
        std::swap(_str, str._str);
        std::swap(_size, str._size);
        std::swap(_capacity, str._capacity);
    }

    // 重载输出运算符以便于输出字符串
    std::ostream &operator<<(std::ostream &out, cocoon::myString &str) {
        for (size_t index = 0; index < str.size(); index++) {
            out << str[index];
        }
        return out;
    }
}