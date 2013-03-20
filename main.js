var ts = require('./TSFileLoader');
ts.TSDoFile('TSPoint.js');

var p1 = new TSPoint(10,15);
var p2 = p1.get();
p1.add(p2);
console.log(p1);

p2.m_x -= 50;
console.log(p1);
console.log(p2);





