#ifndef DER_PARSER_H
#define DER_PARSER_H

#include <stdint.h>
#include <stddef.h>
#include "TagConstants.h"
#include "DERUtilities.h"

class DERParser {
public:
    void parse(const uint8_t *data, size_t data_len);
};

#endif

