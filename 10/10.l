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
#include <stdlib.h>
	#include "10.h"
	#include "10.tab.h"

	unsigned long line_num = 1;
%}
%option noyywrap
%%
[ ]                  { return SPACE; }
\t                   { return TAB; }
\r\n                 { ++line_num; return CRLF; }
\r                   { ++line_num; return CR; }
\n                   { ++line_num; return LF; }
[0-9]+               { yylval.ulvalue = strtoul(yytext, NULL, 10); return ULONG; }
ml                   { yylval.unit = MILLILITER; return UNIT; }
meter                { yylval.unit = METER; return UNIT; }
\:                   { return COLON; }
\*                   { return STAR; }
tannkrem             { yylval.product = TOOTHPASTE; return PRODUCT; }
sjampo               { yylval.product = SHAMPOO; return PRODUCT; }
toalettpapir         { yylval.product = TOILETPAPER; return PRODUCT; }
Jan                  { yylval.month = JANUARY; return MONTH; }
Feb                  { yylval.month = FEBRUARY; return MONTH; }
Mar                  { yylval.month = MARCH; return MONTH; }
Apr                  { yylval.month = APRIL; return MONTH; }
May                  { yylval.month = MAY; return MONTH; }
Jun                  { yylval.month = JUNE; return MONTH; }
Jul                  { yylval.month = JULY; return MONTH; }
Aug                  { yylval.month = AUGUST; return MONTH; }
Sep                  { yylval.month = SEPTEMBER; return MONTH; }
Oct                  { yylval.month = OCTOBER; return MONTH; }
Nov                  { yylval.month = NOVEMBER; return MONTH; }
Dec                  { yylval.month = DECEMBER; return MONTH; }
%%
