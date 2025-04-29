#include<iostream>
#include<vector>
#include<omp.h>
#include<ctime>
using namespace std;

void Bubble(vector<int>&arr){
    int n=arr.size();
    bool swapped=true;
    while(swapped){
        swapped=false;
        #pragma  omp parallel for
        for(int i=0;i<n-1;i++){
            if(arr[i]>arr[i+1]){
                swap(arr[i],arr[i+1]);
                swapped=true;
            }
        }
    }
}
void merge(vector<int>&arr,int l,int m,int r){
    int left=l;
    int right=m+1;
    vector<int>temp;
    while(left<=m && right<=r){
        if(arr[left]<arr[right]){
            temp.push_back(arr[left]);
            left++;
        }
        else{
            temp.push_back(arr[right]);
            right++;
        }
    }
    while(left<=m){
        temp.push_back(arr[left]);
        left++;
    }
    while(right<=r){
        temp.push_back(arr[right]);
        right++;
    }
    for(int i=l;i<=r;i++){
        arr[i]=temp[i-l];
    }
}
void mergeSort(vector<int>&arr,int l,int r){
    if(l<r){
        int m= l+(r-l)/2;
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                mergeSort(arr,l,m);
            }
            #pragma omp section
            {
                mergeSort(arr,m+1,r);
            }
        }
        merge(arr,l,m,r);
    }
}
int main(){
    int n;
    cout<<"Enter the umber of elemenets\n";
    cin>>n;
    vector<int>arr(n);
    cout<<"Enter the elements\n";
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    vector<int>barr=arr;
    vector<int>marr=arr;
    clock_t bublestart=clock();
    Bubble(barr);
    clock_t bubbleend=clock();
    double btime=double(bubbleend-bublestart)/CLOCKS_PER_SEC;
    for(int num:barr){
        cout<<num<<" ";
    }
    cout<<endl;
    clock_t mergestart=clock();
    mergeSort(marr,0,n-1);
    clock_t mergeend=clock();
    double mtime=double(mergeend-mergestart)/CLOCKS_PER_SEC;
    for(int num:marr){
        cout<<num<<" ";
    }
    cout<<endl;
    
    cout.precision(8);
    cout<<"time taken by bubble sort: "<<fixed<<btime<<" seconds\n";
    cout<<"time taken by merge sort: "<<fixed<<mtime<<" seconds\n";
    return 0;
}
