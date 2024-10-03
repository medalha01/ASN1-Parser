#include "DERUtilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t DERUtilities::read_length(const uint8_t *data, size_t *offset, size_t data_len) {
    if (*offset >= data_len) {
        fprintf(stderr, "Invalid length encoding\n");
        exit(EXIT_FAILURE);
    }

    uint8_t first_byte = data[*offset];
    (*offset)++;

    if (first_byte < 128) {
        return first_byte;
    } else {
        uint8_t num_bytes = first_byte & 0x7F;
        if (num_bytes == 0 || num_bytes > sizeof(size_t) || *offset + num_bytes > data_len) {
            fprintf(stderr, "Invalid or unsupported length encoding\n");
            exit(EXIT_FAILURE);
        }

        size_t length = 0;
        for (uint8_t i = 0; i < num_bytes; i++) {
            length = (length << 8) | data[*offset];
            (*offset)++;
        }
        return length;
    }
}

void DERUtilities::parse_integer(const uint8_t *data, size_t *offset, size_t data_len) {
    size_t length = read_length(data, offset, data_len);
    if (*offset + length > data_len) {
        fprintf(stderr, "Integer length exceeds data length\n");
        exit(EXIT_FAILURE);
    }

    if (length > 4) {
        fprintf(stderr, "Integer too large to parse\n");
        exit(EXIT_FAILURE);
    }

    int value = 0;
    for (size_t i = 0; i < length; i++) {
        value = (value << 8) | data[*offset + i];
    }

    *offset += length;
    printf("INTEGER: %d\n", value);
}

void DERUtilities::parse_string(const uint8_t *data, size_t *offset, size_t data_len, const char *type_name) {
    size_t length = read_length(data, offset, data_len);
    if (*offset + length > data_len) {
        fprintf(stderr, "String length exceeds data length\n");
        exit(EXIT_FAILURE);
    }

    char *str = (char *)malloc(length + 1);
    if (!str) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    memcpy(str, &data[*offset], length);
    str[length] = '\0';

    *offset += length;
    printf("%s: %s\n", type_name, str);

    free(str);
}

