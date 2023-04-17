#include"../queue/Queue.h"

#include <iostream>
#include <time.h>
#include <stack>
#include <vector>
using namespace std;

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
    int s[10];//创建数组储存每个柱型的高度，此处定为10个柱型
    for (int i = 0; i < 10; i++) {
        cout << "每个柱型高度：";
        for (int j = 0; j < 10; j++) {
            s[j] = rand() % 100;//为每个柱型赋随机值
            cout << s[j] << " ";
        }
        cout << endl;
        vector<int> heights = { s[0],s[1],s[2],s[3],s[4],s[5],s[6],s[7],s[8],s[9] };
        int res = largestRectangleArea(heights);//计算最小面积
        cout << res << endl;//输出最小面积
    }
    return 0;
}