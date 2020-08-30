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

#define RES r9
	.global _start

	.text
_start:
	xor %RES, %RES
	mov $999, %r8d
        /* Divisibility test by the direct computation method */
        /* is_div(n): 
             c = 1 + ((0xFFFFFFFF / d) & 0xFFFFFFFF)
             return n * c <= c - 1
        */
        mov $3865858, %esp
	mov $10, %cx
.LnextNumber:
	inc %r8w
	cmp $9999, %r8w
	je .done
	mov %r8d, %eax
	xor %edx, %edx
	mul %esp
        inc %eax
	cmp %eax, %esp
	ja .LnextNumber
	mov %r8w, %ax
	xor %bx, %bx
.getDigits:
	xor %dx, %dx
	xor %r15w, %r15w
	xor %r14w, %r14w
	xor %r13w, %r13w
	xor %r12w, %r11w
	div %cx
	xchg %dx, %r15w
	div %cx
	xchg %dx, %r14w
	div %cx
	xchg %dx, %r13w
	div %cx
	xchg %dx, %r11w
	/* Sorting */
.it0:
	cmp %r15w, %r14w
	jna .it1
	xchg %r15w, %r14w
.it1:
	cmp %r14w, %r13w
	jna .it2
	xchg %r14w, %r13w
	cmp %r15w, %r14w
	jna .it2
	xchg %r15w, %r14w
.it2:
	cmp %r13w, %r11w
	jna .ite
	xchg %r13w, %r11w
	cmp %r14w, %r13w
	jna .ite
	xchg %r14w, %r13w
	cmp %r15w, %r14w
	jna .ite
	xchg %r15w, %r14w
	/* Get outputs */
.ite:
#if 1
	imul $1000, %r15w, %r10w
	imul $100, %r14w, %dx
	imul $10, %r13w, %si

	imul $1000, %r11w, %r12w
	imul $100, %r13w, %ax
	imul $10, %r14w, %bp

	add %si, %dx
	add %ax, %bp
	
	add %dx, %r11w
	add %bp, %r15w

	add %r11w, %r10w

	sub %r15w, %r10w
	sub %r12w, %r10w
#else
	/* Unoptimised */

	mov %r15w, %ax
	mul %cx
        add %r14w, %ax
	mul %cx
	add %r13w, %ax
	mul %cx
	mov %ax, %r10w
	add %r11w, %r10w

	mov %r11w, %ax
	mul %cx
        add %r13w, %ax
	mul %cx
	add %r14w, %ax
	mul %cx
	mov %ax, %r12w
	add %r15w, %r12w
	sub %r12w, %r10w
#endif
.continue:
	inc %bx
	cmp $6174, %r10w
	jne .nextIteration
	cmp $7, %bx
	jne .LnextNumber
	inc %RES
	jmp .LnextNumber
.nextIteration:
	mov %r10w, %ax
	jmp .getDigits
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
