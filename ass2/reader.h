#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "DLListTokens.h"
#include "DLListUrls.h"

dll_url GetCollection(void);
void readSection2(dll_token, dll_url, int);
void write_to_file(dll_token);