#include<iostream>
#include<fstream>
#include<time.h>
using namespace std;
void sort(int arr[],int size){
	clock_t start,end;
	double totalTime;
	start=clock();
	for(int i=0,j;i<size-1;i++){
		j=i+1;
		//if(j!=0 && arr[j]<arr[i]){
			while(j!=0 && arr[j]<arr[i]){
				int temp=arr[j];
				arr[j]=arr[i];
				arr[i]=temp;
				i--;j--;
			}
		//}
	}
	end=clock();
	totalTime=(double)(end-start)/CLOCKS_PER_SEC;
	// cout<<"After sorting :"<<endl;
	// for(int i=0;i<size;i++)
	// 	cout<<arr[i]<<" ";
	cout<<"\nTime elapsed: "<<totalTime<<" seconds.";	
	ofstream write;
	write.open("check.txt");
	write<<size<<endl;
	for(int i=0;i<size;i++)
		write<<arr[i]<<" ";
	write<<endl<<"Time elapsed: "<<totalTime<<" seconds.";	
	//write<<endl<<"Last Edited: "<<asctime();		
		
}
int main(){
	int size;
    ifstream read;
	read.open("random_100000_inputs.txt");
    read>>size;
	cout<<"Number of elements: "<<size;
	
	int arr[size];
	for(int i=0;i<size;i++)
		read>>arr[i];
	read.close();	
				
	// cout<<"Before sorting: "<<endl;
	// for(int i=0;i<size;i++)
	// 	cout<<arr[i]<<" ";
	// cout<<"\n------------\n";
	sort(arr,size);
}