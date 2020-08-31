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
#include "DLListTokens.h"
#include "DLListUrls.h"

// data structures representing dll_token

typedef struct DLListNode {
	char   *value;  // value of this list item (string)
	dll_url url_list;
	struct DLListNode *prev;
	               // pointer previous node in list
	struct DLListNode *next;
	               // pointer to next node in list
} DLListNode;

typedef struct token_dll_rep {
	int  nitems;      // count of items in list
	DLListNode *first; // first node in list
	DLListNode *last;  // last node in list
} token_dll_rep;

// create a new DLListNode (private function)
static DLListNode *newDLListNode(char *val, char *url) {
	DLListNode *new;
	char* token = strdup(val);
	new = malloc(sizeof(DLListNode));
	assert(new != NULL);

	dll_url L = newdll_url();
	assert(L != NULL);

	new->url_list = L;
	add_url(L, url);
    new->value = token;  // for int, new->value = it;
	
	new->prev = new->next = NULL;
	return new;
}

// create a new empty dll_token
dll_token newdll_token() {
	struct token_dll_rep *L;

	L = malloc(sizeof (struct token_dll_rep));
	assert (L != NULL);
	L->nitems = 0;
	L->first = NULL;
	L->last = NULL;

	return L;
}

void add_to_DLList(dll_token L, char* val, char* url) {
	assert(L != NULL);
	assert(val != NULL);
	if (strcmp(val, "") == 0){
		return;
	}
	DLListNode *p;
	DLListNode *curr;
	normalise_values(val);
	bool exists = false;
	curr = L->first;
	
	// check if the token already exists
	p = L->first;
	while ( p != NULL) {
		// if the token exists
		if (p != NULL && strcmp(p->value, val) == 0){
			if (!inDLL(p->url_list, url)){
				add_url(p->url_list, url);
			}
			exists = true;
			break;
		}
		p = p->next;
	}
	
	if (L->first == NULL){
		DLListNode *new = newDLListNode(val, url);
		L->nitems++;
		L->first = new;
   	} else if (!exists){
		DLListNode *new = newDLListNode(val, url);
		curr = L->first;
		while (curr->next != NULL){
			curr = curr->next;
		}
		curr->next = new;
		new->prev = curr;
		L->nitems++;
		L->last = new;
	}
	insertion_sort_DLL(L);
}

// display items from a dll_token, comma separated
void showdll_token(dll_token L) {
	assert(L != NULL);
	DLListNode *curr;
	int count = 0;
	for (curr = L->first; curr != NULL; curr = curr->next){
		count++;
		if(count > 1) {
			fprintf(stdout,"\n");
		}
		fprintf(stdout,"%s, ",curr->value);
		showdll_url(curr->url_list);
	}
	fprintf(stdout,"\n");
}

// free up all space associated with list
void freedll_token(dll_token L) {
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

void freedll_node(DLListNode *node){
	free(node->url_list);
	free(node);
}

 // Use Insertion sort on list
void insertion_sort_DLL(dll_token L){
	//showdll_token(L);
	assert(L != NULL);
	DLListNode *i = L->first->next;
	DLListNode *j;
	while (i != NULL){
		j = i;
		while (j->prev != NULL && strcmp(j->prev->value, j->value) > 0){
			char *temp = j->value;
			dll_url temp_url = j->url_list;
			j->value = j->prev->value;
			j->url_list = j->prev->url_list;
			j->prev->value = temp;
			j->prev->url_list = temp_url;
			j = j->prev;
		}
		i = i->next;
	}
}   

void normalise_values(char* token){
	char *pos;

	if ((pos=strchr(token, '\n')) != NULL){
		*pos = '\0';
	}
	if ((pos=strchr(token, '.')) != NULL || (pos=strchr(token, ';')) != NULL || (pos=strchr(token, '?')) != NULL || (pos=strchr(token, ',')) != NULL){
		*pos = '\0';
	}
	for(int i = 0; token[i]; token++){
		token[i] = tolower(token[i]);
	}

}

char* get_token(dll_token L, int index){
	assert(L != NULL);
	DLListNode *p = L->first;
	for (int i = 0; i < index; i++){
		p = p->next;
	}
	return p->value;
}

int get_dll_token_length(dll_token L){
	return L->nitems;
}

dll_url get_url_list(dll_token L, int index){
	assert(L != NULL);
	DLListNode *p = L->first;
	for (int i = 0; i < index; i++){
		p = p->next;
	}
	return p->url_list;
}