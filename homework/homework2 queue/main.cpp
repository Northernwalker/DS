#include"../queue/Queue.h"

#include <iostream>
#include <time.h>
#include <stack>
#include <vector>
using namespace std;

//这个计算面积的不会用队列实现。。。

int largestRectangleArea(vector<int>& heights) {
    int res = 0;
    stack<int> s;
    heights.push_back(0);
    for (int i = 0; i < heights.size(); i++) {
        while (!s.empty() && heights[s.top()] > heights[i]) {
            int h = heights[s.top()];
            s.pop();
            int w = s.empty() ? i : i - s.top() - 1;
            res = max(res, h * w);//比较两者取最大值
        }
        s.push(i);
    }
    return res;
}

int main() {
    srand(time(0));
    int s1[10];//创建数组储存每个柱型的高度，此处定为10个柱型
    for (int i = 0; i < 10; i++) {
        cout << "每个柱型高度：";
        for (int j = 0; j < 10; j++) {
            s1[j] = rand() % 100;//为每个柱型赋随机值
            cout << s1[j] << " ";
        }
        cout << endl;
        vector<int> heights = { s1[0],s1[1],s1[2],s1[3],s1[4],s1[5],s1[6],s1[7],s1[8],s1[9] };
        int res = largestRectangleArea(heights);//计算最小面积
        cout << res << endl;//输出最小面积
    }
    //也可手动输入高度（具体个数可在代码中定义，默认为10个）
    int s2[10] = { 0,0,0,0,0,0,0,0,0,0 };//初始化
    cout << "请输入高度(10个）：" << endl;
    for (int k = 0; k < 10; k++) {
        cin >> s2[k];
    }
    vector<int> heights = { s2[0],s2[1],s2[2],s2[3],s2[4],s2[5],s2[6],s2[7],s2[8],s2[9] };
    int res = largestRectangleArea(heights);//计算最小面积
    cout << res << endl;//输出最小面积
    return 0;
}
