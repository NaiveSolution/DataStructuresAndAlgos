#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "DLListStr.h"
#include "list.h"
#include "Graph.h"
#include "math.h"

DLListStr GetCollection(void);
Graph GetGraph(List);
void readSection1(char*, Graph);
List* calculatePageRank(Graph, float, float, int);
void insertion_sort_PR(List*, Graph);
void writeToPageRankFile(List*, Graph);