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

const luke19 = ((from, to) => {
    const isPalindrome = (n) => {
        const s = String(n);
        const firstHalf = s.substr(0, s.length >> 1);
        const secondHalf = s.substr((s.length >> 1) + (s.length & 1));
        const rSecondHalf = Array.from(secondHalf).reverse().join('');
        return (firstHalf === rSecondHalf);
    };

    const addReversed = (n) => n + Number(Array.from(String(n)).reverse().join(''));    

    const isHiddenPalindrome = (n) => (!isPalindrome(n) && isPalindrome(addReversed(n)));

    return Array.from(Array(to - from + 1).keys()).map(
            (n) => isHiddenPalindrome(n + from) ? (n + from) : void 0
    ).filter(Number.isFinite).reduce((acc, cv) => acc + (+cv), 0);
});

console.log(luke19(1, 123454321));

