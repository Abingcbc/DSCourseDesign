#include <iostream>
#include <stack>
#include <vector>
#include <queue>

using namespace std;

class Activity {
public:
    int _earlyStart = 0;//最早开始时间
    int _lastStart = 99999;//最晚开始时间
    int _pre;//前一个事件
    int _next;//后一个事件
    int _lastingTime;//持续时间

    Activity() {}

    Activity(int earlyStart, int lastStart, int lastingTime, int pre, int next) {
        _earlyStart = earlyStart;
        _lastStart = lastStart;
        _lastingTime = lastingTime;
        _pre = pre;
        _next = next;
    }

};

class PassPoint {
public:
    int _id;//事件编号
    int _earlyStart = 0;//最早开始时间
    int _lastStart = 99999;//最晚开始时间
    vector<PassPoint*> _nextPointList;//后续节点
    vector<Activity*> _activityList;//后续活动
};

int tSort(int* inDegreeArray, PassPoint** passPointArray, int n) {
    int num = 0;
    stack<PassPoint*>* passPointStack = new stack<PassPoint*>;
    stack<PassPoint*>* reversePointStack = new stack<PassPoint*>;
    //遍历节点 将入度为0的节点压入栈
    for (int i = 0; i < n; i++) {
        if (inDegreeArray[i] == 0) {
            passPointArray[i]->_earlyStart = 0;
            passPointStack->push(passPointArray[i]);
            reversePointStack->push(passPointArray[i]);
            num++;
        }
    }
    while (!passPointStack->empty()) {
        auto temp = passPointStack->top();
        passPointStack->pop();
        for (int i = 0; i < temp->_nextPointList.size(); i++) {
            //将后续节点入度为0的节点压入栈
            if (--inDegreeArray[temp->_nextPointList[i]->_id-1] == 0) {
                num++;
                passPointStack->push(temp->_nextPointList[i]);
                reversePointStack->push(temp->_nextPointList[i]);
            }
            temp->_nextPointList[i]->_earlyStart =
                    max(temp->_activityList[i]->_lastingTime + temp->_earlyStart,
                        temp->_nextPointList[i]->_earlyStart);
            temp->_activityList[i]->_earlyStart =
                    temp->_earlyStart;
        }
    }
    if (num != n) {
        cout << 0 << endl;
        return -1;
    }
    //同理使用逆拓扑排序求得最晚开始时间
    reversePointStack->top()->_lastStart = reversePointStack->top()->_earlyStart;
    int result = reversePointStack->top()->_lastStart;
    reversePointStack->pop();
    while (!reversePointStack->empty()) {
        auto temp = reversePointStack->top();
        for (int i = 0; i < temp->_nextPointList.size(); i++) {
            temp->_lastStart = min(temp->_lastStart,
                                   temp->_nextPointList[i]->_lastStart - temp->_activityList[i]->_lastingTime);
            temp->_activityList[i]->_lastStart =
                    temp->_nextPointList[i]->_lastStart - temp->_activityList[i]->_lastingTime;
        }
        reversePointStack->pop();
    }
    delete passPointStack;
    return result;
}

struct cmp {
    bool operator() (Activity* activity1, Activity* activity2) {
        return activity1->_pre > activity2->_pre;
    }
};

void output(Activity** activityArray, int m) {
    priority_queue<Activity*, vector<Activity*>, cmp> activityQueue;
    for (int i = 0; i < m; i++) {
        if (activityArray[i]->_earlyStart == activityArray[i]->_lastStart) {
            activityQueue.push(activityArray[i]);
        }
    }
    while (!activityQueue.empty()) {
        cout << activityQueue.top()->_pre << "->" <<
        activityQueue.top()->_next << endl;
        activityQueue.pop();
    }
}

void mainPage() {
    cout << "请输入任务交界点个数和任务数量：";
    int n, m;
    cin >> n >> m;
    //判断输入是否合法
    if (n <= 0 || m <= 0) {
        cout << "数量不得小于等于0" << endl;
        return;
    }
    PassPoint** passPointArray = new PassPoint*[n];
    Activity** activityArray = new Activity*[m];
    int* inDegreeArray = new int[n];
    for (int i = 0; i < n; i++) {
        passPointArray[i] = new PassPoint;
        passPointArray[i]->_id = i + 1;
        inDegreeArray[i] = 0;
    }
    cout << "请输入任务开始和完成设计的交接点编号以及完成该任务所需要的时间" << endl;
    for (int i = 0; i < m; i++) {
        int start, finish, lastingTime;
        cin >> start >> finish >> lastingTime;
        //判断输入是否合法
        if (start <= 0 || finish <= 0 || lastingTime <= 0) {
            cout << "输入不得小于等于0" << endl;
            return;
        }
        if (start > n || finish > n) {
            cout << "无该节点" << endl;
            return;
        }
        activityArray[i] = new Activity(start, finish, lastingTime, start, finish);
        inDegreeArray[finish-1]++;
        passPointArray[start-1]->_nextPointList.push_back(passPointArray[finish-1]);
        passPointArray[start-1]->_activityList.push_back(activityArray[i]);
    }
    //进行拓扑排序
    int value = tSort(inDegreeArray, passPointArray, n);
    if (value >= 0) {
        cout << value << endl;
        output(activityArray, m);
    }
    //释放内存
    delete[] passPointArray;
    delete[] activityArray;
    delete[] inDegreeArray;
}


int main() {
    mainPage();
    return 0;
}
