// dll_token.h - Interface to doubly-linked list ADT
// Written by John Shepherd, March 2013
// Last modified, Ashesh Mahidadia, Jan 2017 

#ifndef DLListTokens_H
#define DLListTokens_H

#include <stdio.h>
#include "DLListTokens.h"
#include "DLListUrls.h"

// External view of dll_token
// Implementation given in dll_token.c
// Implements a dll_token of string 

typedef struct token_dll_rep *dll_token;

void add_to_DLList(dll_token, char*, char*);
// create a new empty dll_token
dll_token newdll_token();

// free up all space associated with list
void freedll_token(dll_token);

// display items from a dll_token, comma separated
void showdll_token(dll_token L);
void normalise_values(char*);
void insertion_sort_DLL(dll_token);
char* get_token(dll_token, int);
int get_dll_token_length(dll_token);
dll_url get_url_list(dll_token, int);

#endif
