#ifndef DATASTRUCTURE_SORT_H
#define DATASTRUCTURE_SORT_H

#include <time.h>
#include <iostream>
#include <vector>
#include <stack>
#include <math.h>

using namespace std;

void swap(int& num1, int& num2, long int& count) {
    count++;
    int temp = num1;
    num1 = num2;
    num2 = temp;
}

void recursiveBubbleSort(int size, long int& num, vector<int>& tobeSorted) {
    if (size < 2)
        return;
    clock_t start, over;
    start = clock();
    for (int j = 1; j < size; j++) {
        if (tobeSorted[j-1] > tobeSorted[j]) {
            swap(tobeSorted[j-1], tobeSorted[j], num);
        }
    }
    recursiveBubbleSort(size-1, num, tobeSorted);
    if (size == tobeSorted.size()) {
        over = clock();
        cout << "冒泡排序（递归）所用时间： " << over - start << "ms" << endl;
        cout << "冒泡排序（递归）交换次数： " << num << endl;
    }
}

void iterateBubbleSort(vector<int> tobeSorted) {
    clock_t start, over;
    long int num = 0;
    start = clock();
    for (int i = 0; i < tobeSorted.size(); i++) {
        for (int j = 1; j < tobeSorted.size()-i; j++) {
            if (tobeSorted[j-1] > tobeSorted[j]) {
                swap(tobeSorted[j-1], tobeSorted[j], num);
            }
        }
    }
    over = clock();
    cout << "冒泡排序（迭代）所用时间： " << over - start << "ms" << endl;
    cout << "冒泡排序（迭代）交换次数： " << num << endl;

}

void recursiveSelectSort(int current, long int& num, vector<int>& tobeSorted) {
    if (current == tobeSorted.size() - 1) {
        return;
    }
    clock_t start, over;
    start = clock();
    int min = current;
    for (int j = current+1; j < tobeSorted.size(); j++) {
        if (tobeSorted[min] > tobeSorted[j]) {
            min = j;
        }
    }
    swap(tobeSorted[current], tobeSorted[min], num);
    recursiveSelectSort(current+1, num, tobeSorted);
    if (current == 0) {
        over = clock();
        cout << "选择排序（递归）所用时间： " << over - start << "ms" << endl;
        cout << "选择排序（递归）交换次数： " << num << endl;
    }
}

void iterateSelectSort(vector<int> tobeSorted) {
    clock_t start, over;
    long int num = 0;
    start = clock();
    for (int i = 0; i < tobeSorted.size()-1; i++) {
        int min = i;
        for (int j = i+1; j < tobeSorted.size(); j++) {
            if (tobeSorted[min] > tobeSorted[j]) {
                min = j;
            }
        }
        swap(tobeSorted[i], tobeSorted[min], num);
    }
    over = clock();
    cout << "选择排序（迭代）所用时间： " << over - start << "ms" << endl;
    cout << "选择排序（迭代）交换次数： " << num << endl;
}

void recursiveInsertSort(int current, long int& num, vector<int>& tobeSorted) {
    if (current == tobeSorted.size()) {
        return;
    }
    clock_t start, over;
    start = clock();
    for (int j = current-1; j >= 0; j--) {
        if (tobeSorted[j+1] < tobeSorted[j]) {
            swap(tobeSorted[j+1], tobeSorted[j], num);
        }
    }
    recursiveInsertSort(current+1, num, tobeSorted);
    if (current == 0) {
        over = clock();
        cout << "插入排序（递归）所用时间： " << over - start << "ms" << endl;
        cout << "插入排序（递归）交换次数： " << num << endl;
    }
}

void iterateInsertSort(vector<int> tobeSorted) {
    clock_t start, over;
    long int num = 0;
    start = clock();
    for (int i = 0; i < tobeSorted.size(); i++) {
        for (int j = i-1; j >= 0; j--) {
            if (tobeSorted[j+1] < tobeSorted[j]) {
                swap(tobeSorted[j+1], tobeSorted[j], num);
            } else {
                break;
            }
        }
    }
    over = clock();
    cout << "插入排序（迭代）所用时间： " << over - start << "ms" << endl;
    cout << "插入排序（迭代）交换次数： " << num << endl;
}

void recursiveShellSort(int gap, long int& num, vector<int>& tobeSorted) {
    if (gap == 0) {
        return;
    }
    clock_t start, over;
    start = clock();
    for (int i = gap; i < tobeSorted.size(); i++) {
        for (int j = i; j >= gap; j -= gap) {
            if (tobeSorted[j] < tobeSorted[j - gap]) {
                swap(tobeSorted[j], tobeSorted[j - gap], num);
            } else {
                break;
            }
        }
    }
    recursiveShellSort(gap == 2 ? 1 : (int) (gap / 2.2), num, tobeSorted);
    if (gap == (int) tobeSorted.size() / 2) {
        over = clock();
        cout << "希尔排序（递归）所用时间： " << over - start << "ms" << endl;
        cout << "希尔排序（递归）交换次数： " << num << endl;
    }
}

void iterateShellSort(vector<int> tobeSorted) {
    long int num = 0;
    clock_t start, over;
    start = clock();
    int gap = (int) tobeSorted.size() / 2;
    while (gap) {
        for (int i = gap; i < tobeSorted.size(); i++) {
            for (int j = i; j >= gap; j -= gap) {
                if (tobeSorted[j] < tobeSorted[j - gap]) {
                    swap(tobeSorted[j], tobeSorted[j - gap], num);
                } else {
                    break;
                }
            }
        }
        gap = (gap == 2 ? 1 : (int) (gap / 2.2));
    }
    over = clock();
    cout << "希尔排序（迭代）所用时间： " << over - start << "ms" << endl;
    cout << "希尔排序（迭代）交换次数： " << num << endl;
}

void recursiveQuickSort(vector<int>& tobeSorted, long int& num, int left, int right) {
    if (left >= right) {
        return;
    }
    clock_t start, over;
    start = clock();
    int pivot = tobeSorted[left];
    int low = left;
    int high = right;
    while (low < high) {
        while (low < high && tobeSorted[high] >= pivot) {
            high--;
        }
        if (low < high) {
            tobeSorted[low] = tobeSorted[high];
            num++;
        }
        while (low < high && tobeSorted[low] < pivot) {
            low++;
        }
        if (low < high) {
            tobeSorted[high] = tobeSorted[low];
            num++;
        }
    }
    tobeSorted[low] = pivot;
    num++;
    recursiveQuickSort(tobeSorted, num, left, low-1);
    recursiveQuickSort(tobeSorted, num, low+1, right);
    if (left == 0 && right == tobeSorted.size()-1) {
        over = clock();
        cout << "快速排序（递归）所用时间： " << over - start << "ms" << endl;
        cout << "快速排序（递归）交换次数： " << num << endl;
    }
}

void iterateQuickSort(vector<int> tobeSorted) {
    long int num = 0;
    stack<int> left;
    stack<int> right;
    clock_t start, over;
    start = clock();
    left.push(0);
    right.push(tobeSorted.size()-1);
    while (!left.empty()) {
        int low = left.top();
        int high = right.top();
        if (low >= high) {
            left.pop();
            right.pop();
            continue;
        }
        int pivot = tobeSorted[low];
        while (low < high) {
            while (low < high && tobeSorted[high] >= pivot) {
                high--;
            }
            if (low < high) {
                tobeSorted[low] = tobeSorted[high];
                num++;
            }
            while (low < high && tobeSorted[low] < pivot) {
                low++;
            }
            if (low < high) {
                tobeSorted[high] = tobeSorted[low];
                num++;
            }
        }
        tobeSorted[low] = pivot;
        num++;
        //先将左侧子序列两端压入栈
        int temp = right.top();
        right.pop();
        right.push(low-1);
        //再将右侧子序列两端压入栈
        left.push(low+1);
        right.push(temp);
    }
    over = clock();
    cout << "快速排序（迭代）所用时间： " << over - start << "ms" << endl;
    cout << "快速排序（迭代）交换次数： " << num << endl;
}

void recursiveUpdateHeap(vector<int>& tobeSorted, long int& num, int i, int size) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;
    if (left < size && tobeSorted[left] > tobeSorted[i]) {
        largest = left;
    } else {
        largest = i;
    }
    if (right < size && tobeSorted[right] > tobeSorted[largest]) {
        largest = right;
    }
    if (largest != i) {
        swap(tobeSorted[i], tobeSorted[largest], num);
        i = largest;
        recursiveUpdateHeap(tobeSorted, num, i, size);
    }
}

void recursiveBuildMaxHeap(vector<int>& tobeSorted, long int& num) {
    for (int i = tobeSorted.size()/2; i >= 0; i--) {
        recursiveUpdateHeap(tobeSorted, num, i, tobeSorted.size());
    }
}

void recursiveHeapSort(vector<int> tobeSorted) {
    long int num = 0;
    clock_t start, over;
    start = clock();
    recursiveBuildMaxHeap(tobeSorted, num);
    for (int i = tobeSorted.size()-1; i > 0; i--) {
        swap(tobeSorted[0], tobeSorted[i], num);
        recursiveUpdateHeap(tobeSorted, num, 0, i);
    }
    over = clock();
    cout << "堆排序（递归）所用时间： " << over - start << "ms" << endl;
    cout << "堆排序（递归）交换次数： " << num << endl;

}

void iterateUpdateHeap(vector<int>& tobeSorted, long int& num, int i, int size) {
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;
        if (left < size && tobeSorted[left] > tobeSorted[i]) {
            largest = left;
        } else {
            largest = i;
        }
        if (right < size && tobeSorted[right] > tobeSorted[largest]) {
            largest = right;
        }
        if (largest != i) {
            swap(tobeSorted[i], tobeSorted[largest], num);
            i = largest;
        } else {
            break;
        }
    }
}

void iterateBuildMaxHeap(vector<int>& tobeSorted, long int& num) {
    for (int i = tobeSorted.size()/2; i >= 0; i--) {
        iterateUpdateHeap(tobeSorted, num, i, tobeSorted.size());
    }
}

void iterateHeapSort(vector<int> tobeSorted) {
    long int num = 0;
    clock_t start, over;
    start = clock();
    iterateBuildMaxHeap(tobeSorted, num);
    for (int i = tobeSorted.size()-1; i > 0; i--) {
        swap(tobeSorted[0], tobeSorted[i], num);
        iterateUpdateHeap(tobeSorted, num, 0, i);
    }
    over = clock();
    cout << "堆排序（迭代）所用时间： " << over - start << "ms" << endl;
    cout << "堆排序（迭代）交换次数： " << num << endl;
}

void merge(vector<int>& tobeSorted, int low, int mid, int high, long int& num) {
    vector<int> temp = tobeSorted;
    int i = low;
    int j = mid;
    int current = low;
    while (i < mid && j < high) {
        if (tobeSorted[i] < tobeSorted[j]) {
            temp[current] = tobeSorted[i];
            num++;
            i++;
        } else {
            temp[current] = tobeSorted[j];
            j++;
            num++;
        }
        current++;
    }
    while (i < mid) {
        temp[current] = tobeSorted[i];
        current++;
        num++;
        i++;
    }
    while (j < high) {
        temp[current] = tobeSorted[j];
        current++;
        num++;
        j++;
    }
    for (int m = low; m < high; m++) {
        tobeSorted[m] = temp[m];
        num++;
    }
}

void recursiveMergeSort(vector<int>& tobeSorted, int low, int high, long int& num) {
    if (high - low < 2)
        return;
    clock_t start, over;
    start = clock();
    recursiveMergeSort(tobeSorted, low, (low+high)/2, num);
    recursiveMergeSort(tobeSorted, (low+high)/2, high, num);
    merge(tobeSorted, low, (low+high)/2, high, num);
    if (low == 0 && high == tobeSorted.size()) {
        over = clock();
        cout << "归并排序（递归）所用时间： " << over - start << "ms" << endl;
        cout << "归并排序（递归）交换次数： " << num << endl;
    }
}

void iterateMergeSort(vector<int> tobeSorted) {
    long int num = 0;
    const int size = tobeSorted.size();
    clock_t start, over;
    start = clock();
    for (int i = 1; i < size; i *= 2) {
        int j;
        for (j = 0; j + i < size; j += 2*i) {
            if (j + 2*i > size) {
                merge(tobeSorted, j, j+i, size, num);
                break;
            }
            merge(tobeSorted, j, j+i, j+2*i, num);
        }
    }
    over = clock();
    cout << "归并排序（迭代）所用时间： " << over - start << "ms" << endl;
    cout << "归并排序（迭代）交换次数： " << num << endl;
}

void recursiveBaseSort(vector<int>& tobeSorted, int times, int pos) {
    if (pos >= times)
        return;
    vector<int> bucket(tobeSorted.size(), 0);
    vector<int> count(10, 0);
    long int num = 0;
    clock_t start, over;
    start = clock();
    if (pos == 0) {
        int maxNum = 0;
        for (auto i : tobeSorted) {
            if (i > maxNum)
                maxNum = i;
        }
        times = 0;
        while (maxNum != 0) {
            maxNum = maxNum / 10;
            times++;
        }
    }
    for (int i = 0; i < 10; i++) {
        count[i] = 0;
    }
    for (auto i : tobeSorted) {
        int temp = ((int)(i/pow(10, pos))%10);
        count[temp]++;
    }
    //为了统一0，所以采用右边界
    for (int i = 1; i < 10; i++) {
        count[i] = count[i-1] + count[i];
    }
    for (int i = tobeSorted.size()-1; i >= 0; i--) {
        int temp = ((int)(tobeSorted[i]/pow(10, pos))%10);
        bucket[count[temp]-1] = tobeSorted[i];
        count[temp]--;
    }
    tobeSorted = bucket;
    recursiveBaseSort(tobeSorted, times, pos+1);
    if (pos == 0) {
        over = clock();
        cout << "基数排序（递归）所用时间： " << over - start << "ms" << endl;
        cout << "基数排序（递归）交换次数： " << num << endl;
    }
}

void iterateBaseSort(vector<int> tobeSorted) {
    vector<int> bucket(tobeSorted.size(), 0);
    vector<int> count(10, 0);
    long int num = 0;
    clock_t start, over;
    start = clock();
    int maxNum = 0;
    for (auto i : tobeSorted) {
        if (i > maxNum)
            maxNum = i;
    }
    int times = 0;
    while (maxNum != 0) {
        maxNum = maxNum / 10;
        times++;
    }
    for (int pos = 0; pos < times; pos++) {
        for (int i = 0; i < 10; i++) {
            count[i] = 0;
        }
        for (auto i : tobeSorted) {
            int temp = ((int)(i/pow(10, pos))%10);
            count[temp]++;
        }
        //为了统一0，所以采用右边界
        for (int i = 1; i < 10; i++) {
            count[i] = count[i-1] + count[i];
        }
        for (int i = tobeSorted.size()-1; i >= 0; i--) {
            int temp = ((int)(tobeSorted[i]/pow(10, pos))%10);
            bucket[count[temp]-1] = tobeSorted[i];
            count[temp]--;
        }
        tobeSorted = bucket;
    }
    over = clock();
    cout << "基数排序（迭代）所用时间： " << over - start << "ms" << endl;
    cout << "基数排序（迭代）交换次数： " << num << endl;
}

#endif
