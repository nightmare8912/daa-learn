#include <dataLibrary_v5.h>

struct edge
{
    int from, to;
    edge() {}
    edge(int from, int to) : from(from), to(to) {}
};

struct vertex
{
    int data;
    int discoveredTime, finishTime;
    int pred;
    string color;
    LinkedList<edge> list;
};

class Stack
{
private:
    LinkedList<int> list;

public:
    void push(int v)
    {
        list.insertFront(v);
    }

    int pop()
    {
        return list.removeFront()->data;
    }

    bool isEmpty()
    {
        return list.getCount() == 0;
    }
};

class Graph
{
private:
    vertex *v;
    int count;

public:
    Graph(int count)
    {
        this->count = count;
        v = new vertex[count];
    }

    void addEdge(int from, int to)
    {
        v[from].list.insert(edge(from, to));
    }

    void initialize()
    {
        for (int i = 0; i < count; i++)
        {
            v[i].color = "WHITE";
            v[i].data = i;
            v[i].discoveredTime = v[i].finishTime = 0;
            v[i].pred = -1;
        }
    }

    void printVertexWithEdges()
    {
        for (int i = 0; i < count; i++)
        {
            cout << i << " -----> ";
            for (int k = 1; k < v[i].list.getCount() + 1; k++)
                cout << v[i].list.getElementAt(k).to << " "; 
            cout << endl;    
        }
    }

    void dfsVisit(Stack&s, int currVert, int &time)
    {
        v[currVert].discoveredTime = ++time;
        v[currVert].color = "GRAY";
        cout << v[currVert].data << " ";
        for (int i = 1; i < v[currVert].list.getCount() + 1; i++)
        {
            if (v[v[currVert].list.getElementAt(i).to].color == "WHITE")
            {
                v[v[currVert].list.getElementAt(i).to].pred = currVert;
                dfsVisit(s, v[currVert].list.getElementAt(i).to, time);
            }
        }
        v[currVert].color = "BLACK";
        s.push(currVert);
        v[currVert].finishTime = ++time;
    }

    void dfs(Stack &s)
    {
        initialize();
        int time = 0;
        cout << "DFS: ";
        for (int i = 0; i < count; i++)
        {
            if (v[i].color == "WHITE")
                dfsVisit(s, i, time);
        }
    }

    void topologicalSort()
    {
        Stack s;
        dfs(s);
        cout << "\nTopological Sort: ";
        while (!s.isEmpty())
            cout << s.pop() << " ";
    }
};

int main()
{
    int from, to, data;
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
    //     g.addEdge(i, to);
    //     i--;
    // }
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);
    g.printVertexWithEdges();
    g.topologicalSort();
}