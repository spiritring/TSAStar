#ifndef INCLUDE_POINT_H
#define INCLUDE_POINT_H

class Point
{
public:
	Point();
	Point(int x, int y);
	~Point(){}

	bool operator==(Point& p){
		if (m_x == p.m_x && m_y == p.m_y){
			return true;
		}
		return false;
	}

	void operator=(Point& p){
		m_x = p.m_x;
		m_y = p.m_y;
	}

	int m_x;
	int m_y;
};

Point::Point() : m_x(0),m_y(0){}

Point::Point(int x, int y){
	m_x = x;
	m_y = y;
}

#endif // INCLUDE_POINT_H