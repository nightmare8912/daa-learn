#include <iostream>
#include <time.h>
#include <fstream>
using namespace std;
long int count = 0;
void maxheap(int arr[], int i, int n)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
    {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest])
    {
        largest = right;
    }
    if (largest != i)
    {
        count++;
        swap(arr[largest], arr[i]);
        maxheap(arr, largest, n);
    }
}
void heapsort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        maxheap(arr, i, n);
    }
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]);
        maxheap(arr, 0, i);
    }
}
int main()
{

    int n;
    ifstream read;
    ofstream write;
    clock_t st, end;
    double etime;
    read.open("inputs/random_10000_inputs.txt");
    read >> n;
    cout << "Number of elements in the heap: ";
    cout << n << endl;
    int arr[n];
    // cout<<"Heap elements are: "<<endl;
    for (int i = 0; i < n; i++)
    {
        read >> arr[i];
        // cout<<arr[i]<<" ";
    }
    read.close();
    st = clock();
    heapsort(arr, n);
    end = clock();
    etime = (double)(end - st) / CLOCKS_PER_SEC;
    // cout<<"\nAfter sorting: "<<endl;
    // printArray(arr,n);
    cout << "\nTime elapsed: " << etime << " seconds" << endl;
    cout << "Active operations: " << count;
    write.open("check.txt");
    write << "Heap sort of " << n << " elements" << endl;
    for (int i = 0; i < n; i++)
        write << arr[i] << " ";
    // write<<"\nTime elapsed: "<<etime<<" seconds";
    // write<<"\nActive Operations: "<<count;
    // cout<<endl;
}
