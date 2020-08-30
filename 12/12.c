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

#include <stdint.h>
#include <syscall.h>

#define printf(...) do { } while(0)

typedef uint8_t digits[4];

inline static char isDivisibleBy(uint16_t n, uint16_t d) {
	/* Divisibility test by the direct computation method */
	/* is_div(n):
	     c = 1 + ((0xFFFFFFFF / d) & 0xFFFFFFFF)
	     return n * c <= c - 1
	*/
	uint32_t c = UINT32_C(1) + ((UINT32_C(0xFFFFFFFF) / (uint32_t)d));
	return (uint32_t)n * c <= (c - 1);
}

inline static void getDigits(uint16_t n, digits d) {
	d[0] = (n / 1) % 10;
	d[1] = (n / 10) % 10;
	d[2] = (n / 100) % 10;
	d[3] = (n / 1000) % 10;
}

inline static uint16_t getNumber(digits d) {
	return d[3] * UINT16_C(1000) + d[2] * UINT16_C(100) + d[1] * UINT16_C(10) + d[0];
}

inline static uint16_t sortAndDiffNumber(digits const d) {
#define SORTANDSWAP(start, D, op) do { \
    uint8_t i; \
    for (i = (uint8_t)start; i != 0; --i) { \
        if (D[i] op D[i - 1]) { \
            uint16_t const t = D[i]; \
            D[i] = D[i - 1]; \
            D[i -  1] = t; \
        } \
    } \
} while(0)

	digits d1, d2;

	d1[0] = d2[0] = d[0];
	d1[1] = d2[1] = d[1];
	d1[2] = d2[2] = d[2];
	d1[3] = d2[3] = d[3];

	SORTANDSWAP(1, d1, >);
	SORTANDSWAP(2, d1, >);
	SORTANDSWAP(3, d1, >);
	SORTANDSWAP(1, d2, <);
	SORTANDSWAP(2, d2, <);
	SORTANDSWAP(3, d2, <);

	return getNumber(d2) - getNumber(d1);
}

void _start(void) {
	uint16_t n = 1000;

	uint16_t r = 0;
	char buf[5];

	for (; n <= 9999; ++n) {
		digits d;
		uint8_t i;

		if (isDivisibleBy(n, UINT16_C(1111))) {
			continue;
		}
		getDigits(n, d);
		printf("%d: %d %d %d %d :%d\n", n, (int)d[3], (int)d[2], (int)d[1], (int)d[0], (int)getNumber(d));
		for (i = 0; i < 7; ++i) {
			uint16_t const nn = sortAndDiffNumber(d);
			printf("\tnn = %d (i = %d)\n", (int)nn, (int)i);
			if (nn == UINT16_C(6174)) {
				if (i == 6) {
					r++;
				}
				break;
			}
			getDigits(nn, d);
		}
	}

	{
		digits rd;
		getDigits(r, rd);
		buf[0] = rd[3] + '0';
		buf[1] = rd[2] + '0';
		buf[2] = rd[1] + '0';
		buf[3] = rd[0] + '0';
		buf[4] = '\n';
		__asm__ volatile (
		    "syscall"
		    :
		    : "a" (SYS_write), "D" (1), "S" (buf), "d" (sizeof(buf))
		    : "ecx", "r11", "memory"
		);
		__asm__ volatile (
		    "syscall"
		    :
		    : "a" (SYS_exit), "D" (0), "S" (0), "d" (0)
		    : "ecx", "r11", "memory"
		);
	}
}

