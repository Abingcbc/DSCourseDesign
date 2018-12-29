#include <iostream>
#include <queue>

using namespace std;

struct cmp {
    bool operator() (int x, int y) {
        return x > y;
    }
};

priority_queue<int, vector<int>, cmp> woodQueue;

int getMinMoney() {
    int answer = 0;
    //当全部节点都合并才停止
    while (woodQueue.size() != 1) {
        int min1 = woodQueue.top();
        woodQueue.pop();
        int min2 = woodQueue.top();
        woodQueue.pop();
        //将两个子树合并成一个树
        answer = answer + min1 + min2;
        woodQueue.push(min1 + min2);
    }
    return answer;
}

void init() {
    int num;
    cin >> num;
    int length;
    if (num <= 0) {
        cout << "长度必须为正整数" << endl;
        return;
    }
    for (int i = 0; i < num; i++) {
        cin >> length;
        woodQueue.push(length);
    }
    cout << getMinMoney() << endl;
}

int main() {
    init();
    return 0;
}