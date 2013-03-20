TSDirection= [[-1,0],[1,0],[0,-1],[0,1],[-1,1],[1,1],[1,-1],[-1,-1]];
TSAStarMap = [
    0,0,0,0,0,0,0,0,0,0,
    0,0,1,1,1,1,0,0,0,0,
    0,0,1,0,0,1,0,0,0,0,
    1,1,1,0,0,1,0,0,0,0,
    0,0,0,0,0,1,0,0,0,0,
    0,0,0,1,1,1,1,0,1,0,
    0,0,1,1,0,0,0,0,1,0,
    0,0,0,0,0,0,0,0,1,1,
    0,0,1,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,
];

TSMap = function() {
    this.m_width = 10;
    this.m_height = 10;
    this.m_map = TSAStarMap;
    this.m_mapclose = TSAStarMap.concat();
};

TSNode = function(pos, start, end, father) {
    this.pPos = pos;
    var x = pos.m_x - start.m_x;
    var y = pos.m_y - start.m_y;
    var x2 = pos.m_x - end.m_x;
    var y2 = pos.m_y - end.m_y;
    this.nScore = (x*x + y*y) + (x2*x2 + y2*y2);
    this.pFather = father;
    this.get = function() {
        var newNode = new TSNode(this.pPos, new TSPoint(0,0), new TSPoint(0,0), this.pFather);
        newNode.nScore = this.nScore;
        return newNode;
    }
};





