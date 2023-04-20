#include <dataLibrary_v5.h>

struct student
{
    int roll;
    string name;
    student() {}
    student(int roll, string name) : roll(roll), name(name) {}
};

int main()
{
    student s1(123, "abc"), s2(234, "def"), s3(345, "ghi");
    LinkedList<student> list;
    list.insert(s1);
    list.insert(s2);
    list.insert(s3);

    // list.getNodeAt(1)->data.name = "xyz";

    for (int i = 1; i < list.getCount() + 1; i++)
        cout << list.getNodeAt(i)->data.name << " " << list.getElementAt(i).roll << endl;

    // for (sllNode<student> *temp = list.getHead(); temp != NULL; temp = temp->next)
    //     cout << temp->data.name << " " << temp->data.roll << endl;
}