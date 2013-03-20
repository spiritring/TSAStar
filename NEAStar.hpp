#ifndef INCLUDE_NEASTAR_H
#define INCLUDE_NEASTAR_H

#include "Point.hpp"
#include <math.h>
#include <list>
#include <iostream>
#include <stdlib.h> 
using namespace std;

class Node;
class Map;
class NEAStar;

const static int direction[8][2] = {
	{-1,0},
	{1,0},
	{0,-1},
	{0,1},
	{-1,1},
	{1,1},
	{1,-1},
	{-1,-1},
};

char tMap[] =
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,
	0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,
	1,1,1,0,0,1,0,0,0,0,1,1,1,0,0,1,0,0,0,0,1,1,1,0,0,1,0,0,0,0,1,1,1,0,0,1,0,0,0,0,
	0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,
	0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,
	0,0,1,1,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,0,
	0,0,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,0,
	0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,
	0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,
	1,1,1,0,0,1,0,0,0,0,1,1,1,0,0,1,0,0,0,0,1,1,1,0,0,1,0,0,0,0,1,1,1,0,0,1,0,0,0,0,
	0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,
	0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,
	0,0,1,1,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,1,
	0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,1,
	0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,
	0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,
	1,1,1,0,0,1,0,0,0,0,1,1,1,0,0,1,0,0,0,0,1,1,1,0,0,1,0,0,0,0,1,1,1,0,0,1,0,0,0,0,
	0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,
	0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,
	0,0,1,1,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,1,
	0,0,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,1,1,
	0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,
	0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,
	1,1,1,0,0,1,0,0,0,0,1,1,1,0,0,1,0,0,0,0,1,1,1,0,0,1,0,0,0,0,1,1,1,0,0,1,0,0,0,0,
	0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,
	0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,1,1,
	0,0,1,1,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,1,
	0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,1,
	0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,
	0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,
	1,1,1,0,0,1,0,0,0,0,1,1,1,0,0,1,0,0,0,0,1,1,1,0,0,1,0,0,0,0,1,1,1,0,0,1,0,0,0,0,
	0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,
	0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,
	0,0,1,1,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,0,
	0,0,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,0,
	0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,
	0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,
	1,1,1,0,0,1,0,0,0,0,1,1,1,0,0,1,0,0,0,0,1,1,1,0,0,1,0,0,0,0,1,1,1,0,0,1,0,0,0,0,
	0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,
	0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,
	0,0,1,1,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,0,0,0,1,1,0,0,0,0,1,1,
	0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,1,
	0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};


class Map {
public:
	Map() {
		m_width = 40;
		m_height = 60;
		m_map = tMap;
		m_mapclose = new char[m_width*m_height];
		memset(m_mapclose,0,sizeof(char)*m_width*m_height);
	}
	~Map() {
	}

	char* m_map;
	char* m_mapclose;
	int m_width;
	int m_height;
};



class Node {
public:
	Node() {
		pFather = 0;
		nScore = 0;
	}

	Node(Point& pos, Point& start, Point& end, Node* father) {
		pPos = pos;

		int x = pos.m_x - start.m_x;
		int y = pos.m_y - start.m_y;

		int x2 = pos.m_x - end.m_x;
		int y2 = pos.m_y - end.m_y;

		nScore = (x*x + y*y) + (x2*x2 + y2*y2);

		pFather = father;
	}

public:
	Point pPos;
	unsigned long nScore;
	Node* pFather;
};



class NEAStar {
public:
	NEAStar() {
	}

	inline bool isCloseList(Point& pos)
	{
		if (pMap->m_mapclose[pos.m_x*pMap->m_width+pos.m_y] == 1){
			return false;
		}
		return true; 
	}

	inline bool isMapBlock(Point& pos)
	{
		if (pMap->m_map[pos.m_x*pMap->m_width+pos.m_y] == 1){
			return false;
		}
		return true;
	}

	void run() {

		Node* node = new Node(Point(2,0),Point(2,0),Point(2,4),NULL);

		while (true)
		{
			if (pCurrentPos == pEnd) {	
				break;
			}

			pCurrentPos = node->pPos;
			openList.remove(node);
			closeList.push_back(node);
			pMap->m_mapclose[node->pPos.m_x*pMap->m_width+node->pPos.m_y] = 1;

			for (int i = 0 ; i < 8 ; i++)
			{
				Point _Pos;
				_Pos.m_x = pCurrentPos.m_x + direction[i][0];
				_Pos.m_y = pCurrentPos.m_y + direction[i][1];

				if (_Pos.m_x >= 0 && _Pos.m_x < pMap->m_height &&
					_Pos.m_y >= 0 && _Pos.m_y < pMap->m_width)
				{
					if (isMapBlock(_Pos) && isCloseList(_Pos))//��������openlist����Ͳ�������.
					{
						openList.push_back(new Node(_Pos,pStart,pEnd,node));
						pMap->m_mapclose[_Pos.m_x*pMap->m_width+_Pos.m_y] = 1;
					}
				}
			}

			if (openList.empty())
			{
				return;
			}

			Node* minNode = openList.front();
			for (list<Node*>::iterator iter = openList.begin(); iter != openList.end() ; iter++)
			{
				Node* node = (*iter);
				if (node->nScore < minNode->nScore)
				{
					minNode = node;
				}
			}

			node = minNode;
		}
	}

	void Init(Point& start,Point& end,Map* map) {
		pStart = start;
		pCurrentPos = start;
		pEnd = end;
		pMap = map;
	}

	Node* getResult()
	{
		return closeList.back();
	}

	void PrintMap()
	{
		char* _map = pMap->m_map;

		Node* node = getResult();
		while (node->pFather != NULL)
		{
			_map[node->pPos.m_x*pMap->m_width + node->pPos.m_y] = '.';

			node = node->pFather;
		}

		_map[pStart.m_x*pMap->m_width+pStart.m_y] = 3;
		_map[pEnd.m_x*pMap->m_width+pEnd.m_y] = 2;
// 
// 		  		for (list<Node*>::iterator iter = closeList.begin() ; closeList.end() != iter ; iter++)
// 		  		{
// 		  			Node* node = *iter;
// 		  			_map[node->pPos.m_x * pMap->m_width + node->pPos.m_y] = 2;
// 		  		}

		for (int i = 0; i < pMap->m_height ; i++)
		{
			for (int j = 0 ; j < pMap->m_width ; j++)
			{
				char c = _map[i*pMap->m_width+j];
				if (c == 0)
				{
					cout << " ";
				}
				else if (c == 1)
				{
					cout << "0";
				}
				else if (c == 2)
				{
					cout << "+";
				}
				else
				{
					cout << c;
				}
			}
			cout << endl;
		}
	}

private:
	Point pCurrentPos;
	Point pStart;
	Point pEnd;
	Map* pMap;

	list<Node*> openList;
	list<Node*> closeList;
};

#endif // INCLUDE_NEASTAR_H