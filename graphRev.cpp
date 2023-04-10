#include <iostream>
#include <time.h>
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
            for (temp = head; temp->quNext != NULL; temp = temp->quNext)
                ;
            temp->quNext = vert;
        }
        vert->isProcessed = true;
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
    // returns true if queue is empty, otherwise false
    bool isEmpty()
    {
        if (head == NULL)
            return true;
        return false;
    }
};
class stack
{
public:
    vertex *head;
    int count;
    stack()
    {
        head = NULL;
        count = 0;
    }
    // adds the vertex in the stack
    void push(vertex *vert)
    {
        if (head == NULL)
            head = vert;
        else
        {
            vert->quNext = head;
            head = vert;
        }
        vert->isProcessed = true;
        count++;
    }
    // deletes and returns the first vertex from the stack
    vertex *pop()
    {
        if (head == NULL)
            return NULL;
        vertex *temp = head;
        head = head->quNext;
        count--;
        return temp;
    }
    // returns true if stack is empty, otheriwise false
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
    int count;

    graph()
    {
        firstVertex = NULL;
        count = 0;
    }
    // creates and returns a vertex
    vertex *createVertex(char data)
    {
        vertex *vert = new vertex;
        vert->data = data;
        vert->nextVertex = vert->quNext = NULL;
        vert->firstEdge = NULL;
        return vert;
    }
    // checks if the given vertex is already present in the graph or not, return true if present, otherwise false
    bool isPresent(vertex *vert)
    {
        for (vertex *temp = firstVertex; temp != NULL; temp = temp->nextVertex)
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
            for (temp = firstVertex; temp->nextVertex != NULL; temp = temp->nextVertex)
                ;
            temp->nextVertex = vert;
        }
        count ++;
        cout << "Vertex inserted successfully!" << endl;
    }
    // finds the vertex with corresponding data values and returns it, returns NULL if not found
    vertex *findVertex(char vert)
    {
        for (vertex *temp = firstVertex; temp != NULL; temp = temp->nextVertex)
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
            for (temp = vert->firstEdge; temp->nextEdge != NULL; temp = temp->nextEdge)
                ;
            temp->nextEdge = edg;
        }
    }
    // checks if vertices are present, if they are, then it creates and adds the edges to both the vertices
    void insertUndirectedEdge(char vertex1, char vertex2)
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
    // inserts a directed edge between vertex 1 and vertex 2
    void insertDirectedEdge(char vertex1, char vertex2)
    {
        vertex *src, *dest;
        src = findVertex(vertex1);
        if (src == NULL)
        {
            cout << vertex1 << " was not found in the graph" << endl;
            return;
        }
        dest = findVertex(vertex2);
        if (dest == NULL)
        {
            cout << vertex2 << " was not found in the graph" << endl;
            return;
        }
        edge *edg;
        edg = createEdge(src, dest);
        addEdge(src, edg);
        cout << "Edge has been inserted successfully from " << vertex1 << " to " << vertex2 << endl;
    }
    // prints the vertices along with the vertices they're connected with
    void printVertexWithEdges()
    {
        for (vertex *vert = firstVertex; vert != NULL; vert = vert->nextVertex)
        {
            cout << vert->data << " ----> ";
            for (edge *edg = vert->firstEdge; edg != NULL; edg = edg->nextEdge)
                cout << edg->end->data << ", ";
            cout << endl;
        }
    }

    edge *findEdge(vertex *source, vertex *end)
    {
        for (edge *edg = source->firstEdge; edg != NULL; edg = edg->nextEdge)
        {
            if (edg->end == end)
                return edg;
        } 
        return NULL;
    }

    void removeEdge(vertex *vert, edge *edg)
    {
        if (edg == NULL)
            return;
        if (edg == vert->firstEdge)
        {
            delete vert->firstEdge;
            vert->firstEdge = NULL;
        }
            
        else
        {
            edge *temp;
            for (temp = vert->firstEdge; temp->nextEdge->nextEdge != NULL; temp = temp->nextEdge)
                ;
            swap(temp->nextEdge->start, edg->start);
            swap(temp->nextEdge->end, edg->end);
            delete temp->nextEdge;
            temp->nextEdge = NULL;  
        }    
    }

    void deleteEdge(char vertex1, char vertex2)
    {
        vertex *vert1, *vert2;
        vert1 = findVertex(vertex1);
        if (vert1 == NULL)
        {
            cout << vertex1 << " was not found in the graph!" << endl;
            return;
        }
        vert2 = findVertex(vertex2);
        if (vert2 == NULL)
        {
            cout << vertex2 << " was not found in the graph!" << endl;
            return;
        }

        edge *edg1, *edg2;
        edg1 = findEdge(vert1, vert2);
        edg2 = findEdge(vert2, vert1);
        if (edg1 == NULL && edg2 == NULL)
        {
            cout << "No edge exists between " << vertex1 << " and " << vertex2 << endl;
            return;
        }
        if (edg1 != NULL)
            removeEdge(vert1, edg1);
        if (edg2 != NULL)
            removeEdge(vert2, edg2);     
        cout << "Edge between " << vertex1 << " and " << vertex2 << " was removed!" << endl;
    }

    void deleteEdge(vertex *vert)
    {
        for (vertex *temp = firstVertex; temp != NULL; temp = temp->nextVertex)
            removeEdge(temp, findEdge(temp, vert));
        
    }

    void destroyAllEdges(edge *edg)
    {
        if (edg == NULL)
            return;
        destroyAllEdges(edg->nextEdge);
        delete edg; 
    }

    void removeVertex(vertex *vert)
    {
        destroyAllEdges(vert->firstEdge);
        deleteEdge(vert);
        if (vert == firstVertex)
        {
            firstVertex = firstVertex->nextVertex;
            delete vert; 
        } 
        else
        {
            vertex *temp;
            for (temp = firstVertex; temp->nextVertex->nextVertex != NULL; temp = temp->nextVertex)
                ;
            swap(temp->nextVertex->data, vert->data);
            swap(temp->nextVertex->firstEdge, vert->firstEdge);
            delete temp->nextVertex;
            temp->nextVertex = NULL;
        } 
    }

    void deleteVertex(char vertex1)
    {
        vertex *vert;
        vert = findVertex(vertex1);
        if (vert == NULL)
        {
            cout << vertex1 << " is not in the graph!" << endl;
            return;
        }
        removeVertex(vert);
        cout << vertex1 << " has been removed from the graph!" << endl;
    }

    // returns the unprocessed vertices after BFS/DFS
    vertex *findUnprocessedVertex()
    {
        for (vertex *temp = firstVertex; temp != NULL; temp = temp->nextVertex)
        {
            if (!temp->isProcessed)
                return temp;
        }
        return NULL;
    }

    void reset()
    {
        for (vertex *temp = firstVertex; temp != NULL; temp = temp->nextVertex)
        {
            temp->isProcessed = false;
            temp->quNext = NULL;
        }
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
        reset();
        queue q;
    bfs_start:
        q.enqueue(reference);
        while (!q.isEmpty())
        {
            vertex *currVertex = q.dequeue();
            for (edge *edg = currVertex->firstEdge; edg != NULL; edg = edg->nextEdge)
            {
                if (!edg->end->isProcessed)
                    q.enqueue(edg->end);
            }
            cout << currVertex->data << " ";
        }
        reference = findUnprocessedVertex();
        if (reference != NULL)
            goto bfs_start;
        cout << endl;
    }

    bool isEnd(vertex *vert)
    {
        for (edge *edg = vert->firstEdge; edg != NULL; edg = edg->nextEdge)
        {
            if (!edg->end->isProcessed)
                return false;
        }
        return true;
    }

    void dfs()
    {
        if (firstVertex == NULL)
        {
            cout << "No vertices present inside the graph!" << endl;
            return;
        }
        reset();
        stack s;
        vertex *currVertex = firstVertex;
    dfs_start:
        s.push(currVertex);
        cout << currVertex->data << " ";
    back_track:
        while (!isEnd(currVertex))
        {
            for (edge *edg = currVertex->firstEdge; edg != NULL; edg = edg->nextEdge)
            {
                if (!edg->end->isProcessed)
                {
                    currVertex = edg->end;
                    break;
                }
            }
            s.push(currVertex);
            cout << currVertex->data << " ";
        }

        if (!s.isEmpty())
        {
            currVertex = s.pop();
            goto back_track;
        }

        currVertex = findUnprocessedVertex();
        if (currVertex != NULL)
            goto dfs_start;
        cout << endl;
    }

    void dfsVisit(vertex *currVertex)
    {
        cout << currVertex->data << " ";
        currVertex->isProcessed = true;

        for (edge *edg = currVertex->firstEdge; edg != NULL; edg = edg->nextEdge)
        {
            if (!edg->end->isProcessed)
                dfsVisit(edg->end);
        }
    }

    void recDFS()
    {
        reset();
        vertex *reference = firstVertex;
    dfs_start:
        dfsVisit(reference);
        reference = findUnprocessedVertex();
        if (reference != NULL)
            goto dfs_start;
        cout << endl;
    }

    bool recCheckCycle(vertex *reference, vertex *currVertex, int visited_vertices = 0)
    {
        if (visited_vertices > count)
            return false;
        if (currVertex == reference)
            return true;
        for (edge *edg = currVertex->firstEdge; edg != NULL; edg = edg->nextEdge)
        {
            if (recCheckCycle(reference, edg->end, visited_vertices + 1))
            {
                cout << currVertex->data << " ";
                break;
            }
        }
    }

    void checkCycle()
    {
        int no_of_cycles = 0;
        for (vertex *reference = firstVertex; reference != NULL; reference = reference->nextVertex)
        {
            for (edge *edg = reference->firstEdge; edg != NULL; edg = edg->nextEdge)
            {
                if (recCheckCycle(reference, edg->end))
                {
                    cout << reference->data << endl;
                    no_of_cycles++;
                }
            } 
        }
        if (no_of_cycles == 0)
            cout << "No cycles found" << endl;
        else
            cout << "No of cycles: " << no_of_cycles << endl;
    }
};
char getAlphabet()
{
    return (rand() % 25 + 65);
}
int getRand()
{
    return rand() % 8;
}
int main()
{
    int opt = -1;
    char data;
    char vertex1, vertex2;
    srand((long int)clock());
    graph g;
    long int speed = 0;
    while (opt != 11)
    {
        speed ++;
        if (speed % 100000 != 0)
            continue;
        if (speed > 100000)
            speed = 0;  
        cout << "1-Insert vertex, 2-Insert Undirected Edge, 3-Insert Directed Edge, 4-BFS, \n5-Rec-DFS, 6-DFS, 7-Print Vertices with edges, 8-Check Cycles, 9-Delete Edge, 10-Delete Vertex, 11-Exit: ";
        // cin >> opt;
        opt = getRand();  
        switch (opt)
        {
        case 1:
            cout << "Enter vertex: ";
            // cin >> data;
            data = getAlphabet();
            g.insertVertex(g.createVertex(data));
            break;
        case 2:
            cout << "Enter the vertices: ";
            // cin >> vertex1 >> vertex2;
            vertex1 = getAlphabet();
            vertex2 = getAlphabet();
            g.insertUndirectedEdge(vertex1, vertex2);
            break;
        case 3:
            cout << "Enter source and destination vertices: ";
            // cin >> vertex1 >> vertex2;
            vertex1 = getAlphabet();
            vertex2 = getAlphabet();
            g.insertDirectedEdge(vertex1, vertex2);
            break;
        case 4:
            g.bfs();
            break;
        case 5:
            g.recDFS();
            break;
        case 6:
            g.dfs();
            break;
        case 7:
            g.printVertexWithEdges();
            break;
        case 8:
            g.checkCycle();
            break;
        case 9:
            cout << "Enter the vertices: ";
            // cin >> vertex1 >> vertex2;
            vertex1 = getAlphabet();
            vertex2 = getAlphabet();
            g.deleteEdge(vertex1, vertex2);
            break;
        case 10:
            cout << "Enter vertex: ";
            // cin >> data;
            data = getAlphabet();
            g.deleteVertex(data);
            break;    
        case 11:
            cout << "Exited" << endl;
            break;
        default:
            cout << "Invalid option" << endl;
            break;
        }
    }
}