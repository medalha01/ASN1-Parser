#ifndef DER_UTILITIES_H
#define DER_UTILITIES_H

#include <stdint.h>
#include <stddef.h>

class DERUtilities {
public:
    static size_t read_length(const uint8_t *data, size_t *offset, size_t data_len);
    static void parse_integer(const uint8_t *data, size_t *offset, size_t data_len);
    static void parse_string(const uint8_t *data, size_t *offset, size_t data_len, const char *type_name);
};

#endif

