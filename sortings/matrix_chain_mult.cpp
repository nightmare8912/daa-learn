#include <iostream>
#include <time.h>
using namespace std;
class returnType
{
private:
    int m[100][100], s[100][100];
public:
    returnType (int a[100][100], int b[100][100])
    {
        m = a;
        s = b;
    }    
};
returnType bottomUp (int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {

    }
}
int main ()
{
    int n;
    cin >> n;
    clock_t st, end;
    double etime;
    int arr[n];
    srand ((long int) clock());
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand()%n;
        cout << arr[i];
    }

}