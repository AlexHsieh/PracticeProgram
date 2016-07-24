//
//  main.cpp
//  median
//
//  Created by Alex Hsieh on 7/24/16.
//  Copyright © 2016 Alex Hsieh. All rights reserved.
//


#include <fstream>
#include <sstream>
#include <iostream>     // std::cout
#include <algorithm>    // std::make_heap, std::pop_heap, std::push_heap, std::sort_heap
#include <vector>

using namespace std;

bool isPrint = false;

void printVector(vector<long> *v){
    if (isPrint) {
        for (unsigned i=0; i<v->size(); i++)
            std::cout << ' ' << (*v)[i];
        
        std::cout << '\n';
    }
}

struct naiveApproach {
    vector<long> naiv;
    long getMedian(long nextInput);
};

long naiveApproach::getMedian(long nextInput) {
    naiv.push_back(nextInput);
    sort(naiv.begin(), naiv.end());
    printVector(&naiv);
    if (naiv.size()%2) {
        //odd
        int i = (naiv.size()+1)*0.5-1;
        return naiv[i];
    } else {
        //even
        int i = naiv.size()*0.5-1;
        return naiv[i];
    }
}



// The value returned indicates whether the element passed as first argument is considered to be less than the second in the specific strict weak ordering it defines.
struct minComp{
    bool operator()(const long& a,const long& b) const{
        return a>b;
    }
};

struct median {
    vector<long> lowHeap; // extract high
    vector<long> highHeap; // extract min
    long getMedian(long nextInput);
};


long median::getMedian(long nextInput) {
    
    //add into lowHeap or highheap
    if (lowHeap.size() == 0) {
        //there is no value in either lowheap or highheap. We put it in low heap first
        lowHeap.push_back(nextInput);
        make_heap(lowHeap.begin(), lowHeap.end());
        return nextInput;
    } else if (highHeap.size() == 0) {

        //there is one value in lowheap but not highheap.
        
        if (nextInput > lowHeap.front()) {
            highHeap.push_back(nextInput);
            return lowHeap.front();
        } else {
            lowHeap.push_back(nextInput);
            push_heap(lowHeap.begin(), lowHeap.end());
            
            long value = lowHeap.front();
            pop_heap(lowHeap.begin(), lowHeap.end());
            lowHeap.pop_back();
            highHeap.push_back(value);
            push_heap(highHeap.begin(), highHeap.end(), minComp());
            return lowHeap.front();
        }
    } else if (nextInput > lowHeap.front() && nextInput < highHeap.front()) {
        lowHeap.push_back(nextInput);
        push_heap(lowHeap.begin(), lowHeap.end());
        
    } else if (nextInput < lowHeap.front()) {
        // here we choose put value into lowHeap
        lowHeap.push_back(nextInput);
        push_heap(lowHeap.begin(), lowHeap.end());
        
    } else if (nextInput > highHeap.front()) {
        highHeap.push_back(nextInput);
        push_heap(highHeap.begin(), highHeap.end(), minComp());
        
    } else {
        cout << "value : " << nextInput << "error" << endl;
    }
    
    
    //log
    if (isPrint) {
        cout << "lowheap:";
        printVector(&lowHeap);
        cout << "highheap:";
        printVector(&highHeap);
    }
    
    
    //return the
    if (lowHeap.size() == highHeap.size()) {
        return lowHeap.front();
    } else if (lowHeap.size() == highHeap.size() + 1) {
        return lowHeap.front();
    } else if (highHeap.size() == lowHeap.size() + 1) {
        return highHeap.front();
    } else if (lowHeap.size() == highHeap.size() + 2) {
        long value = lowHeap.front();
        pop_heap(lowHeap.begin(), lowHeap.end());
        lowHeap.pop_back();
        highHeap.push_back(value);
        push_heap(highHeap.begin(), highHeap.end(), minComp());
        return lowHeap.front();
    } else if (highHeap.size() == lowHeap.size() + 2) {
        long value = highHeap.front();
        pop_heap(highHeap.begin(), highHeap.end(), minComp());
        highHeap.pop_back();
        lowHeap.push_back(value);
        push_heap(lowHeap.begin(), lowHeap.end());
        return lowHeap.front();
    } else {
        
        cout << "error, lowHeap.size : " << lowHeap.size() << " , highHeap.size : " << highHeap.size() << endl;
        cout << "return 0\n";
        return 0;
    }
}



/*
 * Utility
 */
vector<long> readfile(int dataSetNumber) {
    
    string filePath = "/Users/alexhsieh/Documents/PracticeProgram/Design\ and\ Analysis\,\ Part\ 1/week6/median/";
    ifstream infile;
    switch (dataSetNumber) {
        case 0:
            filePath.append("data_Median.txt");
            break;
        case 1:
            filePath.append("data1");
            break;
        case 2:
            filePath.append("data2.txt");
            break;
        case 3:
            filePath.append("data3");
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
    vector<long> integers;
    
    while (std::getline(infile, line))
    {
        istringstream iss(line);
        long i;
        while (iss >> i ) {
            integers.push_back(i);
        }
    }
    
    return integers;
};



int main(int argc, const char * argv[]) {
    
    cout << "----- Caculate Median Problem -----" << std::endl;
    cout << "1. Use 2 heaps to caculate median for a stream of input which can achieve running time O(log n)\n";
    cout << "2. Use naive approach \n";
    int methodChoice = 0;
    scanf("%i", &methodChoice);
    
    
    cout << "Load file from 0.data(10000)(1213) or 1.data1(10)(50) or 2.data2(20)(1047) :" ;
    int userChoice = 0;
    scanf("%i", &userChoice);
    vector<long> v = readfile(userChoice);

    long medianSum = 0;
    if (methodChoice == 2) {
        naiveApproach np;
        for (int i=0; i<v.size(); i++) {
            long med = np.getMedian(v[i]);
            if (isPrint) {
                printf("med = %ld\n",med);
                printf("=============\n");
            }
            medianSum = medianSum + med;
        }
    } else {
        median median;
        for (int i=0; i<v.size(); i++) {
            long med = median.getMedian(v[i]);
            if (isPrint) {
                printf("med = %ld\n",med);
                printf("=============\n");
            }
            medianSum = medianSum + med;
        }
        
    }
    
    cout << "median sum = " << medianSum << endl;
    cout << "median mod = " << medianSum%10000 << endl;
    
    
    
//    std::vector<long> v = {10,30,5,15,20};
//    
////    std::make_heap (v.begin(),v.end());
////    v.push_back(40); std::push_heap (v.begin(),v.end());
//    std::cout << "initial max heap   : " << v.front() << '\n';
//    
//    std::pop_heap (v.begin(),v.end());
//    std::cout << "max heap before pop : " ;
//    printVector(&v);
//    v.pop_back();
//    std::cout << "max heap after pop : " << v.front() << '\n';
//    
//    v.push_back(49); std::push_heap (v.begin(),v.end());
//    std::cout << "max heap after push 49: " << v.front() << '\n';
//
//    v.push_back(99); std::push_heap (v.begin(),v.end());
//    std::cout << "max heap after push 99: " << v.front() << '\n';
//
//    std::sort_heap (v.begin(),v.end());
//    
//    std::cout << "final sorted range :";
//    for (unsigned i=0; i<v.size(); i++)
//        std::cout << ' ' << v[i];
//    
//    std::cout << '\n';
    return 0;
}
