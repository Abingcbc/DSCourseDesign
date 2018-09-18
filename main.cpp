#include <iostream>

using namespace std;

class LinkedNode {
private:
    LinkedNode *pre_node;
    LinkedNode *next_node;
    int value = 0;
public:
    LinkedNode(LinkedNode *pre, LinkedNode *next, int val):
    pre_node(pre), next_node(next), value(val) {}
    ~LinkedNode() = default;

    int getValue() {
        return value;
    }

    LinkedNode* getNext() {
        return next_node;
    }

    LinkedNode* getPre() {
        return pre_node;
    }

    void setNext(LinkedNode *next) {
        next_node = next;
    }

    void setPre(LinkedNode *pre) {
        pre_node = pre;
    }

    //If the first is smaller than the next, then return -1.
    static int compare(LinkedNode *node1, LinkedNode *node2) {
        if (node1->value < node2->value)
            return -1;
        else if (node1->value == node2->value)
            return 0;
        else
            return 1;
    }
};

class LinkedList {
private:
    LinkedNode *start = nullptr;
    LinkedNode *last = nullptr;
public:
    LinkedList() = default;
    ~LinkedList() {
        while(start != nullptr) {
            LinkedNode *temp = start;
            start = start->getNext();
            delete temp;
        }
    }

    void sortedAdd(int value) {
        LinkedNode *insertedNode = new LinkedNode(nullptr, nullptr, value);
        LinkedNode *temp = start;
        while (temp != nullptr) {
            if (LinkedNode::compare(insertedNode, temp) <= 0) {
                if (temp->getPre() == nullptr) {
                    insertedNode->setNext(temp);
                    temp->setPre(insertedNode);
                    start = insertedNode;
                }
                else {
                    insertedNode->setPre(temp->getPre());
                    insertedNode->setNext(temp);
                    temp->getPre()->setNext(insertedNode);
                    temp->setPre(insertedNode);
                }
                break;
            }
            temp = temp->getNext();
        }
        if (temp == nullptr) {
            if (last == nullptr && start == nullptr) {
                start = insertedNode;
                last = insertedNode;
            }
            else {
                last->setNext(insertedNode);
                insertedNode->setPre(last);
                last = insertedNode;
            }
        }
    }

    static LinkedList* intersection(LinkedList* linkedList1, LinkedList* linkedList2) {
        LinkedNode *temp1 = linkedList1->start;
        LinkedNode *temp2 = linkedList2->start;
        LinkedList *result = new LinkedList();
        while (temp1 != nullptr && temp2 != nullptr) {
            if (LinkedNode::compare(temp1, temp2) == -1) {
                temp1 = temp1->getNext();
            }
            else if (LinkedNode::compare(temp1, temp2) == 0) {
                result->sortedAdd(temp1->getValue());
                temp1 = temp1->getNext();
                temp2 = temp2->getNext();
            }
            else {
                temp2 = temp2->getNext();
            }
        }
        return result;
    }

    void print() {
        if (start == last && last == nullptr) {
            cout << "NULL" << endl;
        }
        else {
            LinkedNode* node = start;
            while (node != nullptr) {
                cout << node->getValue();
                node = node->getNext();
                if (node != nullptr)
                    cout << " ";
            }
        }
    }
};

int main() {
    cout << "请输入两个序列，用-1表示序列的结尾" << endl;
    int value = 0;
    LinkedList *linkedList1 = new LinkedList();
    LinkedList *linkedList2 = new LinkedList();
    while (cin >> value && value > 0) {
        linkedList1->sortedAdd(value);
    }
    while (cin >> value && value > 0) {
        linkedList2->sortedAdd(value);
    }
    LinkedList *result = LinkedList::intersection(linkedList1, linkedList2);
    result->print();
    return 0;
}