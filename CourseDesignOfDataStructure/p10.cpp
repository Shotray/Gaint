#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<windows.h>
using namespace std;



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



    int count=0;
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
    //clock_t end=clock();
    //double totaltime=(double)(end-start)/CLOCKS_PER_SEC;
    //DWORD end=GetTickCount();

	QueryPerformanceCounter(&time_over);	//计时结束
	double run_time=1000000*(time_over.QuadPart-time_start.QuadPart)/dqFreq;
	//乘以1000000把单位由秒化为微秒，精度为1000 000/（cpu主频）微秒
	printf("\nBubbleSort run_time：%fus\n",run_time);

    cout<<"Exchange "<<count<<" times in bubbleSort."<<endl;
    //cout<<"BubbleSort uses "<<end-start<<" ms"<<endl; 
}



int qs_count=0;
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
	
    int count=0;

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
	printf("\ninsertSort run_time：%fus\n",run_time);

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

    int count=0;

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
	printf("\nselectSort run_time：%fus\n",run_time);

    cout<<"Exchange "<<count<<" times in selectSort."<<endl;
}

template<typename T>
void print(vector<T>arr){
    for(int i=0;i<arr.size();i++){
        cout<<arr[i]<<" ";
    }
    return;
}

int main(void){
    cout<<"BubbleSort:"<<endl;
    vector<int> rand_vec=random(10,3,30);
    print(rand_vec);
    bubbleSort(rand_vec);
    print(rand_vec);
    cout<<endl<<endl;

    cout<<"InsertSort:"<<endl;
    rand_vec=random(10,3,30);
    print(rand_vec);
    insertSort(rand_vec);
    print(rand_vec);
    cout<<endl<<endl;

    cout<<"SelectSort:"<<endl;
    rand_vec=random(10,3,30);;
    print(rand_vec);
    selectSort(rand_vec);
    print(rand_vec);
    cout<<endl<<endl;



    cout<<"QuickSort:"<<endl;
    rand_vec=random(10,3,30);
    print(rand_vec);

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
	printf("\nquickSort run_time：%fus\n",run_time);

    cout<<"Exchange "<<qs_count<<" times in quickSort."<<endl;

    print(rand_vec);
    cout<<endl<<endl;
    return 0;
}