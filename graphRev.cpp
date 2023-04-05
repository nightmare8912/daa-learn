#include <iostream>
using namespace std;
struct edge;
struct vertex
{
    char data;
    bool isProcessed;
    vertex *nextVertex, *quNext;
    edge *firstEdge;
};
struct edge
{
    vertex *start, *end;
    edge *nextEdge;
};
class queue
{
    public:
    vertex *head;
    int count;
    queue()
    {
        head = NULL;
        count = 0;
    }

    void enqueue(vertex *vert)
    {
        if (head == NULL)
            head = vert;
        else
        {
            vertex *temp;
            for (temp = head; temp->quNext != NULL; temp = temp->quNext);
            temp->quNext = vert;
        } 
        count++;   
    }

    vertex *dequeue()
    {
        if (head == NULL)
            return NULL;
        vertex *temp = head;
        head = head->quNext;
        return temp;
        count--;
    }

    bool isEmpty()
    {
        if (head == NULL)
            return true;
        return false;    
    }
};
class graph
{
    public:
    vertex *firstVertex;
    
    graph()
    {
        firstVertex = NULL;
    }

    vertex *createVertex(char data)
    {
        vertex *vert = new vertex;
        vert->data = data;
        vert->nextVertex = vert->quNext = NULL;
        vert->firstEdge = NULL;
        return vert;
    }

    bool isPresent(vertex *vert)
    {
        for(vertex *temp = firstVertex; temp != NULL; temp = temp->nextVertex)
        {
            if (temp->data == vert->data)
                return true;
        }
        return false;
    }

    void insertVertex(vertex *vert)
    {
        if (isPresent(vert))
        {
            cout << "Vertex already present!" << endl;
            delete vert;
            return;
        }
        if (firstVertex == NULL)
            firstVertex = vert;
        else
        {
            vertex *temp;
            for (temp = firstVertex; temp->nextVertex != NULL; temp = temp->nextVertex);
            temp->nextVertex = vert;
        }
        cout << "Vertex inserted successfully!" << endl;    
    }

    vertex *findVertex(char vert)
    {
        for(vertex *temp = firstVertex; temp != NULL; temp = temp->nextVertex)
        {
            if (temp->data == vert)
                return temp;
        }
        return NULL;
    }

    edge *createEdge(vertex *vert1, vertex *vert2)
    {
        edge *edg = new edge;
        edg->start = vert1;
        edg->end = vert2; 
        edg->nextEdge = NULL;
        return edg;
    }

    void addEdge(vertex *vert, edge *edg)
    {
        if (vert->firstEdge == NULL)
            vert->firstEdge = edg;
        else
        {
            edge *temp;
            for (temp = vert->firstEdge; temp->nextEdge != NULL; temp = temp->nextEdge);
            temp->nextEdge = edg;
        }
    }

    void insertEdge(char vertex1, char vertex2)
    {
        vertex *vert1, *vert2;
        vert1 = findVertex(vertex1); 
        if (vert1 == NULL)
        {
            cout << vertex1 << " was not found in the graph" << endl;
            return;
        }
        vert2 = findVertex(vertex2);
        if (vert2 == NULL)
        {
            cout << vertex2 << " was not found in the graph" << endl;
            return;
        }

        edge *edg1, *edg2;
        edg1 = createEdge(vert1, vert2);
        addEdge(vert1, edg1);
        edg2 = createEdge(vert2, vert1);
        addEdge(vert2, edg2);
        cout << "Edge has been inserted successfully between " << vertex1 << " and " << vertex2 << endl;
    }

    void printVertexWithEdges()
    {
        for (vertex *vert = firstVertex; vert != NULL; vert = vert->nextVertex)
        {
            cout << vert->data << "---->";
            if (vert->firstEdge == NULL)
                cout << endl;
            else
            {
                for(edge *edg = vert->firstEdge; edg != NULL; edg = edg->nextEdge)
                    cout << edg->end->data << ", ";
            }    
            cout << endl;
        }
    }

    vertex *findUnprocessedVertex()
    {
        for (vertex *temp = firstVertex; temp != NULL; temp = temp->nextVertex)
        {
            if (!temp->isProcessed)
                return temp;
        }
        return NULL;
    }

    void bfs()
    {
        if (firstVertex == NULL)
        {
            cout << "No vertices present inside the graph!" << endl;
            return;
        }
        queue q;
        vertex *reference = firstVertex;
        // cout << "hi";
        for (vertex *temp = firstVertex; temp != NULL; temp = temp->nextVertex)
            temp->isProcessed = false;

        bfs_start:    
        q.enqueue(reference);
        reference->isProcessed = true;
        while(!q.isEmpty())
        {
            vertex *currVertex = q.dequeue();
            // cout << endl <<"hi" << endl;
            // cout << currVertex->data << endl;
            for (edge *edg = currVertex->firstEdge; edg != NULL; edg = edg->nextEdge)
            {
                if (edg->end->isProcessed == false)
                {
                    q.enqueue(edg->end);
                    // cout << edg->end->data << " has been inserted in queue" << endl;
                    edg->end->isProcessed = true;
                }    
            }
            cout << currVertex->data << " ";
        }
        reference = findUnprocessedVertex();
        if(reference != NULL)
            goto bfs_start;    
        cout << endl;
    }

    void normalPrint()
    {
        for (vertex *temp = firstVertex; temp != NULL; temp = temp->nextVertex)
            cout << temp->data << " ";
        cout << endl;    
    }
};
int main()
{
    int opt = -1;
    char data;
    char vertex1, vertex2;
    graph g;
    while(opt != 6)
    {
        cout << "1-Insert vertex, 2-Insert Edge, 3-Normal Traversal, 4-BFS, 5-Print Vertices with edges, 6-Exit: ";
        cin >> opt;
        switch(opt)
        {
            case 1: cout << "Enter vertex: ";
                    cin >> data;
                    g.insertVertex(g.createVertex(data));
                    break;
            case 2: cout << "Enter the vertices: ";
                    cin >> vertex1 >> vertex2;
                    g.insertEdge(vertex1, vertex2);
                    break;
            case 3: g.normalPrint();
                    break;
            case 4: g.bfs();
                    break;        
            case 5: g.printVertexWithEdges();
                    break;        
            case 6: cout << "Exited" << endl;
                    break;
            default:cout << "Invalid option" << endl;
                    break;                             
        }
    }
}