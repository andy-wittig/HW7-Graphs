#ifndef LINKED_GRAPH
#define LINKED_GRAPH

#include "graph.h"
#include "vertex.h"
#include "linkedList.h"

template<class LabelType>
class AdjacencyListGraph : public GraphInterface<LabelType>
{
private:
	int edgeTotal;
	int vertexTotal;

    struct Edge
    {
        //relationships are stored inside the edge which connects verticies
        int edgeWeight;
        vertex<LabelType>* firstVertex;
        vertex<LabelType>* secondVertex;
    };

    LinkedList<Edge> edge_list;
public:
    AdjacencyListGraph() : edgeTotal(0), vertexTotal(0) { }

    //Helpers

    vertex<LabelType>* visit(LabelType data_to_find) const
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

    int getEdgeListPos(LabelType start, LabelType end) const
    {
        vertex<LabelType>* startPtr = visit(start);
        vertex<LabelType>* endPtr = visit(end);

        for (int i = 1; i <= edge_list.getLength(); i++)
        {
            Edge edge = edge_list.getEntry(i);
            if ((edge.firstVertex == startPtr && edge.secondVertex == endPtr) ||
                (edge.firstVertex == endPtr && edge.secondVertex == startPtr))
            {
                return i;
            }
        }
        return -1;
    }

    void printAdjacentEdgeList()
    {
        for (int i = 1; i <= edge_list.getLength(); i++)
        {
            Edge edge = edge_list.getEntry(i);
            edge.firstVertex->printAdjacentList();
            edge.secondVertex->printAdjacentList();
        }
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

    int getEdgeWeight(LabelType start, LabelType end) const
    {
        int edge_pos = getEdgeListPos(start, end);
        if (edge_pos != -1)
        {
            return edge_list.getEntry(edge_pos).edgeWeight; //edge was found!
        }
        else { return -1; } //no given edge exists
    }

    //Graph Functionality

    bool add(LabelType start, LabelType end, int edgeWeight)
    {
        if (start == end) { return false; } //no loops allowed!

        vertex<LabelType>* startPtr = visit(start);
        vertex<LabelType>* endPtr = visit(end);

        if (startPtr == nullptr)
        {
            startPtr = new vertex<LabelType>(start);
            vertexTotal++;
        }
        if (endPtr == nullptr)
        {
            endPtr = new vertex<LabelType>(end);
            vertexTotal++;
        }

        //check if edge already exists
        int edge_pos = getEdgeListPos(start, end);
        if (edge_pos != -1)
        {
                return false; //edge already exists!
        }

        Edge newEdge = { edgeWeight, startPtr, endPtr };
        edge_list.insert(1, newEdge);
        startPtr->addAdjacentVertex(endPtr);
        endPtr->addAdjacentVertex(startPtr);
        edgeTotal++;

        return true;
    }

    bool remove(LabelType start, LabelType end) 
    {
        int edge_pos = getEdgeListPos(start, end);
        if (edge_pos != -1) //edge exists to delete
        {
            Edge edge_struct = edge_list.getEntry(edge_pos);
            edge_struct.firstVertex->removeAdjacentVertex(edge_struct.secondVertex);
            edge_struct.secondVertex->removeAdjacentVertex(edge_struct.firstVertex);
            edge_list.remove(edge_pos);

            //check to see how many vertices to remove
            vertex<LabelType>* startPtr = visit(start);
            vertex<LabelType>* endPtr = visit(end);
            if (startPtr == nullptr) { vertexTotal--; }
            if (endPtr == nullptr) { vertexTotal--; }

            edgeTotal--;
            return true;
        }
        else { return false; }
    }

    //Traversals

    void depthFirstTraversal(LabelType start, void visit(LabelType&))
    {

    }
    void breadthFirstTraversal(LabelType start, void visit(LabelType&))
    {

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