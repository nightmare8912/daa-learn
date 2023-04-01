#include<iostream>
#include<time.h>
using namespace std;
bool isArrayNegative(int arr[],int n){
    for(int i=0;i<n;i++){
        if(arr[i]>0)
            return false;
    }
    return true;
}
int find_max_cont(int arr[],int n){
    int maxSum=0;
    if(isArrayNegative(arr,n)){
        maxSum=0;
        for(int i=0;i<n;i++)
            maxSum+=arr[i];
        return maxSum;    
    }
    for(int i=2;i<=n;i++){
        for(int j=0;j<=n-i;j++){
            int sum=0;
            for(int k=j,counter=0;counter<i;k++,counter++){
                sum+=arr[k];
            }
            if(sum>maxSum)
                maxSum=sum;
        }
    }
    return maxSum;
}
int main(){
    int n;
    clock_t start,end;
    double totalTime;
    cout<<"Enter the number of elements: ";
    cin>>n;
    int arr[n];
    cout<<"Given array: "<<endl;
    for(int i=0;i<n;i++){
        arr[i]=rand()%19+(-9);
        cout<<arr[i]<<" ";
    }
    start=clock();
    int ans=find_max_cont(arr,n);
    end=clock();
    cout<<"\nMaximum sum: "<<ans;
    totalTime=(double)(end-start)/CLOCKS_PER_SEC;
    cout<<"\nTime elapsed: "<<totalTime<<" seconds";
    return 0;       
}