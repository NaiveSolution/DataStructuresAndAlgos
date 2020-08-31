// Graph ADT
// Adjacency List Representation ... COMP9024 17s2
#include "Graph.h"
#include "list.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct GraphRep {
   //List_of_Lists *url;  // list of lists
   List *url;         // array of lists
   int   nV;            // #vertices
   int   nE;            // #edges
} GraphRep;

Graph newGraph(List L) {
   int len = get_list_length(L);
   assert(len >= 0);
   int i;
   
   Graph g = malloc(sizeof(GraphRep));
   assert(g != NULL);
   g->nE = 0;
   g->nV = len;
   // allocate memory for array of lists
   g->url = malloc(len * sizeof(List));
   assert(g->url != NULL);
   for (i = 0; i < len; i++){
      g->url[i] = newListStr();
      add_to_list(g->url[i], get_item_ll(L, i));
   }
   return g;
}

bool validV(Graph g, Vertex v) {
    bool exists = false;
    assert(g != NULL);
    for (int i = 0; i < g->nV; i++){
       if (inLL(g->url[i], v)){
          exists = true;
       }
    }
    return (g != NULL && v != NULL && exists);
}  

void insertEdge(Graph g, Edge e) {

   // Digraph
   // Source: v -- Destination: w
   // v --> w
   assert(g != NULL && validV(g, e.v) && validV(g, e.w));
   
   for (int i = 0; i < g->nV; i++){
      // search for e.v in the list of lists
      if (is_head_LL(g->url[i], e.v)){
         // if the link to w doesnt exist, add it
         if (!inLL(g->url[i], e.w)){
            add_to_list(g->url[i], e.w);
            g->nE++;
         }
      }
   }
}

void removeEdge(Graph g, Edge e) {

   // Digraph
   // Source: v -- Destination: w
   // v --> w
   assert(g != NULL && validV(g,e.v) && validV(g,e.w));

   for (int i = 0; i < g->nV; i++){
      // search for e.v in the list of lists
      if (is_head_LL(g->url[i],e.v)){
         // if the link to w exists, delete it
         if (inLL(g->url[i], e.w)){
            deleteLL(g->url[i], e.w);
            g->nE--;
         }
      }
   }
} 

bool adjacent(Graph g, Vertex v, Vertex w) {
   
   // Digraph
   // Source: v -- Destination: w
   // v --> w
   assert(g != NULL && validV(g,v) && validV(g,w));
   bool exists = false;
   for (int i = 0; i < g->nV; i++){
       if (inLL(g->url[i], v) && inLL(g->url[i], w)){
          exists = true;
       }
    }
   return exists;
} 

void showGraph(Graph g) {
   assert(g != NULL);

   printf("Number of vertices: %d\n", g->nV);
   printf("Number of edges: %d\n", g->nE);

   for (int i = 0; i < g->nV; i++){
      printf("\n[%s] = <", get_item_ll(g->url[i],0));
      for (int j = 1; j < get_list_length(g->url[i]); j++){
         if (get_list_length(g->url[i])== 1){
            printf(" >\n");
         } else {
            printf(" %s ", get_item_ll(g->url[i],j));
         }
      }
      printf(">\n");
   }
}

int get_graph_size(Graph g){
   assert( g != NULL);
   return g->nV;
}

int get_graph_edges(Graph g){
   assert( g != NULL);
   return g->nE;
}

char* get_url_head(Graph g, int index){
   assert( g != NULL);
   return get_list_head(g->url[index]);
}

List* get_url_list(Graph g, int index){
   assert( g != NULL);
   return &g->url[index];
}

void freeGraph(Graph g) {
   assert(g != NULL);
   for (int i = 0; i < g->nV; i++){
      freeLL(g->url[i]);
      int a = 2;
      a++;
   }
   free(g);
}

void initial_rank(Graph g, float initial){
   assert(g != NULL);
   if (g->nV == 0){
      return;
   }
   for (int i = 0; i < g->nV; i++){
      set_list_PR(g->url[i], initial);
   }
}

