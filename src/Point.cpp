#include <Point.h>

Point::Point() {
}

Point::Point(int x, int y) :
	std::pair<int, int>(x, y) {
}

Point::~Point() {

}

bool Point::operator==(const Point& _p) {
	return (this->first == _p.first && this->second == _p.second);
}

bool Point::operator!=(const Point& _p) {
	return !(*this == _p);
}