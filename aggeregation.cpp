#include<iostream>
#include<vector>
#include<omp.h>
using namespace std;

int pmin(vector<int>arr){
    int min_val = arr[0];
    int n=arr.size();
    #pragma omp parallel for
    for(int i=0;i<n;i++){
      if(arr[i]<min_val){
          #pragma omp critical
          {
              min_val = arr[i+1];
          }
      }
    }
    return min_val;
}
int pmax(vector<int>arr){
    int n=arr.size();
    int max_val=arr[0];
    #pragma omp parallel for
    for(int i=0;i<n;i++){
        if(arr[i]>max_val){
            max_val=arr[i];
        }
    }
    return max_val;
}
int psum(vector<int>arr){
    int n=arr.size();
    int sum=0;
    #pragma omp parallel for
    for(int i=0;i<n;i++){
        sum+=arr[i];
    }
    return sum;
}
float paverage(vector<int>arr){
    int n=arr.size();
    float add=float(psum(arr));
    float avg=float(add/n);
    return avg;
}
int main(){
    int n;
    cout<<"Enter the number of elements\n";
    cin>>n;
    vector<int>arr(n);
    cout<<"Enter the elements\n";
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    cout<<"Minimum value = "<<pmin(arr)<<"\n";
    cout<<"Maximum value = "<<pmax(arr)<<"\n";
    cout<<"sum = "<<psum(arr)<<"\n";
    cout<<"average = "<<paverage(arr)<<"\n";
    return 0;
}
