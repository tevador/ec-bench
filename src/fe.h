#ifndef FE_MUL
#define FE_MUL

#include <stdint.h>

#define FE_SIZE 32

typedef struct fe {
    uint8_t data[FE_SIZE];
} fe;

static const fe fe_mont_pallas = {
    .data = {
        0x0f, 0x00, 0x00, 0x00, 0xb3, 0xec, 0x78, 0x8c,
        0xe7, 0xe0, 0x0d, 0x8b, 0xbd, 0x0d, 0xd3, 0xd7,
        0x18, 0x5d, 0xc9, 0xc3, 0x9b, 0xa9, 0x97, 0x77,
        0x14, 0xb7, 0x9c, 0x7b, 0xaf, 0x41, 0x6d, 0x09,
    }
};

static const fe fe_mont_vega = {
    .data = {
        0xbc, 0xbf, 0x27, 0xbc, 0xd5, 0x99, 0x7e, 0x3f,
        0x33, 0xe6, 0x9a, 0x9d, 0x5e, 0x20, 0x25, 0x98,
        0x23, 0x41, 0xbd, 0x5a, 0x5b, 0xeb, 0xeb, 0xa5,
        0x18, 0x5e, 0xc9, 0x9e, 0xc9, 0xd6, 0x24, 0x06,
    }
};

static const fe fe_one = {
    .data = {
        0x01
    }
};

void fe_mul_ed25519(uint8_t* r, const uint8_t* a, const uint8_t* b);
void fe_mul_pallas(uint8_t* r, const uint8_t* a, const uint8_t* b);
void fe_mul_vega(uint8_t* r, const uint8_t* a, const uint8_t* b);

void fe_sqr_ed25519(uint8_t* r, const uint8_t* a);
void fe_sqr_pallas(uint8_t* r, const uint8_t* a);
void fe_sqr_vega(uint8_t* r, const uint8_t* a);

#endif