//#include "closestpair.h"
//#include <algorithm>
//#include <limits>
//#include <cmath>
//#include <iostream>
//#include <utility>
//
//std::ostream& operator<< (std::ostream& os, Point const& p) {
//	os << "(" << p.x << " , " << p.y << ") ";
//	return os;
//}
//
//std::istream& operator>> (std::istream& os, Point & p) {
//	os >> p.x >> p.y;
//	return os;
//}
//
//////////////////////////////////////////////////////////////////////////////////
//
//// Helper function to compute distance
//float distance(const Point& p1, const Point& p2) 
//{
//    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
//}
//
//float closestPair_aux(const std::vector<Point>& pointsX, const std::vector<Point>& pointsY) 
//{
//    int size = pointsX.size();
//
//	// Save time by handling more base cases
//	if (size==2) 
//	{
//		return distance(pointsX[0], pointsX[1]);
//	}
//	if (size==3)
//	{
//        float dist1 = distance(pointsX[0], pointsX[1]);
//        float dist2 = distance(pointsX[1], pointsX[2]);
//        float dist3 = distance(pointsX[0], pointsX[2]);
//        return std::min({dist1, dist2, dist3});
//    }
//    if (size == 4) 
//	{
//        float dist1 = distance(pointsX[0], pointsX[1]);
//        float dist2 = distance(pointsX[0], pointsX[2]);
//        float dist3 = distance(pointsX[0], pointsX[3]);
//        float dist4 = distance(pointsX[1], pointsX[2]);
//        float dist5 = distance(pointsX[1], pointsX[3]);
//        float dist6 = distance(pointsX[2], pointsX[3]);
//        return std::min({dist1, dist2, dist3, dist4, dist5, dist6});
//    }
//    if (size == 5) 
//    {
//        float dist1 = distance(pointsX[0], pointsX[1]);
//        float dist2 = distance(pointsX[0], pointsX[2]);
//        float dist3 = distance(pointsX[0], pointsX[3]);
//        float dist4 = distance(pointsX[0], pointsX[4]);
//        float dist5 = distance(pointsX[1], pointsX[2]);
//        float dist6 = distance(pointsX[1], pointsX[3]);
//        float dist7 = distance(pointsX[1], pointsX[4]);
//        float dist8 = distance(pointsX[2], pointsX[3]);
//        float dist9 = distance(pointsX[2], pointsX[4]);
//        float dist10 = distance(pointsX[3], pointsX[4]);
//        return std::min({dist1, dist2, dist3, dist4, dist5, dist6, dist7, dist8, dist9, dist10});
//    }
//
//	// Divide
//    int mid = size / 2;
//    Point midPoint = pointsX[mid];
//	// For sorted points, check if all x-coordinates are the same
//    if (pointsX[0].x == midPoint.x && pointsX[size-1].x == midPoint.x)
//	 {
//        // Switch to y-ordering.
//        midPoint = pointsY[mid];
//        if (pointsY[0].y == midPoint.y && pointsY[size-1].y == midPoint.y) 
//		{
//             // Optimize: All points are the same. No need to check further
//            return 0.0;
//        }
//    }
//    std::vector<Point> leftX(pointsX.begin(), pointsX.begin() + mid);
//    std::vector<Point> rightX(pointsX.begin() + mid, pointsX.end());
//	// Sort Y for points in leftX and rightX
//	std::vector<Point> leftY;
//    std::vector<Point> rightY;
//    leftY.reserve(mid); 
//    rightY.reserve(pointsY.size() - mid); 
//    for (const auto& point : pointsY)
//	 {
//        if (point.x <= midPoint.x)
//		{
//            leftY.push_back(point);
//        } 
//		else
//		{
//            rightY.push_back(point);
//        }
//    }
//
//    // Conquer
//    float dL = closestPair_aux(leftX, leftY);
//    float dR = closestPair_aux(rightX, rightY);
//    float d = std::min(dL, dR);
//
//	// Merge
//    // closest pair split by the vertical line needs extra checking
//    std::vector<Point> extraCheckingPoints;
//    for (const auto& point : pointsY) 
//	{
//         // Optimize: check x diff < d to eliminate points far from vertical line
//        if (abs(point.x - midPoint.x) < d)  // midPoint is on the vertical line
//		{
//            extraCheckingPoints.push_back(point);
//        }
//    }
//    float min_extraCheckingPoints = d;
//    for (unsigned int i = 0; i < extraCheckingPoints.size(); ++i) 
//	{
//        for (unsigned int j = i + 1; 
//            j < extraCheckingPoints.size() 
//            && (extraCheckingPoints[j].y - extraCheckingPoints[i].y) < d  // Optimize: check y before actual calculating distance
//            && j <= i + 6;
//            ++j) 
//		{
//            min_extraCheckingPoints = std::min(min_extraCheckingPoints, distance(extraCheckingPoints[i], extraCheckingPoints[j]));
//        }
//    }
//    return std::min(d, min_extraCheckingPoints);
//}
//
//
//float closestPair ( std::vector< Point > const& points )
// {
//	int size = points.size();
//	if (size==0) throw "zero size subset";
//	if (size==1) return std::numeric_limits<float>::max();
//  	
//
//    std::vector<Point> pointsX = points;
//    std::vector<Point> pointsY = points;
//
//    // Optimize: sorting before recursion
//    std::sort(pointsX.begin(), pointsX.end(), [](const Point& a, const Point& b) { return a.x < b.x; });
//    std::sort(pointsY.begin(), pointsY.end(), [](const Point& a, const Point& b) { return a.y < b.y; });
//
//    return closestPair_aux(pointsX, pointsY);
//}