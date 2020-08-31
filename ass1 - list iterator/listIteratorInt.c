/*
  listIteratorInt.c : list Iterator ADT implementation
  Written by: Muhammed Tariq Mosaval 
  Student ID: z5214836
  Date: 18/12/2018
*/
/*
	The following picture depicts the structure of the Iterator ADT outlined in this
	file:

		CURSOR_POINT	 NODE	  
			 _____      _____      _____      _____      _____
			|  n  |--->|  n  |--->|  n  |--->|  n  |--->|  n  |---> NULL
			|     |    | val |    |     |    | val |    |     |
	NULL<---|__p__|<---|__p__|<---|__p__|<---|__p__|<---|__p__|

	n = next, p = previous, val = value
*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "listIteratorInt.h"

//a Cursor_Point is a structure that links two Nodes together
typedef struct Cursor_Point {
	struct Node* next;		// Cursor_Point pointer to the next Node
	struct Node* prev;		// Cursor_Point pointer to the previous Node
} Cursor_Point;

// A Node contains the int value and the links to the next and previous Cursor_Points
typedef struct Node {
	int    value;  				// value of this list item (int)
	struct Cursor_Point* prev;	// pointer to the previous Cursor_Point
	struct Cursor_Point* next;	// pointer to the next Cursor_Point
} Node;

typedef struct IteratorIntRep {

	struct Cursor_Point* first_cursor;			// Keeping track of the first cursor
	struct Cursor_Point* last_cursor;			// Likewise for the last cursor
	struct Cursor_Point* current_cursor;		// A cursor point that changes according to the program
	struct Cursor_Point* operation_cursor;		// A cursor point that keeps track of the last
												// next/findnext/previous/findprevious cursor
	struct Node* operation_node;				// The node that will be operated on (deleted or set)
	bool isNext;								// A call to next/findnext will set this to true in order
												// to track the correct operation cursor and node
	bool deleteOn;								// This is turned on only when next/findnext/previous/findprevious is called
  
} IteratorIntRep;

// create new empty Iterator. This will set up a new Cursor_Point node that has next
// and previous pointers that point initially to NULL

IteratorInt IteratorIntNew(){

	// A new Iterator is made with a single cursor point
	// that has a previous and next pointer both pointing to NULL
	IteratorIntRep* new;
	Cursor_Point* first_cursor;
	new = malloc(sizeof(struct IteratorIntRep));
	assert(new != NULL);
	first_cursor = malloc(sizeof(struct Cursor_Point));
	assert(first_cursor != NULL);

	// Setup the iterators first, last, current and operation cursors and nodes
	new->current_cursor = first_cursor;
	new->last_cursor = new->current_cursor;
	new->first_cursor = new->current_cursor;
	new->current_cursor->next = NULL;
	new->current_cursor->prev = NULL;
	new->operation_cursor = NULL;
	new->operation_node = NULL;
	new->isNext = true;
	new->deleteOn = false;

	return new;
}

// Extra function to print the iterator
void printIt(IteratorInt it){

	struct Cursor_Point* printer;
	int result;
	printer = it->first_cursor;
	while (printer->next != NULL){
		result = printer->next->value;
		if (printer == it->current_cursor){
			printf(" ^ ");
		}
		printf(" %d ", result);
		printer = printer->next->next;
	}
	if (it->current_cursor->next == NULL){
		printf(" ^ ");
	}
	printf("\n");
	//it->operation_cursor->next = NULL;
	//it->operation_cursor->prev = NULL;
	fflush(stdout);
}

// reset() moves the current cursor to the first cursor in the iterator
void reset(IteratorInt it){
	assert(it != NULL);
  	it->current_cursor = it->first_cursor;
	it->deleteOn = false;
}

int add(IteratorInt it, int v){
	assert(it != NULL);
	// A call to add creates a new cursor and a new node, both initially unlinked
	// The new node is assigned v
	Node* new_node;
	new_node = malloc(sizeof(Node));
	assert(new_node != NULL);
	new_node->value = v;
	Cursor_Point* new_cursor;
	new_cursor = malloc(sizeof(Cursor_Point));
	assert(new_cursor != NULL);

	// Set up the new Nodes next and previous pointers
	// to point to the current cursor_point and the new cursor_point
	// This is to ensure that a call to add will move the new Node in front of the Node
	// behind the current cursor
	new_node->prev = it->current_cursor;
	new_node->next = new_cursor;

	// Set up the new cursor point
	new_cursor->prev = new_node;
	new_cursor->next = NULL;

	// if the current_cursor is at the end, then the current and last cursor points
	// will be changed to the new cursor
	if (it->current_cursor->next == NULL){
		it->current_cursor->next = new_node;
		it->last_cursor = new_cursor;
		it->current_cursor = new_cursor;
		it->deleteOn = false;
		return 1;
	}

	// if the current_cursor is not at the end, then store the current_cursors next in a temporary
	// value, and reposition ....
	else {
		Node* temp_next = it->current_cursor->next;
		it->current_cursor->next->prev = new_cursor;
		it->current_cursor->next = new_node;
		new_cursor->next = temp_next;
		it->current_cursor = new_cursor;
		it->deleteOn = false;
		return 1;
	}
	it->deleteOn = false;
	return 0;
}

int hasNext(IteratorInt it){
	assert(it != NULL);
	//check if the current cursor is at the end of the list, if it is, then there is no next
	if (it->current_cursor->next == NULL){
		it->deleteOn = false;
		return 0;
	}
	it->deleteOn = false;
	return 1;
}

int hasPrevious(IteratorInt it){
	assert(it != NULL);
	// check if the current cursor is at the start of the list, if it is, then theres no previous
	if (it->current_cursor->prev == NULL){
		it->deleteOn = false;
		return 0;
	}
	it->deleteOn = false;
	return 1;
}

int *next(IteratorInt it){
	assert(it != NULL);
	Cursor_Point* temp_cursor;
	// return NULL if the current cursor is at the end of the list
	if (it->current_cursor->next == NULL){
		return NULL;
	}

	it->isNext = true;
	int *p = &(it->current_cursor->next->value);
	// Set the iterators operation node to the next node and 
	// operation cursor to the current cursor 
	it->operation_node = it->current_cursor->next;
	it->operation_cursor = it->current_cursor;
	//move the current cursor to the next cursor using a temp cursor
	temp_cursor = it->current_cursor->next->next;
	it->current_cursor = temp_cursor;
	// turn on deleting or setting of the iterator
	it->deleteOn = true;

	return p;

}

int *previous(IteratorInt it){	
	assert(it != NULL);
	Cursor_Point* temp_cursor;
	// return NULL if the current cursor is at the start of the list
	if (it->current_cursor->prev == NULL){
		return NULL;
	}

	it->isNext = false;
	int *p = &(it->current_cursor->prev->value);
	// Set the iterators operation node to the previous node and 
	// operation cursor to the current cursor
	it->operation_node = it->current_cursor->prev;
	it->operation_cursor = it->current_cursor;
	//move the current cursor to the previous cursor using a temp cursor
	temp_cursor = it->current_cursor->prev->prev;
	it->current_cursor = temp_cursor;
	// turn on deleting or setting of the iterator
	it->deleteOn = true;

	return p;

}

int deleteElm(IteratorInt it){
	assert(it != NULL);
	Node* next_node;
	Node* prev_node;


	// Next delete functions
	// If the operation cursor is at the start of the list, then just change the current
	// cursors previous pointer to null and free the operation cursor and node
	if (it->isNext && it->operation_cursor->prev == NULL && it->deleteOn == true){

		free(it->operation_cursor);
		free(it->operation_node);

		it->current_cursor->prev = NULL;
		it->operation_node = NULL;
		it->operation_cursor = NULL;
		it->first_cursor = it->current_cursor;
		// turn off deleting and setting for the iterator
		it->deleteOn = false;

		return 1;
	}

	// If the operation cursor is NOT at the start of the list
	if (it->isNext && it->operation_cursor->prev != NULL && it->deleteOn == true){

		prev_node = it->operation_cursor->prev;
		it->operation_cursor->prev->next = it->current_cursor;
		it->current_cursor->prev = prev_node;

		free(it->operation_cursor);
		free(it->operation_node);

		it->operation_node = NULL;
		it->operation_cursor = NULL;
		// turn off deleting and setting for the iterator
		it->deleteOn = false;

		return 1;

	}

	// Previous delete functions
	// If the cursor is at the end of the list, then just change the current
	// cursors next pointer to null and free the operation cursor and node
	if (!(it->isNext) && it->operation_cursor->next == NULL && it->deleteOn == true){

		free(it->operation_node);
		free(it->operation_cursor);

		it->operation_node = NULL;
		it->operation_cursor = NULL;
		it->current_cursor->next = NULL;
		it->last_cursor = it->current_cursor;
		// turn off deleting and setting for the iterator
		it->deleteOn = false;

		return 1;
	}

	// If the cursor is NOT at the end of the list
	if (!(it->isNext) && it->operation_cursor->next != NULL && it->deleteOn == true){

		next_node = it->operation_cursor->next;
		it->current_cursor->next = next_node;
		it->operation_cursor->next->prev = it->current_cursor;

		free(it->operation_cursor);
		free(it->operation_node);

		it->operation_node = NULL;
		it->operation_cursor = NULL;
		// turn off deleting and setting for the iterator
		it->deleteOn = false;

		return 1;
	}

	return 0;
}

int set(IteratorInt it, int v){
	assert(it != NULL);
	// set() works only after a valid iterator call
	if (it->deleteOn == false){
		return 0;
	} 
	it->operation_node->value = v;
	// turn off deleting and setting for the iterator
	it->deleteOn = false;
	return 1;
}

int *findNext(IteratorInt it, int v){
	assert(it != NULL);
	struct Cursor_Point* temp_cursor;
	it->isNext = true;
	// Start iterating through the whole list, starting at the current cursor
	// and ending at the last cursor. Uses a temporary cursor to iterate through the list
	for (temp_cursor = it->current_cursor; temp_cursor->next != NULL || temp_cursor->prev->value == v; temp_cursor = temp_cursor->next->next) {
		// If already at the end of the list, do nothing
		if (it->current_cursor->next == NULL){
			return NULL;
		}
		// If the next node has the value we are looking for, then move the current cursor
		// to in front of this node, move the operation node to the desired node
		// and the operation cursor to the cursor BEFORE the operation node
		if (temp_cursor->next->value == v){
			it->operation_cursor = temp_cursor;
			it->operation_node = temp_cursor->next;
			temp_cursor = temp_cursor->next->next;
			it->current_cursor = temp_cursor;
			int *p = &(it->current_cursor->prev->value);
			it->deleteOn = true;
			// turn off deleting and setting for the iterator
			return p;
		}
	}
	return NULL;
}

int *findPrevious(IteratorInt it, int v){
	assert(it != NULL);
	struct Cursor_Point* temp_cursor;
	it->isNext = false;
	// Start iterating through the whole list, starting at the current cursor
	// and ending at the first cursor. Uses a temporary cursor to iterate through the list
		for (temp_cursor = it->current_cursor; temp_cursor->prev != NULL || temp_cursor->next->value == v; temp_cursor = temp_cursor->prev->prev) {
			// If already at the start of the list, do nothing
			if (it->current_cursor->prev == NULL){
				return NULL;
			}
			// If the previous node has the value we are looking for, then move the current cursor
			// behind this node, move the operation node to the desired node
			// and the operation cursor to the cursor AFTER the operation node
			if (temp_cursor->prev->value == v){
				it->operation_cursor = temp_cursor;
				it->operation_node = temp_cursor->prev;
				temp_cursor = temp_cursor->prev->prev;
				it->current_cursor = temp_cursor;
				int *p = &(it->current_cursor->next->value);
				// turn off deleting and setting for the iterator
				it->deleteOn = true;
				return p;
			}
		}
		return NULL;
}

void freeIt(IteratorInt it){
	assert(it != NULL);
	// Temporary pointers to the structures to preserve the linkages in deletion
	Cursor_Point *deleter, *next_cursor;
	Node* next_node;
	
	deleter = it->first_cursor;
	
	// Typical pattern for iterating through a linked list
	while (deleter->next != NULL){
		next_node = deleter->next;
		next_cursor = deleter->next->next;
		free(deleter);
		deleter = NULL;
		free(next_node);
		next_node = NULL;
		deleter = next_cursor;
		//free(next_cursor);
	}
	free(deleter);
	deleter = NULL;
	
	free(it);
	it->first_cursor = NULL;
	it->last_cursor = NULL;
	it = NULL;
	
	/* ; */
	
	return;

}





