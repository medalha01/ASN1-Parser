#include <stdint.h>
#include <stddef.h>
#include "DERParser.h"

int main() {
    uint8_t der_data[] = {
        0x02, 0x01, 0x2A,                   // INTEGER 42
        0x0C, 0x05, 'H', 'e', 'l', 'l', 'o', // UTF8String "Hello"
        0x13, 0x05, 'W', 'o', 'r', 'l', 'd', // PrintableString "World"
        0x05, 0x00                          // NULL
    };

    size_t data_len = sizeof(der_data);
    DERParser parser;
    parser.parse(der_data, data_len);

    uint8_t der_data_2[] = {
        0x02, 0x01, 0x2A,                   // INTEGER 42
        0x0C, 0x05, 'H', 'e', 'l', 'l', 'o', // UTF8String "Hello"
        0x13, 0x05, 'W', 'o', 'r', 'l', 'd', // PrintableString "World"
        0x05, 0x00,                          // NULL
        0x16, 0x13, 'e', 'x', 'a', 'm', 'p', 'l', 'e', '@', 'e', 'x', 'a', 'm', 'p', 'l', 'e', '.', 'c', 'o', 'm'
    };

    size_t data_len_2 = sizeof(der_data_2);
    parser.parse(der_data_2, data_len_2);

    return 0;
}

