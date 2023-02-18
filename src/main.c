#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "platform.h"
#include "fe.h"

static const fe fe_test = {
    .data = {
        0x8c, 0x47, 0x93, 0x56, 0x13, 0x0d, 0x70, 0x7f,
        0x44, 0xe4, 0xcf, 0xf2, 0x7e, 0xd6, 0x2d, 0xc0,
        0x81, 0x74, 0xf8, 0x11, 0x03, 0xce, 0x7c, 0x32,
        0x61, 0x40, 0x76, 0x04, 0x43, 0x47, 0x5c, 0x39,
    }
};

#ifndef NDEBUG

static inline char parse_nibble(char hex) {
    hex &= ~0x20;
    return (hex & 0x40) ? hex - ('A' - 10) : hex & 0xf;
}

static inline void hex2bin(const char* in, int length, uint8_t* out) {
    for (int i = 0; i < length; i += 2) {
        char nibble1 = parse_nibble(*in++);
        char nibble2 = parse_nibble(*in++);
        *out++ = (uint8_t)nibble1 << 4 | (uint8_t)nibble2;
    }
}

static inline bool equals_hex(const void* val, const char* hex) {
    unsigned char reference[FE_SIZE];
    hex2bin(hex, 2 * FE_SIZE, reference);
    return memcmp(val, reference, sizeof(reference)) == 0;
}

#define BENCH_LOOPS 10
#else
#define BENCH_LOOPS 100000000
#endif

typedef double bench_func();

static void run_bench(const char* name, bench_func* func) {
    printf("    %-40s ... ", name);
    double time = func();
    if (isnan(time)) {
        printf("N/A\n");
    }
    else {
        printf("%.2f ns/op.\n", time * 1e9);
    }
}

#define RUN_BENCH(x) run_bench(#x, &x)

double bench_mul_ed25519() {
    fe result = fe_test;
    double start = wall_clock();
    for (uint32_t i = 0; i < BENCH_LOOPS; ++i) {
        fe_mul_ed25519(result.data, result.data, fe_test.data);
    }
    double end = wall_clock();
    assert(equals_hex(result.data, "d483c5b7fd5a2ef54402871a9f34946c283429e3bfc4eaa7c4cf689818926f5b"));
    double elapsed = (end - start);
    return elapsed / (double)BENCH_LOOPS;
}

double bench_sqr_ed25519() {
    fe result = fe_test;
    double start = wall_clock();
    for (uint32_t i = 0; i < BENCH_LOOPS; ++i) {
        fe_sqr_ed25519(result.data, result.data);
    }
    double end = wall_clock();
    assert(equals_hex(result.data, "6565b2799f65d37eb4d023a37aadf39d4375adc0870f26eba3e737f4200bd830"));
    double elapsed = (end - start);
    return elapsed / (double)BENCH_LOOPS;
}

double bench_mul_pallas() {
    fe test;
    fe result;
    double start = wall_clock();
    //convert to Mongomery form
    fe_mul_pallas(test.data, fe_test.data, fe_mont_pallas.data);
    result = test;
    for (uint32_t i = 0; i < BENCH_LOOPS; ++i) {
        fe_mul_pallas(result.data, result.data, test.data);
    }
    //convert from Mongomery form
    fe_mul_pallas(result.data, result.data, fe_one.data);
    double end = wall_clock();
    assert(equals_hex(result.data, "5275d9413465130fa431cb1cf1807b9c468a86d57e8be1080f5b86e67df6ce13"));
    double elapsed = (end - start);
    return elapsed / (double)BENCH_LOOPS;
}

double bench_sqr_pallas() {
    fe result;
    double start = wall_clock();
    //convert to Mongomery form
    fe_mul_pallas(result.data, fe_test.data, fe_mont_pallas.data);
    for (uint32_t i = 0; i < BENCH_LOOPS; ++i) {
        fe_sqr_pallas(result.data, result.data);
    }
    //convert from Mongomery form
    fe_mul_pallas(result.data, result.data, fe_one.data);
    double end = wall_clock();
    assert(equals_hex(result.data, "ef00b64ce91e43a892384168fa12a3dd5e55e7d8cb45023e7c24caebbd833611"));
    double elapsed = (end - start);
    return elapsed / (double)BENCH_LOOPS;
}

double bench_mul_vega() {
    fe test;
    fe result;
    double start = wall_clock();
    //convert to Mongomery form
    fe_mul_vega(test.data, fe_test.data, fe_mont_vega.data);
    result = test;
    for (uint32_t i = 0; i < BENCH_LOOPS; ++i) {
        fe_mul_vega(result.data, result.data, test.data);
    }
    //convert from Mongomery form
    fe_mul_vega(result.data, result.data, fe_one.data);
    double end = wall_clock();
    assert(equals_hex(result.data, "f27db38304c090bcd57fcbbe36e8fb82f8e306c049f493e7aa5722a2b212e409"));
    double elapsed = (end - start);
    return elapsed / (double)BENCH_LOOPS;
}

double bench_sqr_vega() {
    fe result;
    double start = wall_clock();
    //convert to Mongomery form
    fe_mul_vega(result.data, fe_test.data, fe_mont_vega.data);
    for (uint32_t i = 0; i < BENCH_LOOPS; ++i) {
        fe_sqr_vega(result.data, result.data);
    }
    //convert from Mongomery form
    fe_mul_vega(result.data, result.data, fe_one.data);
    double end = wall_clock();
    assert(equals_hex(result.data, "73c9ebb902ddd12458259c3b730132cfb3a42a1be8f9a8684fd2a9b49ede0e3f"));
    double elapsed = (end - start);
    return elapsed / (double)BENCH_LOOPS;
}

int main() {
    RUN_BENCH(bench_mul_ed25519);
    RUN_BENCH(bench_mul_pallas);
    RUN_BENCH(bench_mul_vega);
    RUN_BENCH(bench_sqr_ed25519);
    RUN_BENCH(bench_sqr_pallas);
    RUN_BENCH(bench_sqr_vega);
    return 0;
}
