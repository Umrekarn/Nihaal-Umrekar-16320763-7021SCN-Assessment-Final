/* fixed version for the same coursework bit */
#include <stdio.h>
#include <string.h>

#define NAME_BUF 10

int main(int argc, char *argv[]) {
    char buffer[NAME_BUF];

    if (argc < 2) {
        printf("Usage: %s <your_name>\n", argv[0]);
        return 1;
    }

    int ret = snprintf(buffer, sizeof(buffer), "%s", argv[1]);
    if (ret < 0) {
        fprintf(stderr, "Encoding error.\n");
        return 1;
    }
    if (ret >= (int)sizeof(buffer)) {
        fprintf(stderr, "Error: name too long (maximum %d characters).\n",
                (int)sizeof(buffer) - 1);
        return 1;
    }

    printf("Hello, %s!\n", buffer);
    return 0;
}
