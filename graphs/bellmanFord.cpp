#include <dataLibrary_v5.h>

struct edge
{
    int from, to;
    int weight;
};

struct vertex
{
    int data, predecessor;
    LinkedList<edge> list;
    int distance;
};

class Graph
{
public:
    vertex *vertices;
    int count;


    Graph(int count)
    {
        vertices = new vertex[count];
        this->count = count;
    }

    void addEdge(int from, int to, int weight)
    {
        edge newedge;
        newedge.from = from;
        newedge.to = to;
        newedge.weight = weight;
        vertices[from].list.insert(newedge);
    }

    void intializeSingleSource(int src)
    {
        for (int i = 0; i < count; i++)
        {
            vertices[i].data = i;
            vertices[i].predecessor = -1;
            vertices[i].distance = 9999;
        }
        vertices[src].distance = 0;
    }

    bool relax(int vert, int predecessor)
    {
        sllNode<edge> *temp;
        int weight;
        for (temp = vertices[predecessor].list.getHead(); temp != NULL; temp = temp->next)
        {
            if (temp->data.to == vert)
            {
                weight = temp->data.weight;
                break;
            }
        }
        if (temp == NULL)
            return false;
        if (vertices[vert].distance > vertices[predecessor].distance + weight)
        {
            vertices[vert].distance = vertices[predecessor].distance + weight;
            vertices[vert].predecessor = predecessor;
            return true;
        }
        return false;    
    }

    // int getNumberOfEdges()
    // {
    //     int no_of_edges = 0;
    //     for (int i = 0; i < count; i++)
    //         no_of_edges += vertices[i].list.getCount();
    //     return no_of_edges;    
    // }

    bool bellmanFord(int src = 0)
    {
        intializeSingleSource(src);
        // int no_of_edges = getNumberOfEdges();
        for (int i = 0; i < count; i++)
        {
            for (int j = 0; j < count; j++)
                relax(j, i);
        }

        for (int i = 0; i < count - 1; i++)
        {
            for (int j = 0; j < count; j++)
            {
                if (relax(j, i))
                    return false;
            }
        }

        return true;
    }

    void showGraph()
    {
        cout << "Bellman ford: \n";
        for (int i = 0; i < count; i++)
            cout << "Data: " <<vertices[i].data << "\tDistance: " << vertices[i].distance << "\tPredecessor: " << vertices[i].predecessor << endl;
        
    }
};
// int getNum()
// {
//     return (rand() % 10);
// }
// char getAlp()
// {
//     if (rand() % 2 == 0)
//         return 'y';
//     else
//         return 'n';
// }
int main()
{
    int n;
    cout << "Enter no of vertices: ";
    cin >> n;
    int to, weight;
    Graph g(n);
    char conts;
    // srand((long int)clock());
    for (int i = 0; i < n; i++)
    {
    re:
        cout << "Enter edges(dest) for vertex " << i  << ": ";
        cin >> to;
        // to = getNum();
        // cout << to << endl;
        if (i == to)
            goto re;    
        cout << "Enter the weight of the edge from " << i << " to " << to << ": ";
        cin >> weight;
        // weight = getNum();
        // cout << weight << endl;
        g.addEdge(i, to, weight); 
        cout << "Continue? (y/n): ";
        cin >> conts;
        // conts = getAlp();
        // cout << conts << endl;
        if (conts == 'y')
            goto re;
    }

    // for (int i = 0; i < n; i++)
    // {
    //     g.vertices[i].data = i;
    //     cout << g.vertices[i].data << " ------> ";
    //     for (sllNode<edge> *temp = g.vertices[i].list.getHead(); temp != NULL; temp = temp->next)
    //         cout << "(" <<temp->data.to << ", " << temp->data.weight << ") ";
    //     cout << endl;    
    // }
    g.bellmanFord();
    // if (g.bellmanFord())
        g.showGraph();
    // else
        cout << "Negative weight cycle exists!" << endl;    
}