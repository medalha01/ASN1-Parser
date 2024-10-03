#include "DERParser.h"
#include <stdio.h>
#include <stdlib.h>

void DERParser::parse(const uint8_t *data, size_t data_len) {
    size_t offset = 0;

    while (offset < data_len) {
        uint8_t tag = data[offset++];
        switch (tag) {
            case TAG_INTEGER:
                DERUtilities::parse_integer(data, &offset, data_len);
                break;
            case TAG_UTF8STRING:
                DERUtilities::parse_string(data, &offset, data_len, "UTF8String");
                break;
            case TAG_PRINTABLESTRING:
                DERUtilities::parse_string(data, &offset, data_len, "PrintableString");
                break;
            case TAG_IA5STRING:
                DERUtilities::parse_string(data, &offset, data_len, "IA5String");
                break;
            case TAG_OCTET_STRING:
                DERUtilities::parse_string(data, &offset, data_len, "OCTET STRING");
                break;
            case TAG_NULL:
                if (data[offset++] != 0x00) {
                    fprintf(stderr, "Invalid NULL encoding\n");
                    exit(EXIT_FAILURE);
                }
                printf("NULL\n");
                break;
            default:
                fprintf(stderr, "Unknown or unhandled tag: 0x%02X\n", tag);
                exit(EXIT_FAILURE);
        }
    }
}

