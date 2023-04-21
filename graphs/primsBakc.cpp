#include <dataLibrary_v5.h>

// only insert(), getElementAt(), getNodeAt(), getCount(), getHead() functions from the LinkedList<> class present
// in the above library are used

struct edge
{
    int from, to, weight;
    edge() {}
    edge(int from, int to, int weight) : from(from), to(to), weight(weight) {}
};

struct vertex
{
    int data;
    bool isProcessed;
    int distance;
    int pred;
    LinkedList<edge> list;
};

class Queue
{
private:
    LinkedList<vertex> qList;
public:
    void enqueue(vertex v)
    {
        qList.insert(v);
    }

    sllNode<vertex> *getMin()
    {
        int minIndex = -1, min = 99999;
        for (int i = 1; i < qList.getCount() + 1; i++)
        {
            if (!qList.getElementAt(i).isProcessed && qList.getElementAt(i).distance < min)
            {
                min = qList.getElementAt(i).distance;
                minIndex = i;
            }
        }
        // cout << "Vertex returned: " << qList.getNodeAt(minIndex)->data.data << "\t" << qList.getNodeAt(minIndex)->data.distance << endl;
        qList.getNodeAt(minIndex)->data.isProcessed = true;
        return qList.getNodeAt(minIndex);      
    }

    sllNode<vertex> *find(int data)
    {
        for (int i = 1; i < qList.getCount() + 1; i++)
        {
            if (qList.getElementAt(i).data == data)
                return qList.getNodeAt(i);
        }
        return NULL;
    }

    bool areAllProcessed()
    {
        for (int i = 1; i < qList.getCount() + 1; i++)
        {
            if (!qList.getElementAt(i).isProcessed)
                return false;
        }
        return true;
    }

    int getMstCost()
    {
        int mst_cost = 0;
        for (int i = 1; i < qList.getCount() + 1; i++)
            mst_cost += qList.getElementAt(i).distance;
        return mst_cost;    
    }

    void printRes()
    {
        for (int i = 1; i < qList.getCount() + 1; i++)
        {
            vertex vert = qList.getElementAt(i);
            cout << vert.data << "\t\t" << vert.distance << "\t\t" << vert.pred << endl;
        }
        cout << "MST_COST: " << getMstCost() << endl;
    }
};

class Graph
{
private:
    int count;
    vertex *v;

public:
    Graph(int count)
    {
        this->count = count;
        v = new vertex[count];
    }

    void initialize(int src)
    {
        for (int i = 0; i < count; i++)
        {
            v[i].data = i;
            v[i].distance = 9999;
            v[i].isProcessed = false;
            v[i].pred = -1;
        }
        v[src].distance = 0;
    }

    void addEdge(int from, int to, int weight)
    {
        v[from].list.insert(edge(from, to, weight));
        v[to].list.insert(edge(to, from, weight));
    }

    void printVertexWithEdges()
    {
        for (int i = 0; i < count; i++)
        {
            cout << i << " -----> ";
            for (int k = 1; k < v[i].list.getCount() + 1; k++)
                cout << "(" << v[i].list.getElementAt(k).to << " " << v[i].list.getElementAt(k).weight << ") "; 
            cout << endl;    
        }
    }

    void printRes(int mst_cost)
    {
        // int mst_cost = 0;
        cout << "Data\t\tDistance\tPredecessor" << endl;
        for (int i = 0; i < count; i++)
        {
            cout << v[i].data << "\t\t\t" << v[i].distance << "\t\t\t" << v[i].pred << endl;
            // mst_cost += v[i].distance;
        }
        cout << "MST_COST: " << mst_cost << endl; 
    }

    void prims(int src = 0)
    {
        initialize(src);
        Queue q;
        for (int i = 0; i < count; i++)
            q.enqueue(v[i]);
        printVertexWithEdges();
        while (!q.areAllProcessed())
        {   
            sllNode<vertex> *currVert = q.getMin();
            for (int i = 1; i < currVert->data.list.getCount() + 1; i++)
            {
                sllNode<vertex> *adjVert = q.find(currVert->data.list.getElementAt(i).to);
                if (!adjVert->data.isProcessed && currVert->data.list.getElementAt(i).weight < adjVert->data.distance)
                {
                    adjVert->data.pred = currVert->data.data;
                    adjVert->data.distance = currVert->data.list.getElementAt(i).weight;
                }
            }
        }
        q.printRes();       
    }
};

int main()
{
    Graph g(9);
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
    // int from, to, weight, data;
    // int n;
    // cout << "Enter no of vertices: ";
    // cin >> n;
    // Graph g(n);
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
    //     i--;
    // }
    g.prims();
    return 0;
}