#![feature(plugin)]
#![plugin(rocket_codegen)]

//imports for spawnning processes and sending html reponse
use std::process::Command;
use rocket::response::content;

//extern crate for rock framework && json 
extern crate rocket;
#[macro_use]
extern crate serde_json;


/// # Function Name: roll_module
/// ---
/// 
/// This function is called with a user navigates to /roll?<args>.
/// Uppon being called it grabs the args and splits them into an vector
/// by the delimiter & (the & does not go into the vector)
/// As long as there is at least 1 specified argument, it will call
/// the roll module with that argument. 
///
/// If &json is specified at the **END** of the path, it will drop down into
/// "Some(i)". It removes the json argument from the vector, then returns
/// the output of roll as a json formated object
///
/// ##Example
/// > calling with one argument /roll?-h
/// > calling with multiple arguments /roll?-v&3d4
/// > requesting json /roll?3d4&json

#[get("/roll?<args>")]
fn roll_module(args: &str) -> String {
let mut args1: Vec<&str> = args.split("&").collect();
let index = args1.iter().position(|&r| r == "json");
match index {
        None => {
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
            let json = json!({"output" : output_string});
            return json.to_string();
        }
    };
}


/// # Function Name: name_module
/// ---
/// 
/// This function is called with a user navigates to /name?<args>.
/// Uppon being called it grabs the args and splits them into an vector
/// by the delimiter & (the & does not go into the vector)
/// As long as there is at least 1 specified argument, it will call
/// the roll module with that argument. 
///
/// If &json is specified at the **END** of the path, it will drop down into
/// "Some(i)". It removes the json argument from the vector, then returns
/// the output of roll as a json formated object
///
/// ##Example
/// > calling with one argument /name?-h
/// > calling with multiple arguments /name?human&male
/// > requesting json /roll?human&male&json

#[get("/name?<args>")]
fn name_module(args: &str) -> String {
let mut args1: Vec<&str> = args.split("&").collect();
let index = args1.iter().position(|&r| r == "json");
match index {
        None => {
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
                let json = json!({"name" : output_string});
                return json.to_string();
            }
     };
}


/// # Function Name: remove_ele
/// ---
/// 
/// This function simple removes the specified element
/// spaw_remove is o(1), but will 
/// >Removes an element from anywhere in the vector and return it, replacing it with the last
/// element.

fn remove_ele(v: &mut Vec<&str>, p: usize){
    v.swap_remove(p);
}


/// # Function Name: not_found
/// ---
/// 
/// This will trigger if the path requested is not found.
/// It displays a simple error message, with suggestions. 

#[error(404)]
fn not_found(req: &rocket::Request) -> content::HTML<String> {
        content::HTML(format!("
        <h1>404 path '{}' not found!</h1>
        <p>Try visiting /roll?-h instead.</p>
        <p>or visit /name?-h instead. </p>
        ",
        req.uri()))
}


/// # Function Name: main
/// ---
/// 
/// Main funciton

fn main() {
    rocket::ignite()
        .mount("/", routes![roll_module, name_module])
        .catch(errors![not_found]) 
        .launch();
}
