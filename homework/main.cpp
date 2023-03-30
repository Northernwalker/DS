#include"../../Complex2.h"
#include"../../../vector/vector.h"
#include<windows.h>
#include<time.h>
using namespace std;


int main()
{
	srand(time(0));//�������������ʱ����أ�ȷ����������ȫ����ĸ���
	double time = 0;
	double counts = 0;
	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	complex* a = new complex[10];//�������һ�鸴��
	Vector<complex>v1(a, 10);//��������ɵĸ������Ƶ�������
	Vector<complex>v2(a, 10);//��������ɵĸ������Ƶ���һ�������б���
	Vector<complex>v3(a, 10);//�ٸ���һ������qwq
	int i;
	//double real,imag;
	for (i = 0; i < 10; i++) {
		v1[i].display();
	}//�����������
	cout<< endl;
	v1.unsort(0, 10);//����
	cout << "���Һ�" << endl;
	for (i = 0; i < 10; i++) {
		v1[i].display();
	}//������Һ�ĸ�������

	cout << endl << "����ʵ���鲿��ͬ�ĸ���:" << endl;
	v1.findcomplex(0, 10);//����ʵ�����鲿��ͬ�ĸ��������

	cout << endl << "׼������ĸ�����" << endl;
	complex insert;//����һ��׼������ĸ���
	insert.display();//չʾ׼������ĸ���
	cout << endl << "�����ĸ���������" << endl;
	v1.insert(2, insert);//��������ĳ�����˴�Ϊ2������һ������
	for (i = 0; i < 11; i++) {
		v1[i].display();
	}//��������ĸ�������

	cout << endl << "����ɾ����ĸ���������" << endl;
	v1.remove(1, 3);//ɾ��������������[1��3��
	for (i = 0; i < 9; i++) {
		v1[i].display();
	}//���ɾ�������ĸ�������

	cout << endl << "ɾ��������ĸ���������" << endl;
	v1.remove(0);//ɾ����������v1[0]
	for (i = 0; i < 8; i++) {
		v1[i].display();
	}//���ɾ��������ĸ�������

	int j = v1.deduplicate();
	cout << endl << "ɾ���ظ�Ԫ�أ�" << j << "��" << endl << "Ψһ����ĸ�������:" << endl;
	for (i = 0; i < 8 - j; i++) {
		v1[i].display();
	}//���ɾ���ظ�Ԫ�غ�ĸ�������
	cout << endl;

	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ  
	v2.mergeSort(0, 10);//����ʱ�鲢����
	QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs  
	cout << "����ʱ�鲢��������ʱ�䣺" << time * 1000 << "ms" << endl;

	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ  
	v3.bubbleSort(0, 10);//����ʱ��������
	QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs  
	cout << "����ʱ������������ʱ�䣺" << time * 1000 << "ms" << endl;

	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ  
	v2.mergeSort(0, 10);//˳��ʱ�鲢����
	QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs  
	cout << "˳��ʱ�鲢��������ʱ�䣺" << time * 1000 << "ms" << endl;

	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ  
	v3.bubbleSort(0, 10); //˳��ʱ��������
	QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs  
	cout << "˳��ʱ������������ʱ�䣺" << time * 1000 << "ms" << endl;


	for (i = 0; i < 5; i++) {
		swap(v2[i], v2[9 - i]);
		swap(v3[i], v3[9 - i]);
	}//��������������

	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ  
	v2.mergeSort(0, 10);//����ʱ�鲢����
	QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs  
	cout << "����ʱ�鲢��������ʱ�䣺" << time * 1000 << "ms" << endl;

	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);//��ʼ��ʱ  
	v3.bubbleSort(0, 10);//����ʱ��������
	QueryPerformanceCounter(&nEndTime);//ֹͣ��ʱ  
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;//�������ִ��ʱ�䵥λΪs  
	cout << "����ʱ������������ʱ�䣺" << time * 1000 << "ms" << endl;

	//����ģ������[m1,m2)�ڵĸ���
	int m1, m2;
	cout << endl<< "������m1��m2��";
	cin >> m1 >> m2;
	Vector<complex>v4(a,10);//������
	int sum = 0;
	double num;
	for ( i = 0; i < 10; i++) {
		num = v3[i].getmodel();
		if (num >= m1 && num < m2) {//����[m1,m2)���䣬�������������ֵ
			v4[sum].givereal(v3[i].getreal());
			v4[sum].givereal(v3[i].getreal());
			sum++;
		}
		else if (num >= m2) {//���Ѵ���m2�����˳���ֵ
			break;
		}
	}
	cout << "���Һ������:" << endl;
		for (i = 0; i < sum; i++) {
		v4[i].display();
	}//�������������
		return 0;
}