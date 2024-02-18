#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Convert hexadecimal string to binary array
int* hexToBinaryArray( char *hexString, size_t *binaryArraySize) {
    size_t hexLen = strlen(hexString);
    *binaryArraySize = hexLen * 4; // Each hex character represents 4 binary digits

    int *binaryArray = malloc(sizeof(int) * (*binaryArraySize));
    if (binaryArray == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < hexLen; i++) {
        char hexChar = hexString[i];
        int decimalValue;

        if (hexChar >= '0' && hexChar <= '9') {
            decimalValue = hexChar - '0';
        } else if (hexChar >= 'A' && hexChar <= 'F') {
            decimalValue = hexChar - 'A' + 10;
        } else if (hexChar >= 'a' && hexChar <= 'f') {
            decimalValue = hexChar - 'a' + 10;
        } else {
            fprintf(stderr, "Invalid hexadecimal character: %c\n", hexChar);
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < 4; j++) {
            binaryArray[i * 4 + (3 - j)] = (decimalValue >> j) & 1;
        }
    }

    return binaryArray;
}
// Function to handle memory
unsigned int memory(char *val, unsigned progAddr) {
    char s[3];
    int len = strlen(val);

    for (int l = 0; l < len - 1; l = l + 2) {
        strncpy(s, val + l, 2);
        s[2] = '\0';
        printf("%X %s\n", progAddr, s);
        progAddr = progAddr + 1;
    }
    return progAddr;
}

int main() {
    FILE *f1;
    unsigned progAddr, csAddr;

    printf("Enter program address from operating system\n");
    scanf("%x", &progAddr);
    csAddr = progAddr;

    printf("Memory after loading with bitmask\n");
    f1 = fopen("objectP1.txt", "r");
    char line[100];

    while (fgets(line, sizeof(line), f1) != NULL) {
        while (line[0] == 'T') {
char add[7];
        strncpy(add,line+2,6);
        add[6]='\0';

        unsigned int aa=strtoul(add,NULL,16);
        progAddr=aa+csAddr;
            char sec[3];
            char thr[4];
            printf("%s\n", line);
            strncpy(sec, line + 9, 2);
            sec[2] = '\0';
            strncpy(thr, line + 12, 3);
            thr[3] = '\0';

            size_t binaryArraySize;
            int *binaryArray = hexToBinaryArray(thr, &binaryArraySize);

            const char *delimiter = "^";
            char *token = strtok(line + 16, delimiter);
            int i = 0;

            while (token != NULL) {
                if (binaryArray[i] == 1) {
                    unsigned int value = strtoul(token, NULL, 16);
                    value = value + csAddr;
                    char string[7];
                    sprintf(string, "%06x", value);
                    string[6] = '\0';
                    progAddr = memory(string, progAddr);
                } else {
                    progAddr = memory(token, progAddr);
                }
                token = strtok(NULL, delimiter);
                i++;
            }
            break;
        }
        printf("\n");
    }
    return 0;
}