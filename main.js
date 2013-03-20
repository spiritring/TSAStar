var ts = require('./TSFileLoader');
ts.TSDoFile('./TSPoint.js');
ts.TSDoFile('./TSAStar.js');


var star = new TSAStar();
var map = new TSMap();
star.Init(new TSPoint(2,0), new TSPoint(2,4), map);
star.run();
star.PrintMap();






