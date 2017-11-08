---
layout: docs
title: NameGenerator
description: A simple route for running the name generation module.
group: api
---

# Function Name: name_module
---

This function is called with a user navigates to /name?<args>.
Uppon being called it grabs the args and splits them into an vector
by the delimiter & (the & does not go into the vector)
As long as there is at least 1 specified argument, it will call
the roll module with that argument.

If &json is specified at the **END** of the path, it will drop down into
"Some(i)". It removes the json argument from the vector, then returns
the output of roll as a json formated object

## Example
calling with one argument `{base_url}/name?-h`
calling with multiple arguments `{base_url}/name?human&male`
requesting json `{base_url}/roll?human&male&json`
## Definition
````rust
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
````
