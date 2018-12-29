#include <iostream>
#include <vector>
#include <string>
#include <queue>


using namespace std;


class ElectricityNode {

public:

    string _name;//电网节点的名字

    ElectricityNode(string name) {
        _name = name;
    }
};

class ElectricityLine {

public:

    ElectricityNode* _node1;//边的第一个节点
    ElectricityNode* _node2;//边的第二个节点
    int _weight;//边的权重

    ElectricityLine(ElectricityNode* node1, ElectricityNode* node2, int weight):
    _node1(node1), _node2(node2), _weight(weight){}
};

struct cmp {
    bool operator() (ElectricityLine* line1, ElectricityLine* line2){
        return line1->_weight > line2->_weight;
    }

};
class ElectricityNet {
    vector<ElectricityNode*> _electricityNodeList;
    vector<ElectricityLine*> _electricityLineList;
    vector<ElectricityLine*> _minTree;

public:

    //创建电网节点
    void createNode() {
        cout << "请输入顶点的个数：";
        int num;
        cin >> num;
        if (num < 1) {
            cout << "请输入一个正整数！" << endl;
            cout << endl;
            return;
        }
        cout << "请依次输入顶点的名称：";
        for (int i = 0; i < num; i++) {
            string name;
            cin >> name;
            ElectricityNode* node = new ElectricityNode(name);
            _electricityNodeList.push_back(node);
        }
        cout << endl;
    }

    //添加电网的边
    void createLine() {
        string node1;
        string node2;
        int weight;
        ElectricityNode* temp1;
        ElectricityNode* temp2;
        while (1) {
            cout << "请输入两个顶点及边：";
            cin >> node1;
            cin >> node2;
            cin >> weight;
            if (node1 == "?" || node2 == "?" || weight == 0)
                break;
            for (auto node : _electricityNodeList) {
                if (node->_name == node1) {
                    temp1 = node;
                } else if (node->_name == node2) {
                    temp2 = node;
                }
            }
            _electricityLineList.push_back(new ElectricityLine(temp1, temp2, weight));
        }
        cout << endl;
    }

    //使用Prim算法求最小生成树
    void createMinTree () {
        if (_electricityNodeList.size() < 2) {
            cout << "电网节点数不得少于2！" << endl;
            return;
        }
        cout << "请输入起始顶点：";
        string start;
        cin >> start;
        int num = 0;
        ElectricityNode* currentNode;
        priority_queue<ElectricityLine*, vector<ElectricityLine*>, cmp> preparedLine;
        //获取起始节点
        for (auto node : _electricityNodeList) {
            if (node->_name == start) {
                num++;
                currentNode = node;
                break;
            }
        }
        if (num == 0) {
            cout << "该顶点不存在" << endl;
            return;
        }
        //Prim算法求最小生成树
        while (num != _electricityNodeList.size()) {
            for (auto line : _electricityLineList) {
                if (line->_node1 == currentNode) {
                    preparedLine.push(line);
                }
            }
            _minTree.push_back(preparedLine.top());
            currentNode = preparedLine.top()->_node2;
            num++;
            preparedLine.pop();
        }
        cout << "生成最小生成树!" << endl;
        cout << endl;
    }

    void printMinTree() {
        for (auto line : _minTree) {
            cout << line->_node1->_name << "-<";
            cout << line->_weight << ">->";
            cout << line->_node2->_name << "    ";
        }
        cout << endl;
    }
};

void mainPage() {
    ElectricityNet* net = new ElectricityNet;
    cout << "**            电网造价模拟系统             **" << endl;
    cout << "==========================================" << endl;
    cout << "**            A --- 创建电网顶点          **" << endl;
    cout << "**            B --- 添加电网的边          **" << endl;
    cout << "**            C --- 构成最小生成树         **" << endl;
    cout << "**            D --- 显示最小生成树         **" << endl;
    cout << "**            E --- 退出 程序             **" << endl;
    cout << "==========================================" << endl;
    cout << endl;
    cout << "请选择操作：";
    char op;
    cin >> op;
    while (1) {
        if (op == 'E')
            break;
        switch (op) {
            case 'A':
                net->createNode();
                break;
            case 'B':
                net->createLine();
                break;
            case 'C':
                net->createMinTree();
                break;
            case 'D':
                net->printMinTree();
                break;
            default:
                cout << "无效操作" << endl;
        }
        cout << "请选择操作：";
        cin >> op;
    }
}

int main() {
    mainPage();
    return 0;
}