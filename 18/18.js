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

const names = require('./names'),
      employees = require('./employees');

const swNames = (() => {
    const swNames = {};

    for (const employee of employees) {
        if (!employee) continue;

        const givenIndex = [...employee['givenName']].map((c) => (c).charCodeAt(0)).reduce((acc, cv) => acc + cv, 0);

        const sn1Index = [...employee['sn'].toLowerCase().substr(0, (employee['sn'].length + 1) >> 1)].map((c) => (c).charCodeAt(0) + 1 - 'a'.charCodeAt(0)).reduce((acc, cv) => acc + cv, 0);

        const sn2Index = (() => {
            const multiplier =  (employee['sex'] === 'M') ?  employee['givenName'].length : (employee['givenName'].length + employee['sn'].length);

            const i = multiplier * [...employee['sn'].substr((employee['sn'].length + 1) >> 1)].map((c) => (c).charCodeAt(0)).reduce((acc, cv) => acc * cv, 1);

            return Number([...String(i)].sort((a, b) => Number(b) - Number(a)).join(''));
        })();

        const swName = [
            (employee['sex'] === 'M') ?
                names['mnames'][givenIndex % names['mnames'].length]
                :
                names['fnames'][givenIndex % names['fnames'].length]
            ,
            [
                names['snames1'][sn1Index % names['snames1'].length],
                names['snames2'][sn2Index % names['snames2'].length],
            ].join(''),
        ].join(' ');

        swNames[swName] = (swNames[swName] || 0) + 1;
    }

    return swNames;
})();

const top = Object.entries(swNames).reduce((acc, cv) => cv[1] > acc[1] ? cv : acc, [null, Number.NEGATIVE_INFINITY]);

console.log(top[0]);
