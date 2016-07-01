//
//  main.cpp
//  RCA
//
//  Created by Alex Hsieh on 6/30/16.
//  Copyright © 2016 Alex Hsieh. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <map> 
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

/*
 * vertex
 */
struct vertex
{
    int vNumber;
    
    vertex()
    {
        vNumber = 0;
    }
    
    ~vertex()
    {
//        cout << "vertex " << vNumber << " 被終結了" << endl;
    }
};

/*
 * Undirected_Graph
 */
class Undirected_Graph
{
private:
    std::map<int, std::vector<int>> graph_container_original;
    std::map<int, std::vector<int>> graph_container;

    void karger_contraction_algorithm() {
        
        //clear vector and copy original data
        graph_container.clear();
        std::map<int, std::vector<int>>::iterator iter;
        
        for (iter=graph_container_original.begin(); iter!=graph_container_original.end(); iter++) {
            graph_container.insert(pair<int, std::vector<int>>(iter->first, iter->second));
        }
        
        // contraction algorithm
        while (graph_container.size() != 2) {
            cout << "graph_container.size() : " << graph_container.size() << " " << endl;
            
            //1. pick a remaining edge uniformly at random
            auto it = graph_container.begin();
            std::advance(it, rand() % graph_container.size());
            int pt1 = it->first;
            int index = rand()%(it->second.size());
            int pt2 = it->second.at(index);
            
            //2. merge (or “contract” ) 2 vertex into a single vertex
            //3. remove self loop
            std::vector<int> contractedEdges;
            std::vector<int> pt1Edges = graph_container.at(pt1);
            std::vector<int> pt2Edges = graph_container.at(pt2);
            
            cout << "contract edge =" << pt1 << "-" << pt2 << endl;

            for (std::vector<int>::iterator it = pt1Edges.begin() ; it != pt1Edges.end(); ++it) {
//                cout << "*it=" << *it  << endl;
                if (*it == pt1 || *it == pt2) {
                    //self loop.. don't add it into new edges
                    cout << "remove self loop =" << *it  << endl;
                } else {
                    contractedEdges.push_back(*it);
                }
            }
            
            for (std::vector<int>::iterator it = pt2Edges.begin() ; it != pt2Edges.end(); ++it) {
//                cout <<  "*it=" << *it << endl;
                if (*it == pt1 || *it == pt2) {
                    //self loop.. don't add it into new edges
                    cout << "remove self loop =" << *it  << endl;
                } else {
                    contractedEdges.push_back(*it);
                }
            }
            
            graph_container.erase(pt1);
            graph_container.erase(pt2);
            graph_container.insert(pair<int, std::vector<int>>(pt1,contractedEdges));
        }
        
    }
    
public:
    void add_vertex(vertex& v, std::vector<int> &edges) {
        //add a vertex to the map
        graph_container_original.insert(pair<int, std::vector<int>>(v.vNumber,edges));
    }
    
    void caculate_minimum_cut() {
        unsigned long int numberOfTimesToExecute = graph_container_original.size() * graph_container_original.size();
        int repeat = 0;
        while (repeat < numberOfTimesToExecute) {
            karger_contraction_algorithm();
            
            //export mini cut
            if (graph_container.size() == 2) {
                unsigned long int numberOfCut = 0;

                std::map<int, std::vector<int>>::iterator iter;
                for (graph_container.begin(); iter!=graph_container.end(); iter++) {
                    cout << "vertex : " << iter->first << " (" ;
                    std::vector<int> cutVector = iter->second;
                    
                    std::vector<int>::iterator iter2;
                    for(cutVector.begin(); iter2 != cutVector.end();iter2++) {
                        cout << cutVector[*iter2] << ",";
                    }
                    cout << ")" << endl;
                }
                
//                if (repeat == 0) {
//                    minimumCut = numberOfCut;
//                } else {
//                    minimumCut = minimumCut < numberOfCut ? numberOfCut : minimumCut;
//                }
//                
//                if (numberOfTimesToExecute <= 100) {
//                    cout << "numberOfCut: " << numberOfCut << endl;
//                }

            }
            repeat++;
            
        }
//        cout << "minimumCut: " << minimumCut << endl;
    }
};

/*
 * Read File
 */
Undirected_Graph readfile(int dataSetNumber) {
    
    std::ifstream infile;
    switch (dataSetNumber) {
        case 1:
            infile.open("/Users/alexhsieh/Documents/PracticeProgram/Design\ and\ Analysis\,\ Part\ 1/randomized\ contraction\ algorithm/testdata1");
            break;
            
        default:
            infile.open("/Users/alexhsieh/Documents/PracticeProgram/Design\ and\ Analysis\,\ Part\ 1/randomized\ contraction\ algorithm/testdata1");
            break;
    }
    
    if (!infile) {
        std::cout << "no file, return" <<endl;
    }
  
    std::string line;
    Undirected_Graph graph;
    while (std::getline(infile, line))
    {
        vertex v;
        vector<int> arr;
        int i = 0;
        std::istringstream iss(line);
        int aNumber;
        while (iss >> aNumber) {
            if (i != 0) {
                arr.push_back(aNumber);
            } else {
                v.vNumber = aNumber;
            }
            i++;
        }
        
        graph.add_vertex(v, arr);
        
        cout << v.vNumber << ": ";
        for (int j=0; j<arr.size(); j++) {
            cout << arr[j] << ", ";
        }
        cout << endl;

    }
    
    return graph;
};

/*
 * Main
 */
int main(int argc, const char * argv[]) {
    std::cout << "-----  Randomized Contraction Algorithm  -----" << endl;
    std::cout << "Load file from 1.data(200) or 2.data(8)?:" ;
    int userChoice = 0;
    scanf("%i", &userChoice);
    
    
    Undirected_Graph graph = readfile(userChoice);
    graph.caculate_minimum_cut();
    
//    if (userChoice == 1) {
//        graph = readfile(1);
//    }
//    int mergeSize = 0;
//    
//    std::vector<int> myArray;
//    if (userChoice == 1) {
//        NSLog(@"Do you want to 1.read small test data(6) or 2.large test data(10000)?:");
//        int datasize = 0;
//        scanf("%i", &datasize);
//        datasize = datasize == 1 ? 6:10000;
//        mergeSize = datasize;
//        myArray = readfile(datasize);
//    } else {
//        NSLog(@"Given an array with N integer. Input N:");
//        int userInput = 0;
//        scanf("%i", &userInput);
//        mergeSize = userInput;
//        srand([NSDate timeIntervalSinceReferenceDate]);
//        myArray = randomNumArr(userInput);
//    }
    
   
    return 0;
};
