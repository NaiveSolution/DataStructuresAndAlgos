
#include "DLListTokens.h"
#include "DLListUrls.h"
#include "reader.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){

    dll_url url_list = GetCollection();
    int num_urls = get_length_url(url_list);
    dll_token words_urls_dll = newdll_token();

    // create the forward index
    for (int i = 0; i < num_urls; i++){
        readSection2(words_urls_dll, url_list, i);
    }
    showdll_token(words_urls_dll);
    write_to_file(words_urls_dll);
    freedll_token(words_urls_dll);
    freedll_url(url_list);
    return 0;
}