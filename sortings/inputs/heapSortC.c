#include<stdio.h>
#include<stdlib.h>
//using namespace std;
void swap(int arr[],int i,int j){
    int temp=arr[i];
    arr[i]=arr[j];
    arr[j]=temp;
}

void maxHeapify(int arr[],int parent,int left,int right,int size){
    if(left<=size && arr[parent]<arr[left]){
        // cout<<"\nPARENT = "<<parent<<" LEFT = "<<left<<" RIGHT = "<<right<<endl;
        swap(arr,parent,left);
        // cout<<"After new run: "<<endl;
        // for(int i=1;i<=size;i++)
        //     cout<<arr[i]<<" ";
        maxHeapify(arr,left,2*left,2*left+1,size);
    }

    if(right<=size && arr[parent]<arr[right]){
        // cout<<"\nPARENT = "<<parent<<" LEFT = "<<left<<" RIGHT = "<<right<<endl;
        swap(arr,parent,right);
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
int main(){
    int n;
    printf("Enter the number of elements in the heap: ");
    scanf("%d",&n);

    int arr[n];
    printf("Heap elements are: \n");
    for(int i=1;i<=n;i++){
        arr[i]=rand()%10;
        printf("%d ",arr[i]);
    }

    buildHeap(arr,n);
    printf("\nAfter heapifying: \n");
    for(int i=1;i<=n;i++)
        printf("%d ",arr[i]);

}