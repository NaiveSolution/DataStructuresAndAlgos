// dll_url.h - Interface to doubly-linked list ADT
// Written by John Shepherd, March 2013
// Last modified, Ashesh Mahidadia, Jan 2017 

#ifndef DLListUrls_H
#define DLListUrls_H
#include <stdbool.h>
#include <stdio.h>
#include "DLListUrls.h"


typedef struct url_dll_rep *dll_url;

void add_url(dll_url, char*);
// create a new empty dll_url
dll_url newdll_url();
// free up all space associated with list
void freedll_url(dll_url);
// display items from a dll_url, comma separated
bool inDLL(dll_url, char*);
int get_length_url(dll_url);
void showdll_url(dll_url L);
void insertion_sort_url(dll_url);
char* get_val_in_index_dll(dll_url, int);
#endif
