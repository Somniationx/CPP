#include "myVector.hpp"
#include <iostream>


int main() {
    // 创建一个整数类型的 myVector 对象
    cocoon::myVector<int> intVector;

    // 添加一些元素到容器中
    for (int i = 1; i <= 10; ++i) {
        intVector.push_back(i);
    }

    // 打印容器的大小和元素
    std::cout << "容器的大小: " << intVector.size() << std::endl;
    std::cout << "容器的元素: ";
    for (const auto &elem : intVector) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // 在容器中插入元素
    intVector.insert(intVector.begin() + 3, 100);

    // 打印插入后的容器
    std::cout << "插入元素后的容器: ";
    for (const auto &elem : intVector) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // 移除容器中的一个元素
    intVector.erase(intVector.begin() + 5);

    // 打印移除元素后的容器
    std::cout << "移除元素后的容器: ";
    for (const auto &elem : intVector) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // 清空容器
    intVector.clear();

    // 检查容器是否为空
    if (intVector.empty()) {
        std::cout << "容器已清空" << std::endl;
    }

    return 0;
}
