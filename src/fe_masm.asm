IFDEF RAX

REG_REL EQU 0

FE_TEST SEGMENT PAGE READ EXECUTE

PUBLIC fe_mul_ed25519
PUBLIC fe_mul_pallas
PUBLIC fe_mul_vega
PUBLIC fe_sqr_ed25519
PUBLIC fe_sqr_pallas
PUBLIC fe_sqr_vega

include constants.inc

fe_mul_ed25519 PROC
  mov qword ptr [rsp+8], rdi
  mov qword ptr [rsp+16], rsi
  mov rdi, rcx
  mov rsi, rdx
  mov rdx, r8

include fe_mul_ed25519.inc

  mov rdi, qword ptr [rsp+8]
  mov rsi, qword ptr [rsp+16]
  ret
fe_mul_ed25519 ENDP

fe_mul_pallas PROC
  mov qword ptr [rsp+8], rdi
  mov qword ptr [rsp+16], rsi
  mov rdi, rcx
  mov rsi, rdx
  mov rdx, r8

include fe_mul_pallas.inc

  mov rdi, qword ptr [rsp+8]
  mov rsi, qword ptr [rsp+16]
  ret
fe_mul_pallas ENDP

fe_mul_vega PROC
  mov qword ptr [rsp+8], rdi
  mov qword ptr [rsp+16], rsi
  mov rdi, rcx
  mov rsi, rdx
  mov rdx, r8

include fe_mul_vega.inc

  mov rdi, qword ptr [rsp+8]
  mov rsi, qword ptr [rsp+16]
  ret
fe_mul_vega ENDP

fe_sqr_ed25519 PROC
  mov qword ptr [rsp+8], rdi
  mov qword ptr [rsp+16], rsi
  mov rdi, rcx
  mov rsi, rdx

include fe_sqr_ed25519.inc

  mov rdi, qword ptr [rsp+8]
  mov rsi, qword ptr [rsp+16]
  ret
fe_sqr_ed25519 ENDP

fe_sqr_pallas PROC
  mov qword ptr [rsp+8], rdi
  mov qword ptr [rsp+16], rsi
  mov rdi, rcx
  mov rsi, rdx

include fe_sqr_pallas.inc

  mov rdi, qword ptr [rsp+8]
  mov rsi, qword ptr [rsp+16]
  ret
fe_sqr_pallas ENDP

fe_sqr_vega PROC
  mov qword ptr [rsp+8], rdi
  mov qword ptr [rsp+16], rsi
  mov rdi, rcx
  mov rsi, rdx

include fe_sqr_vega.inc

  mov rdi, qword ptr [rsp+8]
  mov rsi, qword ptr [rsp+16]
  ret
fe_sqr_vega ENDP

FE_TEST ENDS

ENDIF

END
