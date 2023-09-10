#include"myString.h"

using namespace cocoon;

int main() {
    myString str;
    str.push_back('c');
    str.append("aaaaddd");
    std::cout << str.c_str() << std::endl;
    std::cout << str.size() << std::endl;
    std::cout << str.capacity() << std::endl;

    str.push_back('x');
    std::cout << str.c_str() << std::endl;
    std::cout << str.size() << std::endl;
    std::cout << str.capacity() << std::endl;

    str.shrink_to_fit();
    std::cout << str << std::endl;
    std::cout << str.size() << std::endl;
    std::cout << str.capacity() << std::endl;

    myString str2;
    str2.insert(0,'c');
    std::cout << str2 << std::endl;
    std::cout << str2.size() << std::endl;
    std::cout << str2.capacity() << std::endl;

    str2.insert(0, "hello");
    std::cout << str2 << std::endl;
    std::cout << str2.size() << std::endl;
    std::cout << str2.capacity() << std::endl;

    str2.erase(2,2);
    std::cout << str2 << std::endl;
    std::cout << str2.size() << std::endl;
    std::cout << str2.capacity() << std::endl;
    return 0;
}
