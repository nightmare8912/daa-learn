#include<iostream>
#include<fstream>
#include<time.h>
using namespace std;
long int count=0;
void maxHeapify(int arr[],int parent,int left,int right,int size){
    if(left<=size && arr[parent]<arr[left]){
        count++;
        // cout<<"\nPARENT = "<<parent<<" LEFT = "<<left<<" RIGHT = "<<right<<endl;
        swap(arr[parent],arr[left]);
        // cout<<"After new run: "<<endl;
        // for(int i=1;i<=size;i++)
        //     cout<<arr[i]<<" ";
        maxHeapify(arr,left,2*left,2*left+1,size);
    }

    if(right<=size && arr[parent]<arr[right]){
        count++;
        // cout<<"\nPARENT = "<<parent<<" LEFT = "<<left<<" RIGHT = "<<right<<endl;
        swap(arr[parent],arr[right]);
        // cout<<"After new run: "<<endl;
        // for(int i=1;i<=size;i++)
        //     cout<<arr[i]<<" ";
        maxHeapify(arr,right,2*right,2*right+1,size);
    }
}
void buildHeap(int arr[],int size){
    int lastParent=size/2;
    for(int i=lastParent;i>0;i--){
        int left=2*i,right=2*i+1;
        maxHeapify(arr,i,left,right,size);
    }
}
void heapSort(int arr[],int n){
    for(int i=n;i>0;i--){
        swap(arr[1],arr[i]);
        buildHeap(arr,i-1);
    }
}
void printArray(int arr[],int n){
    for(int i=1;i<=n;i++)
        cout<<arr[i]<<" ";
    cout<<endl;    
}
int main(){
    int n;
    ifstream read;
    ofstream write;
    clock_t st,end;
    double etime;
    read.open("inputs/random_10000_inputs.txt");
    read>>n;
    cout<<"Number of elements in the heap: ";
    cout<<n<<endl;
    int arr[n];
    //cout<<"Heap elements are: "<<endl;
    for(int i=1;i<=n;i++){
        read>>arr[i];
        //cout<<arr[i]<<" ";
    }
    read.close();
    st=clock();
    buildHeap(arr,n);   
    heapSort(arr,n);
    end=clock();
    etime=(double)(end-st)/CLOCKS_PER_SEC;
    //cout<<"\nAfter sorting: "<<endl;
    //printArray(arr,n);
    cout<<"\nTime elapsed: "<<etime<<" seconds"<<endl;
    cout<<"Active operations: "<<count;
    write.open("check.txt");
    write<<"Heap sort of "<<n<<" elements"<<endl;
    for(int i=1;i<=n;i++)
        write<<arr[i]<<" ";
    write<<"\nTime elapsed: "<<etime<<" seconds"; 
    write<<"\nActive Operations: "<<count;
    //cout<<endl;    


}