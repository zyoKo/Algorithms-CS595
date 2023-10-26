#ifndef CLOSESTPAIR_H
#define CLOSESTPAIR_H
#include <vector>
#include <fstream> //ostream, istream
#include <utility> //pair

struct Point
{
	float x;
	float y;
};

std::ostream& operator<<(std::ostream& os, const Point& p);
std::istream& operator>>(std::istream& os, Point& p);

//returns a distance between 2 closest points
float closestPair(std::vector<Point> const& points);
#endif
