#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;
long int count = 0;
int partition(int arr[], int ub, int lb)
{

    int pivot = arr[lb];
    int start = lb;
    int end = ub;
    while (start < end)
    {

        while (arr[start] <= pivot)
        {
            start++;
        }
        while (arr[end] > pivot)
        {
            end--;
        }
        if (start < end)
        {
            swap(arr[start], arr[end]);
        }
    }
    swap(arr[lb], arr[end]);
    return end;
}
void quicksort(int arr[], int ub, int lb)
{
    if (lb < ub)
    {
        count++;
        int loc = partition(arr, ub, lb);
        quicksort(arr, loc - 1, lb);
        quicksort(arr, ub, loc + 1);
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
    int lb = 0;
    int ub = n;
    st=clock();
    partition(arr, ub, lb);
    quicksort(arr, ub, lb);
    end=clock();
    etime=(double)(end-st)/CLOCKS_PER_SEC;
    cout << "\nTime elapsed: " << etime << " seconds" << endl;
    cout << "Active operations: " << count;
    write.open("check.txt");
    write << "Quick sort of " << n << " elements" << endl;
    for (int i = 0; i < n; i++)
        write << arr[i] << " ";
    // write << "\nTime elapsed: " << etime << " seconds";
    // write << "\nActive Operations: " << count;
    // cout << endl;
}