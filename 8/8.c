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

#include <limits.h>
#include <stdio.h>

#define REELS (10)
#define ADVANCE_TWICE (1)
#define MIN_COINS (1)
#define MAX_COINS (10)

#ifndef DEBUG
#define fprintf(...)
#endif

enum OPERATION {
	PLUSS4,
	PLUSS101,
	MINUS9,
	MINUS1,
	REVERSERSIFFER,
	OPP7,
	GANGEMSD,
	DELEMSD,
	PLUSS1TILPAR,
	TREKK1FRAODDE,
	ROTERPAR,
	ROTERODDE,
	ROTERALLE,
	STOPP,
};

enum OPERATION const reels[REELS][4] = {
	{PLUSS101, OPP7, MINUS9, PLUSS101},
	{TREKK1FRAODDE, MINUS1, MINUS9, PLUSS1TILPAR},
	{PLUSS1TILPAR, PLUSS4, PLUSS101, MINUS9},
	{MINUS9, PLUSS101, TREKK1FRAODDE, MINUS1},
	{ROTERODDE, MINUS1, PLUSS4, ROTERALLE},
	{GANGEMSD, PLUSS4, MINUS9, STOPP},
	{MINUS1, PLUSS4, MINUS9, PLUSS101},
	{PLUSS1TILPAR, MINUS9, TREKK1FRAODDE, DELEMSD},
	{PLUSS101, REVERSERSIFFER, MINUS1, ROTERPAR},
	{PLUSS4, GANGEMSD, REVERSERSIFFER, MINUS9},
};

signed long long int run(char initial) {
	signed long long amount;
	char reel_pos[REELS] = { 0 };

	amount = initial;

	do {
		char wp;
		unsigned char const reel = (amount >= 0LL) ? (unsigned char)((unsigned long long)amount % 10ULL) : (unsigned char)((unsigned long long)(-1LL * amount) % 10ULL);
		enum OPERATION const op = reels[reel][reel_pos[reel]];

		fprintf(stderr, "[IN  reel POSITIONS ");
		for (wp = 0; wp < REELS; wp++) {
			fprintf(stderr, "%u ", (unsigned int)reel_pos[wp]);
		}
		fprintf(stderr, "]\n");

		switch(op) {
		case PLUSS4:
			fprintf(stderr, "reel %u PLUSS4        : %10lld ==> ", (unsigned int)reel, amount);
			amount += 4;
			fprintf(stderr, "%10lld\n", amount);
			break;
		case PLUSS101:
			fprintf(stderr, "reel %u PLUSS101      : %10lld ==> ", (unsigned int)reel, amount);
			amount += 101;
			fprintf(stderr, "%10lld\n", amount);
			break;
		case MINUS9:
			fprintf(stderr, "reel %u MINUS9        : %10lld ==> ", (unsigned int)reel, amount);
			amount -= 9;
			fprintf(stderr, "%10lld\n", amount);
			break;
		case MINUS1:
			fprintf(stderr, "reel %u MINUS1        : %10lld ==> ", (unsigned int)reel, amount);
			amount -= 1;
			fprintf(stderr, "%10lld\n", amount);
			break;
		case REVERSERSIFFER: {
			unsigned long long const aamount = (amount >= 0LL) ? (unsigned long long)amount : (unsigned long long)(-1LL * amount);
			signed long long aamountrev;
			char buf[32];
			unsigned char i;
			int l;

			fprintf(stderr, "reel %u REVERSERSIFFER: %10lld ==> ", (unsigned int)reel, amount);

			l = snprintf(buf, sizeof(buf) - 1, "%llu", aamount);
			buf[sizeof(buf) - 1] = '\0';

			for (i = 0; i < l / 2; i++) {
				char const t = buf[i];
				buf[i] = buf[l - i - 1];
				buf[l - i - 1] = t;
			}

			sscanf(buf, "%llu", &aamountrev);

			amount = (amount >= 0) ? (signed long long)aamountrev : (signed long long)(aamountrev) * -1LL;

			fprintf(stderr, "%10lld\n", amount);
			break;
		}
		case OPP7:
			fprintf(stderr, "reel %u OPP7          : %10lld ==> ", (unsigned int)reel, amount);
			do {
				unsigned char const last_digit = (amount >= 0LL) ? (unsigned char)((unsigned long long)amount % 10ULL) : (unsigned char)((unsigned long long)(-1LL * amount) % 10ULL);
				if (last_digit == 7) {
					break;
				}
				amount++;
			} while(1);
			fprintf(stderr, "%10lld\n", amount);
			break;
		case GANGEMSD: {
			unsigned long long const aamount = (amount >= 0LL) ? (unsigned long long)amount : (unsigned long long)(-1LL * amount);
			unsigned long long x, y;
			fprintf(stderr, "reel %u GANGEMSD      : %10lld ==> ", (unsigned int)reel, amount);
			for (x = aamount; x != 0; y = x, x /= 10LL);
			amount *= (signed long long)y;
			fprintf(stderr, "%10lld\n", amount);
			break;
		}
		case DELEMSD: {
			unsigned long long const aamount = (amount >= 0LL) ? (unsigned long long)amount : (unsigned long long)(-1LL * amount);
			unsigned long long x, y, z;
			fprintf(stderr, "reel %u DELEMSD       : %10lld ==> ", (unsigned int)reel, amount);
			for (x = aamount; x != 0; y = x, x /= 10LL);
			z = (amount % (signed long long)y) >= 0LL ? 0LL : -1LL;
			amount /= (signed long long)y;
			amount += z;
			fprintf(stderr, "%10lld (z %llu)\n", amount, z);
			break;
		}
		case PLUSS1TILPAR: {
			unsigned long long const aamount = (amount >= 0LL) ? (unsigned long long)amount : (unsigned long long)(-1LL * amount);
			signed long long aamountrev;
			char buf[32];
			unsigned char i;
			int l;

			fprintf(stderr, "reel %u PLUSS1TILPAR  : %10lld ==> ", (unsigned int)reel, amount);
			l = snprintf(buf, sizeof(buf) - 1, "%llu", aamount);
			buf[sizeof(buf) - 1] = '\0';

			for (i = 0; i < l; i++) {
				switch (buf[i]) {
				case '0':
				case '2':
				case '4':
				case '6':
				case '8':
					buf[i]++;
				}
			}

			sscanf(buf, "%llu", &aamountrev);

			amount = (amount >= 0) ? (signed long long)aamountrev : (signed long long)(aamountrev) * -1LL;

			fprintf(stderr, "%10lld\n", amount);
			break;
		}
		case TREKK1FRAODDE: {
			unsigned long long const aamount = (amount >= 0LL) ? (unsigned long long)amount : (unsigned long long)(-1LL * amount);
			signed long long aamountrev;
			char buf[32];
			unsigned char i;
			int l;

			fprintf(stderr, "reel %u TREKK1FRAODDE : %10lld ==> ", (unsigned int)reel, amount);
			l = snprintf(buf, sizeof(buf) - 1, "%llu", aamount);
			buf[sizeof(buf) - 1] = '\0';

			for (i = 0; i < l; i++) {
				switch (buf[i]) {
				case '1':
				case '3':
				case '5':
				case '7':
				case '9':
					buf[i]--;
				}
			}

			sscanf(buf, "%llu", &aamountrev);

			amount = (amount >= 0) ? (signed long long)aamountrev : (((signed long long)(aamountrev)) * -1LL);

			fprintf(stderr, "%10lld\n", amount);
			break;
		}
		case ROTERPAR: {
			char w;
			fprintf(stderr, "reel %u ROTERPAR      : %10lld ==> ", (unsigned int)reel, amount);
			for (w = 0; w < REELS; w += 2) {
				if (ADVANCE_TWICE || w != reel) {
					reel_pos[w] = (reel_pos[w] + 1) % 4;
				}
			}
			fprintf(stderr, "%10lld\n", amount);
			break;
		}
		case ROTERODDE: {
			char w;
			fprintf(stderr, "reel %u ROTERODDE     : %10lld ==> ", (unsigned int)reel, amount);
			for (w = 1; w < REELS; w += 2) {
				if (ADVANCE_TWICE || w != reel) {
					reel_pos[w] = (reel_pos[w] + 1) % 4;
				}
			}
			fprintf(stderr, "%10lld\n", amount);
			break;
		}
		case ROTERALLE: {
			char w;
			fprintf(stderr, "reel %u ROTERALLE     : %10lld ==> ", (unsigned int)reel, amount);
			for (w = 0; w < REELS; w++) {
				if (ADVANCE_TWICE || w != reel) {
					reel_pos[w] = (reel_pos[w] + 1) % 4;
				}
			}
			fprintf(stderr, "%10lld\n", amount);
			break;
		}
		case STOPP:
			fprintf(stderr, "reel %u STOPP         : %10lld\n", (unsigned int)reel, amount);
			return amount;
			break;
		}

		reel_pos[reel] = (reel_pos[reel] + 1) % 4;
		fprintf(stderr, "[OUT reel POSITIONS ");
		for (wp = 0; wp < REELS; wp++) {
			fprintf(stderr, "%u ", (unsigned int)reel_pos[wp]);
		}
		fprintf(stderr, "]\n");
	} while(1);
}

int main() {
#ifdef BENCHMARK /* Benchmark */
	int j;
	for(j=0; j < 1000*1000; j++)
#endif
    {
		int i;
		signed long long max_payout = LLONG_MIN;

		for(i = MIN_COINS; i < MAX_COINS + 1; i++) {
			signed long long const payout = run((char) i);
			fprintf(stderr, "%10lld   (%2u COINS)\n", payout, i);
			if (payout > max_payout) {
				max_payout = payout;
			}
		}

		printf("%lld\n", max_payout);
	}
}
