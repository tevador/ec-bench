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

;# Barrett reduction
;# modulo 0x7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffed

xor    esi, esi
mov    rdx, 38
mulx   r12, rax, r12
adcx   r8, rax
adox   r9, r12
mulx   r13, rcx, r13
adcx   r9, rcx
adox   r10, r13
mulx   r14, rcx, r14
adcx   r10, rcx
adox   r11, r14
mulx   r15, rcx, r15
adcx   r11, rcx
adox   r15, rsi ;# zero
adcx   r15, rsi ;# zero
shld   r15, r11, 1
btr    r11, 63
imul   r15, r15, 19
add    r8, r15
adc    r9, 0
adc    r10, 0
adc    r11, 0

mov    qword ptr [rdi], r8
mov    qword ptr [rdi+8], r9
mov    qword ptr [rdi+16], r10
mov    qword ptr [rdi+24], r11

pop    r15
pop    r14
pop    r13
pop    r12
