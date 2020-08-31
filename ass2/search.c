#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "DLListSearch.h"
#include "search.h"
#define MAXSTRING 1000

dll_search findMatchedUrls(char* filename, int argc, char** queryWords){
    char delim[2] = " ";
    char line[MAXSTRING];
    char* token;
    char *pos;
    FILE *f;
    char **p = queryWords;
    dll_search L = newdll_search();

    if ((f = fopen(filename, "r")) == NULL) {
	   printf("Error! File doesnt exist!\n");
       exit(1);
    }

    while(fgets(line, MAXSTRING, f) != NULL)  {
        token = strtok(line, delim);
        if ((pos=strchr(token, ',')) != NULL)
            *pos = '\0';
        
        while (*p != NULL){
            if (strcmp(*p, token) == 0){
                while (token != NULL){
                    token = strtok(NULL, delim);
                    if ((pos=strchr(token, '\n')) != NULL)
                        break;
                    add_to_search(L, strdup(token));
                }
            }
            p = p + 1;
        }
        p = queryWords;
    }
    return L;
}

void findPagerank(char* filename, dll_search L){
    char delim[2] = " ";
    char line[MAXSTRING];
    char* token;
    char *url;
    float converted_pr;
    char *pos;
    FILE *f;

    if ((f = fopen(filename, "r")) == NULL) {
	   printf("Error! File doesnt exist!\n");
       exit(1);
    }

    while(fgets(line, MAXSTRING, f) != NULL)  {
        token = strtok(line, delim);
        if ((pos=strchr(token, ',')) != NULL)
            *pos = '\0';
        url = strdup(token);
        if (inDLL(L, token)){
            while (token != NULL){
                token = strtok(NULL, delim);
                if ((pos=strchr(token, '\n')) != NULL){
                    *pos = '\0';
                    converted_pr = atof(token);
                    set_pagerank(L, url, converted_pr);
                    break;
                }  
            }
        }
    }
    insertion_sort_DLL(L);
    sort_by_pagerank(L);
}