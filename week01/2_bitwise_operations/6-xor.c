#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//
// copy stdin to stdout xor each byte with value supplied on STDIN
//
//
// Try
// $ dcc xor.c -o xor
// $ <xor.c xor 42
// $ <xor.c xor 42|xor 42
//

int main(int argc, char *argv[]) {
    assert(argc == 2);
    char key = strtol(argv[1], NULL, 0);
    int c;
    while ((c = getchar()) != EOF) {
        int xor_c = c ^ key;
        putchar(xor_c);
    }
    return 0;
}