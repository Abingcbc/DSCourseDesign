//
//  main.cpp
//  Data_Structure_Design
//
//  Created by cbc on 2018/9/17.
//  Copyright © 2018年 cbc. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

class Student {
private:
    int id;
    string name;
    string sex;
    int age;
    string type;
    Student *pre;
    Student *next;
    
public:
    Student(int _id, string _name, string _sex, int _age, string _type,
            Student *_pre, Student *_next):
    id(_id),
    name(_name),
    sex(_sex),
    age(_age),
    type(_type),
    pre(_pre),
    next(_next) {}
    ~Student() = default;

    void setPre(Student *pre_stu) {
        pre = pre_stu;
    }

    void setNext(Student *next_stu) {
        next = next_stu;
    }

    Student* getPre() {
        return this->pre;
    }

    Student* getNext() {
        return this->next;
    }

    void print() {
        cout << id << "      " << name << "    " << sex << "     "
        << age << "     " << type << endl;
    }

    int getId() {
        return this->id;
    }

    void reset (int _id, string _name, string _sex, int _age, string _type) {
        id = _id;
        name = _name;
        sex = _sex;
        age = _age;
        type = _type;
    }
};

class LinkedList {

private:
    Student *start_stu = nullptr;
    Student *last_stu = nullptr;
    int all_num = 0;

public:
    LinkedList() = default;

    ~LinkedList() {
        while (start_stu != nullptr) {
            Student *temp = start_stu;
            start_stu = temp->getNext();
            delete temp;
        }
    }

    void print() {
        Student *temp = start_stu;
        cout << endl;
        cout << "考号    " << "姓名    " << "性别    " << "年龄    " << "报考类别" << endl;
        while (temp != nullptr) {
            temp->print();
            temp = temp->getNext();
        }
    }

    void build(int _id, string _name, string _sex, int _age, string _type){
        if (start_stu == nullptr) {
            Student *temp_stu = new Student(_id, _name, _sex, _age, _type,
                    nullptr, nullptr);
            start_stu = temp_stu;
            last_stu = temp_stu;
        }
        else {
            Student *temp_stu = new Student(_id, _name, _sex, _age, _type,
                    last_stu, nullptr);
            last_stu->setNext(temp_stu);
            last_stu = temp_stu;
        }
        all_num++;
    }

    void insert(int pos, int _id, string _name, string _sex, int _age, string _type) {
        Student *temp = start_stu;
        Student *stu_insert = new Student(_id, _name, _sex, _age, _type,
                nullptr, nullptr);
        if (pos == 1) {//When insert the first student, there is no previous one.
            temp->setPre(stu_insert);
            stu_insert->setNext(start_stu);
            all_num++;
        }
        else if (pos > 1) {
            for (int i = 0; i < (pos - 2) && temp != nullptr; i++) {
                temp = temp->getNext();
            }
            stu_insert->setNext(temp->getNext());
            stu_insert->setPre(temp);
            if (temp->getNext() != nullptr) {
                temp->getNext()->setPre(stu_insert);
                temp->setNext(stu_insert);
            }
            else {
                temp->setNext(stu_insert);
            }
            all_num++;
        }
        else {
            cout << "请输入一个自然数！" << endl;
        }

    }

    void remove(int id) {
        Student *temp = start_stu;
        while (temp != nullptr) {
            if (temp->getId() == id)
                break;
            temp = temp->getNext();
        }
        if (temp == nullptr) {
            cout << "无此考号的考生" << endl;
        }
        else {
            cout << "你删除的考生信息是：";
            temp->print();
            if (temp->getPre() != nullptr)
                temp->getPre()->setNext(temp->getNext());
            else {
                start_stu = temp->getNext();
            }
            if (temp->getNext() != nullptr)
                temp->getNext()->setPre(temp->getPre());
            delete temp;
            this->print();
            all_num--;
        }
    }

    void find(int id) {
        Student *temp = start_stu;
        while (temp != nullptr) {
            if (temp->getId() == id) {
                cout << "考号    " << "姓名    " << "性别    " << "年龄    " << "报考类别" << endl;
                temp->print();
                break;
            }
            temp = temp->getNext();
        }
        if (temp == nullptr) {
            cout << "无此考号的考生" << endl;
        }
    }

    void reset(int _id, string _name, string _sex, int _age, string _type) {
        Student *temp = start_stu;
        while  (temp != nullptr) {
            if (temp->getId() == _id) {
                temp->reset(_id, _name, _sex, _age, _type);
                break;
            }
        }
        if (temp == nullptr) {
            cout << "无此考号的考生" << endl;
        }
        else {
            this->print();
        }
    }

    int getNum() {
        return all_num;
    }

};

int main() {
    cout << "首先请建立考生信息系统!" << endl;
    int stu_num = 0;
    cout << "请输入考生人数：";
    while (cin >> stu_num) {
        if (stu_num > 0)
            break;
        cout << "请输入一个正整数！" << endl;
        cout << "请输入考生人数：";
    }
    cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
    int id;
    string name;
    string sex;
    int age;
    string type;
    LinkedList *stu_list = new LinkedList;
    for (int i = 0; i < stu_num; i++) {
        cin >> id >> name >> sex >> age >> type;
        stu_list->build(id, name, sex, age, type);
    }

    //print out all the students' information
    stu_list->print();

    cout << "请输入您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作" << endl;
    cout << endl;
    int action = 0;
    cout << "请输入您要进行的操作：";
    while (cin >> action) {
        switch (action) {
            case 0:
                return 0;
            case 1:
                int pos;
                cout << "请输入你要插入的考生的位置：";
                cin >> pos;
                if (pos > (stu_list->getNum() + 1)) {
                    cout << "请输入一个小于" << stu_list->getNum() + 1<< "的正整数！" << endl;
                    break;
                }
                cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别！" << endl;
                cin >> id >> name >> sex >> age >> type;
                stu_list->insert(pos, id, name, sex, age, type);
                stu_list->print();
                break;
            case 2:
                cout << "请输入要删除的考生的考号：";
                cin >> id;
                stu_list->remove(id);
                break;
            case 3:
                cout << "请输入要查找的考生的考号：";
                cin >> id;
                stu_list->find(id);
                break;
            case 4
