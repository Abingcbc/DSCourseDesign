#include <iostream>
#include <list>
#include <string>
#include <queue>

using namespace std;

class Person {

public:
    list<Person*> _children;
    string _name;

    Person(string name) {
        _name = name;
    }

    ~Person() {
        for (auto child : _children) {
            delete child;
        }
    }

    //解散该成员的家庭
    void remove() {
        for (auto child : _children) {
            delete child;
        }
        _children.clear();
    }

};

class FamilyTree {

private:
    Person* ancestor;

public:

    FamilyTree(string name) {
        ancestor = new Person(name);
    }

    ~FamilyTree() {
        queue<Person*> familyTree;
        for (auto child : ancestor->_children) {
            familyTree.push(child);
        }
        delete ancestor;
        while (!familyTree.empty()) {
            Person* now = familyTree.front();
            familyTree.pop();
            for (auto child : now->_children) {
                familyTree.push(child);
            }
            delete now;
        }
    }

    Person* find(string name) {
        //如果为祖先节点，直接返回
        if (ancestor->_name == name) {
            return ancestor;
        }
        //广度优先搜索直至找到该成员或全部遍历完成
        queue<Person*> familyTree;
        familyTree.push(ancestor);
        while (!familyTree.empty()) {
            Person* now = familyTree.front();
            familyTree.pop();
            if (now->_name == name) {
                return now;
            }
            for (auto child : now->_children) {
                familyTree.push(child);
            }
        }
        return nullptr;
    }

    void makeFamily(string name, list<string> children) {
        Person* now = find(name);
        int num = 0;
        //判断是否有该成员
        if (now != nullptr) {
            int size = now->_children.size() + children.size();
            cout << name << "的第一代子孙是：";
            //加入子女
            for (auto child : children) {
                now->_children.push_back(new Person(child));
                cout << child;
                num++;
                if (num != size) {
                    cout << " ";
                }
            }
            cout << endl;
        } else {
            cout << "没有这名家庭成员" << endl;
        }
        cout << endl;
    }

    void insert(string name, string child) {
        Person* now = find(name);
        //判断是否存在该成员
        if (now != nullptr) {
            Person* isExisted = find(child);
            //判断子女是否已存在
            if (isExisted != nullptr) {
                cout << child << "已存在于家庭中" << endl;
                cout << endl;
                return;
            }
            Person* ch = new Person(child);
            now->_children.push_back(ch);
            cout << name << "的第一代子孙是：";
            int num = 0;
            //添加子女
            for (auto ch : now->_children) {
                cout << ch->_name;
                num++;
                if (num != now->_children.size()) {
                    cout << " ";
                }
            }
            cout << endl;
        } else {
            cout << "没有这名家庭成员" << endl;
        }
        cout << endl;
    }

    void remove(string name) {
        Person* person = find(name);
        //判断是否存在该成员
        if (person != nullptr) {
            cout << "要解散家庭的人是：" << name << endl;
            cout << name << "的第一代子孙是：";
            int num = 0;
            for (auto child : person->_children) {
                cout << child->_name;
                num++;
                if (num != person->_children.size()) {
                    cout << " ";
                }
            }
            cout << endl;
        } else {
            cout << "没有这名家庭成员" << endl;
            return;
        }
        //删除该成员的家庭
        person->remove();
        cout << endl;
    }

    void rename(string name, string newName) {
        Person* person = find(name);
        //判断是否存在该成员
        if (person != nullptr) {
            person->_name = newName;
            cout << name << "已更名为" << newName << endl;
        } else {
            cout << "没有这名家庭成员" << endl;
            return;
        }
        cout << endl;
    }

};
void mainPage() {
    cout << "**           家谱管理系统               **" << endl;
    cout << "========================================" << endl;
    cout << "**         请选择要执行的操作：           **" << endl;
    cout << "**          A --- 完善家谱              **" << endl;
    cout << "**          B --- 添加家庭成员           **" << endl;
    cout << "**          C --- 解散局部家庭           **" << endl;
    cout << "**          D --- 更改家庭成员姓名        **" << endl;
    cout << "**          E --- 退出程序              **" << endl;
    cout << "========================================" << endl;
    cout << endl;
}

void choose() {
    cout << "首先请先建立一个家谱！" << endl;
    cout << "请输入祖先的姓名：";
    string name;
    string child;
    cin >> name;
    cout << "此家族的祖先是：" << name << endl;
    cout << endl;
    FamilyTree* familyTree = new FamilyTree(name);
    char choice;
    int num;
    bool isOver = false;
    while (!isOver) {
        cout << "请选择要执行的操作：";
        cin >> choice;
        switch (choice) {
            case 'A': {
                cout << "请输入要建立家庭的人的姓名：";
                cin >> name;
                do {
                    cout << "请输入" << name << "的儿女人数：";
                    cin >> num;
                    if (num <= 0) {
                        cout << "儿女人数必须大于等于0" << endl;
                        cout << endl;
                    }
                } while (num <= 0);
                cout << "请依次输入" << name << "的儿女的姓名：";
                list<string> children;
                for (int i = 0; i < num; i++) {
                    cin >> child;
                    children.push_back(child);
                }
                familyTree->makeFamily(name, children);
                children.clear();
            }
                break;
            case 'B':
                cout << "请输入要添加儿子（或女儿）的人姓名：";
                cin >> name;
                cout << "请输入" << name << "新添加的儿子（或女儿）的姓名：";
                cin >> child;
                familyTree->insert(name, child);
                break;
            case 'C':
                cout << "请输入要解散家庭的人的姓名：";
                cin >> name;
                familyTree->remove(name);
                break;
            case 'D': {
                cout << "请输入要修改姓名的人的目前姓名：";
                cin >> name;
                cout << "请输入更改后的姓名：";
                string newName;
                cin >> newName;
                familyTree->rename(name, newName);
            }
                break;
            case 'E':
                isOver = true;
                break;
            default:
                cout << "无效操作" << endl;
                cout << endl;
                break;
        }
    }
}

int main() {
    mainPage();
    choose();
    return 0;
}
