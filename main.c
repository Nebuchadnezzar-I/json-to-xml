#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Read file line by line
    FILE *file = fopen("source.json", "r");
    char line[256];

    if (file != NULL) {

        // TODO: Handle lex
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }

        // TODO: Handle parsing token by token

        fclose(file);
    } else {
        fprintf(stderr, "Error: Could not open file\n");
    }

    return 0;
}
