#include <iostream>
#include <string>

using namespace std;

#include "adjacencyListGraph.h"
#include "priorityQueue.h"

void addToGraph(GraphInterface<string>&);
void removeFromGraph(GraphInterface<string>&);
void getGraphEdgeWeight(GraphInterface<string>&);
void getAdjacentEdgeList(AdjacencyListGraph<string>&);

int getChoice();

int main()
{
	AdjacencyListGraph<string> my_graph;
	PriorityQueue<int> my_priority_queue;
	int menu_choice;
	do
	{
		menu_choice = getChoice();
		switch (menu_choice)
		{
		case 1:
			addToGraph(my_graph);
			break;
		case 2:
			removeFromGraph(my_graph);
			break;
		case 3:
			getGraphEdgeWeight(my_graph);
			break;
		case 4:
			getAdjacentEdgeList(my_graph);
			break;
		case 0:
			break;
		default:
			cout << endl << "Invalid option..." << endl;
			break;
		}
	} while (menu_choice != 0);
	return 0;
};

int getChoice()
{
	int input_choice;

	cout << "\n--------------------" << endl;
	cout << "0. Exit" << endl;
	cout << "1. Add edge to graph." << endl;
	cout << "2. Remove edge from graph." << endl;
	cout << "3. Get edge weight." << endl;
	cout << "4. Get adjacency list." << endl;
	cout << "--------------------" << endl;

	cin >> input_choice;
	return input_choice;
}

void addToGraph(GraphInterface<string>& graph)
{
	string start_vertex;
	string end_vertex;
	int edge_weight;

	cout << "Please enter the starting vertex:" << endl;
	cin >> start_vertex;
	cout << "Please enter the ending vertex:" << endl;
	cin >> end_vertex;
	cout << "Please enter the edge weight:" << endl;
	cin >> edge_weight;

	bool add_success;
	add_success = graph.add(start_vertex, end_vertex, edge_weight);
	if (add_success)
	{
		cout << "The edge from (" << start_vertex << ") to (" << end_vertex << ") of weight: " << edge_weight << ", was added." << endl;
		cout << "Vertex total: " << graph.getNumVertices() << endl;
		cout << "Edge total: " << graph.getNumEdges() << endl;
	}
	else { cout << "Could not add edge!" << endl; }
}

void removeFromGraph(GraphInterface<string>& graph)
{
	string start_vertex;
	string end_vertex;

	cout << "Please enter the starting vertex:" << endl;
	cin >> start_vertex;
	cout << "Please enter the ending vertex:" << endl;
	cin >> end_vertex;

	bool can_remove = graph.remove(start_vertex, end_vertex);
	if (can_remove)
	{
		cout << "Removed the edge from the graph." << endl;
		cout << "Vertex total: " << graph.getNumVertices() << endl;
		cout << "Edge total: " << graph.getNumEdges() << endl;
	}
	else { cout << "The specified edge doesn't exist to remove"; }
}

void getGraphEdgeWeight(GraphInterface<string>& graph)
{
	string start_vertex;
	string end_vertex;

	cout << "Please enter the starting vertex:" << endl;
	cin >> start_vertex;
	cout << "Please enter the ending vertex:" << endl;
	cin >> end_vertex;

	int edge_weight = graph.getEdgeWeight(start_vertex, end_vertex);
	if (edge_weight != -1) { cout << "The edge's weight is: " << edge_weight << endl; }
	else { cout << "That edge doesn't exist!"; }
}

void getAdjacentEdgeList(AdjacencyListGraph<string>& graph)
{
	graph.printAdjacentEdgeList();
}