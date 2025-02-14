#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer() {
    /*
    wrapper to interact with getline
    */
    InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}

void print_prompt() {
    /*
    prints a prompt to the user, which is done before reading each line of input
    */
    printf("db > ");
}

/*
Used to read a ilne of input. Buffer starts as null so getline allocates enough memory to hold the line of input and makes buffer point to it
@lineptr: a pointer to the variable that we use to point to the buffer containing the read line (if set to NULL, it is mallocatted by getline, and should be freed by user, even if the command fails)
@n: a pointer to the variable that is used to save the size of allocated buffer
@stream: input stream to read from (reading from standard input for now)
@returns: number of byts read, may be less than the siz of the buffer 
*/
//ssize_t getline(char **lineptr, size_t *n, FILE *stream);

void read_input(InputBuffer* input_buffer) {
    ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

    if(bytes_read <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    // -1 because the trailing newline should be ignored
    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}

int main(int argc, char* argv[]) {
    /*
    REPL loop: read-execute-print loop that gets the commands from the command line
    */
    InputBuffer* input_buffer = new_input_buffer();
    while(true) {
        print_prompt();
        read_input(input_buffer);

        if(strcmp(input_buffer->buffer, ".exit") == 0) {
            close_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        } else{
            printf("Unrecognized command:'%s'.\n", input_buffer->buffer);
        } 
    }
}
