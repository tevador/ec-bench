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
;# modulo 0x5eca430000000000000000000000000000000000000000000000000000000001
;# based on Algorithm 5 in https://eprint.iacr.org/2020/665.pdf

mov    rdx, qword ptr [vega_alpha+REG_REL]

mulx   rcx, rax, r8
xor    r8d, r8d
sub    r11, rax
sbb    r12, rcx
sbb    r13, 0
sbb    r14, 0
sbb    r15, 0

mulx   rcx, rax, r9
xor    r9d, r9d
sub    r12, rax
sbb    r13, rcx
sbb    r14, 0
sbb    r15, 0

mulx   rcx, rax, r10
xor    r10d, r10d
sub    r13, rax
sbb    r14, rcx
sbb    r15, 0

mulx   rcx, rax, r11
xor    r11d, r11d
sub    r14, rax
sbb    r15, rcx

;# final constant-time addition

bt     r15, 63
cmovc  r8, qword ptr [vega_p0+REG_REL]
cmovc  r9, qword ptr [vega_p1+REG_REL]
cmovc  r10, qword ptr [vega_p2+REG_REL]
cmovc  r11, qword ptr [vega_p3+REG_REL]
add    r12, r8
adc    r13, r9
adc    r14, r10
adc    r15, r11

mov    qword ptr [rdi], r12
mov    qword ptr [rdi+8], r13
mov    qword ptr [rdi+16], r14
mov    qword ptr [rdi+24], r15

pop    r15
pop    r14
pop    r13
pop    r12
