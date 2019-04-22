#include <iostream>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "graph.h"
#include <vector>
#include <stdio.h>
#include <string.h> 
 
using namespace std;

vector<string> tokenize(string s)
{
    vector<string> tokens;
    string temp;

    stringstream str(s);

    while( str >> temp){
        tokens.push_back(temp);
    }

    return tokens;
}
 

 // Part 1 : Find the connected components and the bridge
void part1(ifstream &inputfile, ofstream &outputfile)
{
    
    string line;
    getline(inputfile,line);
    vector<string> param = tokenize(line);

    Graph g(stoi(param[0]),stoi(param[1]));
    
    while(getline(inputfile, line)){
       
        vector<string> tokens = tokenize(line);
        g.addEdgeNew(tokens[0],tokens[1],stod(tokens[2]));

        
    }

    g.connectedComponents();
    outputfile << g.connectedComponentsCounter << endl;
    g.connectedComponentsCounter =0;

    g.findBridges();
    outputfile << g.bridgeCounter/2 << endl;
    g.bridgeCounter=0;

    for(pair<string,string> x:g.answers){

        string first;
        string second;
        
        if(  x.first.compare(x.second) > 0  ) {
            first = x.second;
            second = x.first;
            outputfile << first << " "<< second << endl;
            
        }


        
    }

}



 // Part 2 :  Find a ticket using Dijkstra	
void part2(ifstream &inputfile, ofstream &outputfile)
{
    string line;
    getline(inputfile,line);
    vector<string> param = tokenize(line);
    int max = stoi(param[1]);
    int counter = 0;
    Graph g(stoi(param[0]),stoi(param[1]));

   


    
    while(getline(inputfile, line) && counter!=max){
       
        vector<string> tokens = tokenize(line);
 
        counter++;
        
    }

    while(getline(inputfile, line)){

        
       
        vector<string> tokens = tokenize(line);

    
        
        if(tokens[0] == "END"){
            break;
        }
        
       


        
    }



}

 // Part 3 :Try to do a tour of all cities 
void part3(ifstream &inputfile, ofstream &outputfile)
{
    string line;
    getline(inputfile,line);
    vector<string> param = tokenize(line);

    Graph g(stoi(param[0]),stoi(param[1]));

    int counter=0; 
    
    while(getline(inputfile, line)){

        vector<string> tokens = tokenize(line);

        if(counter== stoi(param[1])){
            cout << tokens[0] << endl;
            break;
        }
       
       
        
        cout <<tokens[0]<< " " << tokens[1] << " " << tokens[2] << endl;
        g.addEdgeNew(tokens[0],tokens[1],stod(tokens[2]));   

        counter++;
    }


 

}
 
 int main(int argc, char *argv[])
 {
	//Read in the test case
    ifstream inputfile;
    ofstream outputfile;

    if(argc==3){
        inputfile.open(argv[1]);
        outputfile.open(argv[2]);
    }
    else{
        cout<<"Not enough arguments"<<endl;
    }

    string str;

    getline(inputfile, str);
    int part;
    stringstream convert(str);
    convert >> part;


	 if(part == 1) part1(inputfile, outputfile);
	 else if(part == 2) part2(inputfile, outputfile);
	 else if(part == 3) part3(inputfile, outputfile);

	 return 0;
 }
