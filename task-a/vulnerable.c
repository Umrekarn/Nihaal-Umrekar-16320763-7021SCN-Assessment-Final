/* week 4 style demo - vuln on purpose for coursework dont reuse this */
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char buffer[10];

    if (argc < 2) {
        printf("Usage: %s <your_name>\n", argv[0]);
        return 1;
    }

    /* strcpy has no idea how big buffer is - bad */
    strcpy(buffer, argv[1]);

    printf("Hello, %s!\n", buffer);
    return 0;
}
