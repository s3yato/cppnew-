const fs = require("fs");
const path = require("path");
const https = require("https");
const packageJson = require("./package.json");

const VERSION = `v${packageJson.version}`;
const REPO = "s3yato/cppnew-";

const platform = process.platform;
const arch = process.arch;

const platforms = {
    darwin: {
        arm64: "macos-arm64"
    },
    linux: {
        x64: "linux-x64"
    },
    win32: {
        x64: "windows-x64"
    }
};

const name = platforms[platform]?.[arch];

if (!name) {
    console.error(
        `cppnew: unsupported platform: ${platform}-${arch}`
    );
    process.exit(1);
}

const extension = platform === "win32" ? ".exe" : "";

const filename =
    `cppnew-${VERSION}-${name}${extension}`;

const url =
    `https://github.com/${REPO}/releases/download/${VERSION}/${filename}`;

const output = path.join(
    __dirname,
    platform === "win32" ? "cppnew-bin.exe" : "cppnew-bin"
);

console.log(`cppnew: downloading ${filename}...`);

const download = (url, destination) => {
    https.get(url, response => {
        if (
            response.statusCode >= 300 &&
            response.statusCode < 400 &&
            response.headers.location
        ) {
            download(response.headers.location, destination);
            return;
        }

        if (response.statusCode !== 200) {
            console.error(
                `cppnew: download failed (${response.statusCode})`
            );
            process.exit(1);
        }

        const file = fs.createWriteStream(destination);

        response.pipe(file);

        file.on("finish", () => {
            file.close(() => {
                if (platform !== "win32") {
                    fs.chmodSync(destination, 0o755);
                }

                console.log("cppnew: installation complete.");
            });
        });
    }).on("error", error => {
        console.error(`cppnew: ${error.message}`);
        process.exit(1);
    });
};

download(url, output);