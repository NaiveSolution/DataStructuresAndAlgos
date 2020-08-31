// dll_search.h - Interface to doubly-linked list ADT
// Written by John Shepherd, March 2013
// Last modified, Ashesh Mahidadia, Jan 2017 

#ifndef DLListTokens_H
#define DLListTokens_H

#include <stdio.h>
#include <stdbool.h>

#include "DLListSearch.h"

// External view of dll_search
// Implementation given in dll_search.c
// Implements a dll_search of string 

typedef struct search_dll_rep *dll_search;

void add_to_search(dll_search, char*);
// create a new empty dll_search
dll_search newdll_search();

// free up all space associated with list
void freedll_search(dll_search);
bool inDLL(dll_search, char*);
// display items from a dll_search, comma separated
void showdll_search(dll_search);
void show_max_dll_length(dll_search);
void show_auxiliary(dll_search);
void insertion_sort_DLL(dll_search);
char* get_token(dll_search, int);
int get_dll_search_length(dll_search);
void set_pagerank(dll_search, char*, float);
void sort_by_pagerank(dll_search);
#endif
