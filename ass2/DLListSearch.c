/*
 Implementation of doubly-linked list ADT for string values.
 Written by Ashesh Mahidadia Jan 2018, based on code writted by John Shepherd 2015.
 You may need to modify the following implementation and test it properly before using 
 in your program.
*/


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "DLListSearch.h"

// data structures representing dll_search
typedef struct DLListNode {
	char   *value;			// value of this list item (string)
	int num_matches;
	float PR;
	struct DLListNode *prev; // pointer previous node in list
	struct DLListNode *next; // pointer to next node in list
} DLListNode;

typedef struct search_dll_rep {
	int  nitems;      	// count of items in list
	DLListNode *first; 	// first node in list
	DLListNode *last;  	// last node in list
} search_dll_rep;

// create a new DLListNode (private function)
static DLListNode *newDLListNode(char *val) {
	DLListNode *new;
	char* token = strdup(val);
	new = malloc(sizeof(DLListNode));
	assert(new != NULL);

    new->value = token;  // for int, new->value = it;
	new->num_matches = 0;
	new->PR = 0.0;
	new->prev = new->next = NULL;
	return new;
}

DLListNode* find_url(dll_search L, char* url){
	DLListNode *p = L->first;

	while (p->next != NULL && strcmp(p->value, url) != 0){
		p = p->next;
	}
	return p;
}

// create a new empty dll_search
dll_search newdll_search() {
	struct search_dll_rep *L;

	L = malloc(sizeof (struct search_dll_rep));
	assert (L != NULL);
	L->nitems = 0;
	L->first = NULL;
	L->last = NULL;

	return L;
}

bool inDLL(dll_search L, char* n){
	assert(L != NULL);
	DLListNode *p;
	p = L->first;
	while(p != NULL){
		if (!strcmp(p->value, n)){
			return true;
		}
		p = p->next;
	}
	return false;
}

void add_to_search(dll_search L, char* url) {
	assert(L != NULL);
	if (strcmp(url, "") == 0){
		return;
	}

	DLListNode *p = L->first;
	// if list is empty
	if (p == NULL){
		DLListNode *new = newDLListNode(url);
		new->num_matches++;
		L->first = new;
		L->nitems++;
		L->last = new;
	} 
	
	// if list doesnt contain the url
	else if (!inDLL(L, url)){
		while (p->next != NULL){
			p = p->next;
		}
		DLListNode *new = newDLListNode(url);
		new->num_matches++;
		p->next = new;
		new->prev = p;
		L->nitems++;
		L->last = new;
	} 
	
	// if the list contains the url, dont create a new node
	// instead increment the nodes num_matches
	else if (inDLL(L, url)){
		p = find_url(L, url);
		p->num_matches++;
	}
	
}

void set_pagerank(dll_search L, char* url, float input_pr){
	assert(L != NULL);
	
	DLListNode *p = L->first;
	while (strcmp(p->value, url) != 0){
		p = p->next;
	}
	p->PR = input_pr;
}

// display items from a dll_search, comma separated
void showdll_search(dll_search L) {
	assert(L != NULL);
	DLListNode *curr;
	for (curr = L->first; curr != NULL; curr = curr->next){
		fprintf(stdout,"%s\n",curr->value);
	}
}

void show_max_dll_length(dll_search L){
	assert(L != NULL);
	DLListNode *curr = L->first;
	for (int i = 0; i < 30; curr = curr->next){
		fprintf(stdout,"%s\n",curr->value);
	}
}

void show_auxiliary(dll_search L){
	assert(L != NULL);
	DLListNode *curr;
	for (curr = L->first; curr != NULL; curr = curr->next){
		fprintf(stdout,"url: \"%s\" matches: %d PageRank: %f\n",curr->value, curr->num_matches, curr->PR);
	}
}

// free up all space associated with list
void freedll_search(dll_search L) {
	assert(L != NULL);
	DLListNode *curr, *prev;
	curr = L->first;
	while (curr != NULL) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	free(L);
}

// Use Insertion sort on list
void insertion_sort_DLL(dll_search L){
	assert(L != NULL);
	DLListNode *i = L->first->next;
	DLListNode *j;
	while (i != NULL){
		j = i;
		while (j->prev != NULL && j->prev->num_matches < j->num_matches){
			char *temp_value = j->value;
			float temp_pr = j->PR;
			int temp_matches = j->num_matches;

			j->value = j->prev->value;
			j->PR = j->prev->PR;
			j->num_matches = j->prev->num_matches;

			j->prev->value = temp_value;
			j->prev->PR = temp_pr;
			j->prev->num_matches = temp_matches;
			j = j->prev;
		}
		i = i->next;
	}
}   

void sort_by_pagerank(dll_search L){
	assert(L != NULL);
	DLListNode *i = L->first->next;
	DLListNode *j;
	while (i != NULL){
		j = i;
		while (j->prev != NULL && j->prev->num_matches == i->num_matches && j->prev->PR < j->PR){
			char *temp_value = j->value;
			float temp_pr = j->PR;

			j->value = j->prev->value;
			j->PR = j->prev->PR;

			j->prev->value = temp_value;
			j->prev->PR = temp_pr;

			j = j->prev;
		}
		i = i->next;
	}
}

char* get_token(dll_search L, int index){
	assert(L != NULL);
	DLListNode *p = L->first;
	for (int i = 0; i < index; i++){
		p = p->next;
	}
	return p->value;
}

int get_dll_search_length(dll_search L){
	return L->nitems;
}

/* dll_search get_url_list(dll_search L, int index){
	assert(L != NULL);
	DLListNode *p = L->first;
	for (int i = 0; i < index; i++){
		p = p->next;
	}
	return p->url_list;
} */