#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
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
    for(int i=0;i<arr.size()-1;i++){
        for(int j=0;j<arr.size()-1-i;j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
            }
        }
    }
}

//quickSort(vector<T>&arr,int l,int r)
template<typename T>
void quickSort(vector<T>&arr,int l,int r) {
    int i=l,j=r;
    int temp=arr[l];
    while(i<j){
        while(i<j&&arr[j]>=temp)
            j--;
        if(i<j)
            arr[i++]=arr[j];
        while(i<j&&arr[i]<temp)
            i++;
        if(i<j)
            arr[j--]=arr[i];
    }
    arr[i]=temp;
    quickSort(arr,l,i-1);
    quickSort(arr,i+1,r);
}

//insertSort
template<typename T>
void insertSort(vector<T>&arr){
    for(int i=1;i<arr.size();i++){
        int temp=arr[i];
        int j;
        for(j=i-1;j>=0&&temp<arr[j];j--){
            arr[j+1]=arr[j];
        }
        arr[j+1]=temp;
    }
}

//selectSort
template<typename T>
void selectSort(vector<T>&arr){
    int min_index;
    for(int i=0;i<arr.size();i++){
        min_index = i;
        for(int j=i+1;j<arr.size();j++){
            if(arr[j]<arr[min_index])
                min_index =j;
        }
        swap(arr[i],arr[min_index]);
    }
}

template<typename T>
void print(vector<T>arr){
    for(int i=0;i<arr.size();i++){
        cout<<arr[i]<<" "<<endl;
    }
    return;
}

int main(void){
    vector<int> rand_vec=random(10,3,30);
    print(rand_vec);
    selectSort(rand_vec);
    print(rand_vec);
    return 0;
}