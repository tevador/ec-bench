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

;# Barrett reduction
;# modulo 0x7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffed

xor    ebp, ebp
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
adox   r15, rbp ;# zero
adcx   r15, rbp ;# zero
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
pop    rbp
pop    rbx
