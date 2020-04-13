// hello world implemented with fwrite

#include <stdio.h>

int main(void) {
    char bytes[] = "Hello, Andrew!\n";

    fwrite(bytes, 1, 15, stdout); // prints Hello, Andrew! on stdout

    return 0;
}