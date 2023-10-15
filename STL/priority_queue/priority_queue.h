#pragma once

#include <iostream>

using namespace std;

#include <vector>

namespace moon {
    // 小于比较器
    template<class T>
    struct less {
        bool operator()(const T &left, const T &right) {
            return left < right;
        }
    };

    // 大于比较器
    template<class T>
    struct greater {
        bool operator()(const T &left, const T &right) {
            return left > right;
        }
    };

    // 优先级队列类模板
    template<class T, class Container = std::vector<T>, class Compare = less<T>>
    class priority_queue {
    public:
        // 创建空的优先级队列
        priority_queue() : c() {}

        // 通过迭代器范围创建优先级队列
        template<class Iterator>
        priority_queue(Iterator first, Iterator last)
                : c(first, last) {
            // 将c中的元素调整成堆的结构
            int count = c.size();
            int root = ((count - 2) >> 1);
            for (; root >= 0; root--)
                AdjustDown(root);
        }

        // 入队操作
        void push(const T &data) {
            c.push_back(data);
            AdjustUP(c.size() - 1);
        }

        // 出队操作
        void pop() {
            if (empty())
                return;

            swap(c.front(), c.back());
            c.pop_back();
            AdjustDown(0);
        }

        // 获取队列大小
        [[nodiscard]] size_t size() const {
            return c.size();
        }

        // 判断队列是否为空
        [[nodiscard]] bool empty() const {
            return c.empty();
        }

        // 获取堆顶元素，不允许修改
        [[nodiscard]] const T &top() const {
            return c.front();
        }

    private:
        // 向上调整
        void AdjustUP(int child) {
            int parent = ((child - 1) >> 1);
            while (child) {
                if (Compare()(c[parent], c[child])) {
                    swap(c[child], c[parent]);
                    child = parent;
                    parent = ((child - 1) >> 1);
                } else {
                    return;
                }
            }
        }

        // 向下调整
        void AdjustDown(int parent) {
            size_t child = parent * 2 + 1;
            while (child < c.size()) {
                // 找以parent为根的较大的孩子
                if (child + 1 < c.size() && Compare()(c[child], c[child + 1]))
                    child += 1;

                // 检测双亲是否满足情况
                if (Compare()(c[parent], c[child])) {
                    swap(c[child], c[parent]);
                    parent = child;
                    child = parent * 2 + 1;
                } else
                    return;
            }
        }

    private:
        Container c; // 存储元素的容器
    };
}

// 测试优先级队列
void TestQueuePriority() {
    moon::priority_queue<int> q1;
    q1.push(5);
    q1.push(1);
    q1.push(4);
    q1.push(2);
    q1.push(3);
    q1.push(6);
    cout << q1.top() << endl;

    q1.pop();
    q1.pop();
    cout << q1.top() << endl;

    vector<int> v{5, 1, 4, 2, 3, 6};
    moon::priority_queue<int, vector<int>, moon::greater<int>> q2(v.begin(), v.end());
    cout << q2.top() << endl;

    q2.pop();
    q2.pop();
    cout << q2.top() << endl;
}

int main() {
    TestQueuePriority();
    return 0;
}