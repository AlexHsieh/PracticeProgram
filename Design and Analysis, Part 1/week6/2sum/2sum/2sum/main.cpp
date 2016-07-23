//
//  main.cpp
//  2sum
//
//  Created by Alex Hsieh on 7/22/16.
//  Copyright © 2016 Alex Hsieh. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <math.h>

using namespace std;

void exhaustiveSearch(vector<long int> *v, int lowerBound, int higherBound) {
    vector<int>marked(higherBound-lowerBound+1);
    for (int i=0; i<marked.size(); i++) {
        marked[i]=0;
    }
    
    long int k =0;
    for (long int i=0 ; i<v->size(); i++) {
        for (long int j=0; j<v->size(); j++) {
            long int sum = (*v)[i]+(*v)[j];
            if (sum >= lowerBound && sum <= higherBound && (*v)[i]!=(*v)[j]) {
//                printf("(%d,%d),",(*v)[i],(*v)[j]);
                marked[sum-lowerBound] = 1;
                k++;
            }
        }
    }
    
    int sumMustBeUnique = 0;
    for (int i=0; i<marked.size(); i++) {
        if (marked[i] == 1) {
            sumMustBeUnique++;
        }
    }
    cout << "\n";
    cout << "sum in the range:" << k << endl;
    cout << "unique sum :" << sumMustBeUnique << endl;
}

void twoSumInTheRange(vector<int> *sortedVector, int lowerBound, int higherBound) {
    int i=0;
    int j=(int)sortedVector->size()-1;
    int k=0;
    while (i!=j) {
        int t = (*sortedVector)[i] + (*sortedVector)[j];
        if (t < lowerBound) {
            i++;
        } else if(t > higherBound) {
            j--;
        } else {
            k++;
            
        }
    }
}

struct node {
    int number;
    node *leftPtr;
    node *rightPtr;
};


void createBinaryTree(vector<int> *v) {
    //        4
    //      /   \
    //     2     6
    //    / \   / \
    //   1   3 5   7
    //
    // Create binary from the smallest value
    
    node rootNode;
    rootNode.number = (*v)[0];
    int layer = 1;
    int numberOfNodeInLayer = pow(2, layer);
    int totalNodes = 2*numberOfNodeInLayer+1;
    while (totalNodes < v->size()) {
        // create next rootnode
        node nextRootNode;
        nextRootNode.number = (*v)[numberOfNodeInLayer-1];
        nextRootNode.leftPtr = &rootNode;
        rootNode = nextRootNode;
        
        //create root node right tree
        int firstRightNodeIndex = numberOfNodeInLayer + numberOfNodeInLayer*0.5;
    }
}

/*
 * Utility
 */
void quicksort_p (vector<long int> *B , long int locStart, long int locEnd, long int pivot)
{
    long int sortSize = locEnd - locStart + 1;
    if (sortSize <= 1 ) {
        return;
    }
    long int pivotValue = 0;
    if (pivot == 1) {
        pivotValue = (*B)[locStart];
        
    } else if(pivot == 2) {
        pivotValue = (*B)[locEnd];
        
        //switch first value and the last value
        long int value0 = (*B)[locStart];
        (*B)[locStart] = pivotValue;
        (*B)[locEnd] = value0;
        
    } else {
        long int first = (*B)[locStart];
        long int last = (*B)[locEnd];
        long int median = 0;
        if (B->size()%2) {
            //odd
            median = (*B)[sortSize*0.5 + locStart];
        } else {
            //even
            median = (*B)[sortSize*0.5-1 + locStart];
        }
        long int pivotIndex = locStart;
        if ((first > last && first < median) || (first < last && first > median)) {
            pivotValue = first;
            pivotIndex = locStart;
        } else if ((last > first && last < median) || (last < first && last > median) ) {
            pivotValue = last;
            pivotIndex = locEnd;
        } else {
            pivotValue = median;
            pivotIndex = B->size()%2 ? (sortSize*0.5 + locStart) : (sortSize*0.5-1 + locStart);
        }
        
        long int value0 = (*B)[locStart];
        (*B)[locStart] = pivotValue;
        (*B)[pivotIndex] = value0;
    }
    
    
    //sort
    long int i = locStart+1;
    for (long int j=locStart+1; j<locStart+sortSize; j++) {
        if ((*B)[j]>pivotValue) {
            //do nothing
        } else {
            if (i != j) {
                long int valueJ = (*B)[j];
                long int valueI = (*B)[i];
                (*B)[i] = valueJ;
                (*B)[j] = valueI;
            }
            i++;
        }
    }
    
    //switch pivot and the last element of smaller than pivot
    long int valueI = (*B)[i-1];
    (*B)[locStart] = valueI;
    (*B)[i-1] = pivotValue;
    
    //create 2 locStart * locEnd
    long int locStart_smallerThanPivot = locStart;
    long int locEnd_smallerThanPivot = i-2;
    
    long int locStart_largerThanPivot = i;
    long int locEnd_largerThanPivot = locEnd;
    
    //sort 2 array
    quicksort_p(B, locStart_smallerThanPivot, locEnd_smallerThanPivot, pivot);
    quicksort_p(B, locStart_largerThanPivot, locEnd_largerThanPivot, pivot);
}


vector<long int> readfile(int dataSetNumber) {
    
    string filePath = "/Users/alexhsieh/Documents/PracticeProgram/Design\ and\ Analysis\,\ Part\ 1/week6/2sum/";
    ifstream infile;
    switch (dataSetNumber) {
        case 0:
            filePath.append("data.txt");
            break;
        case 1:
            filePath.append("data1");
            break;
        case 2:
            filePath.append("data2");
            break;
            
        default:
            cout << "use data1\n";
            filePath.append("data1");
            break;
    }
    
    infile.open(filePath);
    if (!infile) {
        std::cout << "no file... check file path!" <<std::endl;
    }
    
    string line;
    vector<long int> integers;
    
    while (std::getline(infile, line))
    {
        istringstream iss(line);
        long int i;
        while (iss >> i ) {
            integers.push_back(i);
        }
    }

    cout << "before quicksort, number of integers:" << integers.size() << endl;

    //sort it
    quicksort_p(&integers, 0, (long int)integers.size()-1, 3);
    //erase the duplicate
    integers.erase(unique(integers.begin(), integers.end()), integers.end());
    
    cout << "number of integers:" << integers.size() << endl;
    return integers;
};



int main(int argc, const char * argv[]) {
    cout << "----- 2 SUM in the range / 2 SUM Problem -----" << std::endl;
    cout << "1. compute the number of l < x+y < h\n";
    cout << "2. compute typical x+y = t\n";
    int problemType = 0;
    scanf("%i", &problemType);
    
    if (problemType != 1) {
        cout << "will implement later, process 1...\n";
    }
    
    
    cout << "Load file from 0.data(Huge) or 1.data1(between 3,10)(28)(8) or 2.data2(between -4,2)(?)(5):" ;
    int userChoice = 0;
    scanf("%i", &userChoice);
    vector<long int> v = readfile(userChoice);
    
    int lowerBound =0;
    int higherBound =0;
    if (userChoice == 0) {
        lowerBound = -10000;
        higherBound = 10000;
    } else if(userChoice == 2){
        lowerBound = -4;
        higherBound = 2;
    } else {
        lowerBound = 3;
        higherBound = 10;
    }
    
    cout << "Use 1. Naive approach, O(n2)(take a long time for huge input)\n";
    cout << "    2. better approach O(nlogn):\n" ;
//    if (userChoice == 2) {
        cout << "    3. best approach O(n):\n" ;
//    }
    scanf("%i", &userChoice);
    
    
    time_t  times;
    std::cout << "start time: " << time(&times) << std::endl;
    if (userChoice == 1) {
        exhaustiveSearch(&v, lowerBound, higherBound);
    } else {
    
    }
    time_t  timee;
    std::cout << "end time: " << time(&timee) << std::endl;
    
    return 0;
}
