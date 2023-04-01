#include<iostream>
#include<fstream>
#include<time.h>
using namespace std;
int count=0;
void merge(int arr[],int start,int mid,int end){
    int i=start, j=mid+1,k=start;
    int b[end];
    while(i<=mid && j<=end){
        if(arr[i]<=arr[j]){
            b[k]=arr[i];
            i++;
        }
        else{
            b[k]=arr[j];
            j++;
        }
        count++;
        k++;
    }

    if(i>mid){
        while(j<=end){
            b[k]=arr[j];
            j++;k++;count++;
        }
    }

    else if(j>end){
        while(i<=mid){
            b[k]=arr[i];
            i++;k++;count++;
        }
    }

    for(k=start;k<=end;k++){
            arr[k]=b[k];
    }
}
void mergeSort(int arr[],int start,int end){
    count++;
    if(start<end){
        int mid=(start+end)/2;
        mergeSort(arr,start,mid);
        mergeSort(arr,mid+1,end);
        merge(arr,start,mid,end);
    }
}
void printArray(int arr[],int size){
    for(int i=0;i<size;i++)
        cout<<arr[i]<<" ";
}
int main(){
    int size;
    ifstream read;
    read.open("random_100000_inputs.txt");
    read>>size;
    cout<<"Number of elements: "<<size<<endl;
    int arr[size];
    for(int i=0;i<size;i++)
        read>>arr[i];
    // cout<<"Elements before sorting: "<<endl;    
    // printArray(arr,size);
    // cout<<endl<<"-------------------------------------------"<<endl;
    clock_t beg,end;
    double totalTime;
    beg=clock();
    mergeSort(arr,0,size-1);
    end=clock();
    totalTime=(double)(end-beg)/CLOCKS_PER_SEC;
    // cout<<"Elements after sorting: "<<endl;
    // printArray(arr,size);
    ofstream write;
    write<<"Merge Sort: "<<size<<endl;
    write.open("check.txt");
    for(int i=0;i<size;i++)
        write<<arr[i]<<" ";
    write<<endl<<"Active Operations: "<<count;
    write<<endl<<"Time elapsed: "<<totalTime<<" seconds.";
    cout<<endl<<"Active Operations: "<<count;
    cout<<endl<<"Time Elapsed: "<<totalTime<<" seconds.";
}