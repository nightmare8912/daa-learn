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
    int data, predecessor, distance, set;
    LinkedList<edge> list;
};

class Graph
{
private:
    vertex *v;
    int count, unprocessed_edges, no_of_edges;

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
            v[i].set = i;
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

    void printTest()
    {
        for (int i = 0; i < count; i++)
        {
            cout << i << " ----> ";
            for (int k = 1; k <= v[i].list.getCount(); k++)
                cout << "(" <<v[i].list.getElementAt(k).to << " " << v[i].list.getElementAt(k).weight << ") ";
            cout << endl;
        }
    }

    void mergeSets(int set1, int set2)
    {
        for (int i = 0; i < count; i++)
        {
            if (v[i].set == set2)
                v[i].set = set1;
        }
    }

    void kruskals(int src = 0)
    {
        initialize(src);
        int min_cost = 0;
        printTest();
        unprocessed_edges = no_of_edges;
        while (unprocessed_edges > 0)
        {
            edge edg = findMin();
            if (v[edg.from].set == v[edg.to].set)
                continue;  
            mergeSets(v[edg.from].set, v[edg.to].set);
            min_cost += edg.weight;
            cout << "An edge was added between " << edg.from << " and " << edg.to <<" with weight " << edg.weight <<endl; 
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
    // g.addEdge(1, 5, 1);
    g.kruskals();
}