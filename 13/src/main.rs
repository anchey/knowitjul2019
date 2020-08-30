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

extern crate serde;
extern crate serde_json;
#[macro_use] extern crate serde_derive;

use std::fs::File;
use std::io::Read;
use std::collections::LinkedList;

#[derive(Serialize, Deserialize)]
struct MazeCell {
    x: u16,
    y: u16,
    top: bool,
    left: bool,
    bottom: bool,
    right: bool,
}

#[derive(Debug)]
enum Direction {
    Up,
    Down,
    Left,
    Right
}

//#[derive(Serialize, Deserialize)]
type Maze = Vec<Vec<MazeCell>>;

fn solve(maze: &Maze, directions : &[Direction; 4]) -> Result<u32, &'static str> {
    let mut count : u32 = 0;
    let mut visited : [[bool; 500]; 500] = [ [ false; 500 ] ; 500 ];

    let mut q: LinkedList<(u16, u16)> = LinkedList::new();
    let mut solved: bool = false;

    q.push_back((0, 0));

    while !q.is_empty() {
        let qr = q.pop_back();

        match qr {
            Some((x, y)) => {

                if x >= 500 || y >= 500 {
                    println!("Error, too big {} {}", x, y);
                    break;
                }

                count += 1;

                if (499, 499) == (x, y) {
                    solved = true;
                    break;
                }

                let (xi, yi) = (usize::from(x), usize::from(y));

                assert!(maze[yi][xi].x == x);
                assert!(maze[yi][xi].y == y);

                if visited[yi][xi] {
                    continue;
                }

                visited[yi][xi] = true;

                for direction in directions {
                    match direction {
                        Direction::Up => {
                            if y > 0 && !maze[yi][xi].top && !visited[yi - 1][xi] {
                                q.push_back((x, y - 1));
                            }
                        },
                        Direction::Down => {
                            if y < 499 && !maze[yi][xi].bottom && !visited[yi + 1][xi] {
                                q.push_back((x, y + 1));
                            }
                        },
                        Direction::Left => {
                            if x > 0 && !maze[yi][xi].left && !visited[yi][xi - 1] {
                                q.push_back((x - 1, y));
                            }
                        },
                        Direction::Right => {
                            if x < 499 && !maze[yi][xi].right && !visited[yi][xi + 1] {
                                q.push_back((x + 1, y));
                            }
                        },
                    }
                }
            },
            _ => {},
        }

    }

    return if solved { Ok(count) } else { Err("Unexpected error") };
}

fn main() {
   let mut file = File::open("MAZE.TXT").unwrap();
   let mut buff = String::new();
   let directions_arthur : [Direction; 4] = [Direction::Down, Direction::Right, Direction::Left, Direction::Up];
   let directions_isaac : [Direction; 4] = [Direction::Right, Direction::Down, Direction::Left, Direction::Up];
   file.read_to_string(&mut buff).unwrap();

   let maze: Maze = serde_json::from_str(&buff).unwrap();

   let arthur = solve(&maze, &directions_arthur).unwrap();
   let isaac = solve(&maze, &directions_isaac).unwrap();

   let r = if arthur > isaac { arthur - isaac } else { isaac - arthur };

   println!("{}", r);
}
