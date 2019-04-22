#include <iostream>
#include <string>
#include "graph.h"
#include <vector>
#include <iterator>
#include <map>
#include <stack>
#include <stdio.h>
#include <string.h>
#include <queue>
#include <limits.h>
#include <algorithm>

using namespace std;

#define INFI 1000000

// Constructor for Graph
Graph::Graph(int Vertices, int routes)
{
	setParam(Vertices, routes);


	adj = new list<dPair>[Vertices];

}


//Setters
void Graph::setParam(int myCities, int myRoutes)
{
	numCities = myCities;
	numRoutes = myRoutes;
}

//Getter for City#
int Graph::getCities()
{
	return numCities;
}

//Getters for routes#
int Graph::getRoutes()
{
	return numRoutes;
}

//Converts city strings to mapped int value
int Graph::cityToIntNew(string s)
{
	return cityMapNew.find(s)->second;
}



//Converts city int to its string
string Graph::intToCityNew(int c)
{

	string key;
	for (auto &i : cityMapNew)
	{
		if (i.second == c)
		{
			key = i.first;
			break; // to stop searching
		}
	}

	return key;
}



void Graph::neatPrint()
{
	for (int i = 0; i < numCities; i++)
	{
		
		for (dPair v : adj[i])
		{
			cout << "(" << intToCityNew(i) << ", " << intToCityNew(v.first) << ", " << v.second << ") ";
		}
		cout << endl;
	}
}

void Graph::findBridges()
{
	for (int i = 0; i < numCities; i++)
	{
		
		for (dPair v : adj[i])
		{
			// cout << "(" << intToCityNew(i) << ", " << intToCityNew(v.first) << ", " << v.second << ") ";
			// cout << i << ", " << v.first << endl;

			string u_city = intToCityNew(i);
			string v_city = intToCityNew(v.first);

			// cout << u_city << ", "<< v_city << endl;
			// cout << i << ", " << v.first << endl;

			if (isBridge(u_city, v_city) == true)
			{

				bridgeCounter++;
				answers.push_back(make_pair(u_city, v_city));
			}

			// cout << isBridge("AAC", "AAB") << endl;
		}
		//cout << endl;
	}
}

//Adds a new edge to the graph
void Graph::addEdgeNew(string u, string v, double w)
{

	if (cityMapNew.find(u) == cityMapNew.end())
	{
		//not found
		cityMapNew.insert(pair<string, int>(u, cityCounterNew));
		cityCounterNew++;
	}

	if (cityMapNew.find(v) == cityMapNew.end())
	{
		//not found
		cityMapNew.insert(pair<string, int>(v, cityCounterNew));
		cityCounterNew++;
	}

	int u_city = cityToIntNew(u);
	int v_city = cityToIntNew(v);

	//adj[u_city].push_back(make_pair(w, v_city));

	adj[u_city].push_back(make_pair(v_city, w));
	// cout << "Adding: "<< intToCityNew(u_city) << ", "<< intToCityNew(v_city)<< ", " << w << endl;
	//adj[v_city].push_back(make_pair(w,u_city));
	adj[v_city].push_back(make_pair(u_city, w));
	// cout << "Adding: "<< intToCityNew(v_city) << ", "<< intToCityNew(u_city)<< ", " << w << endl;
}

void Graph::addEdgeUtil(list<pair<int, double>> *meme, int u, int v, double w)
{
	meme[u].push_back(make_pair(v, w));
	meme[v].push_back(make_pair(u, w));
}

// Perform iterative DFS on graph g starting from vertex v
void Graph::iterativeDFS(int v, vector<bool> &discovered)
{
	
	stack<int> stack;

	
	stack.push(v);


	while (!stack.empty())
	{
		
		v = stack.top();
		stack.pop();

		if (discovered[v])
		{
			continue;
		}

		discovered[v] = true;
		

		for (auto it = adj[v].rbegin(); it != adj[v].rend(); ++it)
		{
			int u = it->first;
			if (!discovered[u])
			{
				stack.push(u);
			}
		}
	}
}

void Graph::iterativeDFSTemp(int v, vector<bool> &discovered, list<pair<int, double>> *tempList)
{

	
	stack<int> stack;

	stack.push(v);


	while (!stack.empty())
	{
		
		v = stack.top();
		stack.pop();

		if (discovered[v])
		{
			continue;
		}

		discovered[v] = true;
		

		for (auto it = tempList[v].rbegin(); it != tempList[v].rend(); ++it)
		{
			int u = it->first;
			if (!discovered[u])
			{
				stack.push(u);
			}
		}
	}
}


void Graph::connectedComponents()
{

	vector<bool> visited(numCities);
	for (int v = 0; v < numCities; v++)
		visited[v] = false;

	for (int v = 0; v < numCities; v++)
	{
		if (visited[v] == false)
		{

			iterativeDFS(v, visited);

			cout << "\n";
			cout << "BEEEEEP" << endl;
			connectedComponentsCounter++;
		}
	}
}

bool Graph::isConnected()
{
	vector<bool> visited(numCities);


	iterativeDFS(0, visited);

	for (int i = 0; i < numCities; i++)
		if (visited[i] == false)
			return false;

	return true;
}

bool Graph::isConnectedTemp(list<pair<int, double>> *tempList)
{



	vector<bool> visited(numCities);


	iterativeDFSTemp(0, visited, tempList);


	for (int i = 0; i < numCities; i++)
	{
		if (visited[i] == false)
		{
			return false;
		}
	}
	return true;
}

bool Graph::isBridge(string u_city, string v_city)
{
	

	int u = cityToIntNew(u_city);
	int v = cityToIntNew(v_city);

	list<dPair> *tempList = new list<dPair>[numCities];

	for (int i = 0; i < numCities; i++)
	{


		for (dPair v : adj[i])
		{
			//cout << "(" << intToCityNew(i) << ", " << intToCityNew(v.first) << ", " << v.second << ") ";
			addEdgeUtil(tempList, i, v.first, v.second);
		}
	}

	//tempList = (list< pair<int, double> > *)malloc(sizeof(adj) * numCities);
	//memcpy(tempList,adj,sizeof(adj) * numCities);
	//tempList = adj;

	double temp;

	for (dPair x : tempList[u])
	{
		if (x.first == v)
		{

			temp = x.second;
			// cout << "Removing: " << intToCityNew(u) << ", " << intToCityNew(x.first) << endl;
			tempList[u].remove(x);

			pair<int, double> tempPair;
			tempPair.first = u;
			tempPair.second = x.second;

			tempList[v].remove(tempPair);

			break;
		}
	}



	bool res = isConnectedTemp(tempList);



	return (res == false);
}