#![feature(plugin)]
#![plugin(rocket_codegen)]

use std::process::Command;


extern crate rocket;

#[macro_use]
extern crate serde_json;

#[get("/roll?<args>")]
fn roll_via_url(args: &str) -> String {
let mut args1: Vec<&str> = args.split("&").collect();
let index = args1.iter().position(|&r| r == "json");
match index {
        None => {
            println!("404"); 
            let output = Command::new("./build/roll")
                .args(args1)
                .output()
                .expect("failed");
            return String::from_utf8_lossy(&output.stdout).to_string();
        },

        Some(i) => {
            remove_ele(&mut args1, i);
            let output = Command::new("./build/roll")
                .args(args1)
                .output()
                .expect("failed");
            let mut output_string = String::from_utf8_lossy(&output.stdout).to_string();
            output_string.pop();
            let json = json!({"message" : output_string});
            return json.to_string();
        }
    };
}

#[get("/name?<args>")]
fn name_via_url(args: &str) -> String {
let mut args1: Vec<&str> = args.split("&").collect();
let index = args1.iter().position(|&r| r == "json");
match index {
        None => {
             println!("404"); 
                let output = Command::new("./build/name-generator")
                    .args(args1)
                    .output()
                    .expect("failed");
                return String::from_utf8_lossy(&output.stdout).to_string();
            },

        Some(i) => {
                remove_ele(&mut args1, i);
                let output = Command::new("./build/name-generator")
                    .args(args1)
                    .output()
                    .expect("failed");
                let mut output_string = String::from_utf8_lossy(&output.stdout).to_string();
                output_string.pop();
                let json = json!({"message" : output_string});
                return json.to_string();
            }
     };
}

fn remove_ele(v: &mut Vec<&str>, p: usize){
    v.swap_remove(p);
}

fn main() {
    rocket::ignite().mount("/local/8000", routes![roll_via_url, name_via_url]).launch();
}
