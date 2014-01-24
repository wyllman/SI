#ifndef POINT_H_
#define POINT_H_

#include <map>// Juan, no quites este include!!!!
#include <ostream>
#include <stdint.h>

class Point : public std::pair<int32_t, int32_t> {
public:
	Point();
	Point(int32_t, int32_t);
	~Point();
	bool operator==(const Point&);
	bool operator!=(const Point&);
	friend std::ostream& operator<<(std::ostream&, const Point&);
};

#endif
