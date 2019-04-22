#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <iterator>
#include <map>
#include <list>

using namespace std;


typedef pair<int, double> dPair;


class Graph
{
  private:
	int numCities;
	int numRoutes;


  public:

	list<pair<int, double>> *adj;

	map<string, int> cityMapNew;
	
	int cityCounterNew = 0;

	int connectedComponentsCounter = 0;
	int bridgeCounter = 0;
	vector<pair<string, string>> answers;



	//Setter
	void setParam(int cities, int routes);

	//Getters
	int getCities();
	int getRoutes();

	Graph(int, int);

	void addEdgeNew(string u, string v, double w);
	void addEdgeUtil(list<pair<int, double>> *meme, int u, int v, double w);

	void findBridges();
	void neatPrint();

	void iterativeDFS(int v, vector<bool> &discovered);
	void connectedComponents();



	bool isConnected();
	bool isConnectedTemp(list<pair<int, double>> *tempList);
	void iterativeDFSTemp(int v, vector<bool> &discovered, list<pair<int, double>> *tempList);
	bool isBridge(string u_city, string v_city);

	int cityToIntNew(string s);
	string intToCityNew(int c);

};

#endif
