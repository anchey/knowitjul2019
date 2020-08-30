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

%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "10.h"

	extern int yylex();
	extern int yyparse();
	extern FILE *yyin;

	extern unsigned long line_num;

	void yyerror(const char *s);
	
	struct perioduse totaluse;
	struct perioduse dowuse[7];
	enum weekday dayOfWeek(unsigned short y, unsigned short m, unsigned short d);
%}

%union {
		unsigned long ulvalue;
		enum product product;
		enum month month;
		enum unit unit;
		struct date date;
		struct logentry logentry;
		struct perioduse dayuse;
}

%token SPACE
%token TAB
%token COLON
%token CRLF
%token CR
%token LF
%token STAR

%token <ulvalue>    ULONG
%token <month>      MONTH
%token <product>    PRODUCT
%token <unit>       UNIT

%type	<date>      dayheader
%type	<logentry>  productuse
%type	<dayuse>    uselist

%%
log:
	log daylog
	|
	%empty
	;
spacech:
	SPACE
	|
	TAB
	;
space:
	space spacech
	|
	spacech
	;
newl:
	CRLF
	|
	CR
	|
	LF
	;
daylog:
	dayheader newl uselist
	{
		char const dow = dayOfWeek((unsigned short)2018, (unsigned short)($1.month + 1), (unsigned short)($1.date));

		totaluse.amount[SHAMPOO] += $3.amount[SHAMPOO];
		totaluse.amount[TOILETPAPER] += $3.amount[TOILETPAPER];
		totaluse.amount[TOOTHPASTE] += $3.amount[TOOTHPASTE];
		dowuse[dow].amount[SHAMPOO] += $3.amount[SHAMPOO];
		dowuse[dow].amount[TOILETPAPER] += $3.amount[TOILETPAPER];
		dowuse[dow].amount[TOOTHPASTE] += $3.amount[TOOTHPASTE];
	}
	;
dayheader:
	MONTH space ULONG COLON
	{ 
		$$.month = $1;
		$$.date = $3;
	}
	;
uselist:
	%empty
	{
		$$.amount[SHAMPOO] = 0UL;
		$$.amount[TOILETPAPER] = 0UL;
		$$.amount[TOOTHPASTE] = 0UL;
	}
	|
	uselist productuse
	{
		$$.amount[$2.product] = $2.amount;
	}
	;
productuse:
	space STAR space ULONG space UNIT space PRODUCT newl
	{
		if (
		    (SHAMPOO     == $8 && MILLILITER != $6)
		 || (TOILETPAPER == $8 && METER      != $6)
		 || (TOOTHPASTE  == $8 && MILLILITER != $6)
		) {
			yyerror("Invalid product / unit combination.");
		}
		$$.amount = $4;
		$$.unit = $6;
		$$.product = $8;
	}
	;
%%
struct perioduse totaluse = { { 0 } };
struct perioduse dowuse[7] = { { { 0 } } };

enum weekday dayOfWeek(unsigned short y, unsigned short const m, unsigned short d) {
	return (enum weekday)(d+=m<3?y--:y-2,23*m/9+d+4+y/4-y/100+y/400)%7;
}

int main(int argc, char ** argv) {
	yyparse();
	
	fprintf(stderr, "%lu * %lu * %lu * %lu * %lu\n"
		, (totaluse.amount[SHAMPOO] / 300UL)
		, (totaluse.amount[TOILETPAPER] / 25UL)
		, (totaluse.amount[TOOTHPASTE] / 125UL)
		, (dowuse[SUNDAY].amount[SHAMPOO])
		, (dowuse[WEDNESDAY].amount[TOILETPAPER])
	);

	printf("%lu\n", 1UL
		* (totaluse.amount[SHAMPOO] / 300UL)
		* (totaluse.amount[TOILETPAPER] / 25UL)
		* (totaluse.amount[TOOTHPASTE] / 125UL)
		* (dowuse[SUNDAY].amount[SHAMPOO])
		* (dowuse[WEDNESDAY].amount[TOILETPAPER])
    );
}

void yyerror(const char *s) {
	fprintf(stderr, "Parse error at line %lu (%s)\n", line_num, s);
	exit(EXIT_FAILURE);
}
