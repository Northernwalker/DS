#include<iostream>
using namespace std;


#define true 1
#define false 0
#pragma once

typedef int Rank;

#define DEFAULT_CAPACITY  3 //默认的初始容量（实际应用中可设置为更大）

template <typename T> class Vector { //向量模板类
protected:
    Rank _size; Rank _capacity;  T* _elem; //规模、容量、数据区
    void copyFrom(T const* A, Rank lo, Rank hi) { //以数组区间A[lo, hi)为蓝本复制向量
        _elem = new T[_capacity =2 * (hi - lo)];_size = 0;//分配空间
        while (lo < hi)//A[lo, hi)内的元素逐一
            _elem[_size++] = A[lo++];//复制至_elem[0, hi - lo)
    } //复制数组区间A[lo, hi)
    void expand() { //向量空间不足时扩容
        if (_size < _capacity) return; //尚未满员时，不必扩容
        if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY; //不低于最小容量
        T* oldElem = _elem;  _elem = new T[_capacity <<= 1]; //容量加倍
        for (Rank i = 0; i < _size; i++)
            _elem[i] = oldElem[i]; //复制原向量内容（T为基本类型，或已重载赋值操作符'='）
        delete[] oldElem; //释放原空间
    }
    void shrink() { //装填因子过小时压缩向量所占空间
        if (_capacity < DEFAULT_CAPACITY << 1) return;//不致收缩到DEFAULT_CAPACITY以下
        if (_size << 2 > _capacity) return; //以25%为界
        T* oldElem = _elem; _elem = new T[_capacity >>= 1]; //容量减半
        for (Rank i = 0; i < _size; i++) _elem[i] = oldElem[i]; //复制原向量内容
        delete[] oldElem; //释放原空间
    }
    
    Rank maxItem(Rank lo, Rank hi); //选取最大元素
    void selectionSort(Rank lo, Rank hi); //选择排序算法
    
    void heapSort(Rank lo, Rank hi); //堆排序（稍后结合完全堆讲解）
    Rank partition(Rank lo, Rank hi); //轴点构造算法
    void quickSort(Rank lo, Rank hi); //快速排序算法
public:
    // 构造函数
    Vector(T const* A, Rank n) { 
        copyFrom(A, 0, n);
    } //数组整体复制

    Vector(Rank c = DEFAULT_CAPACITY, Rank s = 0, T v = 0) //容量为c、规模为s、所有元素初始为v
    {
        _elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v);
    } //s<=c

    Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); } //区间
    Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); } //向量整体复制
    Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } //区间

    // 析构函数
    ~Vector() { delete[] _elem; } //释放内部空间
    // 只读访问接口
    Rank size() const { return _size; } //规模
    bool empty() const { return !_size; } //判空
    void findcomplex(Rank lo, Rank hi) {//查找实部和虚部相同的复数
        int diag = 0;
        T* V = _elem + lo;//将子向量_elem[lo,hi]视作另一向量V[0,hi-lo]
        for (int i = lo; i < hi; i++) {
            if (V[i].getreal() == V[i].getimag()) {
                V[i].display();
                cout << " ";
                diag = 1;//找到实部虚部相同的复数
            }
        }
        if (diag == 0) {
            cout << "未找到实部虚部相同的复数";
        }
    }
    Rank find(T const& e) const { return find(e, 0, _size); } //无序向量整体查找
    Rank find(Rank lo, Rank hi) const //无序向量区间查找
    { //0 <= lo < hi <= _size
        while ((lo < hi) && (_elem[lo].getreal() != _elem[hi].getreal()) && (_elem[lo].getimag() != _elem[hi].getimag())) {
            hi--;
        } //从后向前，顺序查找
        return hi; //若hi < lo，则意味着失败；否则hi即命中元素的秩
    }
    Rank search(T const& e) const //有序向量整体查找
    {
        return (0 >= _size) ? -1 : search(e, 0, _size);
    }
    Rank search(T const& e, Rank lo, Rank hi) const; //有序向量区间查找
    // 可写访问接口
    T& operator[](Rank r) const { return _elem[r]; }//重载下标操作符，可以类似于数组形式引用各元素
    Vector<T>& operator=(const Vector<T>& V)//重载赋值操作符，以便直接克隆向量

    {
        delete[] _elem;	//删除原有空间
        copyFrom(V._elem, 0, V._size);
        return *this; //返回值为引用便于链式赋值
    }

    T remove(Rank r) { //删除向量中秩为r的元素，0 <= r < size
        T e = _elem[r]; //备份被删除元素
        remove(r, r + 1); //调用区间删除算法，等效于对区间[r, r + 1)的删除
        return e; //返回被删除元素
    }
    void remove(Rank lo, Rank hi) { //0 <= lo <= hi <= n
        if (lo == hi) {}; //出于效率考虑，单独处理退化情况
        while (hi < _size) _elem[lo++] = _elem[hi++]; //后缀[hi, _size)顺次前移hi-lo位
        _size = lo; //更新规模，lo=_size之后的内容无需清零；如必要，则缩容
        //若有必要，则缩容
        //return hi - lo; //返回被删除元素的数目
    }
    void insert(Rank r, T const& e) { //0 <= r <= size
        expand(); //如必要，先扩容
        for (Rank i = _size; r < i; i--) //自后向前，后继元素
            _elem[i] = _elem[i - 1]; //顺次后移一个单元
        _elem[r] = e; _size++; //置入新元素并更新容量
    } //插入元素
    Rank insert(T const& e) { return insert(_size, e); } //默认作为末元素插入
    void sort(Rank lo, Rank hi); //对[lo, hi)排序
    void sort() { sort(0, _size); } //整体排序
    void unsort(Rank lo, Rank hi)//对[lo, hi)置乱
    {
        T* V = _elem + lo;//将子向量_elem[lo,hi]视作另一向量V[0,hi-lo]
        for (Rank i = hi - lo; i > 0; i--)//自后向前
            swap(V[i - 1], V[rand() % i]);//将V[i-1]与V[0,i)中某一元素随机交换
    }
    void unsort() { unsort(0, _size); } //整体置乱
    int deduplicate() { //删除无序向量中重复元素（高效版）
        int oldSize = _size; //记录原规 //否则删除[i]，O(_size-i)
        Rank i = 0;
        while (i < _size - 1) {
            Rank j;
            j = i + 1;
            while (j < _size) {
                if ((_elem[i].getreal() == _elem[j].getreal()) && (_elem[i].getimag() == _elem[j].getimag())){
                    remove(j, j + 1);
                }
                else {
                    j++;
                }
            }
            i++;
        }
        return oldSize - _size; //被删除元素总数
    }
    Rank uniquify(); //有序去重
    bool bubble(Rank lo, Rank hi) {
        bool sorted = true;//整体有序标志
        while (++lo < hi)//自左向右，逐一检查各对相邻元素
            if (_elem[lo - 1] > _elem[lo]) {//若逆序，则意味着尚未整体有序，并需要通过交换使局部有序
                sorted = false;
                swap(_elem[lo - 1], _elem[lo]);
            }
            else if (_elem[lo - 1] == _elem[lo]) {
                if (_elem[lo - 1].getreal() > _elem[lo].getreal()) {
                    sorted = false;
                    swap(_elem[lo - 1], _elem[lo]);
                }
            }
        return sorted;//返回有序标志
    } //扫描交换
    void bubbleSort(Rank lo, Rank hi) {
        while (!bubble(lo, hi--));
    } //起泡排序算法
    void merge(Rank lo, Rank mi, Rank hi) { // lo < mi < hi
        T* A = _elem + lo; //合并后的有序向量A[0, hi - lo) = _elem[lo, hi)
        int lb = mi - lo; T* B = new T[lb]; //前子向量B[0, lb) <-- _elem[lo, mi)
        for (Rank i = 0; i < lb; B[i]=A[i++]); //复制前子向量
        int lc = hi - mi; T* C = _elem + mi; //后子向量C[0, lc) = _elem[mi, hi)
        for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);) {//B[j]和C[k]中的小者续至A末尾
            if ((j < lb) && (!(k < lc) || (B[j]<= C[k]))) {
                A[i++]=B[j++];
            }
            if ((k < lc) && (!(j < lb) || (C[k] < B[j]))) { 
                A[i++]=C[k++];
            }
        }
        delete[] B; //释放临时空间
    } //归并算法
    void mergeSort(Rank lo, Rank hi) { // 0 <= lo < hi <= size
        if (hi - lo < 2) return; //单元素区间自然有序，否则...
        int mi = (lo + hi) / 2; //以中点为界
        mergeSort(lo, mi); mergeSort(mi, hi); //前缀、后缀分别排序
        merge(lo, mi, hi); //归并
    } //归并排序算法
 // 遍历
    void traverse(void (*) (T&)); //遍历（使用函数指针，只读或局部性修改）
    template <typename VST> void traverse(VST&); //遍历（使用函数对象，可全局性修改）
}; //Vector
