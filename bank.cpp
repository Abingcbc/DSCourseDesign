#include <iostream>
#include <queue>

using namespace std;

void bank() {
    cout << "请输入顾客序列：" << endl;
    int customer, customerNum;
    //两个窗口各一个队列
    queue<int> queueA, queueB;
    cin >> customerNum;
    if (customerNum < 0) {
        cout << "输入顾客总数不得小于0！" << endl;
        return;
    }
    //读入
    while (customerNum > 0) {
        cin >> customer;
        if (customer < 0) {
            cout << "顾客编号不得小于0" << endl;
            break;
        }
        if (customer % 2 == 0) {
            queueB.push(customer);
        } else {
            queueA.push(customer);
        }
        customerNum--;
    }
    //两者都为空的时候再停止，若一个先空，在循环内部可以判断
    while (!queueA.empty() || !queueB.empty()) {
        if (!queueA.empty()) {
            cout << queueA.front();
            queueA.pop();
            if (!queueA.empty() || !queueB.empty())
                cout << " ";
        }
        if (!queueA.empty()) {
            cout << queueA.front();
            queueA.pop();
            if (!queueA.empty() || !queueB.empty())
                cout << " ";
        }
        if (!queueB.empty()) {
            cout << queueB.front();
            queueB.pop();
            if (!queueB.empty() || !queueA.empty())
                cout << " ";
        }
    }
}

int main() {
    bank();
    return 0;
}