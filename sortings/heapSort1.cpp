#include<iostream>
#include<fstream>
#include<time.h>
using namespace std;
long int count=0;
void maxHeapify(int arr[],int parent, int size){
    int left = 2 * parent;
    int right = left + 1;
    int largest = parent;
    if(left <= size && arr[left] > arr[largest])    
        largest = left;
    if(right <= size && arr[right] > arr[largest])  
        largest = right;
    if (largest != parent)
    {
        swap (arr[largest], arr[parent]);
        maxHeapify(arr, largest, size);
    }        
}
void buildHeap(int arr[],int size){
    for (int i = size/2; i >= 1; i--)
        maxHeapify(arr, i, size);
}
void heapSort(int arr[],int n){
        buildHeap(arr, n);
        for (int i = n; i >= 2; i--)
        {
            swap (arr[1], arr[i]);
            n = n - 1;
            buildHeap (arr, n);
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
    // read.open("inputs/random_10000_inputs.txt");
    // read>>n;
    cout<<"Number of elements in the heap: ";
    cin >> n;
    int arr[n];
    //cout<<"Heap elements are: "<<endl;
    for(int i=1;i<=n;i++){
        arr[i] = rand()%10;
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    read.close();
    st=clock();
    buildHeap(arr,n);   
    heapSort(arr,n);
    end=clock();
    etime=(double)(end-st)/CLOCKS_PER_SEC;
    cout<<"\nAfter sorting: "<<endl;
    printArray(arr,n);
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