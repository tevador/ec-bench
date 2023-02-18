;# Copyright (c) 2023 tevador

;# rdi  = destination
;# rsi  = multiplicand

push   r12
push   r13
push   r14
push   r15

xor    r13d, r13d
mov    rdx, qword ptr [rsi]
mulx   r10, r9, qword ptr [rsi+8]
mulx   r11, rcx, qword ptr [rsi+16]
adcx   r10, rcx
mulx   r12, rcx, qword ptr [rsi+24]
adcx   r11, rcx
adcx   r12, r13
xor    r14d, r14d
mov    rdx, qword ptr [rsi+8]
mulx   rax, rcx, qword ptr [rsi+16]
adcx   r11, rcx
adox   r12, rax
mulx   rax, rcx, qword ptr [rsi+24]
adcx   r12, rcx
adox   r13, rax
adcx   r13, r14
xor    r15d, r15d
adox   r9, r9
adox   r10, r10
mov    rdx, qword ptr [rsi+16]
adox   r11, r11
adox   r12, r12
mulx   r14, rcx, qword ptr [rsi+24]
adcx   r13, rcx
adox   r13, r13
adcx   r14, r15
adox   r14, r14
adox   r15, r15
xor    edx, edx
mov    rdx, qword ptr [rsi]
mulx   rdx, r8, rdx
adcx   r9, rdx
mov    rdx, qword ptr [rsi+8]
mulx   rdx, rcx, rdx
adcx   r10, rcx
adcx   r11, rdx
mov    rdx, qword ptr [rsi+16]
mulx   rdx, rcx, rdx
adcx   r12, rcx
adcx   r13, rdx
mov    rdx, qword ptr [rsi+24]
mulx   rdx, rcx, rdx
adcx   r14, rcx
adcx   r15, rdx

;# Mongomery reduction
;# modulo 0x40000000000000000000000000000000224698fc094cf91b992d30ed00000001
;# based on Algorithm 3 in https://eprint.iacr.org/2020/665.pdf

mov    rdx, r8
imul   rdx, qword ptr [pallas_inv+REG_REL]
xor    esi, esi
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
adcx   r12, rsi ;# zero
adox   r13, rsi ;# zero
adcx   r13, rsi ;# zero
adox   r14, rsi ;# zero
adcx   r14, rsi ;# zero
adox   r15, rsi ;# zero
adcx   r15, rsi ;# zero

mov    rdx, r9
imul   rdx, qword ptr [pallas_inv+REG_REL]
xor    esi, esi
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
adcx   r13, rsi ;# zero
adox   r14, rsi ;# zero
adcx   r14, rsi ;# zero
adox   r15, rsi ;# zero
adcx   r15, rsi ;# zero

mov    rdx, r10
imul   rdx, qword ptr [pallas_inv+REG_REL]
xor    esi, esi
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
adcx   r14, rsi ;# zero
adox   r15, rsi ;# zero
adcx   r15, rsi ;# zero

mov    rdx, r11
imul   rdx, qword ptr [pallas_inv+REG_REL]
xor    esi, esi
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
adcx   r15, rsi ;# zero

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
