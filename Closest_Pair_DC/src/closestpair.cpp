#include "closestpair.h"
#include <algorithm>
#include <limits>
#include <cmath>
#include <iostream>
#include <utility>

std::ostream& operator<< (std::ostream& os, Point const& p) {
	os << "(" << p.x << " , " << p.y << ") ";
	return os;
}

std::istream& operator>> (std::istream& os, Point& p) {
	os >> p.x >> p.y;
	return os;
}

////////////////////////////////////////////////////////////////////////////////
float DistanceBetweenTwoPoints(const Point& p1, const Point& p2);

float GetMinimumDistanceBetweenPoints(const std::vector<Point>& points);

float closestPair_aux(const std::vector<Point>& pointsX, const std::vector<Point>& pointsY);


float closestPair(std::vector< Point > const& points)
{
	const size_t size = points.size();

	if (size == 0) throw "zero size subset";
	if (size == 1) return std::numeric_limits<float>::max();

	std::vector<Point> pointsSortedX = points;
	std::sort(pointsSortedX.begin(), pointsSortedX.end(), [](const Point& a, const Point& b) { return a.x < b.x; });

	std::vector<Point> pointsSortedY = points;
	std::sort(pointsSortedY.begin(), pointsSortedY.end(), [](const Point& a, const Point& b) { return a.y < b.y; });

	return closestPair_aux(pointsSortedX, pointsSortedY);
}

float DistanceBetweenTwoPoints(const Point& p1, const Point& p2)
{
	return static_cast<float>(std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2)));
}

// O(n^2) BruteForce method of calculating distance between small set of points
float GetMinimumDistanceBetweenPoints(const std::vector<Point>& points)
{
	float minimum = std::numeric_limits<float>::max();

	const size_t size = points.size();
	for (size_t i = 0; i < size; ++i)
	{
		for (size_t j = i + 1; j < size; ++j)
		{
			if (DistanceBetweenTwoPoints(points[i], points[j]) < minimum)
			{
				minimum = DistanceBetweenTwoPoints(points[i], points[j]);
			}
		}
	}
	return minimum;
}

float closestPair_aux(const std::vector<Point>& pointsX, const std::vector<Point>& pointsY)
{
	const size_t size = pointsX.size();

	if (size <= 10)
		return GetMinimumDistanceBetweenPoints(pointsX);

	const size_t midIndex = size / 2;

	static auto ArePointsSame = [](float a, float b) {
		constexpr float epsilon = 1e-6f;
		return std::abs(a - b) < epsilon;
		};

	// Check if all points have the same x or y coordinates
	if (ArePointsSame(pointsX[0].x, pointsX[size - 1].x)) {
		if (ArePointsSame(pointsY[0].y, pointsY[size - 1].y))
			return 0.0f;
	}

	const std::vector<Point> leftX(pointsX.begin(), pointsX.begin() + midIndex);
	const std::vector<Point> rightX(pointsX.begin() + midIndex, pointsX.end());

	std::vector<Point> leftY, rightY;

	const float midXValue = pointsX[midIndex].x;
	std::partition_copy(
		pointsY.begin(), pointsY.end(),
		std::back_inserter(leftY), std::back_inserter(rightY),
		[midXValue](const Point& point)
		{
			return point.x <= midXValue;
		}
	);

	const float smallestLeft = closestPair_aux(leftX, leftY);
	const float smallestRight = closestPair_aux(rightX, rightY);
	const float minLeftRight = std::min(smallestLeft, smallestRight);

	std::vector<Point> edgeCasePoints;
	for (const auto& point : pointsY) {
		if (std::abs(point.x - pointsX[midIndex].x) < minLeftRight)
			edgeCasePoints.push_back(point);
	}

	float smallest = minLeftRight;
	for (size_t i = 0; i < edgeCasePoints.size(); ++i)
	{
		size_t j = i + 1;
		for (; j < edgeCasePoints.size() && (edgeCasePoints[j].y - edgeCasePoints[i].y) < minLeftRight && j <= i + 6; ++j)
		{
			smallest = std::min(smallest, DistanceBetweenTwoPoints(edgeCasePoints[i], edgeCasePoints[j]));
		}
	}

	return std::min(minLeftRight, smallest);
}