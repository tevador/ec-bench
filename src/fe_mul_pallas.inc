;# Copyright (c) 2023 tevador

;# rdi  = destination
;# rsi  = first multiplicand
;# rdx  = second multiplicand

push   rbx
push   rbp
push   r12
push   r13
push   r14
push   r15

mov    rbx, rdx

xor    r13d, r13d
mov    rdx, qword ptr [rsi]
mulx   r9, r8, qword ptr [rbx]
mulx   r10, rcx, qword ptr [rbx+8]
adcx   r9, rcx
mulx   r11, rcx, qword ptr [rbx+16]
adcx   r10, rcx
mulx   r12, rcx, qword ptr [rbx+24]
adcx   r11, rcx
adcx   r12, r13 ;# zero
xor    r14d, r14d
mov    rdx, qword ptr [rsi+8]
mulx   rbp, rcx, qword ptr [rbx]
adcx   r9, rcx
adox   r10, rbp
mulx   rbp, rcx, qword ptr [rbx+8]
adcx   r10, rcx
adox   r11, rbp
mulx   rbp, rcx, qword ptr [rbx+16]
adcx   r11, rcx
adox   r12, rbp
mulx   rbp, rcx, qword ptr [rbx+24]
adcx   r12, rcx
adox   r13, rbp
adcx   r13, r14 ;#zero
xor    r15d, r15d
mov    rdx, qword ptr [rsi+16]
mulx   rbp, rcx, qword ptr [rbx]
adcx   r10, rcx
adox   r11, rbp
mulx   rbp, rcx, qword ptr [rbx+8]
adcx   r11, rcx
adox   r12, rbp
mulx   rbp, rcx, qword ptr [rbx+16]
adcx   r12, rcx
adox   r13, rbp
mulx   rbp, rcx, qword ptr [rbx+24]
adcx   r13, rcx
adox   r14, rbp
adcx   r14, r15
xor    eax, eax
mov    rdx, qword ptr [rsi+24]
mulx   rbp, rcx, qword ptr [rbx]
adcx   r11, rcx
adox   r12, rbp
mulx   rbp, rcx, qword ptr [rbx+8]
adcx   r12, rcx
adox   r13, rbp
mulx   rbp, rcx, qword ptr [rbx+16]
adcx   r13, rcx
adox   r14, rbp
mulx   rbp, rcx, qword ptr [rbx+24]
adcx   r14, rcx
adox   r15, rbp
adcx   r15, rax ;# zero

;# Mongomery reduction
;# modulo 0x40000000000000000000000000000000224698fc094cf91b992d30ed00000001
;# based on Algorithm 3 in https://eprint.iacr.org/2020/665.pdf

mov    rdx, r8
imul   rdx, qword ptr [pallas_inv+REG_REL]
xor    ebp, ebp
mulx   rcx, rax, qword ptr [pallas_p0+REG_REL]
adcx   r8, rax
adox   r9, rcx
mulx   rcx, rax, qword ptr [pallas_p1+REG_REL]
adcx   r9, rax
adox   r10, rcx
mulx   rcx, rax, qword ptr [pallas_p2+REG_REL]
adcx   r10, rax
adox   r11, rcx
mulx   rcx, rax, qword ptr [pallas_p3+REG_REL]
adcx   r11, rax
adox   r12, rcx
adcx   r12, rbp ;# zero
adox   r13, rbp ;# zero
adcx   r13, rbp ;# zero
adox   r14, rbp ;# zero
adcx   r14, rbp ;# zero
adox   r15, rbp ;# zero
adcx   r15, rbp ;# zero

mov    rdx, r9
imul   rdx, qword ptr [pallas_inv+REG_REL]
xor    ebp, ebp
mulx   rcx, rax, qword ptr [pallas_p0+REG_REL]
adcx   r9, rax
adox   r10, rcx
mulx   rcx, rax, qword ptr [pallas_p1+REG_REL]
adcx   r10, rax
adox   r11, rcx
mulx   rcx, rax, qword ptr [pallas_p2+REG_REL]
adcx   r11, rax
adox   r12, rcx
mulx   rcx, rax, qword ptr [pallas_p3+REG_REL]
adcx   r12, rax
adox   r13, rcx
adcx   r13, rbp ;# zero
adox   r14, rbp ;# zero
adcx   r14, rbp ;# zero
adox   r15, rbp ;# zero
adcx   r15, rbp ;# zero

mov    rdx, r10
imul   rdx, qword ptr [pallas_inv+REG_REL]
xor    ebp, ebp
mulx   rcx, rax, qword ptr [pallas_p0+REG_REL]
adcx   r10, rax
adox   r11, rcx
mulx   rcx, rax, qword ptr [pallas_p1+REG_REL]
adcx   r11, rax
adox   r12, rcx
mulx   rcx, rax, qword ptr [pallas_p2+REG_REL]
adcx   r12, rax
adox   r13, rcx
mulx   rcx, rax, qword ptr [pallas_p3+REG_REL]
adcx   r13, rax
adox   r14, rcx
adcx   r14, rbp ;# zero
adox   r15, rbp ;# zero
adcx   r15, rbp ;# zero

mov    rdx, r11
imul   rdx, qword ptr [pallas_inv+REG_REL]
xor    ebp, ebp
mulx   rcx, rax, qword ptr [pallas_p0+REG_REL]
adcx   r11, rax
adox   r12, rcx
mulx   rcx, rax, qword ptr [pallas_p1+REG_REL]
adcx   r12, rax
adox   r13, rcx
mulx   rcx, rax, qword ptr [pallas_p2+REG_REL]
adcx   r13, rax
adox   r14, rcx
mulx   rcx, rax, qword ptr [pallas_p3+REG_REL]
adcx   r14, rax
adox   r15, rcx
adcx   r15, rbp ;# zero

;# final constant-time subtraction

mov    r8, r12
mov    r9, r13
mov    r10, r14
mov    r11, r15
sub    r8, qword ptr [pallas_p0+REG_REL]
sbb    r9, qword ptr [pallas_p1+REG_REL]
sbb    r10, qword ptr [pallas_p2+REG_REL]
sbb    r11, qword ptr [pallas_p3+REG_REL]
bt     r11, 63
cmovb  r8, r12
cmovb  r9, r13
cmovb  r10, r14
cmovb  r11, r15

mov    qword ptr [rdi], r8
mov    qword ptr [rdi+8], r9
mov    qword ptr [rdi+16], r10
mov    qword ptr [rdi+24], r11

pop    r15
pop    r14
pop    r13
pop    r12
pop    rbp
pop    rbx
