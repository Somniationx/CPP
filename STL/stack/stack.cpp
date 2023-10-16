#pragma once
#include <deque> // 包含 <deque> 头文件，以支持默认容器类型 std::deque

// 定义一个通用堆栈（stack）模板类
template <class T, class Container = std::deque<T>> 
class Stack {
public:
    // 将元素推入堆栈的函数
    void push(const T& x) {
        _con.push_back(x);
    }

    // 从堆栈中弹出元素的函数
    void pop() {
        if (empty()) {
            throw std::runtime_error("Stack is empty"); // 如果堆栈为空，引发异常
        }
        _con.pop_back();
    }

    // 获取堆栈的顶部元素
    const T& top() {
        if (empty()) {
            throw std::runtime_error("Stack is empty"); // 如果堆栈为空，引发异常
        }
        return _con.back();
    }

    // 检查堆栈是否为空
    bool empty() {
        return _con.empty();
    }

    // 获取堆栈的大小（元素个数）
    size_t size() {
        return _con.size();
    }

private:
    Container _con; // 使用一个容器（默认为 std::deque）来实现堆栈
};
