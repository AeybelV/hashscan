#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

char *readInputData(const char *file_name, unsigned int *length) {
    FILE *f = fopen(file_name, "rb");
    if (!f) {
        fprintf(stderr, "ERROR: unable to open file \"%s\": %s\n", file_name,
                strerror(errno));
        return NULL;
    }

    if (fseek(f, 0, SEEK_END) != 0) {
        fprintf(stderr, "ERROR: unable to seek file \"%s\": %s\n", file_name,
                strerror(errno));
        fclose(f);
        return NULL;
    }
    long dataLen = ftell(f);
    if (dataLen < 0) {
        fprintf(stderr, "ERROR: ftell() failed: %s\n", strerror(errno));
        fclose(f);
        return NULL;
    }
    if (fseek(f, 0, SEEK_SET) != 0) {
        fprintf(stderr, "ERROR: unable to seek file \"%s\": %s\n", file_name,
                strerror(errno));
        fclose(f);
        return NULL;
    }

    /* Hyperscan's hs_scan function accepts length as an unsigned int, so we
     * limit the size of our buffer appropriately. */
    if ((unsigned long)dataLen > UINT_MAX) {
        dataLen = UINT_MAX;
        printf("WARNING: clipping data to %ld bytes\n", dataLen);
    } else if (dataLen == 0) {
        fprintf(stderr, "ERROR: input file \"%s\" is empty\n", file_name);
        fclose(f);
        return NULL;
    }

    char *inputData = (char*) malloc(dataLen);
    if (!inputData) {
        fprintf(stderr, "ERROR: unable to malloc %ld bytes for file buffer\n", dataLen);
        fclose(f);
        return NULL;
    }

    char *p = inputData;
    size_t bytesLeft = dataLen;
    while (bytesLeft) {
        size_t bytesRead = fread(p, 1, bytesLeft, f);
        bytesLeft -= bytesRead;
        p += bytesRead;
        if (ferror(f) != 0) {
            fprintf(stderr, "ERROR: fread() failed\n");
            free(inputData);
            fclose(f);
            return NULL;
        }
    }

    fclose(f);

    *length = (unsigned int)dataLen;
    return inputData;
}