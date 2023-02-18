
.intel_syntax noprefix
#if defined(__APPLE__)
.text
#define DECL(x) _##x
#else
.section .text
#define DECL(x) x
#endif

#if defined(__WIN32__) || defined(__CYGWIN__)
#error WinABI is not supported
#endif

#define REG_REL rip
#define db .byte
#define ALIGN .balign

.global DECL(fe_mul_ed25519)
.global DECL(fe_mul_pallas)
.global DECL(fe_mul_vega)
.global DECL(fe_sqr_ed25519)
.global DECL(fe_sqr_pallas)
.global DECL(fe_sqr_vega)

#include "constants.inc"

ALIGN 32
DECL(fe_mul_ed25519):
#include "fe_mul_ed25519.inc"
  ret

ALIGN 32
DECL(fe_mul_pallas):
#include "fe_mul_pallas.inc"
  ret

ALIGN 32
DECL(fe_mul_vega):
#include "fe_mul_vega.inc"
  ret

ALIGN 32
DECL(fe_sqr_ed25519):
#include "fe_sqr_ed25519.inc"
  ret

ALIGN 32
DECL(fe_sqr_pallas):
#include "fe_sqr_pallas.inc"
  ret

ALIGN 32
DECL(fe_sqr_vega):
#include "fe_sqr_vega.inc"
  ret
