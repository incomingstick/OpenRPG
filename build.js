var spawn = require('child_process').spawn;
var build;

var os = require('os');
//control OS
//then run command depengin on the OS

// ignore 'node' and 'build.js' and get all following args
// these args get passed to the build scripts
var args = process.argv.slice(2);

if (os.type() === 'Linux') 
   build = spawn("./build.sh", args); 
else if (os.type() === 'Darwin') 
   build = spawn("./build.sh", args); 
else if (os.type() === 'Windows_NT') 
   build = spawn("build.bat", args);
else
   throw new Error("Unsupported OS found: " + os.type());

build.stdout.on('data', function (data) {
   process.stdout.write(data.toString());
});
   
build.stderr.on('data', function (data) {
   process.stderr.write(data.toString());
});
   
build.on('exit', function (code) {
   console.log('child process exited with code ' + code.toString());
});