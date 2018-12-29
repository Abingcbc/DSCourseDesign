#include <iostream>
#include <stack>

using namespace std;

struct Point {

    int x;//横坐标
    int y;//纵坐标

    Point(int i, int i1) {
        x = i;
        y = i1;
    }


    bool equal(Point point) {
        if (point.x == this->x && point.y == this->y) {
            return true;
        } else {
            return false;
        }
    }
};

char map[7][7] = {
        {'#', '#', '#', '#', '#', '#', '#'},
        {'#', '0', '#', '0', '0', '0', '#'},
        {'#', '0', '#', '0', '#', '#', '#'},
        {'#', '0', '#', '0', '#', '0', '#'},
        {'#', '0', '#', '0', '0', '0', '#'},
        {'#', '0', '0', '0', '#', '0', '#'},
        {'#', '#', '#', '#', '#', '#', '#'}
};

bool isBlocked[7][7];

Point chooseDirection(Point point) {
    //尝试不同方向
    if (point.x + 1 < 7 &&
    map[point.x + 1][point.y] =='0' &&
    !isBlocked[point.x + 1][point.y]) {
        isBlocked[point.x + 1][point.y] = true;
        return Point(1, 0);
    } else if (point.x - 1 >= 0 &&
    map[point.x - 1][point.y] == '0' &&
    !isBlocked[point.x - 1][point.y]) {
        isBlocked[point.x - 1][point.y] = true;
        return Point(-1, 0);
    } else if (point.y + 1 < 7 &&
    map[point.x][point.y + 1] == '0' &&
    !isBlocked[point.x][point.y + 1]) {
        isBlocked[point.x][point.y + 1] = true;
        return Point(0, 1);
    } else if (point.y - 1 >= 0 &&
    map[point.x][point.y - 1] == '0' &&
    !isBlocked[point.x][point.y - 1]) {
        isBlocked[point.x][point.y - 1] = true;
        return Point(0, -1);
    }
    return Point(0, 0);
}

stack<Point> findRout() {
    //不断回溯寻找
    stack<Point> stack1;
    Point start = Point(1, 1);
    Point end = Point(5, 5);
    isBlocked[start.x][start.y] = true;
    stack1.push(start);
    Point direction = Point(0, 0);
    while( !stack1.empty() && !stack1.top().equal(end)) {
        direction = chooseDirection(stack1.top());
        if (direction.equal(Point(0, 0))) {
            stack1.pop();
            continue;
        } else {
            stack1.push(
                    Point(stack1.top().x + direction.x, stack1.top().y + direction.y));
        }
    }
    if (stack1.empty()) {
        stack1.push(start);
        return stack1;
    }
    stack<Point> result;
    while (!stack1.empty()) {
        result.push(stack1.top());
        map[stack1.top().x][stack1.top().y] = 'x';
        stack1.pop();
    }
    return result;
}

int main() {
    cout << "迷宫地图：" << endl;
    for (int i = 0; i < 7; i++) {
        cout << "     " << i << "列";
    }
    cout << endl;
    for (int i = 0; i < 7; i++) {
        cout << i << "行" << "   ";
        for (int j = 0;  j < 7; j++) {
            cout << map[i][j] << "       ";
        }
        cout << endl;
    }
    stack<Point> result = findRout();
    while (1) {
        cout << "<" << result.top().x << "," << result.top().y << ">";
        result.pop();
        if (result.empty()) {
            break;
        }
        cout << " ---> ";
    }
    return 0;
}