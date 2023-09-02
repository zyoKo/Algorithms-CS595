#include "hull-bruteforce.h"

#include <algorithm>
#include <iostream>

bool Point::operator==(Point const& arg2) const
{
	return ((x == arg2.x) && (y == arg2.y));
}

std::ostream& operator<<(std::ostream& os, Point const& p)
{
	os << "(" << p.x << " , " << p.y << ") ";
	return os;
}

std::istream& operator>> (std::istream& os, Point& p) 
{
	os >> p.x >> p.y;
	return os;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//return value is (on left, on right)
std::pair<bool, bool> get_location(
	float const& p1x, //check which side of the line (p1x,p1y)-->(p2x,p2y) 
	float const& p1y, //point (qx,qy) is on
	float const& p2x,
	float const& p2y,
	float const& qx,
	float const& qy)
{
	Point dir = { p2x - p1x, p2y - p1y };
	Point norm = { dir.y, -dir.x };
	Point point = { qx - p1x, qy - p1y };

	//scalar product is positive if on right side
	float scal_prod = norm.x * point.x + norm.y * point.y;

	return std::make_pair((scal_prod < 0), (scal_prod > 0));
}

//struct Line
//{
//	Point& p1, &p2;
//
//	Line(Point& p1, Point& p2)
//		:	p1(p1), p2(p2)
//	{
//	}
//};

//returns a set of indices of points that form convex hull
std::set<int> hullBruteForce(std::vector<Point> const& points)
{
	int num_points = static_cast<int>(points.size());
	//std::cout << "number of points " << num_points << std::endl;
	if (num_points < 3) throw "bad number of points";

	std::set<int> hull_indices;

	for (auto i = 0; i < num_points - 1; ++i)	// initial point
	{
		for (auto j = i + 1; j < num_points; ++j)	// next point that forms line with initial point
		{
			// Create line
			//Line line(points[i], points[j]);

			int chooseSide; // 0 is left, 1 is right
			bool firstRun = true, shouldAddPoints = true;
			for (auto k = 0; k < num_points; ++k)	// testing all points other than the selected line indices
			{
				if (k == i || k == j)
					continue;

				auto checkPointSide = get_location(points[i].x, points[i].y, points[j].x, points[j].y, points[k].x, points[k].y);

				if (!firstRun)
				{
					if ((chooseSide == 0 && checkPointSide.second) || (chooseSide == 1 && checkPointSide.first))
					{
						shouldAddPoints = false;
						break;
					} 
				}
				else
				{
					chooseSide = checkPointSide.first ? 0 : 1;
					firstRun = false;
				}
			}

			//if ((pointsOnLeft == 0 && pointsOnRight != 0) || (pointsOnLeft != 0 && pointsOnRight == 0))
			if (shouldAddPoints)
			{
				hull_indices.emplace(i);
				hull_indices.emplace(j);
				break;
			}
		}
	}

	return hull_indices;
}

std::vector<int> hullBruteForce2(std::vector<Point> const& points)
{
	int num_points = static_cast<int>(points.size());
	if (num_points < 3) throw "bad number of points";

	std::vector<int> hull_indices;
	
	// finding the left most point
	int leftMostPoint = 0;
	for (int i = 1; i < num_points; ++i)
	{
		if (points[i].x < points[leftMostPoint].x)
			leftMostPoint = i;
	}

	int firstPoint = leftMostPoint, ccPoint;

	do 
	{
		hull_indices.emplace_back(firstPoint);

		ccPoint = (firstPoint + 1) % num_points;

		for (int i = 0; i < num_points; ++i)
		{
			if (get_location(points[firstPoint].x, points[firstPoint].y, points[i].x, points[i].y, points[ccPoint].x, points[ccPoint].y).second)
			{
				ccPoint = i;
			}
		}

		firstPoint = ccPoint;
	}
	while (firstPoint != leftMostPoint);

	return hull_indices;
}
