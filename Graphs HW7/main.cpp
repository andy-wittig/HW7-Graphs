#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

#include "adjacencyListGraph.h"

void addToGraph(GraphInterface<string>&);
void removeFromGraph(GraphInterface<string>&);
void getGraphEdgeWeight(GraphInterface<string>&);
void getGraphAdjacencyList(AdjacencyListGraph<string>&);
void getDepthTraversal(AdjacencyListGraph<string>&);
void getBreadthTraversal(AdjacencyListGraph<string>&);
void runShortestPathSimulation();

int getChoice();

int main()
{
	AdjacencyListGraph<string> graph;

	int menu_choice;
	do
	{
		menu_choice = getChoice();
		switch (menu_choice)
		{
		case 1:
			addToGraph(graph);
			break;
		case 2:
			removeFromGraph(graph);
			break;
		case 3:
			getGraphEdgeWeight(graph);
			break;
		case 4:
			getGraphAdjacencyList(graph);
			break;
		case 5:
			getDepthTraversal(graph);
			break;
		case 6:
			getBreadthTraversal(graph);
			break;
		case 7:
			runShortestPathSimulation();
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
	cout << "4. Get graph adjacency list." << endl;
	cout << "5. Get depth traversal of graph." << endl;
	cout << "6. Get breadth traversal of graph." << endl;
	cout << "7. Run shortest path salesman simulation." << endl;
	cout << "--------------------" << endl;

	cin >> input_choice;
	return input_choice;
}

void runShortestPathSimulation()
{

	ofstream output_file("shortest_distance.txt");
	ifstream input_file;
	string get_line;
	vector<string> cities;
	vector<string> shortest_path;

	AdjacencyListGraph<string> city_graph;
	string starting_city = "RNO";
	float minimum_path_cost = 1e9;

	input_file.open("city_distances.txt");
	while (getline(input_file, get_line))
	{
		stringstream stream_line(get_line);
		string city_1, city_2;
		float dist;
		stream_line >> city_1 >> city_2 >> dist;
		city_graph.add(city_1, city_2, dist); //initalize graph (distance in miles to city divided by 40mpg to give gallons)
	}
	unordered_map<string, LinkedList<pair<string, float>>> adjacency_list(city_graph.getAdjacencyList());

	output_file << "Adjacency list:" << endl;
	for (const auto& cur_vertex : adjacency_list)
	{
		output_file << "(" << cur_vertex.first << "): ";
		for (int i = 1; i <= cur_vertex.second.getLength(); i++)
		{
			output_file << "{" << cur_vertex.second.getEntry(i).first << ", ";
			output_file << cur_vertex.second.getEntry(i).second << "} ";
		}
		output_file << endl;
	}

	//create vect of cities exluding the start
	for (const auto& cur_vertex : adjacency_list)
	{
		if (cur_vertex.first != starting_city)
		{
			cities.push_back(cur_vertex.first);
		}
	}

	output_file << "\nPermutations: " << endl;
	do
	{
		LinkedList<string> new_path;

		bool valid_permutation = true;
		for (int i = 0; i < cities.size()-1; i++) //ensure permutation is valid path
		{
			if (city_graph.getEdgeListPos(cities[i], cities[i + 1]) == -1)
			{
				valid_permutation = false;
			}
		}
		if (!valid_permutation) { continue; }

		//construct new permutation path
		output_file << starting_city << "->";
		new_path.push_back(starting_city);
		for (auto& city : cities)
		{
			output_file << city << "->";
			new_path.push_back(city); //convert to linked list to find distance
		}
		output_file << starting_city << endl;
		new_path.push_back(starting_city); //ends back at start

		//find if new path is shortest and update accordingly
		float current_path_cost;
		current_path_cost = city_graph.getPathDistance(new_path);
		if (minimum_path_cost > current_path_cost)
		{
			minimum_path_cost = current_path_cost;
			shortest_path = cities;
		}
	} while (next_permutation(cities.begin(), cities.end()));

	output_file << "\nShortest path: " << starting_city << "->";
	for (auto& city : shortest_path)
	{
		output_file << city << "->";
	}
	output_file << starting_city << endl;
	output_file << "Minimum gas consumption for shortest trip: " << minimum_path_cost << endl;
	output_file.close();
	cout << "Generated shortest path simulation to shortest_distance.txt" << endl;
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

void getGraphAdjacencyList(AdjacencyListGraph<string>& graph)
{
	unordered_map<string, LinkedList<pair<string, float>>> adjacency_list(graph.getAdjacencyList());

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
}

void display(string &data) //display helper
{
	cout << data << " ";
}

void getDepthTraversal(AdjacencyListGraph<string>& graph)
{
	string start_vertex;

	cout << "Please enter the starting vertex to traverse from:" << endl;
	cin >> start_vertex;
	cout << "Depth first traversal: ";

	graph.depthFirstTraversal(start_vertex, display);
}

void getBreadthTraversal(AdjacencyListGraph<string>& graph)
{
	string start_vertex;

	cout << "Please enter the starting vertex to traverse from:" << endl;
	cin >> start_vertex;
	cout << "Breadth first traversal: ";

	graph.breadthFirstTraversal(start_vertex, display);
}