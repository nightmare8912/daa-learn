#include <iostream>
using namespace std;
struct node
{
    int data;
    node *next;
};
node *head;
node *newNode (int data)
{
    node *newnode = new node;
    newnode -> data = data;
    newnode -> next = NULL;
    return newnode;
}
void insert (node *newnode)
{
    if (head == NULL)
        head = newnode;
    else
    {
        node *temp;
        for (temp = head; temp -> next != NULL; temp = temp -> next);
        temp -> next = newnode;
    }    
}
void traverse ()
{
    node *temp;
    for (temp = head; temp != NULL; temp = temp -> next)
        cout << temp -> data << " ";
    cout << endl;    
}
void printRev (node *temp = head)
{
    if (temp -> next != NULL)
        printRev (temp -> next);
    cout << temp -> data << " ";    
}
int main ()
{
    int data, opt;
    while (true)
    {
        cout << "Enter 1 - Insert, 2 - Print, 3 - Print Reverse: ";
        cin >> opt;
        switch (opt)
        {
            case 1: cout << "Enter element: ";
                    cin >> data;
                    insert (newNode (data));
                    break;
            case 2: traverse ();
                    break;
            case 3: printRev ();
                    cout << endl;
                    break;                
        }
    }
}