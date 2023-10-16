#pragma once
#include <deque>

// 定义一个通用队列（queue）模板类
template <class T, class Container = std::deque<T>>
class Queue {
public:
    // 将元素推入队列的函数
    void push(const T& x) {
        _con.push_back(x);
    }

    // 从队列中弹出元素的函数
    void pop() {
        if (empty()) {
            throw std::runtime_error("Queue is empty"); // 如果队列为空，引发异常
        }
        _con.pop_front();
    }

    // 获取队列的前端元素
    const T& front() const {
        if (empty()) {
            throw std::runtime_error("Queue is empty"); // 如果队列为空，引发异常
        }
        return _con.front();
    }

    // 获取队列的后端元素
    const T& back() const {
        if (empty()) {
            throw std::runtime_error("Queue is empty"); // 如果队列为空，引发异常
        }
        return _con.back();
    }

    // 检查队列是否为空
    bool empty() const {
        return _con.empty();
    }

    // 获取队列的大小（元素个数）
    size_t size() const {
        return _con.size();
    }

private:
    Container _con; // 使用一个容器（默认为 std::deque）来实现队列
};
