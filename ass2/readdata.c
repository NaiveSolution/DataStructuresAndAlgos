#include <string.h>
#include <stdio.h>
#include "readdata.h"
#include <stdbool.h>

#define MAXSTRING 1000

DLListStr GetCollection(void){

    DLListStr L = newDLListStr();
    const char *search = "url";
    char delim[2] = " ";
    char *token;
    char line[MAXSTRING];
    FILE *f;

    if ((f = fopen("collection.txt", "r")) == NULL) {
	   printf("Error!\n");
    }

    while(fgets(line, MAXSTRING, f) != NULL)  {
        /* first token */
        token = strtok(line, delim);
        if (strchr(search, *token)){
            char *pos;
            if ((pos=strchr(token, '\n')) != NULL)
                *pos = '\0';
            add_to_DLList(L,strdup(token));
        }
        /* iterate over the rest of the tokens */
        while( token != NULL ) {
            token = strtok(NULL, delim);
            if (token != NULL){
                if (strchr(search, *token)){
                    char *pos;
                    if ((pos=strchr(token, '\n')) != NULL)
                        *pos = '\0';
                    add_to_DLList(L,strdup(token));
                }
            }
        }
    }
    return L;
}

// GetGraph takes the List L, which is the list of urls in collections.txt
Graph GetGraph(List L){
    Graph g = newGraph(L);

    for (int i = 0; i < get_list_length(L); i++){
        // inputs the list of url names from collections.txt into readsection1
        readSection1(strdup(get_item_ll(L, i)), g);
    }
    return g;
}

void readSection1(char *urlname, Graph g){
    List L = newListStr();
    Edge e;

    // get the head of the graphs url list
    e.v = strdup(urlname);

    const char *first = "#start";
    const char *second = "Section-1";
    const char *end = "#end";
    const char *search = "url";
    char delim[2] = " ";
    char *token;
    char line[MAXSTRING] ;
    FILE *f;
    bool exit_loop = false;
    
    if ((f = fopen(strcat(urlname,".txt"), "r")) == NULL) {
	   printf("Error!\n");
    }

    while(fgets(line, MAXSTRING, f) != NULL) {
        /* first token */
        if (exit_loop){
            break;
        }
        token = strtok(line, delim);
        if (strchr(first, *token)){
            token = strtok(NULL, delim);
            if (strchr(second, *token)) {
                while(fgets(line, MAXSTRING, f) != NULL) {
                    token = strtok(line, delim);
                    if (strchr(end, *token)) {
                        token = strtok(NULL, delim);
                        if (strchr(second, *token)) {
                            exit_loop = true;
                            break;
                        }
                    }
                    if (strchr(search, *token)){
                        char *pos;
                        if ((pos=strchr(token, '\n')) != NULL)
                            *pos = '\0';
                        add_to_list(L,strdup(token));
                    }
                    while( token != NULL) {
                        token = strtok(NULL, delim);
                        if (token != NULL) {
                            if (strchr(search, *token)){
                                char *pos;
                                if ((pos=strchr(token, '\n')) != NULL)
                                    *pos = '\0';
                                add_to_list(L,strdup(token));
                            }
                        }
                    }
                }
            }
        }   
    }

    for (int i = 0; i < get_list_length(L); i++){
        e.w = get_item_ll(L, i);
        insertEdge(g, e);
    }
}

List* calculatePageRank(Graph g, float d, float diffPR, int maxIterations){

    int N;
    float starting_rank;
    float *next_pi;
    next_pi = malloc(sizeof(float) * get_graph_size(g));
    float diff = 0.0;
    int iteration = 0;
    float sum  = 0.0;
    float sum_diff = 0.0;
    float delta_PR = 0.0;
    float new_PR_i;
    char *name_head;
    char *name_link;
    List *urls = malloc(get_graph_size(g) * sizeof(List));
    List *list_i;
    List *list_j;

    N = (float)get_graph_size(g);
    starting_rank = (float)1/N;
    
    initial_rank(g, starting_rank);
    diff = diffPR;
    showGraph(g);
    while (iteration < maxIterations && diff >= diffPR){
        iteration++;
        sum_diff = 0;
        for (int i = 0; i < N; i++){

            sum = 0;
            name_head = get_url_head(g, i);             // char* of the url list head
            list_i = get_url_list(g, i);

            for (int j = 0; j < N; j++){
                name_link = get_url_head(g, j);         // char* of the url list head
                list_j = get_url_list(g, j);            // List of the url pointing to the head

                // ignore self loops
                if (strcmp(name_head, name_link) == 0){
                    continue;
                }
                if (get_list_length(*list_j) == 1){
                    delta_PR = get_list_PR(*list_j) / (float)N;
                    sum = sum + delta_PR;
                }
                // confer PR from the links pj toward target pi
                if (inLL(*list_j, name_head)){
                    delta_PR = get_list_PR(*list_j) / (get_list_length(*list_j) - 1);
                    sum = sum + delta_PR;
                }
            }
            new_PR_i = ((1.0f - d)/(float)N) + d*sum;
            next_pi[i] = new_PR_i;
        }
        for (int k = 0; k < N; k++){
            list_i = get_url_list(g, k);
            sum_diff = sum_diff + fabs(next_pi[k] - get_list_PR(*list_i));
            set_list_PR(*list_i, next_pi[k]);
            urls[k] = copy_list(*list_i);
            set_list_PR(urls[k], next_pi[k]);
        } 
        diff = sum_diff;
    }
    insertion_sort_PR(urls, g);
    return urls;
}

void insertion_sort_PR(List* urls, Graph g){

    int i;
	int j;
    for(i = 0; i < get_graph_size(g); i++) {
        j = i;
        //i is not the first element
        while(j > 0) {
            //not in order
            if(get_list_PR(urls[j-1]) < get_list_PR(urls[j])) {
                List temp = urls[j-1];
                urls[j-1] = urls[j];
                urls[j] = temp;
            }
            //in order
            else {
                break;
            }
            j--;
        }
    }
}

void writeToPageRankFile(List* urls, Graph g){

    int out_degree;
    float page_rank;
    List list_i;

    FILE *f = fopen("pagerankList.txt", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    for (int i = 0; i < get_graph_size(g); i++){
        list_i = urls[i];
        const char *url_name = get_list_head(list_i);
        out_degree = get_list_length(list_i) - 1;
        page_rank = get_list_PR(list_i);
        fprintf(f, "%s, %d, %.7f\n", url_name, out_degree, page_rank);
    }
    fclose(f);
    return;
}