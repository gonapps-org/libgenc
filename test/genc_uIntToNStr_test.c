#include "../src/genc_uIntToNStr.h"
#include <stdio.h>
int main() {
    char* str;
    genc_uIntToNStr(200, 10, &str);
    printf("%s\n", str);
    free(str);
    genc_uIntToNStr(10, 16, &str);
    printf("%s\n", str);
    free(str);

    return 0;
}
