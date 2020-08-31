// Linked list interface ... COMP9024 17s2
#include <stdbool.h>

typedef struct NodeL *List;
void add_to_LL(List, char*);
List newListStr();
int get_length_LL(List);
bool inLL(List, char *);
void freeLL(List);
void showLL(List);
char* get_val_in_index_ll(List, int);
char* get_list_url(List);
//void normalise_values(List);
void sorted_list(List);
//List copy_list(List);
