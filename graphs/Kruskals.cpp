#include <dataLibrary_v5.h>

// only insert(), getHead(), getCount(), getElementAt() and getNodeAt() functions from the linked list are used
// and only the append() function from utilities is used from the header file

struct edge
{
    int from, to, weight;
    bool isProcessed;
    edge() : from(-1), to(-1), weight(-1) {}
    edge(int from, int to, int weight) : from(from), to(to), weight(weight) {}
};

struct vertex
{
    int data, predecessor, distance;
    LinkedList<edge> list;
};

class Graph
{
private:
    vertex *v;
    int count, unprocessed_edges, no_of_edges;

    void printList(LinkedList<edge> list)
    {
        for (sllNode<edge> *temp = list.getHead(); temp != NULL; temp = temp->next)
            cout << "From: " <<temp->data.from << "\tTo: " << temp->data.to << "\tWeight: " << temp->data.weight << endl;
    }

public:
    Graph(int count)
    {
        v = new vertex[count];
        this->count = count;
        no_of_edges = 0;
        unprocessed_edges = 0;
    }

    void initialize(int src)
    {
        for (int i = 0; i < count; i++)
        {
            v[i].data = i;
            v[i].distance = 9999;
            v[i].predecessor = -1;
            for (sllNode<edge> *temp = v[i].list.getHead(); temp != NULL; temp = temp->next)
                temp->data.isProcessed = false;
        }
        v[src].distance = 0;
    }

    void addEdge(int from, int to, int weight)
    {
        v[from].list.insert(edge(from, to, weight));
        v[to].list.insert(edge(to, from, weight));
        no_of_edges += 2;
    }

    void processComplementaryEdge(int from, int to)
    {
        for (sllNode<edge> *temp = v[to].list.getHead(); temp != NULL; temp = temp->next)
        {
            if (temp->data.to == from)
            {
                temp->data.isProcessed = true;
                unprocessed_edges--;
                return;
            }
        }
        cout << "Error occured!" << endl;
    }

    edge findMin()
    { 
        int min = 9999;
        int minPresentIn = 0, minPresentAt = 1;
        for (int i = 0; i < count; i++)
        {
            int currPos = 1;
            for (sllNode<edge> *temp = v[i].list.getHead(); temp != NULL; temp = temp->next, currPos++)
            {
                if (!temp->data.isProcessed && temp->data.weight < min)
                {
                    min = temp->data.weight;
                    minPresentIn = i;
                    minPresentAt = currPos;
                }
            }
        }
        sllNode<edge> *temp = v[minPresentIn].list.getNodeAt(minPresentAt);
        temp->data.isProcessed = true;
        unprocessed_edges--;
        return temp->data;
    } 

    int findSLLIndex(LinkedList<vertex> list[], int vert)
    {
        for (int i = 0; i < count; i++)
        {
            for (sllNode<vertex> *temp = list[i].getHead(); temp != NULL; temp = temp->next)
            {
                if (vert == temp->data.data)
                    return i;
            }
        }
        return -1;
    }

    void printRes()
    {
        cout << "Data\tDistance\tPredecessor" << endl;
        for (int i = 0; i < count; i++)
            cout << v[i].data << "\t\t\t" << v[i].distance << "\t\t\t" << v[i].predecessor << endl;
    }
    void print()
    {
        for (int i = 0; i < count; i++)
        {
            cout << v[i].data << endl;
            printList(v[i].list);
        }
    }

    void printLol()
    {
        for (int i = 0; i < count; i++)
        {
            cout << i << " ----> ";
            for (int k = 1; k <= v[i].list.getCount(); k++)
                cout << "(" <<v[i].list.getElementAt(k).to << " " << v[i].list.getElementAt(k).weight << ") ";
            cout << endl;
        }
    }

    void kruskals(int src = 0)
    {
        initialize(src);
        LinkedList<vertex> list[count];
        Utilities<vertex> ut;
        for (int i = 0; i < count; i++)
            list[i].insert(v[i]);
        int min_cost = 0;
        printLol();
        unprocessed_edges = no_of_edges;
        while (unprocessed_edges > 0)
        {
            edge edg = findMin();
            int index1 = findSLLIndex(list, edg.from);
            int index2 = findSLLIndex(list, edg.to);
            if (index1 == index2)
                continue;
            ut.append(list[index1], list[index2]);
            list[index2].destroy();
            min_cost += edg.weight;
            cout << "An edge was added between " << edg.from << " and " << edg.to <<" with weight " << edg.weight <<endl; 
            // processComplementaryEdge(edg.from, edg.to);
        }  
        cout << "min_cost = " << min_cost << endl;        
    }   
};

int main()
{
    int from, to, weight, data;
    int n;
    cout << "Enter no of vertices: ";
    cin >> n;
    Graph g(n);
    // for (int i = 0; i < n; i++)
    // {
    //     cout << "Enter dest for vertex(-1 to stop) " << i << ": ";
    //     cin >> to;
    //     if (to == -1)
    //         continue;
    //     if (to >= n)
    //     {
    //         cout << "vertex " << to << " was not found in the graph" << endl;
    //         i--;
    //         continue;
    //     }        
    //     cout << "Enter weight: ";
    //     cin >> weight;
    //     g.addEdge(i, to, weight);
    //     g.addEdge(to, i, weight);
    //     i--;
    // }
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);
    g.addEdge(1, 5, 1);
    g.kruskals();
}