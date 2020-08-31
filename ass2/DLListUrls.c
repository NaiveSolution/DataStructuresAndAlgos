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

#include "DLListUrls.h"

// data structures representing dll_url

typedef struct DLListNode_url {
	char   *value;  // value of this list item (string)
	struct DLListNode_url *prev;
	               // pointer previous node in list
	struct DLListNode_url *next;
	               // pointer to next node in list
} DLListNode_url;

typedef struct url_dll_rep {
	int nitems;
	DLListNode_url *first; // first node in list
} url_dll_rep;

// create a new DLListNode_url (private function)
static DLListNode_url *newDLListNode_url(char *val) {
	DLListNode_url *new;
	char* token = strdup(val);
	new = malloc(sizeof(DLListNode_url));
	assert(new != NULL);
    new->value = token;  // for int, new->value = it;
	new->prev = new->next = NULL;
	return new;
}

// create a new empty dll_url
dll_url newdll_url() {
	struct url_dll_rep *L;

	L = malloc(sizeof (struct url_dll_rep));
	assert (L != NULL);
	L->nitems = 0;
	L->first = NULL;

	return L;
}

// only adds if the url is unique
void add_url(dll_url L, char* val) {
	assert(L != NULL);
	assert(val != NULL);

	if (strcmp(val, "") == 0){
		return;
	}
	DLListNode_url *p;
	p = L->first;
	if (p == NULL) {
		DLListNode_url *new = newDLListNode_url(val);
		L->first = new;
		L->nitems++;
	} else {
		while (p->next != NULL){
			p = p->next;
		}
		DLListNode_url *new = newDLListNode_url(val);
		p->next = new;
		new->prev = p;
		L->nitems++;
		insertion_sort_url(L);
	}
}

int get_length_url(dll_url L){
	return L->nitems;
}

bool inDLL(dll_url L, char* n){
	assert(L != NULL);
	DLListNode_url *p;
	p = L->first;
	while(p != NULL){
		if (!strcmp(p->value, n)){
			return true;
		}
		p = p->next;
	}
	return false;
}

// display items from a dll_url
void showdll_url(dll_url L) {
	assert(L != NULL);
	DLListNode_url *curr = L->first;
	while(curr != NULL){
		printf("%s ", curr->value);
		curr = curr->next;
	}
}

char* get_val_in_index_dll(dll_url L, int index){
   assert(L != NULL);
   DLListNode_url *p = L->first;
   for (int i = 0; i < index; i++){
      p = p->next;
   }
   return p->value;
}

// free up all space associated with list
void freedll_url(dll_url L) {
	assert(L != NULL);
	DLListNode_url *curr, *prev;
	curr = L->first;
	while (curr != NULL) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	free(L);
}

 // Use Insertion sort on dll url 
void insertion_sort_url(dll_url L){

	assert(L != NULL);
	DLListNode_url *i = L->first->next;
	DLListNode_url *j;
	while (i != NULL){
		j = i;
		while (j->prev != NULL && strcmp(j->prev->value, j->value) > 0){
			char *temp = j->value;
			j->value = j->prev->value;
			j->prev->value = temp;
			j = j->prev;
		}
		i = i->next;
	}
}   


