#ifndef GRAPH_INTERFACE
#define GRAPH_INTERFACE


template<class LabelType> //datatype of vertex
class GraphInterface 
{
public:
    virtual int getNumVertices() const = 0;
    virtual int getNumEdges() const = 0;
    virtual bool add(LabelType start, LabelType end, float edgeWeight) = 0;
    virtual bool remove(LabelType start, LabelType end) = 0;
    virtual float getEdgeWeight(LabelType start, LabelType end) const = 0;
    virtual void depthFirstTraversal(LabelType start, void visit(LabelType&)) = 0;
    virtual void breadthFirstTraversal(LabelType start, void visit(LabelType&)) = 0;
    virtual ~GraphInterface() { };
};
#endif