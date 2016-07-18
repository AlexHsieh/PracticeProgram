//
//  main.cpp
//  DijKstra
//
//  Created by Alex Hsieh on 7/14/16.
//  Copyright © 2016 Alex Hsieh. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;


/*
 * Vertex and Graph
 */
struct vertex {
    int label;
    int distanceFromVextex1; //key
    map<int,int> edges; //map edge vertex and length
    bool isIntheHeap;
    int heapNodeNumber; //index in the heap vector
};

struct undirected_graph {
    int numberOfVertex;
    vector<vertex>vertexes;
};


/*
 * Utility
 */
undirected_graph readfile(int dataSetNumber) {
    
    std::string filePath = "/Users/alexhsieh/Documents/PracticeProgram/Design\ and\ Analysis\,\ Part\ 1/week5-DijKstra/";
    std::ifstream infile;
    switch (dataSetNumber) {
        case 0:
            filePath.append("data.txt");
            break;
        case 1:
            filePath.append("testdata1");
            break;
        case 2:
            filePath.append("testdata2");
            break;
            
        default:
            std::cout << "use data1" << std::endl;
            filePath.append("testdata1");
            break;
    }
    
    infile.open(filePath);
    if (!infile) {
        std::cout << "no file... check file path!" <<std::endl;
    }
    
    std::string line;
    undirected_graph graph;
    graph.numberOfVertex = 0;
    
    while (std::getline(infile, line))
    {
        //        cout << "line.size():" <<line.size() <<endl;
        if (line.size()) {
            std::istringstream iss(line);
            int i=0;
            string parseOutput;
            int output=0;
            int dest = 0;
            int length = 0;
            vertex v;
            while (iss >> output)
            {
                //                printf("%d ",i);
                if (i==0) {
                    v.label = output;
                    v.distanceFromVextex1 = output==1? 0: 1000000;
                    //                    cout << "v.label:" << v.label << endl;
                } else if (i%2){
                    dest = output;
                    //                    cout << "dest:" << dest << endl;
                } else {
                    length = output;
                    //                    cout << "length:" << length << endl;
                    v.edges.insert(pair<int,int>(dest,length));
                }
                if (iss.peek() == ',')
                    iss.ignore();
                i++;
            }
            //            printf("\n");
            graph.vertexes.push_back(v);
            graph.numberOfVertex++;
        }
        
    }
    
    cout << "number of vertex:" << graph.numberOfVertex << ", size: " << graph.numberOfVertex<< endl;
    
    return graph;
};

void printVertexDistance(vector<vertex*>::iterator it) {
    cout << "#" << (*it)->label << ":" << (*it)->distanceFromVextex1 << endl;
}

/*
 * Heap
 */
class minHeap {
private:
    vector<vertex *>heap;
    int nextLeftHeapKey(int n);
    int nextRightHeapKey(int n);
    int parentHeapKey(int n);
    void decreaseHeapKey(int , int, undirected_graph *);
    void bubbleDown(int j);
    void bubbleUp(int j);
    void swapHeapNode(vector<vertex*>::iterator a, vector<vertex*>::iterator b);
    void deleteHeapNode(vertex *v);
    void insertHeapNode(vertex *v);
    
public:
    void minHeapify(vertex *, undirected_graph *);
    vertex * extractMin();
    void reCaculateKey(int srcKey, int destVertexNumber, int leng, undirected_graph *);
    bool isEmpty();
};

int nextLeftHeapIndex(int n) {
    return 2*n+1;
}

int nextRightHeapIndex(int n) {
    return 2*n+2;
}

int parentHeapIndex(int n) {
    int parentIndex = 0;
    if (n != 0) {
        if (n%2) {
            parentIndex = (n-1)*0.5;
        } else {
            parentIndex = (n-2)*0.5;
        }
    }
    return parentIndex;
}

int minHeap::nextLeftHeapKey(int n){
    if (heap.size() > nextLeftHeapIndex(n)) {
        return heap[nextLeftHeapIndex(n)]->distanceFromVextex1;
    }
    return 1000000;
}

int minHeap::nextRightHeapKey(int n){
    if (heap.size() > nextRightHeapIndex(n)) {
        return heap[nextRightHeapIndex(n)]->distanceFromVextex1;
    }
    return 1000000;
}

int minHeap::parentHeapKey(int n){
    return heap[parentHeapIndex(n)] -> distanceFromVextex1;
}


void minHeap::swapHeapNode(vector<vertex*>::iterator a, vector<vertex*>::iterator b) {
    iter_swap(a, b);
    int n = (*a)->heapNodeNumber;
    (*a)->heapNodeNumber = (*b)->heapNodeNumber;
    (*b)->heapNodeNumber = n;
};

void minHeap::decreaseHeapKey(int vertexNum, int leng, undirected_graph *g) {
    if (leng > 0) {
        vertex *v = &(g->vertexes[vertexNum-1]);
        if (v->distanceFromVextex1 != 0) {
            v->distanceFromVextex1 = leng > v->distanceFromVextex1 ? v->distanceFromVextex1 : leng;
        }
    }
}

void minHeap::minHeapify(vertex *src, undirected_graph *g) {
    //push 1st vertex into vector
    src->isIntheHeap = true;
    src->heapNodeNumber = 0;
    heap.push_back(src);
    
    //push all other vertec into vector
    int i=1;
    vector<vertex>::iterator it;
    for (it=g->vertexes.begin(); it!=g->vertexes.end(); it++) {
        if (it->label == 1)
            continue;
        
        it->isIntheHeap = true;
        it->heapNodeNumber = i;
        heap.push_back(&*it);
        i++;
    }
    
    //extract 1st vertex;
    extractMin();
    
    //for each edge of first vertex, maintain the heap:
    for (map<int,int>::iterator it=src->edges.begin(); it!=src->edges.end(); it++) {
        reCaculateKey(src->distanceFromVextex1,it->first,it->second, g);
    }
}

vertex * minHeap::extractMin() {
    vertex *min = heap[0];
    min->isIntheHeap = false;
//    cout << "heap.size=" << heap.size()  << endl;
    
    swapHeapNode(heap.begin(), (heap.end()-1));
    heap.erase(heap.end()-1);
    
    bubbleDown(0);
    return min;
}

void minHeap::bubbleDown(int j) {
    int i = j;
    while (heap[i]->distanceFromVextex1 > nextLeftHeapKey(i) || heap[i]->distanceFromVextex1 > nextRightHeapKey(i)) {
        if (nextLeftHeapKey(i) > nextRightHeapKey(i)) {
            swapHeapNode(heap.begin()+i, heap.begin()+nextRightHeapIndex(i));
            i = nextRightHeapIndex(i);
        } else {
            swapHeapNode(heap.begin()+i, heap.begin()+nextLeftHeapIndex(i));
            i = nextLeftHeapIndex(i);
        }
    }
}

void minHeap::bubbleUp(int j) {
    int i = j;
    while (heap[i]->distanceFromVextex1 < parentHeapKey(i)) {
        swapHeapNode(heap.begin()+i, heap.begin()+parentHeapIndex(i));
        i = parentHeapIndex(i);
    }
}

void minHeap::deleteHeapNode(vertex *v) {
    int num = v->heapNodeNumber;
    swapHeapNode(heap.begin()+ (v->heapNodeNumber), (heap.end()-1));
    v->isIntheHeap = false;
    heap.erase(heap.end()-1);
    bubbleDown(num);
}

void minHeap::insertHeapNode(vertex *v) {
    heap.push_back(v);
    v->isIntheHeap = true;
    bubbleUp((int)heap.size()-1);
}

void minHeap::reCaculateKey(int srcKey, int nodeNumberToCaculate, int leng, undirected_graph *g) {
    
    // if destVertex in the heap
    vertex *v = &(g->vertexes[nodeNumberToCaculate-1]);
    if (v->isIntheHeap) {
        //delete the vertex
        deleteHeapNode(v);
        
        //recomplete min key
        int newLength = srcKey + leng;
        v->distanceFromVextex1 = newLength > v->distanceFromVextex1 ? v->distanceFromVextex1 : newLength;
        
        //reinsert v into heap
        insertHeapNode(v);
    }
}

bool minHeap::isEmpty() {
    return !heap.size();
}
/*
 * Dijkstra
 */
void dijKstra_algorithm(undirected_graph *g) {
    vector<vertex *>A;
    A.push_back(&(g->vertexes[0]));
    minHeap minheap;
    minheap.minHeapify( &(g->vertexes[0]),g);
    
    while (!minheap.isEmpty()) {
        vertex *v = minheap.extractMin();
        A.push_back(v);
        //for each edge of vertex, maintain the heap:
        for (map<int,int>::iterator it=v->edges.begin(); it!=v->edges.end(); it++) {
            minheap.reCaculateKey(v->distanceFromVextex1,it->first,it->second, g);
        }
    }
    
    for (vector<vertex*>::iterator it = A.begin(); it != A.end(); it++) {
        if ((*it)->label == 7) printVertexDistance(it);
        if ((*it)->label == 37) printVertexDistance(it);
        if ((*it)->label == 59) printVertexDistance(it);
        if ((*it)->label == 82) printVertexDistance(it);
        if ((*it)->label == 99) printVertexDistance(it);
        if ((*it)->label == 115) printVertexDistance(it);
        if ((*it)->label == 133) printVertexDistance(it);
        if ((*it)->label == 165) printVertexDistance(it);
        if ((*it)->label == 188) printVertexDistance(it);
        if ((*it)->label == 197) printVertexDistance(it);
    }
}




int main(int argc, const char * argv[]) {
    
    std::cout << "----- Dijkstra's shortest-path algorithm -----" << std::endl;
    std::cout << "Load file from 0.data(200) or 1.data1(8) or 2.data2(7) :" ;
    int userChoice = 0;
    scanf("%i", &userChoice);
    
    undirected_graph g = readfile(userChoice);
    dijKstra_algorithm(&g);
    return 0;
}
