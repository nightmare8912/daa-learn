#include<iostream>
#include<fstream>
using namespace std;
int main(){
    ofstream write;
    write.open("random_400000_inputs.txt");
    for(int i=0;i<400000;i++)
        write<<rand()%1000<<" ";
    write.close();
}