#include<iostream>
#include<string.h>
#include<windows.h>
#include<time.h>
using namespace std;


#define true 1
#define false 0
#pragma once

typedef int Rank;


bool bubble(int array1[], int n) {
    int i = 0;
    bool sorted = true;//整体有序标志
    while (++i < n)//自左向右，逐一检查各对相邻元素
        if (array1[i - 1] > array1[i]) {//若逆序，则意味着尚未整体有序，并需要通过交换使局部有序
            sorted = false;
            swap(array1[i - 1], array1[i]);
        }
    return sorted;//返回有序标志
} //扫描交换

void bubbleSort(int array[], int n) {
    while (!bubble(array, n--));
} //起泡排序算法



void merge(int array[],int lo, int mi, int hi) { // lo < mi < hi
    int* A = array + lo; //合并后的有序向量A[0, hi - lo) = _elem[lo, hi)
    int lb = mi - lo; int* B = new int[lb]; //前子向量B[0, lb) <-- _elem[lo, mi)
    for (Rank i = 0; i < lb; B[i] = A[i++]); //复制前子向量
    int lc = hi - mi; int* C = array + mi; //后子向量C[0, lc) = _elem[mi, hi)
    for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);) {//B[j]和C[k]中的小者续至A末尾
        if ((j < lb) && (!(k < lc) || (B[j] <= C[k]))) {
            A[i++] = B[j++];
        }
        if ((k < lc) && (!(j < lb) || (C[k] < B[j]))) {
            A[i++] = C[k++];
        }
    }
    delete[] B; //释放临时空间
} //归并算法

void mergeSort(int array[],int lo,int hi) {
    if (hi-lo < 2) return; //单元素区间自然有序，否则...
    int mi = (lo + hi) / 2; //以中点为界
    mergeSort(array,lo, mi); mergeSort(array,mi, hi); //前缀、后缀分别排序
    merge(array,lo, mi, hi); //归并
} //归并排序算法


void insertionSort(int array[], int n) {//插入排序
	int i, key, j;
	for (i = 1; i < n; i++) {
		key = array[i];
		j = i - 1;

		while (j >= 0 && array[j] > key) {
			array[j + 1] = array[j];
			j = j - 1;
		}
		array[j + 1] = key;
	}
}

void selectionSort(int arr[], int n) {//选择排序
	int i, j, min_idx;
	for (i = 0; i < n - 1; i++) {
		min_idx = i;
		for (j = i + 1; j < n; j++)
			if (arr[j] < arr[min_idx])
				min_idx = j;
		swap(arr[min_idx], arr[i]);
	}
}

void quickSort(int array[], int lo, int hi) {
	if (lo < hi) {
		int pivot = array[hi];
		int i = lo - 1;
		for (int j = lo; j <= hi - 1; j++) {
			if (array[j] < pivot) {
				i++;
				swap(array[i], array[j]);
			}
		}
		swap(array[i + 1], array[hi]);
		int pi = i + 1;
		quickSort(array, lo, pi - 1);
		quickSort(array, pi + 1, hi);
	}
}

int main()
{
    srand(time(0));//设置随机种子与时间相关，确保能生成完全随机的复数
    double time = 0;
    double counts = 0;
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;
    LARGE_INTEGER nEndTime;
    int nn1[10],nn2[10],nn3[10],nn4[10],nn5[10];//随机生成一组数
    for (int i = 0; i < 10; i++) {
        nn1[i] = rand() % 100;
        nn2[i] = nn1[i];
		nn3[i] = nn2[i];
		nn4[i] = nn2[i];
		nn5[i] = nn2[i];
    }

	cout << "数组:";
	for (int i = 0; i < 10; i++) {
		cout << nn1[i] << " ";
	}


	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//开始计时  
	mergeSort(nn1,0, 10);//乱序时归并排序
	QueryPerformanceCounter(&nEndTime);//停止计时  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s  
	cout <<endl<< "乱序时归并排序运行时间：" << time * 1000 << "ms" << endl;

	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//开始计时  
	bubbleSort(nn2, 10);//乱序时起泡排序
	QueryPerformanceCounter(&nEndTime);//停止计时  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s  
	cout << "乱序时起泡排序运行时间：" << time * 1000 << "ms" << endl;

	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//开始计时  
	insertionSort(nn3, 10);//乱序时插入排序
	QueryPerformanceCounter(&nEndTime);//停止计时  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s  
	cout <<"乱序时插入排序运行时间：" << time * 1000 << "ms" << endl;

	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//开始计时  
	selectionSort(nn4, 10);//乱序时选择排序
	QueryPerformanceCounter(&nEndTime);//停止计时  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s  
	cout << "乱序时选择排序运行时间：" << time * 1000 << "ms" << endl;

	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//开始计时  
	quickSort(nn5,0,10);//乱序时快速排序
	QueryPerformanceCounter(&nEndTime);//停止计时  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s  
	cout << "乱序时快速排序运行时间：" << time * 1000 << "ms" << endl << endl;

	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//开始计时  
	mergeSort(nn1,0, 10);//顺序时归并排序
	QueryPerformanceCounter(&nEndTime);//停止计时  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s  
	cout << "顺序时归并排序运行时间：" << time * 1000 << "ms" << endl;

	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//开始计时  
	bubbleSort(nn2, 10); //顺序时起泡排序
	QueryPerformanceCounter(&nEndTime);//停止计时  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s  
	cout << "顺序时起泡排序运行时间：" << time * 1000 << "ms" << endl;

	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//开始计时  
	insertionSort(nn3, 10); //顺序时插入排序
	QueryPerformanceCounter(&nEndTime);//停止计时  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s  
	cout << "顺序时插入排序运行时间：" << time * 1000 << "ms" << endl;

	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//开始计时  
	selectionSort(nn4, 10);//顺序时选择排序
	QueryPerformanceCounter(&nEndTime);//停止计时  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s  
	cout << "顺序时选择排序运行时间：" << time * 1000 << "ms" << endl;

	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//开始计时  
	quickSort(nn5,0,10);//顺序时快速排序
	QueryPerformanceCounter(&nEndTime);//停止计时  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s  
	cout << "顺序时快速排序运行时间：" << time * 1000 << "ms" << endl << endl;

	for (int i = 0; i < 5; i++) {
		swap(nn1[i], nn1[9 - i]);
		swap(nn2[i], nn2[9 - i]);
		swap(nn3[i], nn3[9 - i]);
		swap(nn4[i], nn4[9 - i]);
		swap(nn5[i], nn5[9 - i]);
	}//将复数向量逆序

	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//开始计时  
	mergeSort(nn1,0, 10);//逆序时归并排序
	QueryPerformanceCounter(&nEndTime);//停止计时  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s  
	cout << "逆序时归并排序运行时间：" << time * 1000 << "ms" << endl;

	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//开始计时  
	bubbleSort(nn2, 10);//逆序时起泡排序
	QueryPerformanceCounter(&nEndTime);//停止计时  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s  
	cout << "逆序时起泡排序运行时间：" << time * 1000 << "ms" << endl;

	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//开始计时  
	insertionSort(nn3, 10);//逆序时起泡排序
	QueryPerformanceCounter(&nEndTime);//停止计时  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s  
	cout << "逆序时插入排序运行时间：" << time * 1000 << "ms" << endl;

	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//开始计时  
	selectionSort(nn4, 10);//逆序时选择排序
	QueryPerformanceCounter(&nEndTime);//停止计时  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s  
	cout << "逆序时选择排序运行时间：" << time * 1000 << "ms" << endl;

	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//开始计时  
	quickSort(nn5,0, 10);//逆序时快速排序
	QueryPerformanceCounter(&nEndTime);//停止计时  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//计算程序执行时间单位为s  
	cout << "逆序时快速排序运行时间：" << time * 1000 << "ms" << endl;
}