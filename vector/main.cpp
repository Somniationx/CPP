#include "myVector.hpp"
#include <iostream>


int main() {
    // ����һ���������͵� myVector ����
    cocoon::myVector<int> intVector;

    // ���һЩԪ�ص�������
    for (int i = 1; i <= 10; ++i) {
        intVector.push_back(i);
    }

    // ��ӡ�����Ĵ�С��Ԫ��
    std::cout << "�����Ĵ�С: " << intVector.size() << std::endl;
    std::cout << "������Ԫ��: ";
    for (const auto &elem : intVector) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // �������в���Ԫ��
    intVector.insert(intVector.begin() + 3, 100);

    // ��ӡ����������
    std::cout << "����Ԫ�غ������: ";
    for (const auto &elem : intVector) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // �Ƴ������е�һ��Ԫ��
    intVector.erase(intVector.begin() + 5);

    // ��ӡ�Ƴ�Ԫ�غ������
    std::cout << "�Ƴ�Ԫ�غ������: ";
    for (const auto &elem : intVector) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // �������
    intVector.clear();

    // ��������Ƿ�Ϊ��
    if (intVector.empty()) {
        std::cout << "���������" << std::endl;
    }

    return 0;
}
