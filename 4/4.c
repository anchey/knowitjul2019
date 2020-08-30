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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE (1000U)

#define HORIZONTAL (0)
#define VERTICAL (1)

#define LEFT (2)
#define RIGHT (4)
#define UP (8)
#define DOWN (16)

#ifdef DEBUG
#define TRACE_MOVEMENT(D) do { \
	fprintf(stderr, "(%3u, %3u)->(%3u, %03u) @(%3u, %3u)+%2u[%s]\n", \
		ox, oy, \
		dx, dy, \
		x, y, \
		visited[x][y], \
		D == UP ? "U" : D == LEFT ? "L" : D == DOWN ? "D" : "R" \
	); \
} while(0)
#else
#define TRACE_MOVEMENT(D) do {} while(0)
#endif

extern unsigned int const coordinates[][2];
extern size_t const coordinates_l;

int main() {
	unsigned int visited[SIZE][SIZE];
	unsigned int i, x, y;
	unsigned int time;

	memset(visited, 0, sizeof(visited));

	for(i = 0, x = 0, y = 0, time = 0; i < coordinates_l; ++i) {
		unsigned int const dx = coordinates[i][HORIZONTAL];
		unsigned int const dy = coordinates[i][VERTICAL];
		unsigned int const steps[] = {
			(dx > x) ? (dx - x) : (x - dx),
			(dy > y) ? (dy - y) : (y - dy),
		};
		unsigned char const direction[] = {
			(dx > x) ? RIGHT : LEFT,
			(dy > y) ? UP    : DOWN,
		};
		unsigned int j;
#ifdef DEBUG
		unsigned int const ox = x, oy = y;
#endif

		for(j = 0; j < steps[HORIZONTAL]; j++) {
			TRACE_MOVEMENT(direction[HORIZONTAL]);
			switch (direction[HORIZONTAL]) {
			case LEFT:
				x--;
				break;
			case RIGHT:
				x++;
				break;
			default:
				assert(0);
			}
			time += ++visited[x][y];
		}

		for(j = 0; j < steps[VERTICAL]; j++) {
			TRACE_MOVEMENT(direction[VERTICAL]);
			switch (direction[VERTICAL]) {
			case DOWN:
				y--;
				break;
			case UP:
				y++;
				break;
			default:
				assert(0);
			}
			time += ++visited[x][y];
		}
	}

	printf("Time: %u\n", time);
}
