#!/usr/bin/env python3

#  Copyright 2019 Ricardo Iván Vieitez Parra
#
#  Permission to use, copy, modify, and distribute this software for any
#  purpose with or without fee is hereby granted, provided that the above
#  copyright notice and this permission notice appear in all copies.
#
#  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
#  REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
#  AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
#  INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
#  LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
#  OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
#  PERFORMANCE OF THIS SOFTWARE.
#

def krampus(num) -> int:
    squared = num * num
    numStr = str(squared)

    for i in range(1, len(numStr)):
        num1 = int(numStr[i:])
        num2 = int(numStr[:i])

        if num1 == 0 or num == 0: return 0
        if num1+num2 == num: return num

    return 0

sum = 0
for num in open("krampus.txt").readlines():
    sum += krampus(int(num))

print(sum)
