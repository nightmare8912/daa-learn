#include<iostream>
#include<fstream>
using namespace std;
int main(){
    int a,b=0,c;
    ifstream read;
    read.open("check.txt");
    read>>a;
    while(!read.eof()){
        read>>c;
        //cout<<c<<" ";
        if(!read.eof())
            b++;
    }
    cout<<endl<<"b = "<<b<<endl;
    if(a!=b)
        cout<<"ERROR! ,a = "<<a;
    read.close();    
}