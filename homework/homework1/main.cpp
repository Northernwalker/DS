#include"../../Complex2.h"
#include"../../../vector/vector.h"
#include<windows.h>
#include<time.h>
using namespace std;


int main()
{
	srand(time(0));//设置随机种子与时间相关，确保能生成完全随机的复数
	double time = 0;
	double counts = 0;
	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	complex* a = new complex[10];//随机生成一组复数
	Vector<complex>v1(a, 10);//将随机生成的复数复制到向量中
	Vector<complex>v2(a, 10);//将随机生成的复数复制到另一个向量中备用
	Vector<complex>v3(a, 10);//再复制一个备用qwq
	int i;
	//double real,imag;
	for (i = 0; i < 10; i++) {
		v1[i].display();
	}//输出复数向量
	cout<< endl;
	v1.unsort(0, 10);//置乱
	cout << "置乱后：" << endl;
	for (i = 0; i < 10; i++) {
		v1[i].display();
	}//输出置乱后的复数向量

	cout << endl << "查找实部虚部相同的复数:" << endl;
	v1.findcomplex(0, 10);//查找实部和虚部相同的复数并输出

	cout << endl << "准备插入的复数：" << endl;
	complex insert;//生成一个准备插入的复数
	insert.display();//展示准备插入的复数
	cout << endl << "插入后的复数向量：" << endl;
	v1.insert(2, insert);//在向量中某处（此处为2）插入一个复数
	for (i = 0; i < 11; i++) {
		v1[i].display();
	}//输出插入后的复数向量

	cout << endl << "区间删除后的复数向量：" << endl;
	v1.remove(1, 3);//删除复数向量区间[1，3）
	for (i = 0; i < 9; i++) {
		v1[i].display();
	}//输出删除区间后的复数向量

	cout << endl << "删除单个后的复数向量：" << endl;
	v1.remove(0);//删除复数向量v1[0]
	for (i = 0; i < 8; i++) {
		v1[i].display();
	}//输出删除单个后的复数向量

	int j = v1.deduplicate();
	cout << endl << "删除重复元素：" << j << "个" << endl << "唯一化后的复数向量:" << endl;
	for (i = 0; i < 8 - j; i++) {
		v1[i].display();
	}//输出删除重复元素后的复数向量
	cout << endl;

	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//开始计时  
	v2.mergeSort(0, 10);//乱序时归并排序
	QueryPerformanceCounter(&nEndTime);//停止计时  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s  
	cout << "乱序时归并排序运行时间：" << time * 1000 << "ms" << endl;

	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//开始计时  
	v3.bubbleSort(0, 10);//乱序时起泡排序
	QueryPerformanceCounter(&nEndTime);//停止计时  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s  
	cout << "乱序时起泡排序运行时间：" << time * 1000 << "ms" << endl;

	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//开始计时  
	v2.mergeSort(0, 10);//顺序时归并排序
	QueryPerformanceCounter(&nEndTime);//停止计时  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s  
	cout << "顺序时归并排序运行时间：" << time * 1000 << "ms" << endl;

	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//开始计时  
	v3.bubbleSort(0, 10); //顺序时起泡排序
	QueryPerformanceCounter(&nEndTime);//停止计时  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s  
	cout << "顺序时起泡排序运行时间：" << time * 1000 << "ms" << endl;


	for (i = 0; i < 5; i++) {
		swap(v2[i], v2[9 - i]);
		swap(v3[i], v3[9 - i]);
	}//将复数向量逆序

	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//开始计时  
	v2.mergeSort(0, 10);//逆序时归并排序
	QueryPerformanceCounter(&nEndTime);//停止计时  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s  
	cout << "逆序时归并排序运行时间：" << time * 1000 << "ms" << endl;

	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//开始计时  
	v3.bubbleSort(0, 10);//逆序时起泡排序
	QueryPerformanceCounter(&nEndTime);//停止计时  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s  
	cout << "逆序时起泡排序运行时间：" << time * 1000 << "ms" << endl;

	//查找模在区间[m1,m2)内的复数
	int m1, m2;
	cout << endl<< "请输入m1，m2：";
	cin >> m1 >> m2;
	Vector<complex>v4(a,10);//子向量
	int sum = 0;
	double num;
	for ( i = 0; i < 10; i++) {
		num = v3[i].getmodel();
		if (num >= m1 && num < m2) {//若在[m1,m2)区间，则给子向量按序赋值
			v4[sum].givereal(v3[i].getreal());
			v4[sum].giveimag(v3[i].getimag());
			sum++;
		}
		else if (num >= m2) {//若已大于m2，则退出赋值
			break;
		}
	}
	cout << "查找后的向量:" << endl;
		for (i = 0; i < sum; i++) {
		v4[i].display();
	}//按序输出子向量
		return 0;
}
