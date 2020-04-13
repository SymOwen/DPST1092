#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>

int main(void) {

    printf("Pattern? ");
    char line[256];
    if (fgets(line, sizeof line, stdin) == NULL) {
        return 0;
    }

    char *newline = strrchr(line, '\n');
    if (newline != NULL) {
        *newline = '\0';
    }

    glob_t matches; // holds pattern expansion
    int result = glob(line, GLOB_NOCHECK|GLOB_TILDE, NULL, &matches);

    if (result != 0) {
        printf("glob returns %d\n", result);
    } else {
        printf("%d matches\n", (int)matches.gl_pathc);
        for (int i = 0; i < matches.gl_pathc; i++) {
            printf("\t%s\n", matches.gl_pathv[i]);
        }
    }

    return 0;
}