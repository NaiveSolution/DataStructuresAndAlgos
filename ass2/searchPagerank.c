#include <stdio.h>
#include <stdlib.h>
#include "DLListSearch.h"
#include "search.h"

int main(int argc, char* argv[]){

    dll_search matched_Url_list = findMatchedUrls("invertedIndex.txt", argc, argv);
    findPagerank("pagerankList.txt", matched_Url_list);

    if (get_dll_search_length(matched_Url_list) < 30){
        showdll_search(matched_Url_list);
    } else {
        show_max_dll_length(matched_Url_list);
    }

    //show_auxiliary(matched_Url_list);

    return 0;
}