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

#include <inttypes.h>
#include <stdio.h>

uint8_t const maxDigits[] = {
	/*  0 */ 1,
	/*  1 */ 1,
	/*  2 */ 1,
	/*  3 */ 2,
	/*  4 */ 2,
	/*  5 */ 2,
	/*  6 */ 3,
	/*  7 */ 3,
	/*  8 */ 3,
	/*  9 */ 4,
	/* 10 */ 4,
	/* 11 */ 4,
	/* 12 */ 4,
	/* 13 */ 5,
	/* 14 */ 5,
	/* 15 */ 5,
	/* 16 */ 6,
	/* 17 */ 6,
	/* 18 */ 6,
	/* 19 */ 7,
	/* 20 */ 7,
	/* 21 */ 7,
	/* 22 */ 7,
	/* 23 */ 8,
	/* 24 */ 8,
	/* 25 */ 8,
	/* 26 */ 9,
	/* 27 */ 9,
	/* 28 */ 9,
	/* 29 */ 10,
	/* 30 */ 10,
	/* 31 */ 10,
	/* 32 */ 10,
	/* 33 */ 11,
	/* 34 */ 11,
	/* 35 */ 11,
	/* 36 */ 12,
	/* 37 */ 12,
	/* 38 */ 12,
	/* 39 */ 13,
	/* 40 */ 13,
	/* 41 */ 13,
	/* 42 */ 13,
	/* 43 */ 14,
	/* 44 */ 14,
	/* 45 */ 14,
	/* 46 */ 15,
	/* 47 */ 15,
	/* 48 */ 15,
	/* 49 */ 16,
	/* 50 */ 16,
	/* 51 */ 16,
	/* 52 */ 16,
	/* 53 */ 17,
	/* 54 */ 17,
	/* 55 */ 17,
	/* 56 */ 18,
	/* 57 */ 18,
	/* 58 */ 18,
	/* 59 */ 19,
	/* 60 */ 19,
	/* 61 */ 19,
	/* 62 */ 19,
	/* 63 */ 20,
};

uint64_t const bases[] = {
	/*  0 */ UINT64_C(1),
	/*  1 */ UINT64_C(10),
	/*  2 */ UINT64_C(100),
	/*  3 */ UINT64_C(1000),
	/*  4 */ UINT64_C(10000),
	/*  5 */ UINT64_C(100000),
	/*  6 */ UINT64_C(1000000),
	/*  7 */ UINT64_C(10000000),
	/*  8 */ UINT64_C(100000000),
	/*  9 */ UINT64_C(1000000000),
	/* 10 */ UINT64_C(10000000000),
	/* 11 */ UINT64_C(100000000000),
	/* 12 */ UINT64_C(1000000000000),
	/* 13 */ UINT64_C(10000000000000),
	/* 14 */ UINT64_C(100000000000000),
	/* 15 */ UINT64_C(1000000000000000),
	/* 16 */ UINT64_C(10000000000000000),
	/* 17 */ UINT64_C(100000000000000000),
	/* 18 */ UINT64_C(1000000000000000000),
};

inline static uint8_t uint64len(uint64_t const n) __attribute__ ((const));
inline static uint64_t rotate(uint64_t const n, uint8_t const p, uint8_t const len) __attribute__ ((const));
inline static uint64_t isqrt64(uint64_t const n) __attribute__ ((const));
inline static char isPerfectSquare(uint64_t n) __attribute__ ((const));
inline static uint64_t triangularNumber(uint32_t const i) __attribute__ ((const));

inline static uint8_t uint64len(uint64_t const n) {
	uint64_t bsr;
	uint8_t len;

	if (n == 0) {
		return 1;
	}

	__asm__ volatile ("bsrq\t%1, %0" : "=r" (bsr) : "rm" (n) );

	len = maxDigits[bsr];

	if (bsr && maxDigits[bsr - 1] != len && (n / bases[len - 1]) == 0) {
		len--;
	}

	return len;
}

inline static uint64_t rotate(uint64_t const n, uint8_t const p, uint8_t const len) {
	uint64_t const l = n % bases[p], r = n / bases[p];

	if (p > len) {
		__builtin_unreachable();
	}

	return l * bases[len - p] + r;
}

inline static uint64_t isqrt64(uint64_t const n) {
	/* Algorithm below by Tristan Muntsinger (Tristan.Muntsinger@gmail.com) */
	uint64_t register c = UINT64_C(0x80000000);
	uint64_t register g = UINT64_C(0x80000000);

	for(;;) {
		if (g*g > n) {
			g ^= c;
		}
		c >>= UINT64_C(1);
		if(c == UINT64_C(0)) {
			return g;
		}
		g |= c;
	}
}

inline static char isPerfectSquare(uint64_t n) {
#if 0
	uint64_t const isqrt = isqrt64(n);

	if ((n - (isqrt * isqrt)) == 0) {
		return 1;
	} else {
		return 0;
	}
#else
	if ((UINT64_C(0x202021202030213) & (UINT64_C(1) << (n & UINT64_C(63)))) > 0) {
		uint64_t const isqrt = isqrt64(n);

		return (isqrt * isqrt) == n;
	} else {
		return 0;
	}
#endif
}

inline static uint64_t triangularNumber(uint32_t const i) {
	return ((uint64_t)i * ((uint64_t)i + UINT64_C(1))) >> UINT64_C(1);
}

int main(int argc, char * * argv) {
	uint32_t i, c = 0;

	(void)argc;
	(void)argv;

	for (i = UINT32_C(0); i < UINT32_C(1000000); i++) {
		uint64_t t, tr;
		uint8_t len, p;

		t = triangularNumber(i);
		len = uint64len(t);

		p = 0;

		tr = t;

		do {
#ifdef DEBUG
			fprintf(stderr, "i = %4" PRIu32 " (c=%3" PRIu32 ") ;; t: %7" PRIu64 " len: %4" PRIu8 " tr: %7" PRIu64 " pS: %u p: %2" PRIu8 " \n", i, c, t, len, tr, (unsigned int)isPerfectSquare(tr), p);
#endif

			if (isPerfectSquare(tr)) {
				c++;
				break;
			}

			if (++p == len) {
				break;
			}
			tr = rotate(t, p, len);
		} while(1);
	}

	printf("%" PRIu32  "\n", c);

	return 0;
}
