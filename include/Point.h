#ifndef POINT_H_
#define POINT_H_

#include <bits/stl_pair.h>

class Point : public std::pair<int, int> {
public:
	Point();
	Point(int, int);
	~Point();
	bool operator==(const Point&);
	bool operator!=(const Point&);
};

#endif