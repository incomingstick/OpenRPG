var spawn = require('child_process').spawn;
var build;

var os = require('os');
//control OS
//then run command depengin on the OS

if (os.type() === 'Linux') 
   build = spawn("./build.sh", ['release']); 
else if (os.type() === 'Darwin') 
   build = spawn("./build.sh", ['release']); 
else if (os.type() === 'Windows_NT') 
   build = spawn("build.bat", ['release']);
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