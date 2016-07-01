//
//  main.m
//  RCA_objc
//
//  Created by Alex Hsieh on 7/1/16.
//  Copyright © 2016 Alex Hsieh. All rights reserved.
//

#import <Foundation/Foundation.h>

#include <iostream>
#include <fstream>
#include <sstream>

@interface Vertex : NSObject
@property (nonatomic,assign) unsigned int number;
@property (nonatomic,strong) Vertex *parent;
@end
@implementation Vertex

-(instancetype)initWithCoder:(NSCoder *)decoder
{
    self.number = [[decoder decodeObjectForKey:@"VertexNumber"] unsignedIntValue];
    self.parent = nil;//[decoder decodeObjectForKey:@"VertexMergedNumberSet"];
    return self;
}

-(void)encodeWithCoder:(NSCoder *)encoder
{
    [encoder encodeObject:@(self.number) forKey:@"VertexNumber"];
}
@end

@interface Edge : NSObject
@property (nonatomic) unsigned int srcNumber;
@property (nonatomic) unsigned int desNumber;
@end
@implementation Edge
-(instancetype)initWithCoder:(NSCoder *)decoder
{
    self.srcNumber = [[decoder decodeObjectForKey:@"Edge.srcNumber"] unsignedIntValue];
    self.desNumber = [[decoder decodeObjectForKey:@"Edge.desNumber"] unsignedIntValue];
    return self;
}

-(void)encodeWithCoder:(NSCoder *)encoder
{
    [encoder encodeObject:@(self.srcNumber) forKey:@"Edge.srcNumber"];
    [encoder encodeObject:@(self.desNumber) forKey:@"Edge.desNumber"];
}
@end


@interface UndirctedGraph : NSObject
@property (nonatomic) unsigned int numberOfVertexs;

// graph is represented as an array of edges.
// Since the graph is undirected, the edge
// from src to dest is also edge from dest
// to src. Both are counted as 1 edge here.
@property (nonatomic,strong) NSMutableArray *edges;
@property (nonatomic,strong) NSMutableArray *vertexs;
@end

@implementation UndirctedGraph

- (NSMutableArray *)edges {
    if (!_edges) {
        _edges = [NSMutableArray array];
    }
    return _edges;
}

- (NSMutableArray *)vertexs {
    if (!_vertexs) {
        _vertexs = [NSMutableArray array];
    }
    return _vertexs;
}

-(instancetype)copyWithZone:(NSZone *)zone
{
    return [NSKeyedUnarchiver unarchiveObjectWithData:
            [NSKeyedArchiver archivedDataWithRootObject:self]
            ];
}

-(instancetype)initWithCoder:(NSCoder *)decoder
{
    self.edges = [decoder decodeObjectForKey:@"UndirctedGraph.edges"];
    self.vertexs = [decoder decodeObjectForKey:@"UndirctedGraph.vertexs"];
    self.numberOfVertexs =  [[decoder decodeObjectForKey:@"UndirctedGraph.numberOfVertexs"] unsignedIntValue];
    return self;
}

-(void)encodeWithCoder:(NSCoder *)encoder
{
    [encoder encodeObject:self.edges forKey:@"UndirctedGraph.edges"];
    [encoder encodeObject:self.vertexs forKey:@"UndirctedGraph.vertexs"];
    [encoder encodeObject:@(self.numberOfVertexs) forKey:@"UndirctedGraph.numberOfVertexs"];
}
@end


@interface KargerContractionAlgorithm : NSObject
+ (unsigned int)kargerContractionAlgorithm:(UndirctedGraph*)graph;
@end
@implementation KargerContractionAlgorithm

+ (unsigned int)kargerContractionAlgorithm:(UndirctedGraph*)graph {
    
    while (graph.numberOfVertexs != 2) {
        //1. randomly pickup one edge
        Edge *edge = graph.edges[ rand() % graph.edges.count];
//        NSLog(@"start contract edge: %d-%d",edge.srcNumber, edge.desNumber);
        
        //2. remove the edge; merge 2 vertex
        //Note: there are 2 edges here
        Edge *oppositEdge = [self findEdgeOfSrc:edge.desNumber dest:edge.srcNumber inGraph:graph];
        [graph.edges removeObjectsInArray:@[edge,oppositEdge]];

        
        //merge 2 vertex and union all merged vertex number
        Vertex *vsrc = [self findRootVertex:graph.vertexs[edge.srcNumber-1]];
        Vertex *vdes = [self findRootVertex:graph.vertexs[edge.desNumber-1]];
        if (vsrc == vdes) {
            NSLog(@"this should not happen.. we found a edge which 2 points already merged");
        } else {
            vdes.parent = vsrc;
            graph.numberOfVertexs--;
        }
    
        
        //3. remove self loop
//        NSLog(@"remove self loop, numberofvertex:%d",graph.numberOfVertexs);
        NSMutableArray *edgeToRmove = [NSMutableArray array];
        for (Edge *edge in graph.edges) {
            Vertex *vsrc = [self findRootVertex:graph.vertexs[edge.srcNumber-1]];
            Vertex *vdes = [self findRootVertex:graph.vertexs[edge.desNumber-1]];
            if (vsrc == vdes) {
                [edgeToRmove addObject:edge];
            }
        }
        [graph.edges removeObjectsInArray:edgeToRmove];
    }
    
    return graph.edges.count * 0.5;
}

+ (Edge *)findEdgeOfSrc:(unsigned int)src dest:(unsigned int)dest inGraph:(UndirctedGraph*)graph {
    NSPredicate *filter = [NSPredicate predicateWithFormat:@"srcNumber == %ld AND desNumber == %d",src,dest];
    NSArray *edges = graph.edges.copy;
    return [edges filteredArrayUsingPredicate:filter].firstObject;
}

+ (Vertex *)findRootVertex:(Vertex *)v {
    if (v.parent) {
        return [self findRootVertex:v.parent];
    }
    return v;
}

@end

/*
 * Read File
 */
UndirctedGraph* readfile(int dataSetNumber) {
    
    std::ifstream infile;
    switch (dataSetNumber) {
        case 1:
            infile.open("/Users/alexhsieh/Documents/PracticeProgram/Design\ and\ Analysis\,\ Part\ 1/randomized\ contraction\ algorithm/data.txt");
            break;
        case 2:
            infile.open("/Users/alexhsieh/Documents/PracticeProgram/Design\ and\ Analysis\,\ Part\ 1/randomized\ contraction\ algorithm/testdata1");
            break;
        case 3:
            infile.open("/Users/alexhsieh/Documents/PracticeProgram/Design\ and\ Analysis\,\ Part\ 1/randomized\ contraction\ algorithm/testdata2");
            break;
        case 4:
            infile.open("/Users/alexhsieh/Documents/PracticeProgram/Design\ and\ Analysis\,\ Part\ 1/randomized\ contraction\ algorithm/testdata3");
            break;
        case 5:
            infile.open("/Users/alexhsieh/Documents/PracticeProgram/Design\ and\ Analysis\,\ Part\ 1/randomized\ contraction\ algorithm/testdata4");
            break;
        case 6:
            infile.open("/Users/alexhsieh/Documents/PracticeProgram/Design\ and\ Analysis\,\ Part\ 1/randomized\ contraction\ algorithm/testdata5");
            break;
        case 7:
            infile.open("/Users/alexhsieh/Documents/PracticeProgram/Design\ and\ Analysis\,\ Part\ 1/randomized\ contraction\ algorithm/testdata6");
            break;
            
        
        default:
            infile.open("/Users/alexhsieh/Documents/PracticeProgram/Design\ and\ Analysis\,\ Part\ 1/randomized\ contraction\ algorithm/testdata1");
            break;
    }
    
    if (!infile) {
        std::cout << "no file, return" <<std::endl;
    }
    
    std::string line;
    UndirctedGraph *graph = [[UndirctedGraph alloc]init];
    graph.numberOfVertexs = 0;
    while (std::getline(infile, line))
    {
        int i = 0;
        std::istringstream iss(line);
        int aNumber;
        int src = 0;
        while (iss >> aNumber) {
            if (i != 0) {
                Edge *edge = [[Edge alloc]init];
                edge.srcNumber = src;
                edge.desNumber = aNumber;
                [graph.edges addObject:edge];
            } else {
                src = aNumber;
                Vertex *v = [[Vertex alloc]init];
                v.number = aNumber;
                v.parent = nil;
                [graph.vertexs addObject:v];
                graph.numberOfVertexs++;
            }
            i++;
        }
        
    }
    
    return graph;
};

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        std::cout << "-----  Randomized Contraction Algorithm  -----" << std::endl;
        std::cout << "Load file from 1.data(200) or 2.data1(8)(2) or 3.data2(8)(2) 4.data3(8)(1) 5.data4(8)(1) 6.data5(40)(3) 7.data6(8)(2)?:" ;
        int userChoice = 0;
        scanf("%i", &userChoice);
        
        UndirctedGraph *graph = readfile(userChoice);
        unsigned long int brutleForceNumber = graph.vertexs.count* graph.vertexs.count;
        brutleForceNumber = brutleForceNumber > 1000 ? 1000:brutleForceNumber;
        int miniCut = 100;
        for (int i=0; i< brutleForceNumber; i++) {
            NSDate *start = [NSDate date];
            
            srand(clock());
            @autoreleasepool {
                UndirctedGraph *g = graph.copy;
                int karCut = [KargerContractionAlgorithm kargerContractionAlgorithm:g];
//                if(brutleForceNumber<100)NSLog(@"Cut%d = %d",i,karCut);
                if (karCut < miniCut) {
                    miniCut = karCut;
                    NSLog(@"found New mini cut:%d on %dth try",miniCut,i);
                }
            }
            
            if (i%50==0) {
                NSLog(@"%dth execution took %f ",i,[[NSDate date] timeIntervalSinceDate:start]);
            }
        }
        NSLog(@"Final miniCut:%d",miniCut);
    }
    return 0;
}
