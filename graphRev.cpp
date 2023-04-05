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
    // adds the vertex in the queue
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
    // deletes and returns the first vertex from the queue
    vertex *dequeue()
    {
        if (head == NULL)
            return NULL;
        vertex *temp = head;
        head = head->quNext;
        count--;
        return temp;
    }
    // returns true if queue is empty, otheriwise false
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
    //creates and returns a vertex
    vertex *createVertex(char data)
    {
        vertex *vert = new vertex;
        vert->data = data;
        vert->nextVertex = vert->quNext = NULL;
        vert->firstEdge = NULL;
        return vert;
    }
    // checks if the given vertex is already present in the queue or not, return true if present, otherwise false
    bool isPresent(vertex *vert)
    {
        for(vertex *temp = firstVertex; temp != NULL; temp = temp->nextVertex)
        {
            if (temp->data == vert->data)
                return true;
        }
        return false;
    }
    // inserts the vertex in the queue after checking if it is present or not
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
    // finds the vertex with corresponding data values and returns it, returns NULL if not found
    vertex *findVertex(char vert)
    {
        for(vertex *temp = firstVertex; temp != NULL; temp = temp->nextVertex)
        {
            if (temp->data == vert)
                return temp;
        }
        return NULL;
    }
    // creates the edge with given source and destination vertices
    edge *createEdge(vertex *vert1, vertex *vert2)
    {
        edge *edg = new edge;
        edg->start = vert1;
        edg->end = vert2; 
        edg->nextEdge = NULL;
        return edg;
    }
    // adds the edge to the vertex's edge list
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
    // checks if vertices are present, if they are, then it creates and adds the edges to both the vertices
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
    // print vertices along with the vertices they're connected with
    void printVertexWithEdges()
    {
        for (vertex *vert = firstVertex; vert != NULL; vert = vert->nextVertex)
        {
            cout << vert->data << " ----> ";
            if (vert->firstEdge != NULL)
            {
                for(edge *edg = vert->firstEdge; edg != NULL; edg = edg->nextEdge)
                    cout << edg->end->data << ", ";
            }    
            cout << endl;
        }
    }
    // returns the unprocessed vertices after BFS
    vertex *findUnprocessedVertex()
    {
        for (vertex *temp = firstVertex; temp != NULL; temp = temp->nextVertex)
        {
            if (!temp->isProcessed)
                return temp;
        }
        return NULL;
    }
    // performs bfs
    void bfs()
    {
        if (firstVertex == NULL)
        {
            cout << "No vertices present inside the graph!" << endl;
            return;
        }
        vertex *reference = firstVertex;
        for (vertex *temp = firstVertex; temp != NULL; temp = temp->nextVertex)
        {
            temp->isProcessed = false;
            temp->quNext = NULL;
        }
        bfs_start: 
        queue q;   
        q.enqueue(reference);
        reference->isProcessed = true;
        while(!q.isEmpty())
        {
            vertex *currVertex = q.dequeue();
            for (edge *edg = currVertex->firstEdge; edg != NULL; edg = edg->nextEdge)
            {
                if (edg->end->isProcessed == false)
                {
                    q.enqueue(edg->end);
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