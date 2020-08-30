/* Copyright 2019 Ricardo Iván Vieitez Parra
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

    .global _start

    .text
_start:
    xor %r12, %r12
.L00:
    xor %r8, %r8
.L0:
    xor %eax, %eax
    xor %edi, %edi
    mov $c, %rsi
    mov $1, %edx
    syscall
    mov $1, %ecx
    cmp %rax, %rcx
    jne .end

    mov 0(%rsi), %rbx
    mov $0x0A, %ecx /* '\n' */
    cmp %rbx, %rcx
    je .L1
    sub $0x30, %ebx /* '0' */
    mov $10, %eax
    mul %r8
    mov %rax, %r8
    add %rbx, %r8
    jmp .L0
.L1: 
    mov %r8, %rax
    mul %rax
    mov %rax, %r9
    mov $1, %r10d
.L2:
    mov $10, %eax
    mul %r10
    mov %rax, %r10
    mov %r9, %rax
    xor %rdx, %rdx
    div %r10
    test %rax, %rax /* 0 not allowed */
    jz .L5
    test %edx, %edx /* 0 not allowed */
    jz  .L2
    add %rax, %rdx
    xor %r8, %rdx
    jnz .L2
.L4:
    add %r8, %r12
.L5:
    jmp .L00

.end:
    mov $63, %esi
    add $r, %rsi
    movb $0x0a, 0(%rsi)
    mov $10, %ecx
.p:
    dec %rsi
    xor %edx, %edx
    mov %r12, %rax
    div %rcx
    mov %rax, %r12
    add $0x30, %dl
    mov %dl, 0(%rsi)
    test %r12, %r12
    jnz .p

    mov $1, %eax
    mov $1, %edi
    mov $64, %edx
    add $r, %rdx
    sub %rsi, %rdx
    syscall

    mov $60, %eax
    xor %edi, %edi
    xor %esi, %esi
    xor %edx, %edx
    syscall

    .data
c: .space 1
r: .space 64
