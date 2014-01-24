#include <Point.h>

using namespace std;

Point::Point() {
}

Point::Point(int32_t x, int32_t y) :
	pair<int32_t, int32_t>(x, y) {
}

Point::~Point() {

}

bool Point::operator==(const Point& _p) {
	return (this->first == _p.first && this->second == _p.second);
}

bool Point::operator!=(const Point& _p) {
	return !(*this == _p);
}

ostream& operator<<(ostream& os, const Point& p) {
	os << "(" << p.first << "," << p.second << ")";
	return os;
}