#include "readdata.h"
#include <stdio.h>
#include <stdlib.h>
#include "DLListStr.h"

int main(int argc, char* argv[]){

    float d = atof(argv[1]);
    float diffPR = atof(argv[2]);
    int maxIterations = atoi(argv[3]);
    List *ordered_urls;

    DLListStr dll_collection = GetCollection();
    List list_collection = newListStr();

    for (int i = 0; i < get_dll_length(dll_collection); i++){
        add_to_list(list_collection, *get_item(dll_collection, i));
    }
    freeDLListStr(dll_collection);
    Graph g = GetGraph(list_collection);
    ordered_urls = calculatePageRank(g, d, diffPR, maxIterations);
    writeToPageRankFile(ordered_urls, g);

    freeGraph(g);
    return 0;
} 