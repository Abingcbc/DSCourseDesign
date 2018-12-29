#include "sort.h"

using namespace std;

vector<int> randomNumbers;

void initialRandomNumbers(int num) {
    for (int i = 0; i < num; i++) {
        randomNumbers.push_back(rand());
    }
}



void mainPage() {
    cout << "**           排序算法比较            **" << endl;
    cout << "=====================================" << endl;
    cout << "**           1 --- 冒泡排序          **" << endl;
    cout << "**           2 --- 选择排序          **" << endl;
    cout << "**           3 --- 直接插入排序       **" << endl;
    cout << "**           4 --- 希尔排序          **" << endl;
    cout << "**           5 --- 快速排序          **" << endl;
    cout << "**           6 --- 堆排序            **" << endl;
    cout << "**           7 --- 归并排序          **" << endl;
    cout << "**           8 --- 基数排序          **" << endl;
    cout << "**           9 --- 退出程序          **" << endl;
    cout << endl;
    cout << "请输入要产生的随机数的个数：" << endl;
    int count = 0;
    cin >> count;
    initialRandomNumbers(count);
    int operation = 10;
    while (operation != 9) {
        switch (operation) {
            case 1: {
                long int num = 0;
                vector<int> tobeSorted = randomNumbers;
                //当递归次数过大时，内存会溢出
                if (count <= 100000)
                    recursiveBubbleSort(randomNumbers.size(), num, tobeSorted);
                iterateBubbleSort(randomNumbers);
                break;
            }
            case 2: {
                long int num = 0;
                vector<int> tobeSorted = randomNumbers;
                //当递归次数过大时，内存会溢出
                if (count <= 100000)
                    recursiveSelectSort(0, num, tobeSorted);
                iterateSelectSort(randomNumbers);
                break;
            }
            case 3: {
                long int num = 0;
                vector<int> tobeSorted = randomNumbers;
                //当递归次数过大时，内存会溢出
                if (count <= 100000)
                    recursiveInsertSort(0, num, tobeSorted);
                iterateInsertSort(randomNumbers);
                break;
            }
            case 4: {
                long int num = 0;
                vector<int> tobeSorted = randomNumbers;
                //当递归次数过大时，内存会溢出
                if (count <= 100000)
                    recursiveShellSort((int) tobeSorted.size() / 2, num, tobeSorted);
                iterateShellSort(randomNumbers);
                break;
            }
            case 5: {
                long int num = 0;
                vector<int> tobeSorted = randomNumbers;
                //当递归次数过大时，内存会溢出
                if (count <= 100000)
                    recursiveQuickSort(tobeSorted, num, 0, tobeSorted.size() - 1);
                iterateQuickSort(randomNumbers);
                break;
            }
            case 6:
                //当递归次数过大时，内存会溢出
                if (count <= 100000)
                    recursiveHeapSort(randomNumbers);
                iterateHeapSort(randomNumbers);
                break;
            case 7: {
                long int num = 0;
                vector<int> tobeSorted = randomNumbers;
                //当递归次数过大时，内存会溢出
                if (count <= 100000)
                    recursiveMergeSort(tobeSorted, 0, tobeSorted.size(), num);
                iterateMergeSort(randomNumbers);
                break;
            }
            case 8: {
                long int num = 0;
                vector<int> tobeSorted = randomNumbers;
                //当递归次数过大时，内存会溢出
                if (count <= 100000)
                    recursiveBaseSort(tobeSorted, 10, 0);
                iterateBaseSort(randomNumbers);
                break;
            }
            case 9:
                return;
            case 10:
                break;
            default:
                cout << "无该操作" << endl;
                break;
        }
        cout << "请选择排序算法：";
        cin >> operation;
    }
}

int main() {
    mainPage();
    return 0;
}