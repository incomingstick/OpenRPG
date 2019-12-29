var spawn = require('child_process').spawn;
var build;

var os = require('os');
//control OS
//then run command depengin on the OS

// ignore 'node' and 'build.js' and get all following args
// these args get passed to the build scripts
var args = process.argv.slice(2);

if(args[0] !== 'download') {
   if (os.type() === 'Linux') 
      build = spawn("./build.sh", args); 
   else if (os.type() === 'Darwin') 
      build = spawn("./build.sh", args); 
   else if (os.type() === 'Windows_NT') 
      build = spawn("build.bat", args);
   else
      throw new Error("Unsupported OS found: " + os.type());
   
   build.stdout.on('data', (data) => {
      process.stdout.write(data.toString());
   });
      
   build.stderr.on('data', (data) => {
      process.stderr.write(data.toString());
   });
      
   build.on('exit', (code) => {
      console.log('child process exited with code ' + code.toString());
   });
} else {
   const fs = require('fs')
   var tmpdir = os.tmpdir();

   // make the tmpdir if it doesn't exist
   if(!fs.existsSync(tmpdir)) {
      fs.mkdirSync(tmpdir);
   }

   // if the tmpdir still doesn't exist, lets try it locally
   if(!fs.existsSync(tmpdir)) {
      tmpdir = './';
   }

   var repo = require('./package.json').repository.url;
   var ver = require('./package.json').version;
   var ext = '.tar.gz'
   
   var osType;

   if (os.type() === 'Windows_NT') 
      osType = 'win64';
   else if (os.type() === 'Linux' || os.type() === 'Darwin')
      osType = os.type();
   else
      throw new Error("Unsupported OS found: " + os.type());

   const path = require('path');

   
   const base = 'OpenRPG-'+ ver + '-' + osType ;
   var filename = base + ext;
   var gitURL = repo + '/releases' + '/download' + '/v'+ ver + '/'+ filename;
   var shaExt = '.sha512'
   
   var download = path.join(tmpdir, filename);

   console.log('Downloading...\t', gitURL);

   const https = require('https');
   const url = require('url');

   var file = fs.createWriteStream(download);
   https.get(gitURL, (response) => {
      if (response.statusCode > 300 && response.statusCode < 400 && response.headers.location) {
         if (url.parse(response.headers.location).hostname) {
            https.get(response.headers.location, (data) => {
               data.pipe(file);
            });
         } else {
            https.get(url.resolve(url.parse(url).hostname, response.headers.location), (data) => {
               data.pipe(file);
            });
         }
      } else {
         response.pipe(file);
      }
   }).on('error', (error) => {
      console.error(error);
   });

   console.log('Unzipping...\t', download);

   // TODO sha256 check the download before writing
   /**
    * FIXME tar and zlib seem to both fail when passed our downloaded 
    **/
   const tar = require('tar');
   // const unzip = require('zlib').createUnzip();

   // switch to reading from writing to the downloaded file
   const comp = fs.createReadStream(download);
   // const tarball = fs.createWriteStream(path.join(tmpdir, 'openrpg.tar'));
   // comp.pipe(unzip).pipe(tarball);

   tar.extract({
      cwd: tmpdir,
      file: comp.path,
      sync: true
   });

   let uncomp = path.join(tmpdir, base);
   var dist = path.join(tmpdir, 'openrpg');

   if(fs.existsSync(dist)) fs.rmdirSync(dist, { recursive: true });
   if(fs.existsSync(uncomp)) fs.rename(uncomp, dist, (error) => { if(error) throw error; });

   // fs.unlinkSync(file.path);
}
