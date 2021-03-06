//
//  main.m
//  MergeSort
//
//  Created by Alex Hsieh on 3/6/16.
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

@interface MergeSort : NSObject
@property (nonatomic) NSUInteger numberOfInversion;
+ (NSArray *)mergeSort:(NSArray *)arrayToSort;
+ (NSArray *)randomNumberArray:(NSUInteger)num;

@end

@implementation MergeSort

static MergeSort *sharedInstance = nil;

+ (instancetype)sharedInstance {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[MergeSort alloc]init];
    });
    return sharedInstance;
}

+ (NSArray *)randomNumberArray:(NSUInteger)num {
    NSMutableArray *arr = [NSMutableArray array];
    for (int i = 0; i < num; i++) {
        [arr addObject:@(rand())];
    }
    return arr;
}

+ (NSArray *)mergeSort:(NSArray *)arrayToSort {
    
    if (arrayToSort.count == 1) {
        return arrayToSort;
    } else {
        NSArray *arr = [self dividedArrayIntoOneItemInEachArray:arrayToSort];
        arrayToSort =nil;
        NSArray *combinedArr = [self combineAllArrayInArrays:arr];
        NSLog(@"numberOfInversion = %ld",[MergeSort sharedInstance].numberOfInversion);
        return combinedArr[0];
    }
    
}

+ (NSArray *)dividedArrayIntoOneItemInEachArray:(NSArray *)arrayToDivided {
    NSMutableArray *arr = [NSMutableArray array];
    for (NSNumber *num in arrayToDivided) {
        [arr addObject:@[num]];
    }
    return arr.copy;
}

+ (NSArray *)combineAllArrayInArrays:(NSArray *)arrays {

    NSArray *combinedArr = arrays;
    int log = 0;
    while (combinedArr.count != 1) {
        log++;
//        NSLog(@"log:%d",log);
        @autoreleasepool {
            NSArray *cArr = @[];
            for (int i = 0; i<=combinedArr.count-2; i=i+2) {
                cArr = [cArr arrayByAddingObject:[self compareAndCombineArray:combinedArr[i] andArray:combinedArr[i+1]]];
            }
            if (combinedArr.count%2 == 1 ) {
                cArr = [cArr arrayByAddingObject:combinedArr.lastObject];
            }
            
            combinedArr = cArr;
        }
    }
    return combinedArr;
}

+ (NSArray *)compareAndCombineArray:(NSArray *)arr1 andArray:(NSArray *)arr2 {
    NSMutableArray *combinedArr = [NSMutableArray array];
    int k = 0,i = 0,j = 0;
    for (k = 0; k < arr1.count+arr2.count; k++) {
        
        if (i < arr1.count && j < arr2.count) {
            if ([arr1[i] integerValue] < [arr2[j] integerValue]) {
                [combinedArr addObject:arr1[i]];
                i++;
            } else {
                [combinedArr addObject:arr2[j]];
                j++;
                [MergeSort sharedInstance].numberOfInversion = [MergeSort sharedInstance].numberOfInversion + (arr1.count - i);
            }
        } else {
            if (i < arr1.count) {
                [combinedArr addObject:arr1[i]];
                i++;
            } else if (j < arr2.count) {
                [combinedArr addObject:arr2[j]];
                j++;
            }
        }
        
    }
    return combinedArr;
}

@end

vector<vector<int>> dividedArrayIntoOneItemInEachArray(vector<int> &A) {
    unsigned long count = A.size();
    std::vector<vector<int>> dividedArr (count);
    
    for(int i=0; i<count; i++){
        dividedArr[i].push_back(A[i]);
    }
    
//    std::cout << '\n';
    
//    for(int i=0; i<count; i++)
//        cout << dividedArr[i][0] << " ";
    
    //    for(vector<vector<int> >::iterator it = dividedArr.begin(); it != dividedArr.end(); ++it)
    //    {
    //        //it is now a pointer to a vector<int>
    //        for(vector<int>::iterator jt = it->begin(); jt != it->end(); ++jt)
    //        {
    //            // jt is now a pointer to an integer.
    //            cout << "jt:" << *jt << ", ";
    //        }
    //        cout << endl;
    //    }
    
//    std::cout << '\n';
    return dividedArr;
}

unsigned long int inversionCount = 0;

vector<int> compareAndMergeArray(vector<int> &A, vector<int> &B) {
    int indexA = 0;
    int indexB = 0;
    int indexC = 0;
    
    vector<int> C(A.size()+B.size()) ;
    
    while (indexA < A.size() && indexB < B.size()) {
//        cout << "A:" << A[indexA] << ", " << "B:" << B[indexB] << endl;
        if (A[indexA] < B[indexB]) {
            C[indexC] = A[indexA];
            indexA++;
            indexC++;
        } else {
            C[indexC] = B[indexB];
            indexB++;
            indexC++;
            inversionCount = inversionCount + (A.size()-indexA);
        }
    }
    
    while (indexA < A.size()) {
        C[indexC] = A[indexA];
        indexA++;
        indexC++;
    }
    while (indexB < B.size()) {
        C[indexC] = B[indexB];
        indexB++;
        indexC++;
    }
    return C;
}

vector<int> combineAllArrayInArray(vector<vector<int>> &A) {

    std::vector<vector<int>> combinedArr = A;
    int log = 0;
    while (combinedArr.size() != 1) {
        log++;
//        cout << "log: " << log << endl;
        unsigned long cArrSize = combinedArr.size()%2 == 1 ? combinedArr.size()/2+1 : combinedArr.size()/2;
        std::vector<vector<int>> cArr(cArrSize);
        for (int i = 0; i<=combinedArr.size()-2; i=i+2) {
            std::vector<int> a = compareAndMergeArray(combinedArr[i],combinedArr[i+1]);
            cArr[i/2] = a;
        }
        if (combinedArr.size()%2 == 1 ) {
            unsigned long size = cArr.size();
            cArr[size-1] = combinedArr[combinedArr.size()-1];
        }
        
        combinedArr = cArr;
    }
    
    vector<int> b = combinedArr[0];
    return b;
    
}

vector<int> mergesort (vector<int> &A)
{    
    std::vector<vector<int>> dividedArr = dividedArrayIntoOneItemInEachArray(A);
    vector<int> mergedArr = combineAllArrayInArray(dividedArr);
    NSLog(@"final inversion count = %ld",inversionCount);
    
    return mergedArr;
}

vector<int> randomNumArr(int a) {
    vector<int> arr(a);
    for (int i=0; i<a; i++) {
        arr[i] = rand();
    }
    return arr;
}


vector<int> readfile(int numberOfItem) {
    
    std::ifstream infile;
    if (numberOfItem == 6) {
        infile.open("/Users/alexhsieh/Documents/PracticeProgram/Design and Analysis, Part 1/merge sort/MergeSort/xx.txt");
    } else {
        infile.open("/Users/alexhsieh/Documents/PracticeProgram/Design and Analysis, Part 1/merge sort/MergeSort/data.txt");
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
        NSLog(@"-----  Merge Sort  -----");
        NSLog(@"Do you want to 1.read data from file or 2.manually create random number?:");
        int userChoice = 0;
        scanf("%i", &userChoice);
        
        int mergeSize = 0;
        
        std::vector<int> myArray;
        if (userChoice == 1) {
            NSLog(@"Do you want to 1.read small test data(6) or 2.large test data(100000)?:");
            int datasize = 0;
            scanf("%i", &datasize);
            datasize = datasize == 1 ? 6:100000;
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
        

        //user input
        NSLog(@"Do the Merge sort of this array");
        
        //C++ merge sort
        NSDate *startTime = [NSDate date];
        vector<int> sortedArrUseC = mergesort(myArray);
        NSLog(@"C++ sorting time = %f",[[NSDate date] timeIntervalSinceDate:startTime]);
        if(mergeSize<=50) cout << "C++ original array count =" << myArray.size() << ", array =" << &myArray << endl;
        if(mergeSize<=50) {
            cout << "C++ sorted array count =" << sortedArrUseC.size() << ", sorted array =" << &sortedArrUseC << endl;
        } else {
            long int size = sortedArrUseC.size();
            NSLog(@"sorted array count = %ld, sorted array = [%d,%d,...,%d,%d]",size,sortedArrUseC[0],sortedArrUseC[1],sortedArrUseC[size-2],sortedArrUseC[size-1]);
        }
        
        
        NSMutableArray *mutArr = [NSMutableArray array];
        for (int i = 0; i<myArray.size(); i++) {
            [mutArr addObject:@(myArray[i])];
        }
        //objective-C merge sort
        NSArray *arr = [mutArr copy];//[MergeSort randomNumberArray:userInput];
        startTime = [NSDate date];
        NSArray *sortedArr = [MergeSort mergeSort:arr];
        NSLog(@"objective-C sorting time = %f",[[NSDate date] timeIntervalSinceDate:startTime]);
        if(mergeSize<=50) NSLog(@"original array count = %ld, array = %@",arr.count,arr);
        if(mergeSize<=50) {
            NSLog(@"sorted array count = %ld, sorted array = %@",sortedArr.count,sortedArr);
        } else {
            NSLog(@"sorted array count = %ld, sorted array = [%@,%@,...,%@,%@]",sortedArr.count,sortedArr[0],sortedArr[1],sortedArr[sortedArr.count-2],sortedArr.lastObject);
        }
        
        
        
        //use cocoa sorting function
        NSDate *cocoaStartTime = [NSDate date];
        NSArray *cocoaSortedArr = [arr sortedArrayUsingComparator:^NSComparisonResult(NSNumber *num1, NSNumber *num2){
            if (num1.integerValue > num2.integerValue) {
                return NSOrderedDescending;
            } else {
                return NSOrderedAscending;
            }
        }];
        NSLog(@"cocoa sorting time = %f",[[NSDate date] timeIntervalSinceDate:cocoaStartTime]);
        if(mergeSize<=50) {
            NSLog(@"cocoa sorted array count = %ld, sorted array = %@",cocoaSortedArr.count,cocoaSortedArr);
        } else {
            NSLog(@"sorted array count = %ld, sorted array = [%@,%@,...,%@,%@]",cocoaSortedArr.count,cocoaSortedArr[0],cocoaSortedArr[1],cocoaSortedArr[sortedArr.count-2],cocoaSortedArr.lastObject);
        }

    }
    return 0;
}
