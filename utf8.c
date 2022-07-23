#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "utf8.h"

int codepoint_len(const uint32_t cp)
{
    int len = 0;
    for(utf_t **u = utf; *u; ++u) {
        if((cp >= (*u)->beg) && (cp <= (*u)->end)) {
            break;
        }
        ++len;
    }
    if(len > 4) /* Out of bounds */
        exit(1);
 
    return len;
}
 
int utf8_len(const char ch)
{
    int len = 0;
    for(utf_t **u = utf; *u; ++u) {
        if((ch & ~(*u)->mask) == (*u)->lead) {
            break;
        }
        ++len;
    }
    if(len > 4) { /* Malformed leading byte */
        exit(1);
    }
    return len;
}
 
char *to_utf8(const uint32_t cp)
{
    static char ret[5];
    const int bytes = codepoint_len(cp);
 
    int shift = utf[0]->bits_stored * (bytes - 1);
    ret[0] = (cp >> shift & utf[bytes]->mask) | utf[bytes]->lead;
    shift -= utf[0]->bits_stored;
    for(int i = 1; i < bytes; ++i) {
        ret[i] = (cp >> shift & utf[0]->mask) | utf[0]->lead;
        shift -= utf[0]->bits_stored;
    }
    ret[bytes] = '\0';
    return ret;
}
 
uint32_t to_cp(const char chr[4])
{
    int bytes = utf8_len(*chr);
    int shift = utf[0]->bits_stored * (bytes - 1);
    uint32_t codep = (*chr++ & utf[bytes]->mask) << shift;
 
    for(int i = 1; i < bytes; ++i, ++chr) {
        shift -= utf[0]->bits_stored;
        codep |= ((char)*chr & utf[0]->mask) << shift;
    }
 
    return codep;
}
