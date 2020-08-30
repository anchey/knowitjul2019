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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE (1024 * 1024 * 2)

int main() {
	char buf[BUF_SIZE];
	unsigned long w = 275, h = 183;
	size_t r = 0, s, pos;

	char prev[3] = {0, 0, 0};
	char cur[3] = {0, 0, 0};

	do {
		s = fread(&buf[r], sizeof(*buf), sizeof(buf) / sizeof(*buf) - r, stdin);
		r += s;
	} while (s != 0 && r < sizeof(buf) / sizeof(*buf));

	if (ferror(stdin)) {
		fprintf(stderr, "Unable to read data\n");
		exit(EXIT_FAILURE);
	}

	if (r < 16 || memcmp("P6\n", &buf[0], 3) != 0) {
		fprintf(stderr, "Unsupported format\n");
		exit(EXIT_FAILURE);
	} else {
		fwrite(&buf[0], sizeof(*buf), 15, stdout);
	}

	pos = 15;

	do {
		cur[0] = buf[pos] ^ prev[0];
		cur[1] = buf[pos + 1] ^ prev[1];
		cur[2] = buf[pos + 2] ^ prev[2];
		prev[0] = buf[pos++];
		prev[1] = buf[pos++];
		prev[2] = buf[pos++];
		fwrite(cur, 1, 3, stdout);
	} while(pos < sizeof(buf) && pos < r);

	fflush(stdout);
}
