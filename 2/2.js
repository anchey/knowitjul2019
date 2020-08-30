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

/*const data = document.body.textContent.split('\n').map((x)=>x.split(''));
data.forEach(Object.freeze);
Object.freeze(data);*/

// Running instructions (in browser): open world.txt and then run this script

const data2 = document.body.textContent.split('\n').map((x)=>x.split(''));

const fill = (xs, ys) => {
    const s = new Set();
    s.add([xs, ys]);
    do {
        const c = s.values().next().value, [x, y] = c;
        s.delete(c);
        if (Array.isArray(data2[x]) && data2[x][y] === ' ') {
            data2[x][y] = '+';
            s.add([x, y + 1]);
            s.add([x, y - 1]);
            s.add([x + 1, y]);
        }
    } while (s.size);
};

fill(0, 0);
fill(0, 2000);

document.body.innerHTML = '<pre>' + data2.map(x=>x.join('')).join('\n');

const drain = () => {
    const drainAbove = (xs, ys) => {
        const s = new Set();
        s.add([xs, ys]);
        do {
            const c = s.values().next().value, [x, y] = c;
            s.delete(c);
            if (Array.isArray(data2[x]) && data2[x][y] === '+') {
                data2[x][y] = ' ';
                s.add([x, y + 1]);
                s.add([x, y - 1]);
                s.add([x - 1, y]);
            }
        } while (s.size);
    };

    for(let x = 0; x < data2.length; x++) {
        const lb = data2[x].indexOf('#');
        const rb = data2[x].lastIndexOf('#');
        if (lb > 0) {
            drainAbove(x, 0);
        }
        if (rb > 0) {
            drainAbove(x, data2[x].length - 1);
        }
    }
};

drain();

document.body.innerHTML = '<pre>' + data2.map(x=>x.join('')).join('\n');

// Answer

data2.map(x=>x.join('')).join('').split('').filter(x=>x==='+').length;
