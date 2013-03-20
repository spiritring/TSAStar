var fs = require('fs');
exports.TSDoFile = function ( path ) {
    try {
        var data = fs.readFileSync(path , "utf-8");
        eval(data);
    } finally {
        console.log("Cant Find File Path = " + path);
    }
}