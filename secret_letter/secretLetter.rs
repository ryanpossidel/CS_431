/*
CS 431
Language: Rust
Secret Letter
Compile:
	cargo run
	if you add crates: cargo build
*/

use std::io;
use rand::prelude::*;
use std::time::{Instant};

fn main() {
	
	let start = Instant::now();
	let mut rng = rand::thread_rng();
    let random = rng.gen_range(0..25);
	let mut alpha_str = String::new();
            for c in "abcdefghijklmnopqrstuvwxyz".chars() {
                if rng.gen() {
                    alpha_str.push(c);
                }
                else {
                    alpha_str.push(c.to_ascii_uppercase());
                }
            }
	
	let mut ans = String::new();
	ans = alpha_str.chars().nth(random).unwrap().to_string();
	ans = ans.to_lowercase();
	alpha_str.remove(random);
	let mut i = 0;
	loop{
		print!("{:?}",alpha_str.chars().nth(i).unwrap());
		i += 1;
		let newline = i % 5;
		if newline == 0{
			println!();
		}
		if i ==	25{
			break;
		}
    }
	
	loop{
		println!("What letter is hidden? ");
		let mut guess = String::new();
		io::stdin().read_line(&mut guess).expect("Failed to read line");
		guess = guess.to_lowercase();
		if ans == guess.trim(){		
			println!("You Got It in {} seconds!", 
					(start.elapsed().as_millis() / 100) as f64 / 10.0);
			break;
		}
	}
}