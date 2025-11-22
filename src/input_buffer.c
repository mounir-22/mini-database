#include "../include/database.h"

InputBuffer* new_input_buffer() {
    InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}

void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}

void print_prompt() { 
    printf("db > "); 
}

void read_input(InputBuffer* input_buffer) {
    char* buffer = malloc(256);
    if (!fgets(buffer, 256, stdin)) {
        printf("Error reading input\n");
        free(buffer);
        exit(EXIT_FAILURE);
    }

    size_t input_length = strlen(buffer);
    // Remove trailing newline if present
    if (input_length > 0 && buffer[input_length - 1] == '\n') {
        buffer[input_length - 1] = '\0';
        input_length--;
    }

    input_buffer->buffer = buffer;
    input_buffer->buffer_length = 256;
    input_buffer->input_length = input_length;
}