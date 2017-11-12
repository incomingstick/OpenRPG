---
layout: docs
title: Die
description: A simple route for running the dice roll module.
group: web-api
---

# Function Name: roll_module

---
This function is called with a user navigates to `/roll?<args>`.

Uppon being called it grabs the args and splits them into an vector
by the delimiter & (the & does not go into the vector)
As long as there is at least 1 specified argument, it will call
the roll module with that argument.

If `&json` is specified at the **END** of the path, it will drop down into
`"Some(i)"`. It removes the json argument from the vector, then returns
the output of roll as a json formated object

## Example

Calling with one argument `{base_ul}/roll?-h`

Calling with multiple arguments `{base_url}/roll?-v&3d4`

Requesting json `{base_url}/roll?3d4&json`

## Definition

````rust
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
````
