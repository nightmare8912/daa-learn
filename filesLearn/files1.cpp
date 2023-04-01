#include<iostream>
#include<fstream>
using namespace std;
void fileWrite(){
    ofstream write;
    write.open("file1.txt");
    for(int i=0;i<10;i++)
        write<<i<<"\t";
    write.close();    
}
void fileRead(){
    ifstream read;
    int data;
    read.open("file1.txt");
    while(!read.eof()){
        read>>data;
        if(!read.eof())
            cout<<data<<" ";
    }
}
int main(){
    fileRead();
}