#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<windows.h>
using namespace std;


int kTotal;
const int kLeft=0;
const int kRight=100000;

//construct random vector
vector<int> random(int n,int l,int r){
    vector<int> random_vector;
    srand(time(0));
    for(int i=0;i<n;i++){
        random_vector.push_back((rand()%(r-l+1)+l));
    }
    return random_vector;
}

//bubbleSort
template<typename T>
void bubbleSort(vector<T>&arr){
    _LARGE_INTEGER time_start;	//开始时间
	_LARGE_INTEGER time_over;	//结束时间
	double dqFreq;		//计时器频率
	LARGE_INTEGER f;	//计时器频率
	QueryPerformanceFrequency(&f);
	dqFreq=(double)f.QuadPart;
	QueryPerformanceCounter(&time_start);	//计时开始



    long long count=0;
    //DWORD start=GetTickCount();
    //clock_t start=clock();
    for(int i=0;i<arr.size()-1;i++){
        for(int j=0;j<arr.size()-1-i;j++){
            if(arr[j]>arr[j+1]){
                count++;
                swap(arr[j],arr[j+1]);
            }
        }
    }

	QueryPerformanceCounter(&time_over);	//计时结束
	double run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
	//乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
	printf("\nBubbleSort run_time:%fus\n",run_time);

    cout<<"Exchange "<<count<<" times in bubbleSort."<<endl;
}



long long qs_count=0;
template<typename T>
int partition(vector<T>&arr, int left, int right){
    int pivot = arr[right];                 //choose the rightest element as the pivot
    int curr = left;
    for(int i=left; i<right; i++){
        if(pivot > arr[i]){                 //always put smaller element in the left
            swap(arr[curr], arr[i]);
            qs_count++;
            curr++;
        }
    }
    swap(arr[curr], arr[right]);           //at last, put pivot element in the position it should be
    qs_count++;
    return curr;
}

//quickSort(vector<T>&arr,int l,int r)
template<typename T>
void quickSort(vector<T>&arr, int left, int right){
    if(left < right){
        int p = partition(arr, left, right);
        quickSort(arr, left, p-1);
        quickSort(arr, p+1, right);
    }
}

//insertSort
template<typename T>
void insertSort(vector<T>&arr){
    _LARGE_INTEGER time_start;	//开始时间
	_LARGE_INTEGER time_over;	//结束时间
	double dqFreq;		//计时器频率
	LARGE_INTEGER f;	//计时器频率
	QueryPerformanceFrequency(&f);
	dqFreq=(double)f.QuadPart;
	QueryPerformanceCounter(&time_start);	//计时开始
	
    long long count=0;

    for(int i=1;i<arr.size();i++){
        int temp=arr[i];
        int j;
        for(j=i-1;j>=0&&temp<arr[j];j--){
            arr[j+1]=arr[j];
            count++;
        }
        arr[j+1]=temp;count++;
    }

    QueryPerformanceCounter(&time_over);	//计时结束
	double run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
	//乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
	printf("\ninsertSort run_time:%fus\n",run_time);

    cout<<"Exchange "<<count<<" times in insertSort."<<endl;
}

//selectSort
template<typename T>
void selectSort(vector<T>&arr){
    _LARGE_INTEGER time_start;	//开始时间
	_LARGE_INTEGER time_over;	//结束时间
	double dqFreq;		//计时器频率
	LARGE_INTEGER f;	//计时器频率
	QueryPerformanceFrequency(&f);
	dqFreq=(double)f.QuadPart;
	QueryPerformanceCounter(&time_start);	//计时开始

    long long count=0;

    int min_index;
    for(int i=0;i<arr.size();i++){
        min_index = i;
        for(int j=i+1;j<arr.size();j++){
            if(arr[j]<arr[min_index])
                min_index =j;
        }
        swap(arr[i],arr[min_index]);
        count++;
    }

    QueryPerformanceCounter(&time_over);	//计时结束
	double run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
	//乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
	printf("\nselectSort run_time:%fus\n",run_time);

    cout<<"Exchange "<<count<<" times in selectSort."<<endl;
}

//shellSort
template<typename T>
void shellSort(vector<T>&arr) {
    _LARGE_INTEGER time_start;	//开始时间
	_LARGE_INTEGER time_over;	//结束时间
	double dqFreq;		//计时器频率
	LARGE_INTEGER f;	//计时器频率
	QueryPerformanceFrequency(&f);
	dqFreq=(double)f.QuadPart;
	QueryPerformanceCounter(&time_start);	//计时开始

    long long count=0;

    int h = 1;
    while (h < arr.size() / 3) {
        h = 3 * h + 1;
    }
    while (h >= 1) {
        for (int i = h; i < arr.size(); i++) {
            for (int j = i; j >= h && arr[j] < arr[j - h]; j -= h) {
                count++;
                std::swap(arr[j], arr[j - h]);
            }
        }
        h = h / 3;
    }

    QueryPerformanceCounter(&time_over);	//计时结束
	double run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
	//乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
	printf("\nBubbleSort run_time:%fus\n",run_time);

    cout<<"Exchange "<<count<<" times in shellSort."<<endl;

}

long long mergeCount=0;
//mergeSort
template<typename T>
void merge_sort_recursive(vector<T>&arr, T reg[], int start, int end) {
    if (start >= end)
        return;
    int len = end - start, mid = (len >> 1) + start;
    int start1 = start, end1 = mid;
    int start2 = mid + 1, end2 = end;
    merge_sort_recursive(arr, reg, start1, end1);
    merge_sort_recursive(arr, reg, start2, end2);
    int k = start;
    while (start1 <= end1 && start2 <= end2){
        mergeCount++;
        reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
    }
    while (start1 <= end1){
        mergeCount++;
        reg[k++] = arr[start1++];
    }
    while (start2 <= end2){
        mergeCount++;
        reg[k++] = arr[start2++];
    }
    for (k = start; k <= end; k++){
        mergeCount++;
        arr[k] = reg[k];
    }
}

template<typename T>
void mergeSort(vector<T>&arr) {
    _LARGE_INTEGER time_start;	//开始时间
	_LARGE_INTEGER time_over;	//结束时间
	double dqFreq;		//计时器频率
	LARGE_INTEGER f;	//计时器频率
	QueryPerformanceFrequency(&f);
	dqFreq=(double)f.QuadPart;
	QueryPerformanceCounter(&time_start);	//计时开始

    T reg[kTotal];
    merge_sort_recursive(arr, reg, 0, arr.size()-1);

    QueryPerformanceCounter(&time_over);	//计时结束
	double run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
	//乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
	printf("\nmergeSort run_time:%fus\n",run_time);

    cout<<"Exchange "<<mergeCount<<" times in mergeSort."<<endl;

}

//bucketSort
template<typename T>
void bucketSort(vector<T>&arr){
    _LARGE_INTEGER time_start;	//开始时间
	_LARGE_INTEGER time_over;	//结束时间
	double dqFreq;		//计时器频率
	LARGE_INTEGER f;	//计时器频率
	QueryPerformanceFrequency(&f);
	dqFreq=(double)f.QuadPart;
	QueryPerformanceCounter(&time_start);	//计时开始

    long long count=0;
    int temp[kRight+1]={0};
    for(int i=0; i<arr.size(); i++){
        count++;
        temp[arr[i]]++;
    }
    int k=0;
    for(int i=0;i<=kRight; i++){
        while(temp[i]){
            count++;
            arr[k]=i;
            temp[i]--;
            k++;
        }
        if(k==arr.size()) break;
    }

    QueryPerformanceCounter(&time_over);	//计时结束
	double run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
	//乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
	printf("\nbucketSort run_time:%fus\n",run_time);

    cout<<"Exchange "<<count<<" times in bucketSort."<<endl;

    return;
}


long long heapCount=0;
//heapSort
template<typename T>
void max_heapify(vector<T>&arr, int start, int end) {
    //建立父节点指标和子节点指标
    int dad = start;
    int son = dad * 2 + 1;
    while (son <= end) { //若子节点指标在范围内才做比较
        if (son + 1 <= end && arr[son] < arr[son + 1]) //先比较两个子节点大小，选择最大的
            son++;
        if (arr[dad] > arr[son]) //如果父节点大于子节点代表调整完毕，直接跳出函数
            return;
        else { //否则交换父子内容再继续子节点和孙节点比较
            heapCount++;
            T temp=arr[dad];
            arr[dad]=arr[son];
            arr[son]=temp;
            dad = son;
            son = dad * 2 + 1;
        }
    }
}

template<typename T>
void heapSort(vector<T>&arr) {
    _LARGE_INTEGER time_start;	//开始时间
	_LARGE_INTEGER time_over;	//结束时间
	double dqFreq;		//计时器频率
	LARGE_INTEGER f;	//计时器频率
	QueryPerformanceFrequency(&f);
	dqFreq=(double)f.QuadPart;
	QueryPerformanceCounter(&time_start);	//计时开始

    int i;
    //初始化，i从最后一个父节点开始调整
    for (i = arr.size() / 2 - 1; i >= 0; i--)
        max_heapify(arr, i, arr.size() - 1);
    //先将第一个元素和已排好元素前一位做交换，再从新调整，直到排序完毕
    for (i = arr.size() - 1; i > 0; i--) {
        heapCount++;
        T temp=arr[0];
        arr[0]=arr[i];
        arr[i]=temp;
        max_heapify(arr, 0, i - 1);
    }

    QueryPerformanceCounter(&time_over);	//计时结束
	double run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
	//乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
	printf("\nheapSort run_time:%fus\n",run_time);

    cout<<"Exchange "<<heapCount<<" times in heapSort."<<endl;
}

template<typename T>
void print(vector<T>arr){
    for(int i=0;i<arr.size();i++){
        cout<<arr[i]<<" ";
    }
    return;
}

void solve(){
    cout<<"Pealse input the size of random numbers:";
    cin>>kTotal;

    cout<<"BubbleSort:";
    vector<int> rand_vec=random(kTotal,kLeft,kRight);
    //print(rand_vec);
    bubbleSort(rand_vec);
    //print(rand_vec);
    cout<<endl;

    cout<<"InsertSort:";
    rand_vec=random(kTotal,kLeft,kRight);
    //print(rand_vec);
    insertSort(rand_vec);
    //print(rand_vec);
    cout<<endl;

    cout<<"SelectSort:";
    rand_vec=random(kTotal,kLeft,kRight);;
    //print(rand_vec);
    selectSort(rand_vec);
    //print(rand_vec);
    cout<<endl;



    cout<<"QuickSort:";
    rand_vec=random(kTotal,kLeft,kRight);
    //print(rand_vec);

    _LARGE_INTEGER time_start;	//开始时间
	_LARGE_INTEGER time_over;	//结束时间
	double dqFreq;		//计时器频率
	LARGE_INTEGER f;	//计时器频率
	QueryPerformanceFrequency(&f);
	dqFreq=(double)f.QuadPart;
	QueryPerformanceCounter(&time_start);	//计时开始

    quickSort(rand_vec,0,(rand_vec.size()-1));

    QueryPerformanceCounter(&time_over);	//计时结束
	double run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
	//乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
	printf("\nquickSort run_time:%fus\n",run_time);

    cout<<"Exchange "<<qs_count<<" times in quickSort."<<endl;

    //print(rand_vec);
    cout<<endl;

    cout<<"shellSort:";
    rand_vec=random(kTotal,kLeft,kRight);;
    //print(rand_vec);
    shellSort(rand_vec);
    //print(rand_vec);
    cout<<endl;

    cout<<"mergeSort:";
    rand_vec=random(kTotal,kLeft,kRight);
    //print(rand_vec);
    mergeSort(rand_vec);
    //print(rand_vec);
    cout<<endl;

    cout<<"bucketSort:";
    rand_vec=random(kTotal,kLeft,kRight);
    //print(rand_vec);
    bucketSort(rand_vec);
    //print(rand_vec);
    cout<<endl;

    cout<<"heapSort:";
    rand_vec=random(kTotal,kLeft,kRight);;
    //print(rand_vec);
    heapSort(rand_vec);
    //print(rand_vec);
    cout<<endl;
}

int main(void){
    solve();
    system("pause");
    return 0;
}