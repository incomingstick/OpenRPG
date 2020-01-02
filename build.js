var spawn = require('child_process').spawn;
var build;

var os = require('os');
//control OS
//then run command depending on the OS

// ignore 'node' and 'build.js' and get all following args
// these args get passed to the build scripts
var args = process.argv.slice(2);

if (args[0] !== 'download') {
    if (os.type() === 'Linux') build = spawn('./build.sh', args);
    else if (os.type() === 'Darwin') build = spawn('./build.sh', args);
    else if (os.type() === 'Windows_NT') build = spawn('build.bat', args);
    else throw new Error('Unsupported OS found: ' + os.type());

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
    const fs = require('fs');
    var tmpdir = os.tmpdir();

    // make the tmpdir if it doesn't exist
    if (!fs.existsSync(tmpdir)) {
        fs.mkdirSync(tmpdir);
    }

    // if the tmpdir still doesn't exist, lets try it locally
    if (!fs.existsSync(tmpdir)) {
        tmpdir = './';
    }

    var repo = require('./package.json')
        .repository.url.replace('git+', '')
        .replace('OpenRPG.git', 'OpenRPG');
    var ver = require('./package.json').version;
    var ext = '.tar.gz';

    var osType;

    if (os.type() === 'Windows_NT') osType = 'win64';
    else if (os.type() === 'Linux' || os.type() === 'Darwin') osType = os.type();
    else throw new Error('Unsupported OS found: ' + os.type());

    const path = require('path');

    const base = 'OpenRPG-' + ver + '-' + osType;
    var filename = base + ext;
    var gitURL = repo + '/releases' + '/download' + '/v' + ver + '/' + filename;
    var shaExt = '.sha512';

    var download = path.join(tmpdir, filename);

    const https = require('https');
    const url = require('url');
    const crypto = require('crypto');

    console.log('Fetching Checksum...\t', gitURL + shaExt);

    let checksum;
    https
        .get(gitURL + shaExt, (sha) => {
            if (sha.statusCode > 300 && sha.statusCode < 400 && sha.headers.location) {
                if (url.parse(sha.headers.location).hostname) {
                    https.get(sha.headers.location, (data) => {
                        let mem = '';

                        data.on('data', (chunk) => {
                            mem += chunk;
                        });

                        data.on('end', () => {
                            checksum = mem.split(' ', 1)[0];
                        });
                    });
                } else {
                    https.get(url.resolve(url.parse(url).hostname, response.headers.location), (data) => {
                        let mem = '';

                        data.on('data', (chunk) => {
                            mem += chunk;
                        });

                        data.on('end', () => {
                            checksum = mem.split(' ', 1)[0];
                        });
                    });
                }
            } else {
                let mem = '';

                sha.on('data', (chunk) => {
                    mem += chunk;
                });

                sha.on('end', () => {
                    checksum = mem.split(' ', 1)[0];
                });
            }
        })
        .on('error', (error) => {
            console.error(error);
        });

    console.log('Downloading GZip...\t', gitURL);

    var file = fs.createWriteStream(download);
    https
        .get(gitURL, (response) => {
            if (response.statusCode > 300 && response.statusCode < 400 && response.headers.location) {
                if (url.parse(response.headers.location).hostname) {
                    https.get(response.headers.location, (tarball) => {
                        const sha512 = crypto.createHash('sha512');
                        sha512.setEncoding('hex');

                        tarball.on('end', () => {
                            sha512.end();

                            const hex = sha512.read();

                            if (hex !== checksum) {
                                fs.unlinkSync(download);
                                throw new Error('Checksum failed!');
                            } else console.log('Checksum passed!');
                        });

                        tarball.pipe(file);
                        tarball.pipe(sha512);
                    });
                } else {
                    https.get(url.resolve(url.parse(url).hostname, response.headers.location), (tarball) => {
                        const sha512 = crypto.createHash('sha512');
                        sha512.setEncoding('hex');

                        tarball.on('end', () => {
                            sha512.end();

                            const hex = sha512.read();

                            if (hex !== checksum) {
                                fs.unlinkSync(download);
                                throw new Error('Checksum failed!');
                            } else console.log('Checksum passed!');
                        });

                        tarball.pipe(file);
                        tarball.pipe(sha512);
                    });
                }
            } else {
                const sha512 = crypto.createHash('sha512');
                sha512.setEncoding('hex');

                tarball.on('end', () => {
                    sha512.end();

                    const hex = sha512.read();

                    if (hex !== checksum) {
                        fs.unlinkSync(download);
                        throw new Error('Checksum failed!');
                    } else console.log('Checksum passed!');
                });

                tarball.pipe(file);
                tarball.pipe(sha512);
            }
        })
        .on('error', (error) => {
            console.error(error);
        });

    // TODO sha256 check the download before writing
    file.on('finish', () => {
        const tar = require('tar');

        console.log('Unzipping...\t', download);
        tar.extract({
            cwd: tmpdir,
            file: file.path,
            sync: true
        });

        let uncomp = path.join(tmpdir, base);
        var dist = path.join(__dirname, 'dist');

        const mv = require('mv');
        if (fs.existsSync(dist)) fs.rmdirSync(dist, { recursive: true });
        if (fs.existsSync(uncomp))
            mv(uncomp, dist, (error) => {
                if (error) throw error;
            });

        console.log(file.path, '->', dist);

        fs.unlinkSync(file.path);
    });
}
