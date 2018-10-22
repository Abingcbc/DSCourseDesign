#include <iostream>
#include <stack>
#include <string>

using namespace std;

int getLevel(string str) {
    if (str == "(" || str == ")") {
        return 0;
    }
    else if (str == "*" || str == "/") {
        return 2;
    }
    else if (str == "+" || str == "-") {
        return 1;
    }
    return 0;
}

bool isOperate(string string1) {
    if (string1 == "(" || string1 == ")" ||
        string1 == "+" || string1 == "-" ||
        string1 == "*" || string1 == "/") {
        return true;
    }
    else {
        return false;
    }
}

string transform() {
    string element;
    stack<string> stack1;
    string result;
    while (cin >> element) {
        if (element == "q")
            break;
        if (element == "(") {
            stack1.push(element);
        }
        else if (element == ")") {
            while (stack1.top() != "(") {
                result.append(" " + stack1.top());
                stack1.pop();
            }
            stack1.pop();
        }
        else {
            if (isOperate(element)) {
                while (!stack1.empty() && getLevel(stack1.top()) >= getLevel(element)) {
                    result.append(" " + stack1.top());
                    stack1.pop();
                }
                stack1.push(element);
            } else {
                string string1 = "+";
                if (element[0] == string1[0]) {
                    element.erase(element.begin());
                }
                if (result.empty()) {
                    result.append(element);
                } else {
                    result.append(" " + element);
                }
            }
        }
    }
    while (!stack1.empty()) {
        result.append(" " + stack1.top());
        stack1.pop();
    }
    return result;
}

int main() {
    string result;
    result = transform();
    cout << result << endl;
    return 0;
}