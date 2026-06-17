.section .data
format_int: .string "%d\n"
format_float: .string "%g\n"

.section .text
.globl main

main:
    pushq %rbp
    movq %rsp, %rbp
    subq $4096, %rsp
    movq $5, %rax
    movq %rax, -8(%rbp)
    movq -8(%rbp), %rax
    pushq %rax
    movq $10, %rax
    movq %rax, %rbx
    popq %rax
    addq %rbx, %rax
    movq %rax, %rsi
    leaq format_int(%rip), %rdi
    movl $0, %eax
    call printf@PLT
    movq %rbp, %rsp
    popq %rbp
    ret
