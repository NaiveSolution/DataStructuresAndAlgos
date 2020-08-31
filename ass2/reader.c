#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "reader.h"
#include <stdbool.h>
#include "DLListTokens.h"
#include "DLListUrls.h"

#define MAXSTRING 1000
 
dll_url GetCollection(void){

    dll_url L = newdll_url();
    const char *search = "url";
    char delim[2] = " ";
    char *token;
    char line[MAXSTRING];
    FILE *f;

    if ((f = fopen("collection.txt", "r")) == NULL) {
	   printf("Error!\n");
    }

    while(fgets(line, MAXSTRING, f) != NULL)  {
        
        token = strtok(line, delim);
        if (strchr(search, *token)){
            char *pos;
            if ((pos=strchr(token, '\n')) != NULL)
                *pos = '\0';
            add_url(L,strdup(token));
        }
        
        while( token != NULL ) {
            token = strtok(NULL, delim);
            if (token != NULL){
                if (strchr(search, *token)){
                    char *pos;
                    if ((pos=strchr(token, '\n')) != NULL)
                        *pos = '\0';
                    add_url(L,strdup(token));
                }
            }
        }
    }
    return L;
}

void readSection2(dll_token words_urls_dll, dll_url url_list, int index){
    char* url = get_val_in_index_dll(url_list, index);
    char* url_copy = strdup(url);

    const char *first = "#start";
    const char *second = "Section-2";
    const char *end = "#end";
    char delim[2] = " ";
    char *token;
    char *empty_string = "";
    char line[MAXSTRING] ;
    FILE *f;
    bool exit_loop = false;
    char *pos;

    if ((f = fopen(strcat(url,".txt"), "r")) == NULL) {
	   printf("Error: url file \"%s\" does not exist!\n", url);
       exit(0);
    }

    while(fgets(line, MAXSTRING, f) != NULL) {
        if (exit_loop){
            break;
        }
        token = strtok(line, delim);
        if ((pos=strchr(token, '\n')) != NULL){
            *pos = '\0';
        }
        if (strcmp(first, token) == 0){
            token = strtok(NULL, delim);
            if ((pos=strchr(token, '\n')) != NULL){
                *pos = '\0';
            }
            if (strcmp(second, token) == 0) {
                while(fgets(line, MAXSTRING, f) != NULL) {
                    token = strtok(line, delim);
                    if (strcmp("\n", token) == 0){
                        continue;
                    }
                    if ((pos=strchr(token, '\n')) != NULL){
                        *pos = '\0';
                    }
                    if (strcmp(end, token) == 0) {
                        token = strtok(NULL, delim);
                        if ((pos=strchr(token, '\n')) != NULL){
                            *pos = '\0';
                        }
                        if (strcmp(second, token) == 0) {
                            exit_loop = true;
                            break;
                        }
                    }
                    add_to_DLList(words_urls_dll, strdup(token), url_copy);
                    while (token != NULL){
                        token = strtok(NULL, delim);
                        if ((pos=strchr(token, '\n')) != NULL){
                            *pos = '\0';
                            if (strcmp(empty_string, token) == 0) {
                                break;
                            } else {
                                add_to_DLList(words_urls_dll, strdup(token), url_copy);
                                break;
                            }
                        }
                        if (token != NULL){
                            add_to_DLList(words_urls_dll, strdup(token), url_copy);
                        }
                        
                    }
                }
            }
        }
    }
}


void write_to_file(dll_token L){
    FILE *f = fopen("invertedIndex.txt", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    for (int i = 0; i < get_dll_token_length(L) ; i++){
        fprintf(f, "%s, ", get_token(L, i));
        dll_url temp_url = get_url_list(L, i);
        for (int j = 0; j < get_length_url(temp_url); j++){
            fprintf(f, "%s ", get_val_in_index_dll(temp_url, j));
        }
        fprintf(f, "\n");
    }
    fclose(f);
} 