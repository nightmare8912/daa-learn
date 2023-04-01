#include<iostream>
#include<fstream>
#include<time.h>
#include<stdlib.h>
using namespace std;

long int count=0;

void InsertionSort(int *a,int n)
{
	int i,j,key;
	for(j=1;j<n;j++)
	{
		key = a[j];
		i=j-1;
		while(i>=0 && a[i]>key)
		{
			a[i+1] = a[i];
			i = i-1;		
			count++;
		}
		count++;
		a[i+1] = key;
	}
}

int main()
{
	
	ofstream outf;
	ifstream read;

	clock_t st,end;
	double etime;

	int n;	
    read.open("random_100_inputs.txt");
	read>>n;
	int a[n];	
	for(int i=0;i<n;i++)
		read>>a[i];
	read.close();
    cout<<"Number of elements : "<<n;
	// cout<<"\nBefore Sorting: \n";
	// for(int i=0;i<n;i++)
	// 	cout<<a[i]<<" ";
	
	count = 0;
    st = clock();
	InsertionSort(a,n);
    end = clock();

	// cout<<"\nAfter Sorting: \n";
	// for(int i=0;i<n;i++)
	// 	cout<<a[i]<<" ";

	outf.open("check.txt");
    outf<<"Insertion Sort: "<<endl;
	for(int i=1;i<=n;i++)
		outf<<a[i]<<"\t";    
    outf<<"\nTotal Active Operations: "<<count;
    outf<<"\nExecution Time: "<<etime<<" seconds";    
	outf.close();
	etime = (double)(end-st)/CLOCKS_PER_SEC;
	
	cout<<"\n\nInsertion Sort:";
	cout<<"\nTotal Active Operations: "<<count;
	cout<<"\nExecution Time: "<<etime<<" Seconds\n";
	
}