#ifndef VERTEX
#define VERTEX

#include "linkedList.h"

template <class LabelType>
class vertex
{
private:
	LabelType vertexData; //data is stored in the vertex
	LinkedList<vertex<LabelType>*> vertexAdjacencyList;
public:
	vertex(const LabelType& data) : vertexData(data) { }

	LabelType getData() const
	{
		return vertexData;
	}

	void addAdjacentVertex(vertex<LabelType>* vertexPtr)
	{
		vertexAdjacencyList.insert(1, vertexPtr);
	}

	void removeAdjacentVertex(vertex<LabelType>* vertexPtr)
	{
		for (int i = 1; i <= vertexAdjacencyList.getLength(); i++)
		{
			if (vertexAdjacencyList.getEntry(i) == vertexPtr)
			{
				vertexAdjacencyList.remove(i);
			}
		}
	}

	void printAdjacentList()
	{
		cout << vertexData << ": ";
		for (int i = 1; i <= vertexAdjacencyList.getLength(); i++)
		{
			string adjacent_vertex = vertexAdjacencyList.getEntry(i)->getData();
			cout << adjacent_vertex << " ";
		}
		cout << endl;
	}

	~vertex() { }
};
#endif