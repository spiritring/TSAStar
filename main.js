var ts = require('./TSFileLoader');
ts.TSDoFile('./TSPoint.js');
ts.TSDoFile('./TSAStar.js');

var tsA = [1,2,3,4];
var tsB = [];
tsB = tsA.concat();
console.log(tsA);
console.log(tsB);

tsA[2] = 190;
tsB[2] = 90;
console.log(tsA);
console.log(tsB);






