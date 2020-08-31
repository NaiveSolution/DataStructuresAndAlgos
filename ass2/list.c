// Linked list implementation ... COMP9024 17s2
#include "list.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct NodeL {
   char *val;
   struct NodeL *next;
} NodeL;

NodeL *makeNodeL(char *n) {
   NodeL *new = malloc(sizeof(NodeL));
   assert(new != NULL);
   new->val = n;
   new->next = NULL;
   return new;
}

List newListStr() {
   NodeL *new = malloc(sizeof(NodeL));
   assert(new != NULL);
   new->val = NULL;
   new->next = NULL;
   return new;
}

// input the head NodeL to this function
void add_to_LL(List p, char* input) {
   assert( input != NULL && p != NULL);
 
   // if List is empty
   if (p->val == NULL){
      p->val = input;
   } else {
      NodeL *new = makeNodeL(input);
      while (p->next != NULL){
         if ((strcmp(input, p->val) > 0 && strcmp(input, p->next->val) < 0) || strcmp(input, p->val) == 0){
            NodeL *temp = p->next;
            p->next = new;
            new->next = temp;
            sorted_list(p);
            break;
         }
         p = p->next;
      }
      p->next = new;
      sorted_list(p);
   }
}

 void sorted_list(List p){
   NodeL *node = NULL, *temp_node = NULL;
   char* temp_val;//temp variable to store node data
   node = p;
   //temp = node;//temp node to hold node data and next link

      while(node != NULL) {
         temp_node = node;
         while (temp_node->next !=NULL) { //travel till the second last element
            
            if(strcmp(temp_node->val, temp_node->next->val) > 0) {// compare the data of the nodes 
               temp_val = temp_node->val;
               temp_node->val = temp_node->next->val;
               temp_node->next->val = temp_val;
            }
            temp_node = temp_node->next;    // move to the next element 
         }
         node = node->next;    // move to the next node
      }
   
} 

// input the head NodeL to return list length
int get_length_LL(List p){
   assert(p != NULL);
   int i = 0;
   while(p != NULL){
      ++i;
      p = p->next;
   }
   return i;
}

bool inLL(List L, char *n) {
   assert(L != NULL);

   while(L != NULL){
      if (!strcmp(L->val, n)){
         return true;
      }
      L = L->next;
   }
   return false;
} 

void showLL(List L) {
   assert(L != NULL);
   while(L != NULL){

      printf("%s ", L->val);
      
      L = L->next;
   }
}

void freeLL(List L) {
   assert(L != NULL);

   while(L != NULL){
      NodeL *temp = L->next;
      free(L);
      L = temp;
   }
}

char* get_val_in_index_ll(List L, int index){
   assert(L != NULL);
   for (int i = 0; i < index; i++){
      L = L->next;
   }
   return L->val;
}

/* void normalise_values(List L){
   char *input;
   char *pos;
   for( ; L != NULL; L = L->next){
      input = L->val;
      for(int i = 0; input[i]; input++){
         input[i] = tolower(input[i]);
      }
      input = L->val;
      if ((pos=strchr(input, '.')) != NULL || (pos=strchr(input, ';')) != NULL || (pos=strchr(input, '?')) != NULL || (pos=strchr(input, ',')) != NULL){
         *pos = '\0';
      }
      L->val = input;
   }

}
 */



