# **constructor**

- C++98

|       default (1) | `string();`                                                  |
| ----------------: | ------------------------------------------------------------ |
|          copy (2) | `string (const string& str);`                                |
|     substring (3) | `string (const string& str, size_t pos, size_t len = npos);` |
| from c-string (4) | `string (const char* s);`                                    |
| from sequence (5) | `string (const char* s, size_t n);`                          |
|          fill (6) | `string (size_t n, char c);`                                 |
|         range (7) | `template <class InputIterator>  string  (InputIterator first, InputIterator last);` |

## Construct string object

> **Constructs a [string](https://cplusplus.com/string) object, initializing its value depending on the constructor version used.**

> 构造一个字符串对象，根据使用的构造函数版本初始化其值。

### (1) empty string constructor (default constructor)

> **`default (1)  string();`**

> **Constructs an [empty](https://cplusplus.com/string::empty) string, with a [length](https://cplusplus.com/string::length) of zero characters.**

> 构造一个空字符串，长度为零个字符。

```cpp
#include <iostream>
#include <string>

int main() {
    std::string str;
    std::cout << str << std::endl;
    return 0;
}

//结果
//E:\DataStructure\StringTest\cmake-build-debug\StringTest.exe
//
//
//进程已结束，退出代码为 0
```

### (2) copy constructor

> **`copy (2)  string (const string& str);`**

> **Constructs a copy of *`str`*.**

> 构造 字符串str 的副本。

```cpp
#include <iostream>
#include <string>

int main() {
    std::string str0 ("Initial string");
    //拷贝s0副本
    std::string& str1(s0);
    std::cout << str1 << std::endl;
    return 0;
}

//E:\DataStructure\StringTest\cmake-build-debug\StringTest.exe
//Initial string
//
//进程已结束，退出代码为 0
```

### (3) substring constructor

> **`substring (3)  string (const string& str, size_t pos, size_t len = npos);`**

> **Copies the portion of *str* that begins at the character position *pos* and spans *len* characters (or until the end of *str*, if either *str* is too short or if *len* is [string::npos](https://cplusplus.com/string::npos)).**

> 复制 str 中从字符位置 pos 开始并跨越 len 个字符的部分（或者直到 str 的末尾，如果 str 太短或 len 是 string::npos）。
>
> str太短指的是len值超过pos后字符个数（含pos位置）。

```cpp
#include <iostream>
#include <string>

int main() {
    std::string str0("Initial string");

    //从pos（2）开始取5个字符构造str1(len == 5)
    std::string str1(str0, 2, 5);

    //从pos（2）开始，取20个字符构造str2，看看结果如何（len==20）
    std::string str2(str0, 2, 20);

    //只给pos（2），len的值使用缺省值，看看结果如何(len == npos)
    std::string str3(str0, 2);

    std::cout << "str0:" << str0 << std::endl;
    std::cout << "str1:" << str1 << std::endl;
    std::cout << "str2:" << str2 << std::endl;
    std::cout << "str3:" << str3 << std::endl;

    return 0;
}

//E:\DataStructure\StringTest\cmake-build-debug\StringTest.exe
//str0:Initial string
//str1:itial
//str2:itial string
//str3:itial string
//
//进程已结束，退出代码为 0
```

### (4) from c-string

> **`from c-string (4)  string (const char* s);`**

> **Copies the null-terminated character sequence (C-string) pointed by *s*.**

> 复制指针s 指向的以空字符终止的字符序列（即C 字符串）。

```cpp
#include <iostream>
#include <string>

int main() {
    const char *s = "Hello World!";
    //使用c字符串构造str
    std::string str(s);

    std::cout << str << std::endl;
    return 0;
}

//E:\DataStructure\StringTest\cmake-build-debug\StringTest.exe
//Hello World!
//
//进程已结束，退出代码为 0
```

### (5) from buffer

> **`from sequence (5)  string (const char* s, size_t n);`**

> **Copies the first *n* characters from the array of characters pointed by *s*.**

> 复制指针 s 指向的字符序列中的前 n 个字符。

```cpp
#include <iostream>
#include <string>

int main() {
    const char *s = "Hello World!";

    //n值为5，即字符串s前5个字符
    std::string str1(s, 5);

    //此时n值为15，超过字符串s有效字符长度
    //编译器有警告表明长度超过，看看结果如何
    std::string str2(s, 25);

    std::cout << "str1:" << str1 << std::endl;
    std::cout << "str2:" << str2 << std::endl;
    return 0;
}

//结果似乎有些奇怪，可以多多尝试探索一下编译器如何处理
//E:\DataStructure\StringTest\cmake-build-debug\StringTest.exe
//str1:Hello
//str2:Hello World! str1: str2:
//
//进程已结束，退出代码为 0
```

### (6) fill constructor

> **`fill (6)  string (size_t n, char c);`**

> **Fills the string with *n* consecutive copies of character *c*.**

> 用n个字符 c 填充字符串。

```cpp
#include <iostream>
#include <string>

int main() {
    std::string str(5, 'c');
    std::cout << str << std::endl;
    return 0;
}

//E:\DataStructure\StringTest\cmake-build-debug\StringTest.exe
//ccccc
//
//进程已结束，退出代码为 0
```

# **Capacity**

## size

```cpp
size_t size() const;
```

> **Return length of string**

> Returns the length of the string, in terms of bytes.
>
> This is the number of actual bytes that conform the contents of the [string](https://cplusplus.com/string), **which is not necessarily equal to its storage [capacity](https://cplusplus.com/string::capacity).**

```cpp
#include <iostream>
#include <string>

int main ()
{
    std::string str ("Test string");
    std::cout << "The size of str is " << str.size() << " bytes.\n";
    return 0;
}

//E:\DataStructure\StringTest\cmake-build-debug\StringTest.exe
//The size of str is 11 bytes.
//
//进程已结束，退出代码为 0
```

## length

```cpp
size_t length() const;
```

> **Return length of string**

> Returns the length of the string, in terms of bytes.
>
> This is the number of actual bytes that conform the contents of the [string](https://cplusplus.com/string), **which is not necessarily equal to its storage [capacity](https://cplusplus.com/string::capacity).**

```cpp
#include <iostream>
#include <string>

int main ()
{
    std::string str ("Test string");
    std::cout << "The size of str is " << str.length() << " bytes.\n";
    return 0;
}

//E:\DataStructure\StringTest\cmake-build-debug\StringTest.exe
//The size of str is 11 bytes.
//
//进程已结束，退出代码为 0
```

## max_size

```cpp
size_t max_size() const;
```

> **Return maximum size of string**

> **Returns the maximum length the [string](https://cplusplus.com/string) can reach.**

> This is the maximum potential [length](https://cplusplus.com/string::length) the string can reach due to known system or library implementation limitations, **but the object is not guaranteed to be able to reach that length:** it can still fail to allocate storage at any point before that length is reached.

```cpp
#include <iostream>
#include <string>

int main ()
{
    std::string str ("Test string");
    std::cout << "size: " << str.size() << "\n";
    std::cout << "length: " << str.length() << "\n";
    std::cout << "capacity: " << str.capacity() << "\n";
    std::cout << "max_size: " << str.max_size() << "\n";
    return 0;
}

//E:\DataStructure\StringTest\cmake-build-debug\StringTest.exe
//size: 11
//length: 11
//capacity: 15
//max_size: 4611686018427387903
//
//进程已结束，退出代码为 0
```

## resize

```cpp
void resize (size_t n);void resize (size_t n, char c);
```

> **Resize string**

> Resizes the string to a [length](https://cplusplus.com/string::length) of *n* characters.

> If *n* is smaller than the current [string length](https://cplusplus.com/string::length), the current value is shortened to its first *n* character, removing the characters beyond the *n*th.

> 如果 n 小于当前字符串长度，则当前值将缩短为其前 n 个字符，并删除第 n 个之后的字符。

> If *n* is greater than the current [string length](https://cplusplus.com/string::length), the current content is extended by inserting at the end as many characters as needed to reach a size of *n*. If *c* is specified, the new elements are initialized as copies of *c*, otherwise, they are *value-initialized characters* (null characters).

> 如果 n 大于当前字符串长度，则通过在末尾插入所需数量的字符来扩展当前内容，以达到 n 的大小。如果指定了 c，则新元素将初始化为 字符c ，否则，它们是值初始化字符（空字符）。

```cpp
#include <iostream>
#include <string>

int main() {
    std::string str("I like to code in c");
    std::cout << str << '\n';
    std::cout << "初始 str.size:" << str.size() << '\n';
    std::cout << "初始 str.capacity:" << str.capacity() << '\n';

    size_t sz = str.size();

    //指定字符
    str.resize(sz + 2, '+');
    std::cout << str << '\n';
    std::cout << "新增两个字符 str.size:" << str.size() << '\n';
    std::cout << "新增两个字符 str.capacity:" << str.capacity() << '\n';

    //默认字符
    str.resize(14);
    std::cout << str << '\n';
    std::cout << "缩减 str.size:" << str.size() << '\n';
    std::cout << "缩减 str.capacity:" << str.capacity() << '\n';
    return 0;
}

//E:\DataStructure\StringTest\cmake-build-debug\StringTest.exe
//I like to code in c
//初始 str.size:19
//初始 str.capacity:19
//I like to code in c++
//新增两个字符 str.size:21
//新增两个字符 str.capacity:38
//I like to code
//缩减 str.size:14
//缩减 str.capacity:38
//
//进程已结束，退出代码为 0
```

> 当resize函数中n值小于当前size时，不会对其容量capacity造成影响。

## capacity

```cpp
size_t capacity() const;
```

> **Return size of allocated storage**

> Returns the size of the storage space currently allocated for the [string](https://cplusplus.com/string), **expressed in terms of bytes.**

> **This *capacity* is not necessarily equal to the [string length](https://cplusplus.com/string::length).** It can be equal or greater, with the extra space allowing the object to optimize its operations when new characters are added to the [string](https://cplusplus.com/string).

> Notice that this *capacity* does not suppose a limit on the [length](https://cplusplus.com/string::length) of the [string](https://cplusplus.com/string). When this *capacity* is exhausted and more is needed, it is automatically expanded by the object (reallocating it storage space). The theoretical limit on the [length](https://cplusplus.com/string::length) of a [string](https://cplusplus.com/string) is given by member [max_size](https://cplusplus.com/string::max_size).
>
> 理论最大值由成员变量max_size给出，容量不够时自动扩容。

```cpp
#include <iostream>
#include <string>

int main ()
{
    std::string str ("Test string");
    std::cout << "size: " << str.size() << "\n";
    std::cout << "length: " << str.length() << "\n";
    std::cout << "capacity: " << str.capacity() << "\n";
    std::cout << "max_size: " << str.max_size() << "\n";
    return 0;
}

//E:\DataStructure\StringTest\cmake-build-debug\StringTest.exe
//size: 11
//length: 11
//capacity: 15
//max_size: 4611686018427387903
//
//进程已结束，退出代码为 0
```

## reserve

```cpp
void reserve (size_t n = 0);
```

> **Request a change in capacity**

> Requests that the [string capacity](https://cplusplus.com/string::capacity) be adapted to a planned change in [size](https://cplusplus.com/string::size) to a [length](https://cplusplus.com/string::length) of up to *n* characters.

> If *n* is greater than the current [string capacity](https://cplusplus.com/string::capacity), the function causes the container to **increase its [capacity](https://cplusplus.com/string::capacity) to *n* characters (or greater).**
>
> 当n值大于此时capacity时，容量会扩容到n或者更大，具体根据编译器实现有所不同。

> In all other cases, it is taken as a non-binding request to shrink the [string capacity](https://cplusplus.com/string::capacity): the container implementation is free to optimize otherwise and leave the [string](https://cplusplus.com/string) with a [capacity](https://cplusplus.com/string::capacity) greater than *n*.
>
> 似乎用它来缩容时并不起作用。

> This function has no effect on the [string length](https://cplusplus.com/string::length) and cannot alter its content.
>
> 该函数对字符串长度没有影响，也不能改变其内容。

```cpp
#include <iostream>
#include <string>

int main() {
    std::string str("Hello World!");
    std::cout << str.capacity() << "\n";

    str.reserve(30);
    std::cout << str.capacity() << "\n";

    str.reserve(10);
    std::cout << str.capacity() << "\n";
    std::cout << str << "\n";

    return 0;
}

//E:\DataStructure\StringTest\cmake-build-debug\StringTest.exe
//15
//30
//30
//Hello World!
//
//进程已结束，退出代码为 0
```

## clear

```cpp
void clear();
```

> **Clear string**

> Erases the contents of the [string](https://cplusplus.com/string), which becomes an [**empty string**](https://cplusplus.com/string::empty) (with a [length](https://cplusplus.com/string::length) of `0` characters).

```cpp
#include <iostream>
#include <string>

int main() {
    std::string str("Hello World!");
    std::cout << "str.capacity" << str.capacity() << "\n";
    std::cout << "str.size" << str.size() << "\n";

    str.clear();
    std::cout << "str.capacity" << str.capacity() << "\n";
    std::cout << "str.size" << str.size() << "\n";
    
    return 0;
}

//E:\DataStructure\StringTest\cmake-build-debug\StringTest.exe
//str.capacity15
//str.size12
//str.capacity15
//str.size0
//
//进程已结束，退出代码为 0
```

## empty

```cpp
bool empty() const;
```

> **Test if string is empty**

> Returns whether the [string](https://cplusplus.com/string) is empty (i.e. whether its [length](https://cplusplus.com/string::length) is `0`).

```cpp
#include <iostream>
#include <string>

int main() {
    std::string str1("Hello World!");
    std::string str2;

    std::cout << str1.empty() << "\n";
    std::cout << str2.empty() << "\n";
    return 0;
}

//E:\DataStructure\StringTest\cmake-build-debug\StringTest.exe
//0
//1
//
//进程已结束，退出代码为 0
```

