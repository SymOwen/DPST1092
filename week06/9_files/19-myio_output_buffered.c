// simple re-implementation of stdio functions fopen, fgetc, fputc, fclose
// *zero* error handling for clarity

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// how equivalents for  EOF & BUFSIZ from stdio.h
#define MY_EOF -1
#define MY_BUFSIZ 512

// struct to hold data for a stream
typedef struct my_file {
    int     fd;
    int     is_output_stream;
    int     n_buffered_bytes;
    int     next_byte;
    uint8_t buffer[MY_BUFSIZ];
} my_file_t;

my_file_t *my_fopen(char *file, char *mode) {
    int fd = -1;
    if (mode[0] == 'r') {
        fd = open(file, O_RDONLY);
    } else if (mode[0] == 'w') {
        fd = open(file, O_WRONLY | O_CREAT, 0666);
    } else if (mode[0] == 'a') {
        fd = open(file, O_WRONLY | O_APPEND);
    }

    if (fd == -1) {
        return NULL;
    }

    my_file_t *f = malloc(sizeof *f);
    f->fd = fd;
    f->is_output_stream = mode[0] != 'r';
    f->next_byte = 0;
    f->n_buffered_bytes = 0;
    return f;
}

int my_fgetc(my_file_t *f) {
    if (f->next_byte == f->n_buffered_bytes) {
        // buffer is empty so fill it with a read
        int bytes_read = read(f->fd, f->buffer, sizeof f->buffer);
        if (bytes_read <= 0) {
            return MY_EOF;
        }
        f->n_buffered_bytes = bytes_read;
        f->next_byte = 0;
    }

    // return 1 byte from the buffer
    int byte = f->buffer[f->next_byte];
    f->next_byte++;
    return byte;
}

int my_fputc(int c, my_file_t *f) {
    if (f->n_buffered_bytes == sizeof f->buffer) {
        // buffer is full so empty it with a write
        write(f->fd, f->buffer, sizeof f->buffer); // no error checking
        f->n_buffered_bytes = 0;
    }

    // add byte byte to buffer to be written later
    f->buffer[f->n_buffered_bytes] = c;
    f->n_buffered_bytes++;
    return 1;
}

int my_fclose(my_file_t *f) {
    // don't keave unwritten bytes
    if (f->is_output_stream && f->n_buffered_bytes > 0) {
        write(f->fd, f->buffer, f->n_buffered_bytes); // no error checking
    }

    int result = close(f->fd);
    free(f);
    return result;
}

int main(int argc, char *argv[]) {
    my_file_t *input_stream = my_fopen(argv[1], "r");
    if (input_stream == NULL) {
        perror(argv[1]);
        return 1;
    }

    my_file_t *output_stream = my_fopen(argv[2], "w");
    if (output_stream == NULL) {
        perror(argv[2]);
        return 1;
    }

    int c;
    while ((c = my_fgetc(input_stream)) != MY_EOF) {
        my_fputc(c, output_stream);
    }

    my_fclose(input_stream);
    my_fclose(output_stream);

    return 0;
}