#ifndef LINKED_GRAPH
#define LINKED_GRAPH

#include <unordered_map>

#include "graph.h"
#include "vertex.h"
#include "linkedList.h"
#include "arrayQueue.h"

template<class LabelType>
class AdjacencyListGraph : public GraphInterface<LabelType>
{
private:
	int edgeTotal;
	int vertexTotal;

    struct Edge
    {
        //relationships are stored inside the edge which connects verticies
        float edgeWeight;
        vertex<LabelType>* firstVertex;
        vertex<LabelType>* secondVertex;
    };

    LinkedList<Edge> edge_list;
    LinkedList<vertex<LabelType>*> vertex_list;
    unordered_map<LabelType, bool> vertices_visited;
    unordered_map<LabelType, LinkedList<pair<LabelType, float>>> adjacency_list;
public:
    AdjacencyListGraph() : edgeTotal(0), vertexTotal(0) { }

    //Helpers

    vertex<LabelType>* findVertex(LabelType data_to_find) const
    {
        for (int i = 1; i <= edge_list.getLength(); i++) //traverse edge list
        {
            Edge current_edge = edge_list.getEntry(i);
            //find if vertex exsists
            if (current_edge.firstVertex->getData() == data_to_find) { return current_edge.firstVertex; }
            else if (current_edge.secondVertex->getData() == data_to_find) { return current_edge.secondVertex; }
        }

        return nullptr;
    }

    int getEdgeListPos(LabelType start, LabelType end) const //helper function for accessing linkedlist
    {
        vertex<LabelType>* startPtr = findVertex(start);
        vertex<LabelType>* endPtr = findVertex(end);

        for (int i = 1; i <= edge_list.getLength(); i++)
        {
            Edge edge = edge_list.getEntry(i);
            if ((edge.firstVertex == startPtr && edge.secondVertex == endPtr) ||
                (edge.firstVertex == endPtr && edge.secondVertex == startPtr))
            {
                return i;
            }
        }
        return -1; //edge not found
    }

    unordered_map<LabelType, LinkedList<pair<LabelType, float>>> getAdjacencyList()
    {
        adjacency_list.clear(); //ensures adjacency list is updated
        for (int i = 1; i <= vertex_list.getLength(); i++)
        {
            vertex<LabelType>* current_vertex = vertex_list.getEntry(i);
            adjacency_list.insert(make_pair(current_vertex->getData(), current_vertex->getAdjacentVertices()));
        }

        return adjacency_list;
    }

    float getPathDistance(LinkedList<LabelType>& path) const
    {
        float distance = 0;

        for (int i = 1; i < path.getLength(); i++)
        {
            LabelType current_city = path.getEntry(i);
            LabelType next_city = path.getEntry(i + 1);
            distance += getEdgeWeight(current_city, next_city);
        }

        return distance;
    }

    LinkedList<LabelType> getVertexList()
    {
        return vertex_list;
    }

    //Getters

    int getNumVertices() const
    {
        return vertexTotal;
    }

    int getNumEdges() const
    {
        return edgeTotal;
    }

    float getEdgeWeight(LabelType start, LabelType end) const
    {
        int edge_pos = getEdgeListPos(start, end);
        if (edge_pos != -1)
        {
            return edge_list.getEntry(edge_pos).edgeWeight; //edge was found!
        }
        else { return -1; } //no given edge exists
    }

    //Graph Functionality

    bool add(LabelType start, LabelType end, float edgeWeight)
    {
        if (start == end) { return false; } //no loops!

        //check if edge already exists
        int edge_pos = getEdgeListPos(start, end);
        if (edge_pos != -1) //edge was found
        {
            return false;
        }

        vertex<LabelType>* startPtr = findVertex(start);
        vertex<LabelType>* endPtr = findVertex(end);

        if (startPtr == nullptr)
        {
            startPtr = new vertex<LabelType>(start);
            vertex_list.push_back(startPtr);
            vertexTotal++;
        }
        if (endPtr == nullptr)
        {
            endPtr = new vertex<LabelType>(end);
            vertex_list.push_back(endPtr);
            vertexTotal++;
        }
        //initalize new edge
        Edge new_edge = { edgeWeight, startPtr, endPtr };
        edge_list.push_back(new_edge);
        edgeTotal++;
        //set adjacency
        startPtr->setAdjacentVertex(endPtr->getData(), edgeWeight);
        endPtr->setAdjacentVertex(startPtr->getData(), edgeWeight);

        return true;
    }

    bool remove(LabelType start, LabelType end) 
    {
        int edge_pos = getEdgeListPos(start, end);
        if (edge_pos != -1) //edge exists to delete
        {
            //remove edge and adjacency
            Edge edge_struct = edge_list.getEntry(edge_pos);
            edge_struct.firstVertex->removeAdjacentVertex(edge_struct.secondVertex->getData());
            edge_struct.secondVertex->removeAdjacentVertex(edge_struct.firstVertex->getData());
            edge_list.remove(edge_pos);
            edgeTotal--;

            //remove vertices
            vertex<LabelType>* startPtr = findVertex(start);
            vertex<LabelType>* endPtr = findVertex(end);

            if (startPtr == nullptr) 
            { 
                for (int i = 1; i <= vertex_list.getLength(); i++)
                {
                    if (vertex_list.getEntry(i)->getData() == start) 
                    { 
                        vertex_list.remove(i); 
                        vertexTotal--;
                    }
                }
            }
            if (endPtr == nullptr)
            {
                for (int i = 1; i <= vertex_list.getLength(); i++)
                {
                    if (vertex_list.getEntry(i)->getData() == end)
                    {
                        vertex_list.remove(i);
                        vertexTotal--;
                    }
                }
            }

            return true;
        }
        else { return false; }
    }

    //Traversals
    void depthFirstTraversal(LabelType start, void visit(LabelType&))
    {
        depthFirstTraversalHelper(start, visit);
        vertices_visited.clear();
    }

    void depthFirstTraversalHelper(LabelType start, void visit(LabelType&))
    {
        visit(start);
        vertices_visited[start] = true;
        auto temp_adjacency_list = getAdjacencyList();
        for (const auto& adj_vertex : temp_adjacency_list[start])
        {
            if (!vertices_visited[adj_vertex.first])
            {
                depthFirstTraversalHelper(adj_vertex.first, visit);
            }
        }
    }

    void breadthFirstTraversal(LabelType start, void visit(LabelType&))
    {
        breadthFirstTraversalHelper(start, visit);
        vertices_visited.clear();
    }

    void breadthFirstTraversalHelper(LabelType start, void visit(LabelType&))
    {
        ArrayQueue<LabelType> queue;
        auto temp_adjacency_list = getAdjacencyList();

        vertices_visited[start] = true;
        queue.enqueue(start);

        while (!queue.isEmpty())
        {
            LabelType current_vertex = queue.peekFront();
            queue.dequeue();

            visit(current_vertex);

            for (const auto& adj_vertex : temp_adjacency_list[current_vertex])
            {
                if (!vertices_visited[adj_vertex.first])
                {
                    vertices_visited[adj_vertex.first] = true;
                    queue.enqueue(adj_vertex.first);
                }
            }
        }
    }

    ~AdjacencyListGraph() { }
};
#endif

//Graphs represent relationships while trees deal with heirarchical relationships.
//The Internet is a useful example of graphs, aswell as social networks that demonstrate connections between people like friendships.
//The vertex would be a URL and an edge might be a hyperlink towards another website.
//Vertecies store objects, and edges represent the connection.
//It is possible to have disconnected graphs.

//Adjacency matricies can be constructed to store relationships
//A graph is a set of edges and verticies
// G = {V, E}
//Verticies can be stored in an array and then use the position in the array for the adjacency matrix
//Edges are handled through the adjacency matrix