#include <stdio.h>
int gnatt[500];
int findSum(int temp[], int n)
{
    int sum = 0;
    for (int i = 1; i <= n; i++)
        sum += temp[i];
    return sum;
}
int findProcToExec(int currTime, int arr[], int leftBurst[], int n)
{
    int pid = -1, min = 999999999;
    for (int k = 1; k <= n; k++)
    {
        if (leftBurst[k] > 0 && currTime >= arr[k] && leftBurst[k] < min)
        {
            min = leftBurst[k];
            pid = k;
        }
    }
    return pid;
}
void schedule(int arr[], int burst[], int finish[], int n)
{
    int leftBurst[n];
    for (int i = 1; i <= n; i++)
        leftBurst[i] = burst[i];
    int totTime = findSum(burst, n);
    for (int i = 0; i < totTime; i++)
    {
        int pid = findProcToExec(i, arr, leftBurst, n);
        if (pid != -1)
        {
            leftBurst[pid]--;
            if (leftBurst[pid] == 0)
                finish[pid] = i + 1; 
            gnatt[i+1]=pid;       
        }
        else
            i--;
    }
}
void calcTat(int arr[], int finish[], int tat[], int n)
{
    for (int i = 1; i <= n; i++)
        tat[i] = finish[i] - arr[i];
}
void calcWait(int burst[], int tat[], int wait[], int n)
{
    for (int i = 1; i <= n; i++)
        wait[i] = tat[i] - burst[i];
}
void printRes(int arr[], int burst[], int finish[], int wait[], int tat[], int n)
{
    printf("\nProc\t\tArr\t\tBurst\t\tFInish\t\tWait\t\tTAT\t\t\n\n");
    for (int i = 1; i <= n; i++)
    {
        printf("%d \t\t %d \t\t  %d \t\t   %d \t\t %d\t\t  %d\n", i, arr[i], burst[i], finish[i], wait[i], tat[i]);
    }
    //  printf("Average TAT: %d\nAvergae Wait: %d",avgTat,avgWait);
    printf("\n-----------------------------\n");
}
void printGnatt(int n){
    for(int i = 1;i <= n; i++)
        printf("P%d \t|\t %d\n", gnatt[i], i);
    // printf("\n");
    // for(int i=1; i <=n ; i++)
    //     printf("%d ",i);    
}
int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int arr[n], burst[n], tat[n], wait[n], finish[n];
    for (int i = 1; i <= n; i++)
    {
        printf("Enter the arrival and burst time for process %d: ", i);
        scanf("%d %d", &arr[i], &burst[i]);
    }

    schedule(arr, burst, finish, n);
    calcTat(arr, finish, tat, n);
    calcWait(burst, tat, wait, n);
    double avgTat, avgWait;
    // avgTat = findSum(tat, n)/n;
    // avgWait=findSum(wait, n)/n;
    printRes(arr, burst, finish, wait, tat ,n);  
    int totTime = findSum(burst, n);
    printGnatt(totTime);
}