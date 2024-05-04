#include <iostream>
#include <string>

using namespace std;

#include "adjacencyListGraph.h"
#include "priorityQueue.h"
#include <algorithm>

void addToGraph(GraphInterface<string>&);
void removeFromGraph(GraphInterface<string>&);
void getGraphEdgeWeight(GraphInterface<string>&);
void runDijkstraSimulation();

int getChoice();

int main()
{
	AdjacencyListGraph<string> my_graph;

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
			runDijkstraSimulation();
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
	cout << "4. Run Djikstra's algorithm salesman simulation." << endl;
	cout << "--------------------" << endl;

	cin >> input_choice;
	return input_choice;
}

void runDijkstraSimulation()
{
	AdjacencyListGraph<string> city_graph;

	//initalize graph (distance in miles to city divided by 40mpg to give gallons)
	city_graph.add("RNO", "SFO", 5.45);
	city_graph.add("RNO", "SLC", 12.95);
	city_graph.add("RNO", "SEA", 17.6);
	city_graph.add("RNO", "LAS", 10.975);

	city_graph.add("SFO", "RNO", 5.45);
	city_graph.add("SFO", "SLC", 18.4);
	city_graph.add("SFO", "SEA", 20.2);
	city_graph.add("SFO", "LAS", 14.225);

	city_graph.add("SLC", "SFO", 18.4);
	city_graph.add("SLC", "RNO", 12.95);
	city_graph.add("SLC", "SEA", 20.725);
	city_graph.add("SLC", "LAS", 10.525);

	city_graph.add("SEA", "SFO", 20.2);
	city_graph.add("SEA", "SLC", 20.725);
	city_graph.add("SEA", "RNO", 17.6);
	city_graph.add("SEA", "LAS", 27.825);

	city_graph.add("LAS", "SFO", 14.225);
	city_graph.add("LAS", "SLC", 10.525);
	city_graph.add("LAS", "SEA", 27.825);
	city_graph.add("LAS", "RNO", 10.975);

	//PriorityQueue<pair<string, float>> priority_queue;
	unordered_map<string, LinkedList<pair<string, float>>> adjacency_list(city_graph.getAdjacencyList());

	cout << "Adjacency list:" << endl;
	for (const auto& cur_vertex : adjacency_list)
	{
		cout << "(" << cur_vertex.first << "): ";
		for (int i = 1; i <= cur_vertex.second.getLength(); i++)
		{
			cout << "{" << cur_vertex.second.getEntry(i).first << ", ";
			cout << cur_vertex.second.getEntry(i).second << "} ";
		}
		cout << endl;
	}

	LinkedList<string> vertices;
	string starting_city = "RNO";
	float minimum_cost = 1e9;

	for (const auto& cur_vertex : adjacency_list) //create list of vertices exluding the start
	{
		if (cur_vertex.first != starting_city)
		{
			vertices.insert(1, cur_vertex.first);
		}
	}

	for (auto it = vertices.begin(); it != vertices.end(); ++it) {
		std::cout << *it << " ";
	}

	do
	{
		float permutation_cost = city_graph.getPathDistance(vertices, starting_city);
		minimum_cost = min(minimum_cost, permutation_cost);
	} while (next_permutation(vertices.begin(), vertices.end()));

	cout << minimum_cost << endl;
}

void addToGraph(GraphInterface<string>& graph)
{
	string start_vertex;
	string end_vertex;
	float edge_weight;

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

	float edge_weight = graph.getEdgeWeight(start_vertex, end_vertex);
	if (edge_weight != -1) { cout << "The edge's weight is: " << edge_weight << endl; }
	else { cout << "That edge doesn't exist!"; }
}