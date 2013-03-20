var ts = require('./TSFileLoader');
ts.TSDoFile('./TSPoint.js');
ts.TSDoFile('./TSAStar.js');

var NEAStar = function() {
    this.pCurrentPos = new TSPoint(0,0);
    this.pStart = new TSPoint(0,0);
    this.pEnd = new TSPoint(0,0);
    this.pMap = new TSMap();
    this.openList = [];
    this.closeList = [];

    this.isCloseList = function(pos){
        if (this.pMap.m_mapclose[pos.m_x*this.pMap.m_width+pos.m_y] == 1){
            return false;
        }
        return true;
    };

    this.isMapBlock = function(pos){
        if (this.pMap.m_map[pos.m_x*this.pMap.m_width+pos.m_y] == 1){
            return false;
        }
        return true;
    };

    this.run = function() {
        var node = new TSNode(new TSPoint(2,0), new TSPoint(2,0), new TSPoint(2,4), null);
        while (true){
            if (this.pCurrentPos.equal(this.pEnd)) {
                break;
            }
            this.pCurrentPos = node.pPos;

            for (var i = 0 ; i < this.openList.length ; i++){
                var _node = this.openList[i];
                if (_node.pPos.equal(node.pPos)) {
                    this.openList.splice(i,i+1);
                    break;
                }
            }

            this.closeList.push(node); //TSTS
            this.pMap.m_mapclose[node.pPos.m_x * this.pMap.m_width + node.pPos.m_y] = 1;
            for (var i = 0 ; i < 4 ; i++){
                var _Pos = new TSPoint(this.pCurrentPos.m_x + TSDirection[i][0], this.pCurrentPos.m_y + TSDirection[i][1]);
                if (_Pos.m_x >= 0 && _Pos.m_x < this.pMap.m_height &&
                    _Pos.m_y >= 0 && _Pos.m_y < this.pMap.m_width){
                    if (this.isMapBlock(_Pos) && this.isCloseList(_Pos)){
                        this.openList.push(new TSNode(_Pos,this.pStart,this.pEnd,node));
                        this.pMap.m_mapclose[_Pos.m_x*this.pMap.m_width+_Pos.m_y] = 1;
                    }
                }
            }

            if (this.openList.length == 0){
                return;
            }

            var minNode = this.openList[0].get();
            for (var i = 0 ; i < this.openList.length; i++){
                var node = this.openList[i];
                if (node.nScore < minNode.nScore){
                    minNode = node.get();;
                }
            }
            node = minNode.get();;
        }
    }

    this.Init = function(start, end, map) {
        this.pStart = start;
        this.pCurrentPos = start;
        this.pEnd = end;
        this.pMap = map;
    }

    this.getResult = function(){
        return this.closeList[this.closeList.length-1];
    }

    this.PrintMap = function(){
        var _map = this.pMap.m_map;

        var node = this.getResult();
        while (node.pFather != null){
            _map[node.pPos.m_x * this.pMap.m_width + node.pPos.m_y] = '.';
            node = node.pFather;
        }

        _map[this.pStart.m_x * this.pMap.m_width + this.pStart.m_y] = 3;
        _map[this.pEnd.m_x * this.pMap.m_width + this.pEnd.m_y] = 2;

        var R = "";

        for (var i = 0; i < this.pMap.m_height; i++){
            for (var j = 0 ; j < this.pMap.m_width; j++){
                var c = _map[i * this.pMap.m_width + j];
                if (c == 0){
                    R += ' ';
                }
                else if (c == 1){
                    R += '0';
                }
                else if (c == 2){
                    R += '+';
                }
                else{
                    R += c;
                }
            }
            R += '\n';
        }
        console.log(R);
    }
};

var star = new NEAStar();
var map = new TSMap();
star.Init(new TSPoint(2,0), new TSPoint(2,4), map);
star.run();
star.PrintMap();






