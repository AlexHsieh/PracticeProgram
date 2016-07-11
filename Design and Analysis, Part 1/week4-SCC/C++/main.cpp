//
//  main.cpp
//  SCC
//
//  Created by Alex Hsieh on 7/9/16.
//  Copyright © 2016 Alex Hsieh. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
using namespace std;

struct vertex {
    int label;
    int rev_finishing_time;
    bool explored;
    struct vertex *next;
    struct vertex *previous;
    std::vector<int> heads;
    std::vector<int> tails; //reverse arc
    bool finished1stPass;
};

class directed_graph {
public:
    std::map<int, vertex > graphVertexMap;
    int numberOfVertexs;
    std::vector<vertex *> finished1stPassVertexs;
    std::vector<int> sscVector;
};


/*
 * Stack operation
 */
class stack {
public:
    vertex *top = NULL;
    void push(vertex *);
    vertex* pop();
    bool isEmpty();
    void display();
};

void stack::push(vertex *aVertex) {
    
    if (aVertex->previous != NULL) {
        aVertex->previous->next = aVertex->next;
    }

    if (aVertex->next != NULL) {
        aVertex->next->previous = aVertex->previous;
    }
    
    if (top != NULL) {
        aVertex->next = top;
        top->previous = aVertex;
    }
    top = aVertex;
}

vertex* stack::pop() {
    vertex *nextTop = top->next;
    top->next = NULL;
    if (nextTop != NULL) {
        nextTop->previous = NULL;
    }
    vertex *currentTop = top;
    top = nextTop;
    return currentTop;
};

bool stack::isEmpty() {
    return top == NULL ? true:false;
};

void printVertex(vertex *v) {
    if (v->explored) {
        
    } else {
        std::cout << v->label << "-";
        if (v->next != NULL) {
            printVertex(v->next);
        }
    }
}

void stack::display() {
    printVertex(top);
    std::cout << "end" << std::endl;
}


/*
 * Depth First Search Via Recrusive Approach
 */

int dfs_reverse (directed_graph *graph ,vertex *v, int finsihingTime) {
    
    if (v->explored) {
        //do nothing
    } else {
        v->explored = true;
        for (int j=0; j<v->tails.size(); j++) {
            int vertexNum = v->tails[j];
            vertex *v2 = &(graph->graphVertexMap.find(vertexNum)->second);
            finsihingTime = dfs_reverse(graph, v2, finsihingTime);
        }
        finsihingTime++;
//        std::cout << "finishingTime: " << finsihingTime << " ,v->label: " << v->label <<std::endl;
        v->rev_finishing_time = finsihingTime;
        graph->finished1stPassVertexs.push_back(v);
    }
    return finsihingTime;
}

void dfs_rev_operation (directed_graph *graph) {
    int n = graph->numberOfVertexs;
    int finishingTime = 0;
    for (int i=n; i!=0; i--) {
        vertex *vertex = &(graph->graphVertexMap.find(i)->second);
        finishingTime = dfs_reverse(graph,vertex,finishingTime);
    }
}

int dfs (directed_graph *graph ,vertex *v, int numberOfConnectedComponents) {
    
    if (v->explored) {
        //do nothing
    } else {
        v->explored = true;
        for (int j=0; j<v->heads.size(); j++) {
            int vertexNum = v->heads[j];
            vertex *v2 =  &(graph->graphVertexMap.find(vertexNum)->second);//(vertex *)(v->heads[j]);
            numberOfConnectedComponents = dfs(graph, v2, numberOfConnectedComponents);
        }
        numberOfConnectedComponents++;
    }
    return numberOfConnectedComponents;
}

void dfs_operation (directed_graph *graph) {
    int n = graph->numberOfVertexs;
    for (int i=n-1; i>=0; i--) {
        int numberOfConnectedComponents = 0;
        vertex *vertex = graph->finished1stPassVertexs[i];
        numberOfConnectedComponents = dfs(graph,vertex,numberOfConnectedComponents);
//        if (numberOfConnectedComponents > 0) {
//            std::cout << "leader: " << vertex->label << ", # of SSC:" << numberOfConnectedComponents << std::endl;
//        }
    }
}



/*
 * Depth First Search Via Stack Approach
 */

int dfs_rev_by_stack (directed_graph *graph, stack *stack, int finsihingTime) {
    
    if (stack->top->explored) {
        
        vertex *v = stack->pop();
        if (v->rev_finishing_time == 0) {
            v->finished1stPass = true;
            finsihingTime++;
//            std::cout << "finishingTime: " << finsihingTime << " ,v->label: " << v->label <<std::endl;
            v->rev_finishing_time = finsihingTime;
            graph->finished1stPassVertexs.push_back(v);
        }
    } else {
        stack->top->explored = true;
        vertex *currentVertex = stack->top;
        for (int j=int(currentVertex->tails.size()-1); j>=0; j--) {
            int vertexNum = currentVertex->tails[j];
            vertex *v2 = &(graph->graphVertexMap.find(vertexNum)->second);
            if (v2->explored == false) {
                stack->push(v2);
            }
        }
    }
    return finsihingTime;
}

void dfs_rev_operation_by_stack (directed_graph *graph) {
    stack stack;
    int finishingTime = 0;
    for (int i=graph->numberOfVertexs ;i>0;i--) {
        vertex *rootVertex = &(graph->graphVertexMap.find(i)->second);
        if (rootVertex->explored) {
            continue;
        }
        stack.push(rootVertex);
        while (!stack.isEmpty()) {
            finishingTime = dfs_rev_by_stack(graph, &stack, finishingTime);
        }
    }
    
}

int dfs_by_stack (directed_graph *graph ,stack *stack, int numberOfConnectedComponents) {
    if (stack->top->explored) {
        stack->pop();
    } else {
        stack->top->explored = true;
        vertex *currentVertex = stack->top;
        numberOfConnectedComponents++;
        for (int j=int(currentVertex->heads.size()-1); j>=0; j--) {
            int vertexNum = currentVertex->heads[j];
            vertex *v2 = &(graph->graphVertexMap.find(vertexNum)->second);
            if (!(v2->explored)) {
                stack->push(v2);
            }
        }
    }
    return numberOfConnectedComponents;
}

void dfs_operation_by_stack (directed_graph *graph) {
    stack stack;
    int n = graph->numberOfVertexs;
    for (int i=n-1; i>=0; i--) {
        int numberOfConnectedComponents = 0;
        vertex *rootVertex = graph->finished1stPassVertexs[i];
        if (rootVertex->explored) {
            continue;
        }
        stack.push(rootVertex);
        while (!stack.isEmpty()) {
            numberOfConnectedComponents = dfs_by_stack(graph,&stack,numberOfConnectedComponents);
        }
        if (numberOfConnectedComponents > 0) {
//            std::cout << "leader: " << rootVertex->label << ", # of SSC:" << numberOfConnectedComponents << std::endl;
            graph->sscVector.push_back(numberOfConnectedComponents);
        }
    }

}

/*
 * Utility
 */
directed_graph readfile(int dataSetNumber) {
    
    std::string filePath = "/Users/alexhsieh/Documents/PracticeProgram/Design\ and\ Analysis\,\ Part\ 1/week4-SCC/";
    std::ifstream infile;
    switch (dataSetNumber) {
        case 0:
            filePath.append("SCC.txt");
            break;
        case 1:
            filePath.append("data1");
            break;
        case 2:
            filePath.append("data2");
            break;
        case 3:
            filePath.append("data3");
            break;
        case 4:
            filePath.append("data4");
            break;
        case 5:
            filePath.append("data5");
            break;
            
        default:
            std::cout << "use data1" << std::endl;
            filePath.append("data1");
            break;
    }
    
    infile.open(filePath);
    if (!infile) {
        std::cout << "no file... check file path!" <<std::endl;
    }
    
    std::string line;
    directed_graph graph;
    std::map<int, vertex > graphVertexMap;
    
    graph.numberOfVertexs = 0;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        int vertexNum;
        int edgeHead;
        while (iss >> vertexNum >> edgeHead) {
//            if (vertexNum == edgeHead) {
//                continue;
//            }
//            std::cout << "1. vertexNum: " << vertexNum << ", edgeHead:" <<edgeHead << std::endl;
            if (graphVertexMap.count(vertexNum) > 0) {
                vertex *v = &(graphVertexMap.find(vertexNum)->second);
                v->heads.push_back(edgeHead);
            } else {
                vertex v;
                v.rev_finishing_time = 0;
                v.explored = false;
                v.next = NULL;
                v.previous = NULL;
                v.heads.push_back(edgeHead);
                v.label = vertexNum;
                v.finished1stPass = false;
                graphVertexMap.insert(std::pair<int,vertex>(vertexNum,v));
                graph.numberOfVertexs++;
            }
        }
    }
    
    std::ifstream infile2;
    infile2.open(filePath);
    while (std::getline(infile2, line))
    {
        std::istringstream iss(line);
        int vertexNum;
        int edgeHead;
        while (iss >> edgeHead >> vertexNum) {
//            if (vertexNum == edgeHead) {
//                continue;
//            }
//            std::cout << "2. vertexNum: " << vertexNum << ", edgeHead:" << edgeHead << std::endl;
            if (graphVertexMap.count(vertexNum) > 0) {
                vertex *v = &(graphVertexMap.find(vertexNum)->second);
                v->tails.push_back(edgeHead);
            } else {
                vertex v;
                v.rev_finishing_time = 0;
                v.explored = false;
                v.next = NULL;
                v.previous = NULL;
                v.tails.push_back(edgeHead);
                v.label = vertexNum;
                v.finished1stPass = false;
                graphVertexMap.insert(std::pair<int,vertex>(vertexNum,v));
                graph.numberOfVertexs++;
            }

        }
    }
    std::cout << "number of vertex:" << graph.numberOfVertexs << ", graphVertexMap.size: " << graphVertexMap.size()<< std::endl;
    graph.graphVertexMap = graphVertexMap;
    
    return graph;
};

void markAllVertextUnExplored(directed_graph *graph) {
    int n = graph->numberOfVertexs;
    for (int i=0; i<n; i++) {
        vertex *vertex = graph->finished1stPassVertexs[i];
        vertex->explored = false;
        vertex->next = NULL;
        vertex->previous = NULL;
    }
}




int main(int argc, const char * argv[]) {
    
    std::cout << "----- Kosaraju's Strongly Connected Components Algorithm -----" << std::endl;
    std::cout << "Load file from 0.data(Huge) or 1.data1(9)(3,3,3,0,0) or 2.data2(8)(3,3,2,0,0) 3.data3(8)(3,3,1,1,0) 4.data4(8)(7,1,0,0,0) 5.data5(12)(6,3,2,1,0):" ;
    int userChoice = 0;
    scanf("%i", &userChoice);
    directed_graph g = readfile(userChoice);
    
    std::cout << "Use 1.Recrusive approach(Will crash for huge input) or 2. stack approach:" ;
    scanf("%i", &userChoice);
    
    time_t  times;
    std::cout << "start time: " << time(&times) << std::endl;
    if (userChoice == 1) {
        dfs_rev_operation(&g);
        markAllVertextUnExplored(&g);
        dfs_operation(&g);
    } else {
        std::cout << "stack approach" << std::endl;
        dfs_rev_operation_by_stack(&g);
        markAllVertextUnExplored(&g);
        dfs_operation_by_stack(&g);
    }
    time_t  timee;
    std::cout << "end time: " << time(&timee) << std::endl;

    cout << "sscVector size:" << g.sscVector.size() << endl;
    
    int no1 = 0;
    int no2 = 0;
    int no3 = 0;
    int no4 = 0;
    int no5 = 0;
    
    for (int i=0 ; i<g.sscVector.size(); i++) {
        int value = g.sscVector[i];
        if (value > no1) {
            no5 = no4;
            no4 = no3;
            no3 = no2;
            no2 = no1;
            no1 = value;
        } else if (value > no2) {
            no5 = no4;
            no4 = no3;
            no3 = no2;
            no2 = value;
        } else if (value > no3) {
            no5 = no4;
            no4 = no3;
            no3 = value;
        } else if (value > no4) {
            no5 = no4;
            no4 = value;
        } else if (value > no4) {
            no5 = value;
        }
    }
    cout << no1 << "," << no2 << "," << no3 << "," << no4 << "," << no5 <<endl;
    
    return 0;
}
