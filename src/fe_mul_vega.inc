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
pop    rbp
pop    rbx
