#include <iostream>
#include <cmath>
#include <iomanip>

using std::cin;
using std::cout;

const double EPS = 1e-9;

class Point {
public:
  double x = 0;
  double y = 0;
  double z = 0;

  Point(double x = 0, double y = 0, double z = 0): x(x), y(y), z(z) {}
};

class LineSegment {
public:
  Point first;
  Point second;

  LineSegment(double x1, double y1, double z1, double x2, double y2, double z2):
  first(x1, y1, z1),
  second(x2, y2, z2) {}

};

double DistanceBetweenPoints(const Point& left, const Point& right);

double DistanceBetweenPointAndSegment(const Point& point,
                                      const LineSegment& segment);

double SearchMinDistance(const Point& point, Point& left, Point& right);
  // finds minimal distance between the point and the line segment from point
  // left to point right (using ternary search on it)

double SearchMin(const LineSegment& segment, Point& left, Point& right);
  // finds minimal distance between two line segments: first one is given as a
  // class LineSegment, second is the line segment from point left to point
  // right (using ternary search on it)

double CalculateDistance(const LineSegment& first_seg,
                         const LineSegment& second_seg);

////////////////////////////////////////////////////////////////////////////////

int main() {
  int x1 = 0, y1 = 0, z1 = 0,
      x2 = 0, y2 = 0, z2 = 0;

  cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
  LineSegment first_seg(x1, y1, z1, x2, y2, z2);

  cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
  LineSegment second_seg(x1, y1, z1, x2, y2, z2);

  cout << std::setprecision(10) <<  CalculateDistance(first_seg, second_seg);
  return 0;
}

////////////////////////////////////////////////////////////////////////////////

double DistanceBetweenPoints(const Point& left, const Point& right) {
  return sqrt(pow(left.x - right.x, 2) + pow(left.y - right.y, 2) +
              pow(left.z - right.z, 2));
}

double DistanceBetweenPointAndSegment(const Point& point,
                                      const LineSegment& segment) {
  Point left = segment.first;
  Point right = segment.second;
  return SearchMinDistance(point, left, right);
}


double SearchMinDistance(const Point& point, Point& left, Point& right) {
  // finds minimal distance between the point and the line segment from point
  // left to point right (using ternary search on it)

  if (DistanceBetweenPoints(left, right) < EPS) {
    Point result;
    result.x = (left.x + right.x) / 2;
    result.y = (left.y + right.y) / 2;
    result.z = (left.z + right.z) / 2;
    return DistanceBetweenPoints(point, result);
  }

  Point local_left;
  local_left.x = (left.x * 2 + right.x) / 3;
  local_left.y = (left.y * 2 + right.y) / 3;
  local_left.z = (left.z * 2 + right.z) / 3;

  Point local_right;
  local_right.x = (left.x + right.x * 2) / 3;
  local_right.y = (left.y + right.y * 2) / 3;
  local_right.z = (left.z + right.z * 2) / 3;

  if (DistanceBetweenPoints(local_left, point) <
      DistanceBetweenPoints(local_right, point)) {

    return SearchMinDistance(point, left, local_right);
  } else {
    return SearchMinDistance(point, local_left, right);
  }
}

double SearchMin(const LineSegment& segment, Point& left, Point& right) {
  // finds minimal distance between two line segments: first one is given as a
  // class LineSegment, second is the line segment from point left to point
  // right (using ternary search on it)

  if (DistanceBetweenPoints(left, right) < EPS) {

    Point result;
    result.x = (left.x + right.x) / 2;
    result.y = (left.y + right.y) / 2;
    result.z = (left.z + right.z) / 2;
    return DistanceBetweenPointAndSegment(result, segment);

  }

  Point local_left;
  local_left.x = (left.x * 2 + right.x) / 3;
  local_left.y = (left.y * 2 + right.y) / 3;
  local_left.z = (left.z * 2 + right.z) / 3;

  Point local_right;
  local_right.x = (left.x + right.x * 2) / 3;
  local_right.y = (left.y + right.y * 2) / 3;
  local_right.z = (left.z + right.z * 2) / 3;

  if (DistanceBetweenPointAndSegment(local_left, segment) <
      DistanceBetweenPointAndSegment(local_right, segment)) {

    return SearchMin(segment, left, local_right);
  } else {
    return SearchMin(segment, local_left, right);
  }
}

double CalculateDistance(const LineSegment& first_seg,
                         const LineSegment& second_seg) {

  Point left = second_seg.first;
  Point right = second_seg.second;

  return SearchMin(first_seg, left, right);

}