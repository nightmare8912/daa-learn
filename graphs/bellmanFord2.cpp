#include <dataLibrary_v5.h>

// This code is not working yet

struct edge
{
    int from, to, weight;
    bool isProcessed;
    edge() : from(-1), to(-1), weight(9999), isProcessed(false) {}
    edge(int from, int to, int weight) : from(from), to(to), weight(weight), isProcessed(false) {}
};

struct vertex
{
    int data, pred, dist;
    LinkedList<edge> list;
};

class Graph
{
private:
    vertex *vertices;
    int count, no_of_edges;

public:
    Graph(int count)
    {
        vertices = new vertex[count];
        this->count = count;
        no_of_edges = 0;
    }

    void addEdge(int from, int to, int weight)
    {
        edge newEdge(from, to, weight);
        vertices[from].list.insert(newEdge);
        no_of_edges++;
    }

    void initializeVertices()
    {
        for (int i = 0; i < count; i++)
            vertices[i].data = i;
    }
private:
    void printList(LinkedList<edge> list)
    {
        for (sllNode<edge> *temp = list.getHead(); temp != NULL; temp = temp->next)
            cout << "From: " <<temp->data.from << "\tTo: " << temp->data.to << "\tWeight: " << temp->data.weight << endl;
    }

    void intializeSingleSource(int ref)
    {
        for (int i = 0; i < count; i++)
        {
            vertices[i].dist = 9999;
            vertices[i].pred = -1;
        }
        vertices[ref].dist = 0;
    }

    bool relax(int src, int dest)
    {
        sllNode<edge> *temp;
        for (temp = vertices[src].list.getHead(); temp != NULL; temp = temp->next)
        {
            if (temp->data.to == dest)
                break;
        }

        if (temp == NULL)
            return false;

        int currVal = vertices[dest].dist;
        vertices[dest].dist = min(vertices[dest].dist, vertices[src].dist + temp->data.weight);
        if (currVal != vertices[dest].dist)
        {
            vertices[dest].pred = src;
            return true;
        }    
        return false;
    }

    void resetEdges()
    {
        for (int i = 0; i < count ; i++)
        {
            for (sllNode<edge> *temp = vertices[i].list.getHead(); temp != NULL; temp = temp->next)
                temp->data.isProcessed = false;
        }
    }

    edge findNextEdge(int i)
    {
        sllNode<edge> *temp;
        for (temp = vertices[i].list.getHead(); temp != NULL; temp = temp->next)
        {
            if (!temp->data.isProcessed)
                return temp->data;
        }
        edge empty;
        return empty;
    }
public:
    void print()
    {
        for (int i = 0; i < count; i++)
        {
            cout << vertices[i].data << endl;
            printList(vertices[i].list);
        }
    }

    void printGraph()
    {
        cout << "Data\t\tPredecessor\t\tMinWt" << endl;
        for (int i = 0; i < count; i++)
            cout << vertices[i].data << "\t\t\t" << vertices[i].pred << "\t\t\t\t" << vertices[i].dist << endl;
    }

    bool bellmanFord(int ref = 0)
    {
        intializeSingleSource(ref);
        for (int i = 0; i < count - 1; i++)
        {
            resetEdges();
            for (int j = 0; j < count; j--)
            {
                int k = vertices[i].list.getCount();
                while (true)
                {
                    edge edg = findNextEdge(j);
                    edg.isProcessed = true;
                    if (edg.from == -1)
                        break;
                    relax(j, edg.to);
                }
            }  
        }

        resetEdges();
        for (int j = 0; j < count; j--)
        {
            while (true)
            {
                edge edg = findNextEdge(j);
                if (edg.from == -1)
                    break;
                if (relax(j, edg.to))
                    return false;
                edg.isProcessed = true;    
            }
        }
        return true; 
    }
};

int main()
{
    int from, to, weight, data;
    int n;
    cout << "Enter no of vertices: ";
    cin >> n;
    Graph g(n);
    g.initializeVertices();
    for (int i = 0; i < n; i++)
    {
        cout << "Enter dest for vertex " << i << ": ";
        cin >> to;
        if (to == -1)
            continue;
        cout << "Enter weight: ";
        cin >> weight;
        g.addEdge(i, to, weight);
        i--;
    }
    g.print();
    if (g.bellmanFord())
        cout << "success" << endl;
    else
        cout << "failure" << endl;
    g.printGraph();        
}