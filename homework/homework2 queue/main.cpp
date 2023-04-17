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
            res = max(res, h * w);//�Ƚ�����ȡ���ֵ
        }
        s.push(i);
    }
    return res;
}

int main() {
    srand(time(0));
    int s[10];//�������鴢��ÿ�����͵ĸ߶ȣ��˴���Ϊ10������
    for (int i = 0; i < 10; i++) {
        cout << "ÿ�����͸߶ȣ�";
        for (int j = 0; j < 10; j++) {
            s[j] = rand() % 100;//Ϊÿ�����͸����ֵ
            cout << s[j] << " ";
        }
        cout << endl;
        vector<int> heights = { s[0],s[1],s[2],s[3],s[4],s[5],s[6],s[7],s[8],s[9] };
        int res = largestRectangleArea(heights);//������С���
        cout << res << endl;//�����С���
    }
    return 0;
}