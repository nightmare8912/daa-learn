#include <iostream>
#include <time.h>

using namespace std;

template <typename T>
class LinkedList;

template <typename T>
class Tree;

template <typename T>
class Buckets;

template <typename T>
class Utilities;

/*
    sll Node is used to implement the singly linked list
*/

template <typename T>
struct sllNode
{
    T data;
    sllNode<T> *next;
};

template <typename T>
class LinkedList
{

private:
    /*
        head represents the first element in the list
        count represents the number of elements in the list
    */

    sllNode<T> *head;
    int count;

public:
    LinkedList()
    {
        head = NULL;
        count = 0;
    }

    sllNode<T> *getHead()
    {
        return head;
    }

    int getCount()
    {
        return count;
    }

private:
    /*
        createNode creates a new node, initializes it with given data and returns the node
    */

    sllNode<T> *createNode(T data)
    {
        sllNode<T> *temp = new sllNode<T>;
        temp->data = data;
        temp->next = NULL;
        return temp;
    }

    /*
        this function will insert the node provided to it in the list (AT THE START)
        it does so after making sure that the node provided to it is not used by other list
        , it does so by checking its next value, if its not NULL, it will create a fresh node
        it is done to avoid conficts between the two lists
    */

    void insertFront(sllNode<T> *newnode)
    {
        if (newnode->next != NULL)
            newnode = createNode(newnode->data);
        if (head == NULL)
            head = newnode;
        else
        {
            newnode->next = head;
            head = newnode;
        }
        count++;
    }

public:
    /*
        it will call the above two functions, it creates a new node with provided data, and inserts it
        in the list (AT THE START), by calling the above function
    */

    void insertFront(T data)
    {
        insertFront(createNode(data));
    }

private:
    /*
        this function will insert the node provided to it in the list (AT THE END)
        it does so after making sure that the node provided to it is not used by other list
        , it does so by checking its next value, if its not NULL, it will create a fresh node
        it is done to avoid conficts between the two lists
    */

    void insertEnd(sllNode<T> *newnode)
    {
        if (newnode->next != NULL)
            newnode = createNode(newnode->data);
        if (head == NULL)
            head = newnode;
        else
        {
            sllNode<T> *temp;
            for (temp = head; temp->next != NULL; temp = temp->next)
                ;
            temp->next = newnode;
        }
        count++;
    }

public:
    /*
        it will call the above two functions, it creates a new node with provided data, and inserts it
        in the list (AT THE END), by calling the above function
    */

    void insertEnd(T data)
    {
        insertEnd(createNode(data));
    }
    // private:
    // void insert(sllNode<T> *temp, int type = 1)
    // {
    //     // sllNode<T> *newnode = createNode(temp->data);
    //     if (type == 1)
    //         insertEnd(temp);
    //     else
    //         insertFront(temp);
    // }
private:

    /*
        this function will insert the given node at the given position, it is made private to avoid
        runtime errors that may occur due to invalid positions provided by the user, and also to avoid
        a node that is being used by other  linked list to be inserted
    */

    void insertPos(sllNode<T> *newnode, int pos)
    {
        sllNode<T> *prev, *curr;
        // prev = NULL; curr = head;
        int i = 1;
        for (prev = NULL, curr = head; curr != NULL && i < pos; prev = curr, curr = curr->next, i++)
            ;
        prev->next = newnode;
        newnode->next = curr;
        count ++;
    }    
public:
    /*
        this function is provided for convenience, its task is to insert the given data in
        the list, the position of insertion depends on the value of type provided,
        if no value is provided, it will insert at the end, otherwise it will insert at the start
    */

    void insert(T data, int type = 1)
    {
        if (type == 1)
            insertEnd(data);
        else
            insertFront(data);        
    }

    /*
        this function will insert the given value at the position provided by the user, if the provided
        pos is <= 1, it will call insertFront() function, similarly it will call insertEnd() function,
        if the position is greater than the number of elements, however if the position is between 1 and 
        no of elements in list, it will call the insertPos function()
    */

    void insertPos(T data, int pos)
    {
        if (pos <= 1)
            insertFront(data);
        else if (pos > count)
            insertEnd(data);
        else
            insertPos(createNode(data), pos);
    }
    
    /*
        this function will REMOVE the first element from the list and return it
    */

    sllNode<T> *removeFront()
    {
        if (head == NULL)
            return NULL;
        sllNode<T> *temp = head;
        head = head->next;
        temp->next = NULL;
        count--;
        return temp;
    }

    /*
        this function will REMOVE the last element from the list and return it
    */

    sllNode<T> *removeEnd()
    {
        if (head == NULL)
            return NULL;
        sllNode<T> *temp1, *temp2;
        for (temp1 = head; temp1->next->next != NULL; temp1 = temp1->next)
            ;
        temp2 = temp1->next;
        temp1->next = NULL;
        count--;
        return temp2;
    }

    /*
        this function will REMOVE the element at the given position from the list, and return it
        if however, the value of pos is <= 1, it will call the removeFront() function, and similarly,
        if the value of pos is >= no_of_elements in the list, it will call removeEnd() function
    */

    sllNode<T> *removePos(int pos)
    {
        if (head == NULL)
            return NULL;
        if (pos <= 1)
            return removeFront();
        else if (pos >= count)
            return removeEnd();
        else
        {
            sllNode<T> *prevN, *currN, *nextN;
            prevN = NULL; currN = head; nextN = currN->next;
            int i = 1;
            while (currN != NULL && i < pos)
            {
                i++;
                prevN = currN;
                // currN = nextN;
                // nextN = nextN->next;
                currN = currN->next;
            }

            prevN->next = currN->next;
            currN->next = NULL;
            count--;
            return currN;
        }        
    }

    /*
        this function is provided for convenience, its task is to REMOVE the element
        from the list, the position of REMOVAL depends on the value of type provided,
        if no value is provided, it will REMOVE from the end, otherwise it will REMOVE from the start
    */

    sllNode<T> *remove(int type = 1)
    {
        if (type == 1)
            return removeEnd();
        else
            return removeFront();
    }

    /*
        this function will REMOVE and DELETE the first element from the LIST AND MEMORY and return it
    */

    void delFront()
    {
        sllNode<T> *temp = removeFront();
        if (temp != NULL)
            delete temp;
    }

    /*
        this function will REMOVE and DELETE the last element from the LIST AND MEMORY and return it
    */

    void delEnd()
    {
        sllNode<T> *temp = removeEnd();
        if (temp != NULL)
            delete temp;
    }

    /*
       this function is provided for convenience, its task is to REMOVE AND DELETE the element
       from the LIST AND MEMORY, the position of REMOVAL depends on the value of type provided,
       if no value is provided, it will REMOVE from the end, otherwise it will REMOVE from the start
   */

    void del(int type = 1)
    {
        if (type == 1)
            delEnd();
        else
            delFront();
    }

    /*
        this function will REMOVE and DELETE the element at the given position from the list
    */

    void delPos(int pos)
    {
        sllNode<T> *temp = removePos(pos);
        if (temp != NULL)
            delete temp;
    }

    /*
        this function will find if the element provided is in the list, if found, it removes it from the list
        and returns it, if not found, it returns NULL
    */

    sllNode<T> *findAndRemove(T data)
    {
        int pos = 1;
        for (sllNode<T> *temp = head; temp != NULL; temp = temp->next, pos++)
        {
            if (temp->data == data)
                return removePos(pos);
        }
        return NULL;
    }

    /*
        this function will delete the elements from the list and the memory
    */

    void findAndDelete(T data)
    {
        sllNode<T> *temp = findAndRemove(data);
        if (temp != NULL)
            delete temp;
    }

private:
    void reverse(sllNode<T> *currNode, sllNode<T> *prevNode)
    {
        if (currNode->next == NULL)
        {
            head = currNode;
            currNode->next = prevNode;
            return;
        }
        reverse(currNode->next, currNode);
        currNode->next = prevNode;
    }

public:

    /*
        this function will call the above function, which will simply reverse the list, it does so by using
        recursion
    */
    void reverse()
    {
        reverse(head, NULL);
    }

    /*
        this function will print the list in reverse order from the provided node, it uses recursion to do it
    */

    void printRev(sllNode<T> *temp)
    {
        if (temp == NULL)
            return;
        printRev(temp->next);
        cout << temp->data << " ";
    }

    /*
        this function will print the entire list in reverse order
    */

    void printRev()
    {
        printRev(head);
        cout << endl;
    }

    void print(int type = 1)
    {
        if (type != 1)
        {
            printRev();
            return;
        }
        for (sllNode<T> *temp = head; temp != NULL; temp = temp->next)
            cout << temp->data << " ";
        cout << endl;
        return;
    }

private:

    /*
        this function will delete the elements from the linked list, it does so by using recursion,
        however it is made private to avoid runtime errors, as the list might not be deleted
        properly if the value of temp != head, so it is called by another inbuilt function
    */

    void destroy(sllNode<T> *temp)
    {
        if (temp == NULL)
            return;
        destroy(temp->next);
        delete temp;
    }

public:

    /*
        this function will call the above function, which will destroy the entire linkedList
    */

    void destroy()
    {
        destroy(head);
        head = NULL;
        count = 0;
    }

    /*
        destructor 
    */

    ~LinkedList()
    {
    }
};

template <typename T>
struct bucketNode
{
    int key;
    LinkedList<T> linkedList;
    bucketNode<T> *next;
};

template <typename T>
class Buckets
{
private:
    bucketNode<T> *head;
    int count;
    Utilities<T> ut;

public:
    Buckets()
    {
        head = NULL;
        count = 0;
    }

    bucketNode<T> *getHead()
    {
        return head;
    }

    int getCount()
    {
        return count;
    }

    void updateKeys()
    {
        count = 0;
        for (bucketNode<T> *temp = head; temp != NULL; temp = temp->next)
            temp->key = count++;
    }

private:
    bucketNode<T> *createNode(LinkedList<T> list)
    {
        bucketNode<T> *newnode = new bucketNode<T>;
        newnode->next = NULL;
        newnode->linkedList = ut.createNewCopy(list);
        newnode->key = 0;
        return newnode;
    }

    void insertFront(bucketNode<T> *newnode)
    {
        if (newnode->next != NULL)
            newnode = createNode(newnode->linkedList);
        if (head == NULL)
            head = newnode;
        else
        {
            newnode->next = head;
            head = newnode;
        }
        updateKeys();
    }

public:
    void insertFront(LinkedList<T> list)
    {
        insertFront(createNode(list));
    }

private:
    void insertEnd(bucketNode<T> *newnode)
    {
        if (newnode->next != NULL)
            newnode = createNode(newnode->linkedList);
        if (head == NULL)
            head = newnode;
        else
        {
            bucketNode<T> *temp;
            for (temp = head; temp->next != NULL; temp = temp->next)
                ;
            temp->next = newnode;
        }
        updateKeys();
    }

public:
    void insertEnd(LinkedList<T> list)
    {
        insertEnd(createNode(list));
    }

    void insert(bucketNode<T> *bucketNode, int type = 1)
    {
        if (type == 1)
            insertEnd(bucketNode);
        else
            insertFront(bucketNode);
    }

    void insert(LinkedList<T> list, int type = 1)
    {
        insert(createNode(list), type);
    }

    bucketNode<T> *removeFront()
    {
        if (head == NULL)
            return NULL;
        bucketNode<T> *temp = head;
        head = head->next;
        temp->next = NULL;
        updateKeys();
        return temp;
    }

    bucketNode<T> *removeEnd()
    {
        if (head == NULL)
            return NULL;
        bucketNode<T> *temp1, *temp2;
        for (temp1 = head; temp1->next->next != NULL; temp1 = temp1->next)
            ;
        temp2 = temp1->next;
        temp1->next = NULL;
        updateKeys();
        return temp2;
    }

    bucketNode<T> *remove(int type = 1)
    {
        if (type == 1)
            return removeEnd();
        else
            return removeFront();
    }

    void delFront()
    {
        bucketNode<T> *temp = removeFront();
        if (temp != NULL)
        {
            temp->linkedList.destroy();
            delete temp;
        }
    }

    void delEnd()
    {
        bucketNode<T> *temp = removeEnd();
        if (temp != NULL)
        {
            temp->linkedList.destroy();
            delete temp;
        }
    }

    void del(int type = 1)
    {
        if (type == 1)
            delEnd();
        else
            delFront();
    }

    void printIndex()
    {
        for (bucketNode<T> *temp = head; temp != NULL; temp = temp->next)
            cout << temp->key << " ";
        cout << endl;
    }

    void printWithoutIndex()
    {
        for (bucketNode<T> *temp = head; temp != NULL; temp = temp->next)
            temp->linkedList.print();
    }

    void printWithIndex()
    {
        for (bucketNode<T> *temp = head; temp != NULL; temp = temp->next)
        {
            cout << temp->key << " -----> ";
            temp->linkedList.print();
        }
    }

    void print(int type = 0)
    {
        if (type == 0)
            printWithIndex();
        else if (type == 1)
            printWithoutIndex();
        else if (type == -1)
            printIndex();
    }

private:
    void destroy(bucketNode<T> *temp)
    {
        if (temp == NULL)
            return;
        destroy(temp->next);
        temp->linkedList.destroy();
        delete temp;
    }

public:
    void destroy()
    {
        destroy(head);
        head = NULL;
        count = 0;
    }

    ~Buckets()
    {
    }
};

template <typename T>
class Utilities
{
public:
    string gap(int n = 3)
    {
        for (int i = 0; i < n; i++)
            cout << endl;
        return "";
    }

    string dummy(int n = 3, int n2 = 2)
    {
        gap(n2);
        for (int i = 0; i < n; i++)
            cout << (char)((rand() % 25) + 65);
        gap(n2);
        return "";
    }

    void initializeRandom(T arr[], int size, int lower_range = -1, int upper_range = -1)
    {
        if (lower_range < 0)
        {
            upper_range = rand() % 30;
            lower_range = rand() % upper_range;
        }

        if (upper_range < lower_range)
            swap(upper_range, lower_range);

        if (upper_range == lower_range)
            upper_range += lower_range;

        for (int i = 0; i < size; i++)
            arr[i] = rand() % (upper_range - lower_range + 1) + lower_range, rand() % 2;
    }

    void initializeRandom(LinkedList<T> &list, int lower_range = -1, int upper_range = -1, int no_of_elem = -1)
    {
        if (lower_range < 0)
        {
            upper_range = rand() % 30;
            lower_range = rand() % upper_range;
        }

        if (upper_range < lower_range)
            swap(upper_range, lower_range);

        if (upper_range == lower_range)
            upper_range += lower_range;

        if (no_of_elem < 0)
        {
            srand((long int)clock());
            no_of_elem = rand() % 20;
        }

        // sleep(1);

        for (int i = 0; i < no_of_elem; i++)
            list.insert(rand() % (upper_range - lower_range + 1) + lower_range, rand() % 2);
    }

    void initializeRandom(Buckets<T> &buck, int lower_range = -1, int upper_range = -1, int no_of_elem = -1)
    {
        if (lower_range < 0)
        {
            srand((unsigned)time((0)));
            upper_range = rand() % 30;
            lower_range = rand() % upper_range;
        }

        if (upper_range < lower_range)
            swap(upper_range, lower_range);

        if (upper_range == lower_range)
            upper_range += lower_range;

        if (no_of_elem < 0)
        {
            srand((unsigned)time(0));
            no_of_elem = rand() % 20;
        }
        for (int i = 0; i < no_of_elem; i++)
        {
            LinkedList<T> list;
            initializeRandom(list);
            buck.insert(list);
        }
    }

    void sortAsc(T arr[], int size, int st_index = -1, int end_index = -1)
    {
        if (end_index <= 0)
            end_index = size;
        if (st_index < 0)
            st_index = 0;
        for (int i = st_index; i < end_index; i++)
        {
            for (int j = i + 1; j < end_index; j++)
            {
                if (arr[i] > arr[j])
                    swap(arr[i], arr[j]);
            }
        }
    }

    void sortDesc(T arr[], int size, int st_index = 0, int end_index = -1)
    {
        if (end_index <= 0)
            end_index = size;
        if (st_index < 0)
            st_index = 0;
        for (int i = st_index; i < end_index; i++)
        {
            for (int j = i + 1; j < end_index; j++)
            {
                if (arr[i] < arr[j])
                    swap(arr[i], arr[j]);
            }
        }
    }

    void sort(T arr[], int size, int type = 1, int st_index = -1, int end_index = -1)
    {
        if (type == 1)
            sortAsc(arr, size, st_index, end_index);
        else
            sortDesc(arr, size, st_index, end_index);
    }

    void sortAsc(LinkedList<T> &list)
    {
        for (sllNode<T> *i = list.getHead(); i != NULL; i = i->next)
        {
            for (sllNode<T> *j = i->next; j != NULL; j = j->next)
            {
                if (i->data > j->data)
                    swap(i->data, j->data);
            }
        }
    }

    void sortDesc(LinkedList<T> &list)
    {
        for (sllNode<T> *i = list.getHead(); i != NULL; i = i->next)
        {
            for (sllNode<T> *j = i->next; j != NULL; j = j->next)
            {
                if (i->data < j->data)
                    swap(i->data, j->data);
            }
        }
    }

    void sort(LinkedList<T> &list, int type = 1)
    {
        if (type == 1)
            sortAsc(list);
        else
            sortDesc(list);
    }

    LinkedList<T> createNewCopy(LinkedList<T> list)
    {
        LinkedList<T> newList;
        for (sllNode<T> *temp = list.getHead(); temp != NULL; temp = temp->next)
            newList.insertEnd(temp->data);
        return newList;
    }

    Buckets<T> createNewCopy(Buckets<T> buck)
    {
        Buckets<T> newBuck;
        for (bucketNode<T> *temp = buck.getHead(); temp != NULL; temp = temp->next)
        {
            newBuck.insertEnd(temp->linkedList);
        }
        return newBuck;
    }

    void copy(LinkedList<T> &list1, LinkedList<T> list2)
    {
        list1.destroy();
        for (sllNode<T> *temp = list2.getHead(); temp != NULL; temp = temp->next)
            list1.insertEnd(temp->data);
    }

    void copy(Buckets<T> &buck1, Buckets<T> buck2)
    {
        buck1.destroy();
        for (bucketNode<T> *temp = buck2.getHead(); temp != NULL; temp = temp->next)
            buck1.insertEnd(temp->linkedList);
    }

    void append(LinkedList<T> &list1, LinkedList<T> &list2)
    {
        for (sllNode<T> *temp = list2.getHead(); temp != NULL; temp = temp->next)
            list1.insertEnd(temp->data);
    }

    void append(Buckets<T> &buck1, Buckets<T> buck2)
    {
        for (bucketNode<T> *temp = buck2.getHead(); temp != NULL; temp = temp->next)
            buck1.insertEnd(temp->linkedList);
    }

    void prepend(LinkedList<T> &list1, LinkedList<T> list2)
    {
        for (sllNode<T> *temp = list2.getHead(); temp != NULL; temp = temp->next)
            list1.insertFront(temp->data);
    }

    void prepend(Buckets<T> &buck1, Buckets<T> buck2)
    {
        for (bucketNode<T> *temp = buck2.getHead(); temp != NULL; temp = temp->next)
            buck1.insertFront(temp->linkedList);
    }

    int getOccurences(LinkedList<T> list, T data)
    {
        int count = 0;
        for (sllNode<T> *temp = list.getHead(); temp != NULL; temp = temp->next)
        {
            if (temp->data == data)
                count++;
        }
        return count;
    }

    void removeDuplicates(LinkedList<T> &list)
    {
        sllNode<T> *newTemp;
        for (sllNode<T> *temp = list.getHead(); temp != NULL; temp = temp->next)
        {
            if (getOccurences(list, temp->data) > 1)
            {
                newTemp = temp->next;
                list.findAndDelete(temp->data);
                temp = newTemp;
            }
        }
    }

    bool isEqual(LinkedList<T> list1, LinkedList<T> list2)
    {
        if (list1.getCount() != list2.getCount())
            return false;
        sllNode<T> *temp1, *temp2;
        for (temp1 = list1.getHead(), temp2 = list2.getHead(); temp1 != NULL && temp2 != NULL; temp1 = temp1->next, temp2 = temp2->next)
        {
            if (temp1->data != temp2->data)
                return false;
        }

        if (temp1 != NULL || temp2 != NULL)
            return false;
        return true;
    }

    bool isEqual(Buckets<T> buck1, Buckets<T> buck2)
    {
        if (buck1.getCount() != buck2.getCount())
            return false;
        bucketNode<T> *temp1, *temp2;
        for (temp1 = buck1.getHead(), temp2 = buck2.getHead(); temp1 != NULL && temp2 != NULL; temp1 = temp1->next, temp2 = temp2->next)
        {
            if (!isEqual(temp1->linkedList, temp2->linkedList))
                return false;
        }
        if (temp1 != NULL || temp2 != NULL)
            return false;
        return true;
    }

    bool isEqualJumbled(LinkedList<T> list1, LinkedList<T> list2)
    {
        bool rv = false;
        if (list1.getCount() != list2.getCount())
            return false;
        LinkedList<T> temp1, temp2;
        temp1 = createNewCopy(list1);
        temp2 = createNewCopy(list2);
        sort(temp1);
        sort(temp2);
        if (isEqual(temp1, temp2))
            rv = true;
        temp1.destroy();
        temp2.destroy();
        return rv;
    }

    bool isPresentJumbled(Buckets<T> buck, LinkedList<T> list)
    {
        for (bucketNode<T> *temp = buck.getHead(); temp != NULL; temp = temp->next)
        {
            if (isEqualJumbled(temp->linkedList, list))
                return true;
        }
        return false;
    }

    bool isPresent(LinkedList<T> list, T data)
    {
        for (sllNode<T> *temp = list.getHead(); temp != NULL; temp = temp->next)
        {
            if (temp->data == data)
                return true;
        }
        return false;
    }

    bool isPresent(Buckets<T> buck, LinkedList<T> list)
    {
        for (bucketNode<T> *temp = buck.getHead(); temp != NULL; temp = temp->next)
        {
            if (isEqual(temp->linkedList, list))
                return true;
        }
        return false;
    }

    void insertNonDuplicateElements(LinkedList<T> &list, T data)
    {
        if (isPresent(list, data))
            return;
        list.insert(data);    
    }

    void insertNonDuplicateElements(Buckets<T> &buck, LinkedList<T> list)
    {
        if (isPresent(buck, list))
            return;
        buck.insert(list);    
    }

    void printArray(int arr[], int size)
    {
        for (int i = 0; i < size; i++)
            cout << arr[i] << " ";
        cout << endl;
    }

    void printArray(LinkedList<T> list[], int no_of_elem)
    {
        for (int i = 0; i < no_of_elem; i++)
            list[i].print();
    }

    void printArray(Buckets<T> buck[], int no_of_elem)
    {
        for (int i = 0; i < no_of_elem; i++)
            buck[i].print();
    }

    ~Utilities()
    {
    }
};