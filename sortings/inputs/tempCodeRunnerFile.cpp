cout<<"\nTime elapsed: "<<etime<<" seconds"<<endl;
    cout<<"Active operations: "<<count;
    write.open("check.txt");
    write<<"Heap sort of "<<n<<" elements"<<endl;
    for(int i=1;i<=n;i++)
        write<<arr[i]<<" ";
    write<<"\nTime elapsed: "<<etime<<" seconds"; 
    write<<"\nActive Operations: "<<count;
    //cout<<endl; 