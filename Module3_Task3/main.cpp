#include <iostream>
#include <cmath>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

struct Point {
    double x;
    double y;

    Point operator+ (const Point& point) {
        return Point(x + point.x, y + point.y);
    }

    Point(double x, double y): x(x), y(y) {}
};

/**
 * Compares two polar angles (in the clock-wise direction). The first one is
 * defined by two points:
 * first_one and first_two. The second one is defined by two points:
 * second_one, second_two.
 *
 * @return If first angle is smaller -1 is returned. Otherwise 1 is returned.
 */
int CompareAngle(Point first_one, Point first_two, Point second_one,
                 Point second_two);

/**
 * Calculating dilation (Minkowski's sum) for two polygons: first and second.
 * The result is stored in vector result.
 */
void CalculateDilation(vector<Point>& first, vector<Point>& second,
                       vector<Point>& result);

/**
 * Checks if polygon is containing point (0;0) using binary search.
 */
bool ContainingCenterPoint(vector<Point>& polygon);

/**
 * Adjusting polygon so the beginning point (the rightest point among the lowest
 * points) of it is in the head of vector.
 */
void AdjustStartingPoint(size_t start_index, vector<Point>& polygon,
                         vector<Point>& new_polygon);

/**
 * Getting polygon and storing it in the vector of points.
 */
void GetPolygon(size_t number_of_points, vector<Point>& polygon);

////////////////////////////////////////////////////////////////////////////////

int main() {
    size_t first_num = 0, second_num = 0;

    cin >> first_num;
    vector<Point> first;

    GetPolygon(first_num, first);

    cin >> second_num;
    vector<Point> second;

    GetPolygon(second_num, second);

    vector<Point> polygon;
    CalculateDilation(first, second, polygon);

    if (ContainingCenterPoint(polygon)) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////


int CompareAngle(Point first_one, Point first_two, Point second_one,
                 Point second_two) {

  int result_modifier = 0; // The result might be different depending on what
  // semi-plane the angles are. To take it into consideration the final result
  // will be multiplied by one or minus one giving the correct final result.


  bool first_up = false; // True if first angle is placed on the upper
  // semi-plane.
  bool second_up = false; // True if second angle is placed on the upper
  // semi-plane.

  double ordinate_f = first_two.x - first_one.x;
  double ordinate_s = second_two.x - second_one.x;

  double abscissa_f = first_two.y - first_one.y;
  double abscissa_s = second_two.y - second_one.y;

  if (abscissa_f >= 0) {
    first_up = true;
  }

  if (abscissa_s >= 0) {
    second_up = true;
  }

  if (first_up && !second_up) {
    return -1;
  }

  if (second_up && !first_up) {
    return 1;
  }

  if (first_up) {
    result_modifier = 1;
  } else {
    result_modifier = -1;
  }

  double cos_f = ordinate_f / (sqrt(pow(ordinate_f, 2) + pow(abscissa_f, 2)));
  double cos_s = ordinate_s / (sqrt(pow(ordinate_s, 2) + pow(abscissa_s, 2)));

  if (cos_f < cos_s) {
    return -1 * result_modifier;
  } else {
    return 1 * result_modifier;
  }
}


void CalculateDilation(vector<Point>& first, vector<Point>& second,
                       vector<Point>& result) {
  int current_first = 0;
  int current_second = 0;

  size_t first_size = first.size();
  size_t second_size = second.size();

  first.push_back(first[0]);
  second.push_back(second[0]);

  first.push_back(first[1]);
  second.push_back(second[1]);

  while (current_first < first_size && current_second < second_size) {
    result.push_back(first[current_first] + second[current_second]);

    if (CompareAngle(first[current_first], first[current_first + 1],
        second[current_second], second[current_second + 1]) == -1) {
      ++current_first;
    } else {
      ++current_second;
    }

  }

  while (current_first < first_size) {
    result.push_back(first[current_first++] + second[0]);
  }

  while (current_second < second_size) {
    result.push_back(second[current_second++] + first[0]);
  }
}


bool ContainingCenterPoint(vector<Point>& polygon) {
  Point vertex = polygon[0];
  Point center(0, 0);
  size_t size = polygon.size();
  size_t left = 1, right = size - 1, mid = 0;

  if (CompareAngle(vertex, polygon[right], vertex, center) == -1) {
    return false;
  }

  if (CompareAngle(vertex, polygon[left], vertex, center) == 1) {
    return false;
  }

  while (left != right - 1) {
    mid = (left + right) / 2;

    if (CompareAngle(vertex, polygon[mid], vertex, center) == -1) {
      left = mid;
    } else {
      right = mid;
    }
  }

  double double_signed_square = (polygon[left].x - polygon[right].x) *
      (0 - polygon[right].y) - (polygon[left].y - polygon[right].y) *
      (0 - polygon[right].x);

  return double_signed_square >= 0;
}


void AdjustStartingPoint(size_t start_index, vector<Point>& polygon,
    vector<Point>& new_polygon) {

  for (size_t index = start_index; index < polygon.size(); ++index) {
    new_polygon.push_back(polygon[index]);
  }
  for (size_t index = 0; index < start_index; ++index) {
    new_polygon.push_back(polygon[index]);
  }
}


void GetPolygon(size_t number_of_points, vector<Point>& polygon) {
  double x = 0, y = 0;
  size_t bottom_right_point = 0;

  for (size_t index = 0; index < number_of_points; ++index) {
    cin >> x >> y;
    polygon.emplace_back(x, y);
    if (y < polygon[bottom_right_point].y) {
      bottom_right_point = index;
    }

    if ((y == polygon[bottom_right_point].y) &&
        (x > polygon[bottom_right_point].x)) {
      bottom_right_point = index;
    }
  }

  vector<Point> sorted_polygon;
  AdjustStartingPoint(bottom_right_point, polygon, sorted_polygon);
  polygon = sorted_polygon;
}