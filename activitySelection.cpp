#include <iostream>
#include <time.h>
using namespace std;
void sort(int start[], int finish[], int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = i+1; j <= n; j++)
        {
            if (start[i] > start[j])
            {
                swap (start[i], start[j]);
                swap (finish[i], finish[j]);
            }
        }
    }
}
void activitySelect(int start[], int finish[], int n)
{
    // sort(start, finish, n);
    int selectedIndex = 1; // activity 1 is always selected
    for (int i = 1; i <= n; i++)
    {
        cout << selectedIndex << " ";
        if (start[i]  >= finish[selectedIndex])
            selectedIndex = i;
    }
    cout << selectedIndex << endl;
}
void printArray(int arr[], int n)
{
    for (int i = 1; i <= n; i++)
        cout << arr[i] << " ";
    cout << endl;    
}
int main()
{
    int n;
    cout << "Enter n: ";
    cin >> n;
    srand((long int)clock());
    int start[n], finish[n];
    for (int i = 1; i <= n; i++)
    {
        // finish[i] = rand () % 25;
        // start[i] = rand () % finish[i];
        cin >> start[i] >> finish[i];
    }
    sort(start, finish, n);
    cout << "Start: ";
    printArray(start, n);
    cout << "Finish: ";
    printArray(finish, n);
    activitySelect(start, finish, n);
}