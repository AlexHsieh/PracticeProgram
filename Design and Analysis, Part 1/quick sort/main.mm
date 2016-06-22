//
//  main.m
//  quicksort
//
//  Created by Alex Hsieh on 6/22/16.
//  Copyright © 2016 Alex Hsieh. All rights reserved.
//

#import <Foundation/Foundation.h>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

#pragma mark - quick sort

unsigned long int numberOfComparision = 0;


vector<int> quicksort (vector<int> &A , int pivot)
{
    if (A.size() == 1 || A.size() == 0) {
        return A;
    }
    int pivotValue = 0;
    if (pivot == 1) {
        pivotValue = A[0];
        
    } else if(pivot == 2) {
        pivotValue = A[A.size()-1];
        
        //switch first value and the last value
        int value0 = A[0];
        A[0] = pivotValue;
        A[A.size()-1] = value0;
        
    } else {
        int first = A[0];
        int last = A[A.size()-1];
        int central = 0;
        if (A.size()%2) {
            //odd
            central = A[A.size()*0.5];
        } else {
            //even
            central = A[A.size()*0.5-1];
        }
        int pivotIndex = 0;
        if ((first > last && first < central) || (first < last && first > central)) {
            pivotValue = first;
            pivotIndex = 0;
        } else if ((last > first && last < central) || (last < first && last > central) ) {
            pivotValue = last;
            pivotIndex = (int)A.size()-1;
        } else {
            pivotValue = central;
            pivotIndex = A.size()%2 ? A.size()*0.5 : A.size()*0.5-1;
        }
        
        int value0 = A[0];
        A[0] = pivotValue;
        A[pivotIndex] = value0;
    }
    
    
    numberOfComparision = numberOfComparision + A.size()-1;
    //sort
    int i = 1;
    for (int j=1; j<A.size(); j++) {
        if (A[j]>pivotValue) {
            //do nothing
        } else {
            if (i != j) {
                int valueJ = A[j];
                int valueI = A[i];
                A[i] = valueJ;
                A[j] = valueI;
            }
            i++;
        }
    }
    
    //switch pivot and the last element of smaller than pivot
    int valueI = A[i-1];
    A[0] = valueI;
    A[i-1] = pivotValue;
    
    //create 2 arrr
    vector<int> smallerThanPivot(i-1);
    for (int k=0; k<i-1; k++) {
        smallerThanPivot[k] = A[k];
    }
    vector<int> largerThanPivot(A.size()-i);
    for (int k=i; k<A.size(); k++) {
        largerThanPivot[k-i] = A[k];
    }
    //sort 2 array
    quicksort(smallerThanPivot, pivot);
    quicksort(largerThanPivot, pivot);
    
    //update array A
    for (int k=0; k<i-1; k++) {
        A[k] = smallerThanPivot[k];
    }
    
    for (int k=i; k<A.size(); k++) {
        A[k] = largerThanPivot[k-i];
    }
    

    return A;
}

#pragma mark - utility

vector<int> randomNumArr(int a) {
    vector<int> arr(a);
    for (int i=0; i<a; i++) {
        arr[i] = rand();
    }
    
    if (arr.size() <= 50) {
        for (int i=0; i<arr.size(); i++) {
            cout << "arr["<< i << "]:" << arr[i] << endl;
        }
    }
    
    return arr;
}

vector<int> readfile(int numberOfItem) {
    
    std::ifstream infile;
    if (numberOfItem == 6) {
        infile.open("/Users/alexhsieh/Documents/PracticeProgram/Design and Analysis, Part 1/quick sort/xx.txt");
    } else {
        infile.open("/Users/alexhsieh/Documents/PracticeProgram/Design and Analysis, Part 1/quick sort/data.txt");
    }
    std::string line;
    if (!infile) { NSLog(@"no file, return");}
    
    vector<int> arr(numberOfItem);
    int i = 0;
    
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        int aNumber;
        if (!(iss >> aNumber)) { break; } // error
        arr[i] = aNumber;
        if (numberOfItem < 50){cout << "arr["<< i << "]:" << arr[i] << endl;}
        i++;
    }
    
    return arr;
};

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        NSLog(@"-----  Quick Sort  -----");
        NSLog(@"Do you want to 1.read data from file or 2.manually create random number?:");
        int userChoice = 0;
        scanf("%i", &userChoice);
        
        int mergeSize = 0;
        
        std::vector<int> myArray;
        if (userChoice == 1) {
            NSLog(@"Do you want to 1.read small test data(6) or 2.large test data(10000)?:");
            int datasize = 0;
            scanf("%i", &datasize);
            datasize = datasize == 1 ? 6:10000;
            mergeSize = datasize;
            myArray = readfile(datasize);
        } else {
            NSLog(@"Given an array with N integer. Input N:");
            int userInput = 0;
            scanf("%i", &userInput);
            mergeSize = userInput;
            srand([NSDate timeIntervalSinceReferenceDate]);
            myArray = randomNumArr(userInput);
        }
        
        NSLog(@"Pick up pivot: 1.first 2.last 3.median-of-three: ");
        int pivot = 0;
        scanf("%i", &pivot);
        
        //quick sort
        NSDate *startTime = [NSDate date];
        vector<int> sortedArrUseC = quicksort(myArray, pivot);
        NSLog(@"C++ sorting time = %f",[[NSDate date] timeIntervalSinceDate:startTime]);
        cout << "C++ number of comparision =" << numberOfComparision << endl;
        if(mergeSize<=50) {
            cout << "C++ sorted array count =" << sortedArrUseC.size() << ", sorted array =" << &sortedArrUseC << endl;
            int i = 0;
            while (i<sortedArrUseC.size())
            {
                cout << "arr["<< i << "]:" << sortedArrUseC[i] << endl;
                i++;
            }
        } else {
            long int size = sortedArrUseC.size();
            NSLog(@"sorted array count = %ld, sorted array = [%d,%d,...,%d,%d]",size,sortedArrUseC[0],sortedArrUseC[1],sortedArrUseC[size-2],sortedArrUseC[size-1]);
        }
        
    }
    return 0;
}
