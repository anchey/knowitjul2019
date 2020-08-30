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

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE (256)
#define S3S (3)

extern char list[];
extern size_t const list_l;

int main() {
	unsigned int i;
	char buf[BUF_SIZE];

	assert((list_l % 2 == 0));
	assert((list_l % S3S == 0));

#if defined(DEBUG) || defined(TRACE)
	fprintf(stderr, "Input:  %.*s\n", (int)list_l, list);
#endif

	/* Step 3 */
	for (i = 0; i < list_l / 2; i += S3S) {
		memcpy(buf, &list[i], S3S);
		memcpy(&list[i], &list[list_l - i - S3S], S3S);
		memcpy(&list[list_l - i - S3S], buf, S3S);
#ifdef TRACE
		fprintf(stderr, "Step 3: %.*s (i = %u)\n", (int)list_l, list, i);
#endif
	}

#if defined(DEBUG) || defined(TRACE)
	fprintf(stderr, "Step 3: %.*s\n", (int)list_l, list);
#endif

	/* Step 2 */
	for (i = 0; i < list_l; i += 2) {
		char temp;
		temp = list[i];
		list[i] = list[i + 1];
		list[i + 1] = temp;
#ifdef TRACE
		fprintf(stderr, "Step 2: %.*s (i = %u)\n", (int)list_l, list, i);
#endif
	}

#if defined(DEBUG) || defined(TRACE)
	fprintf(stderr, "Step 2: %.*s\n", (int)list_l, list);
#endif

	/* Step 1 */
	memcpy(buf, &list[0], list_l / 2);
	memcpy(&list[0], &list[list_l / 2], list_l / 2);
	memcpy(&list[list_l / 2], buf, list_l / 2);

#if defined(DEBUG) || defined(TRACE)
	fprintf(stderr, "Step 1: %.*s\n", (int)list_l, list);
#endif

#if defined(DEBUG) || defined(TRACE)
	fprintf(stderr, "Final:  %.*s\n", (int)list_l, list);
#endif

	printf("%.*s\n", (int)list_l, list);
}
