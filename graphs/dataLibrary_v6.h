#ifndef DATAV5_H
#define DATAV5_H
 
#include <iostream>
#include <string>
#include <cstdio>
#include <time.h>
#include <fstream>
#include <sstream>

using namespace std;

template <typename T>
class LinkedList;

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

    float getSizeOfElements() {
        return count * sizeof(T);
    }

    float getListSize() {
        return count * sizeof(head);
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
        if (count == 0)
        	head = NULL;
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
        if (count == 1)
        {
        	temp2 = head; 
			goto end; 
		}
			
        for (temp1 = head; temp1->next->next != NULL; temp1 = temp1->next)
            ;
        temp2 = temp1->next;
        temp1->next = NULL;
    end:
		count--;
		if (count == 0)
        	head = NULL;
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
                currN = currN->next;
            }

            prevN->next = currN->next;
            currN->next = NULL;
            count--;
            if (count == 0)
            	head = NULL;
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
    
    /*
    	this function will get the position of the given element from the list, it returns the position of the first occurence	
    	, if the element if not in the list, it returns -1
    */
    
    int getPos(T data)
    {
    	int pos = 1;
    	for (sllNode<T> *temp = head; temp != NULL; temp = temp->next, pos++)
    	{
    		if (temp->data == data)
    			return pos;
		}
		return -1;
	}
	/*
    	it will find and return the node at the given position, however if the position value provided lies outside
    	the limit of (1, count), it returns the head
    */
	
	sllNode<T> *getNodeAt(int pos)
	{
		if (pos <= 1 || pos > count)
			return head;
		else
		{
			int i = 1;
			for (sllNode<T> *temp = head; temp != NULL; temp = temp->next, i++)
			{
				if (i == pos)
					return temp;
			}	
		}
	}
	/*
    	it will return the data, instead of the node, it calls the above function to implement itself	
    */
	
	T getElementAt(int pos)
	{
		return getNodeAt(pos)->data;	 	
	}
	
	/*
    	it will find and return the position of the minimum element in the list, if however the list if empty, it returns -1	
    */	
		
	int getMinPos()
	{
		if (head == NULL)
			return -1;
		int min = head->data, minPos = 1;
		int currPos = 1;
		for (sllNode<T> *temp = head; temp != NULL; temp = temp->next, currPos++)
		{
			if (temp->data < min)
			{
				min = temp->data;
				minPos = currPos;
			}
		}
		return minPos;
	}
	/*
    	it will find the position of the maximum element in the list and return it, returns -1 if list if empty	
    */
	
	int getMaxPos()
	{
		if (head == NULL)
			return -1;
		int max = head->data, maxPos = 1;
		int currPos = 1;
		for (sllNode<T> *temp = head; temp != NULL; temp = temp->next, currPos++)
		{
			if (temp->data > max)
			{
				max = temp->data;
				maxPos = currPos;
			}
		}
		return maxPos;
	}
	
	/*
    	it returns the minimum value in the list	
    */	
	
	T getMinData()
	{
		return getElementAt(getMinPos());
	}
	
	/*
    	it returns the maximum value in the list	
    */
	
	T getMaxData()
	{
		return getElementAt(getMaxPos());
	}
	
	/*
    	it removes the minumum value from the list and returns it	
    */
		
	sllNode<T> *extractMin()
	{
		return removePos(getMinPos());
	}
	
	/*
    	it extracts the maximum value from the list and returns it	
    */
	
	sllNode<T> *extractMax()
	{
		return removePos(getMaxPos());
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
    void reverse_deprecated()
    {
    	if (head == NULL)
    		return;
        reverse(head, NULL);
    }

    void reverse() {
        sllNode<T> *prev = NULL;
        sllNode<T> *current = head;
        sllNode<T> *next_node;

        while (current) {
            next_node = current->next;
            current->next = prev;
            prev = current;
            current = next_node;
        }
        head = prev;
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
    
    /*
    	this function will print the entire list, if no parameters are provided, it prints the list in normal order,
		if however, the value of parameter is provided, it will print the list in reverse	
    */

private:

    void printRev_deprecated(int count) {
        LinkedList<T> list;
        for (sllNode<T> *temp = head; temp != NULL; temp = temp->next) 
            list.insertFront(temp->data);
        list.print(count);
        list.destroy();
    }

    void printRev(int count) {
        int i;
        sllNode<T> *temp;
        LinkedList<T> list;
        for (temp = head, i = 1; temp != NULL; temp = temp->next, ++i) {
            if (i > this->count - count) 
                list.insertFront(temp->data);
        }
        list.print();
        list.destroy();
    }
public:

    void print(int type = 0)
    {
        if (type == 0)
            type = count;
        if (type < 0)
        {
            printRev(-type);
            return;
        }
        int i;
        sllNode<T> *temp;
        for (temp = head, i = 1; temp != NULL && i <= type; temp = temp->next, ++i)
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

    void destroy_deprecated()
    {
        destroy(head);
        head = NULL;
        count = 0;
    }

    void destroy()
    {
        while (count > 0)
            delFront();
        head = NULL;
        count = 0;
    }

    /*
        destructor 
    */

    ~LinkedList()
    {
        // destroy();
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

    void reverse() {
        bucketNode<T> *prev = NULL;
        bucketNode<T> *current = head;
        bucketNode<T> *next_node;

        while (current) {
            next_node = current->next;
            current->next = prev;
            prev = current;
            current = next_node;
        }
        head = prev;
        updateKeys();
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
    void destroy_deprecated()
    {
        destroy(head);
        head = NULL;
        count = 0;
    }

    void destroy()
    {
        bucketNode<T> *temp;
        while (count > 0)
        {
            temp = removeFront();
            temp->linkedList.destroy();
            delete temp;
        }
        head = NULL;
        count = 0;
    }

    ~Buckets()
    {
        // destroy();
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

    void initializeRandom_deprecated(LinkedList<T> &list, int lower_range = -1, int upper_range = -1, int no_of_elem = -1)
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

    void initializeRandom_deprecated(Buckets<T> &buck, int lower_range = -1, int upper_range = -1, int no_of_elem = -1)
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
            list.insertFront(rand() % (upper_range - lower_range + 1) + lower_range);
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
            buck.insertFront(list);
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

    LinkedList<T> stringToList(string input) {
        LinkedList<T> result;
        istringstream iss(input);
        T num;

        while (iss >> num) {
            result.insert(num);
        }

        return result;
    }

    LinkedList<T> readFile(LinkedList<T> &list, string filepath, int number_to_read = -1) {
        ifstream read;
        read.open(filepath);
        T val;
        if (number_to_read < 0) {
            while(!read.eof()) {
                read >> val;
                // if (!read.eof())
                list.insertFront(val);
            }
        }
        else {
            for(int i = 1; !read.eof() && i <= number_to_read; ++i) {
                read >> val;
                // if (!read.eof())
                list.insertFront(val);
            }
        }
        read.close();
        list.reverse();
        return list;
    }

    void writeFile(LinkedList<T> list, string filename, string sep = " ",int num_to_write = -1) {
        ofstream write;
        int i;
        sllNode<T> *temp;
        write.open(filename);

        if (num_to_write == -1)
            num_to_write = list.getCount();

        for (temp = list.getHead(), i = 1; i <= num_to_write && temp != NULL; temp = temp->next, ++i)
            write << temp->data << sep;

        write.close();
    }

    void appendFile(LinkedList<T> list, string filename, string sep = "",int num_to_write = -1) {
        ofstream write;
        int i;
        sllNode<T> *temp;
        write.open(filename ,ios::app);

        if (num_to_write == -1)
            num_to_write = list.getCount();

        for (temp = list.getHead(), i = 1; i <= num_to_write && temp != NULL; temp = temp->next, ++i)
            write << temp->data << sep;

        write.close();
    }

    Buckets<T> readFile_deprecated(Buckets<T> &buck, string filepath,  int number_of_lines = -1, string demoFileName = "towritefile_dlibv5.h-pratyush") {
        ifstream read;
        ofstream write;
        read.open(filepath);
        T val;
        string line;
        if (number_of_lines <= -1) {
            while(!read.eof()) {
                write.open(demoFileName);
                getline(read, line);
                write << line;
                write.close();

                LinkedList<T> list;
                readFile(list, demoFileName);
                buck.insertFront(list);
            }
        }
        else {
            for (int i = 1; !read.eof() && i <= number_of_lines; i++) {
                write.open(demoFileName);
                getline(read, line);
                write << line;
                write.close();

                LinkedList<T> list;
                readFile(list, demoFileName);
                buck.insertFront(list);
            }
        }
        read.close();
        remove((demoFileName).c_str());
        buck.reverse();
        return buck;
    }

    Buckets<T> readFile(Buckets<T> &buck, string filepath,  int number_of_lines = -1) {
        ifstream read;
        read.open(filepath);
        T val;
        string line;
        if (number_of_lines <= -1) {
            while(!read.eof()) {
                getline(read, line);
                buck.insertFront(stringToList(line));
            }
        }
        else {
            for (int i = 1; !read.eof() && i <= number_of_lines; i++) {
                getline(read, line);
                buck.insertFront(stringToList(line));
            }
        }
        read.close();
        buck.reverse();
        return buck;
    }

    void writeFile(Buckets<T> buck, string filename, string horz_sep = " ", string vert_sep = "\n",int num_to_write = -1) {
        bucketNode<T> *temp;
        int i;
        ofstream write;
        if (num_to_write == -1)
            num_to_write = buck.getCount();
        write.open(filename);
        write.close();
        for (temp = buck.getHead(), i = 1; temp != NULL && i <= num_to_write; temp = temp->next, ++i) {
            appendFile(temp->linkedList, filename, horz_sep);
            if (vert_sep != "") {
                write.open(filename ,ios::app);
                write << vert_sep;
                write.close();
            }
        }
    }

    ~Utilities()
    {
    }
};

#endif