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

#ifndef SSZ
#define SSZ $0x200
#endif
#ifndef INITIAL
#define INITIAL $10703437
#endif
#define ICE r9
#define MOU r10
#define REM r8
#define RES r12

	.global _start

	.text
_start:
	/* Get the stack ready */
	pushq %rbp
	mov %rsp, %rbp
	sub SSZ, %rsp
	mov INITIAL, %REM
	xor %ICE, %ICE
	xor %MOU, %MOU
	xor %RES, %RES
	/* Read SSZ bytes from stdin and store them in the stack */
.L0read:
	xor %eax, %eax
	xor %edi, %edi
	mov %rsp, %rsi
	mov SSZ, %edx
	syscall
	cmp $0, %rax
	jle .done /* Failed to read / END */
	xor %r11, %r11
	/* Loop through the stack values */
.L1main:
	/* If reached the end of the buffer, read again */
	cmp %r11, %rax
	je .L0read
	movb 0(%rsi), %cl
	inc %rsi
	inc %r11
	cmp $'G', %cl
	je .G
	cmp $'I', %cl
	je .I
	cmp $'A', %cl
	je .A
	cmp $'S', %cl
	je .S
	cmp $'F', %cl
	je .F
	jmp .L1main /* ignore unknown characters */
.G:
	sub $27, %REM
	jmp .endLC
.I:
	inc %ICE
	mov %ICE, %rcx
.Iloop:
	add $12, %REM
	dec %rcx
	jnz .Iloop
	xor %MOU, %MOU
	jmp .endLA
.A:
	sub $59, %REM
	jmp .endLC
.S:
	sub $212, %REM
	jmp .endLC
.F:
	test %MOU, %MOU
	jnz .FNZ
	sub $70, %REM
	inc %MOU
	xor %ICE, %ICE
	jmp .endLA
.FNZ:
	add $35, %REM
	jmp .endLC
.endLC:
	xor %ICE, %ICE
	xor %MOU, %MOU
.endLA:
	inc %RES
	cmp $0, %REM
	jle .done
	jmp .L1main
.done:
	mov $63, %esi
	add $r, %rsi
	movb $'\n', 0(%rsi)
	mov $10, %ecx
.ultostr:
	dec %rsi
	xor %edx, %edx
	mov %RES, %rax
	div %rcx
	mov %rax, %RES
	add $'0', %dl
	movb %dl, 0(%rsi)
	test %RES, %RES
	jnz .ultostr

	mov $1, %eax
	mov %eax, %edi
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
r: .space 64
