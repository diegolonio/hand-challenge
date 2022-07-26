#ifndef _UTF8_H_
#define _UTF8_H_

#include <inttypes.h>

typedef struct {
    char mask;    /* char data will be bitwise AND with this */
    char lead;    /* start bytes of current char in utf-8 encoded character */
    uint32_t beg; /* beginning of codepoint range */
    uint32_t end; /* end of codepoint range */
    int bits_stored; /* the number of bits from the codepoint that fits in char */
} utf_t;
 
utf_t *utf[] = {
    /*             mask        lead        beg      end       bits */
    [0] = &(utf_t){0b00111111, 0b10000000, 0,       0,        6    },
    [1] = &(utf_t){0b01111111, 0b00000000, 0000,    0177,     7    },
    [2] = &(utf_t){0b00011111, 0b11000000, 0200,    03777,    5    },
    [3] = &(utf_t){0b00001111, 0b11100000, 04000,   0177777,  4    },
    [4] = &(utf_t){0b00000111, 0b11110000, 0200000, 04177777, 3    },
          &(utf_t){0},
};
 
/* All lengths are in bytes */
int codepoint_len(const uint32_t); /* len of associated utf-8 char */
int utf8_len(const char);          /* len of utf-8 encoded char */
 
char *to_utf8(const uint32_t);
uint32_t to_cp(const char []);

#include "utf8.c"

#endif /* _UTF8_H_ */
