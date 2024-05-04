#ifndef VERTEX
#define VERTEX

#include "linkedList.h"

template <class LabelType>
class vertex
{
private:
	LabelType vertex_data; //data is stored in the vertex
	LinkedList<pair<LabelType, float>> adjacent_vertices;
public:
	vertex(const LabelType& data) : vertex_data(data) { }

	LabelType getData() const
	{
		return vertex_data;
	}

	void setAdjacentVertex(LabelType vertexData, float edgeWeight)
	{
		adjacent_vertices.insert(1, make_pair(vertexData, edgeWeight));
	}

	void removeAdjacentVertex(LabelType vertexData)
	{
		for (int i = 1; i <= adjacent_vertices.getLength(); i++)
		{
			if (adjacent_vertices.getEntry(i).first == vertexData)
			{
				adjacent_vertices.remove(i);
			}
		}
	}

	LinkedList<pair<LabelType, float>> getAdjacentVertices() const
	{
		return adjacent_vertices;
	}

	~vertex() { }
};
#endif