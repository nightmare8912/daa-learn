#include <iostream>
#include <time.h>
using namespace std;
struct node
{
    char data;
    int freq;
    node *left, *right, *next;
};
class queue
{
public:
    int count;
    node *head;

    queue()
    {
        count = 0;
        head = NULL;
    }

    node *newNode(char data, int freq)
    {
        node *newnode = new node;
        newnode->data = data;
        newnode->freq = freq;
        newnode->left = newnode->right = newnode->next = NULL;
        return newnode;
    }

    void insert(node *newnode)
    {
        if (head == NULL)
            head = newnode;
        else
        {
            newnode->next = head;
            head = newnode;
        }
        count++;
    }

    bool isPresent(char elem)
    {
        for (node *temp = head; temp != NULL; temp = temp->next)
        {
            if (temp->data == elem)
                return true;
        }
        return false;
    }

    void traverse()
    {
        for (node *temp = head; temp != NULL; temp = temp->next)
            cout << temp->data << ": " << temp->freq << endl;
    }

    void sort()
    {
        node *i, *j;
        for (i = head; i != NULL; i = i->next)
        {
            for (j = i->next; j != NULL; j = j->next)
            {
                if (j->freq < i->freq)
                {
                    swap(i->data, j->data);
                    swap(i->freq, j->freq);
                    swap(i->left, j->left);
                    swap(i->right, j->right);
                }
            }
        }
    }
};
class tree
{
public:
    int count;
    node *root;
    queue q;

    tree(queue q)
    {
        count = 0;
        root = NULL;
        this->q = q;
    }

    node *newNode(node *left, node *right)
    {
        node *newnode = new node;
        newnode->left = left;
        newnode->right = right;
        newnode->freq = left->freq + right->freq;
        newnode->data = '*';
        newnode->next = NULL;
        return newnode;
    }

    node *extractMin()
    {
        node *temp = q.head;
        q.head = q.head->next;
        q.count--;
        return temp;
    }

    void preOrder(node *temp)
    {
        if (temp != NULL)
        {
            cout << temp->data << " " << temp->freq << ", ";
            preOrder(temp->left);
            preOrder(temp->right);
        }
    }

    bool isLeaf(node *temp)
    {
        if (temp->left == NULL && temp->right == NULL)
            return true;
        return false;
    }

    void printCodes(node *temp, string res = "")
    {
        if (isLeaf(temp))
        {
            cout << temp->data << ": " << res << "\n";
            return;
        }
        printCodes(temp->left, res + "0");
        printCodes(temp->right, res + "1");
    }

    void buildHuffmanTree()
    {
        while (q.count != 1)
        {
            q.sort();
            node *min1 = extractMin();
            node *min2 = extractMin();
            q.insert(newNode(min1, min2));
        }
        root = q.head;
        preOrder(root);
        cout << "\n---------\n\n";
        cout << "Codes: " << endl;
        printCodes(root);
    }
};
int main()
{
    int n = 27;
    char elem;
    int freq;
    queue q;
    while (n > 26)
    {
        cout << "Enter n: ";
        cin >> n;
        if (n > 26)
            cout << "\n-----Enter a number less than or equal to 26-----\n\n";
    }
    srand((long int)clock());
    for (int i = 0; i < n; i++)
    {
        elem = rand() % 26 + 65;
        freq = rand() % 10 + 1;
        // cin >> elem >> freq;
        if (q.isPresent(elem))
            i--;
        else
            q.insert(q.newNode(elem, freq));
    }
    q.traverse();
    tree t(q);
    t.buildHuffmanTree();
}