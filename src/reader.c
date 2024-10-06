#include <stdio.h>
#include <stdlib.h>
#include "reader.h"

char* read_file(const  char* path){

    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Could not open file\n");
        return NULL;
    }

    // Read file content in chunks
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* content = (char*)malloc(file_size + 1); // Allocate memory for file content (+1 for null terminator)
    if (content == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    size_t totalBytesRead = 0;
    size_t bytesRead = 0;
    while ((bytesRead = fread(content + totalBytesRead, 1, file_size - totalBytesRead, file)) > 0) {
        totalBytesRead += bytesRead;
    }

    if (totalBytesRead != file_size) {
        fprintf(stderr, "File read error: expected %ld bytes but read %zu bytes\n", file_size, totalBytesRead);
        free(content);
        fclose(file);
        return NULL;
    }

    content[totalBytesRead] = '\0'; // Null terminate

    // Close file
    fclose(file);

    // Return content
    return content;

}