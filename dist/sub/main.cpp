// Tessa Power 14112766
// Assignment 3
//
// Styleguide: Google C++ Style Guidelines
// https://google.github.io/styleguide/cppguide.html
//
// C++ Standard: C++17
// clang++ -std=c++17 -o main main.cpp && ./main

// Dear Marker,
//
// Please see the alg namespace (line 495) for the main functions that process
// the image of the buttons, and in particular the recursive functions.
//
// Unfortunately due to the requirement of submitting a single .cpp file, this
// project, which was neatly organised into easily understood and succint header
// and source files, has now become an abomination. Due to the interdependent
// nature of the classes and code, it's not possible to organise the classes in
// a way that makes things easier to grasp as a whole. For that, I am truly
// sorry!
//
// Realistically, we should be allowed (and encouraged) to submit a .zip of our
// projects for assignments so that we might avoid creating such unreadable
// programs that are unpleasant to mark. If things get too difficult, I can
// always send a .zip of my project or a create a GitHub Gist. Best of luck!

#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

// ⚠️ WARNING ⚠️
// These global variables are part of the assignment starter code & can't be
// altered.
int screenx, screeny, maxcolours;

// Setting this to true will visually color all test points in the output image.
// This is useful to visualise the process of checking for broken buttons.
#define DEBUG_VISUALIZATIONS false

/* =============================================================================
 *   geom (namespace)
 *   Contains the classes that are primarily concerned with geometry.
 * =============================================================================
 */
namespace geom {

// Forward declarations
class RectIterator;
class PerimeterIterator;
class CircumferenceIterator;

class Point {
public:
  constexpr Point(int X, int Y) noexcept : x{X}, y{Y} {};

  [[nodiscard]] int get_x() const { return x; }
  [[nodiscard]] int get_y() const { return y; }

  /**
   * @return Array containing the neighboring top, right, bottom, and left
   *   points as cartesian coordinates in that order.
   */
  [[nodiscard]] std::array<Point, 4> neighbors() const;

  constexpr friend bool operator==(const Point &lhs, const Point &rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }

  constexpr friend bool operator!=(const Point &lhs, const Point &rhs) {
    return !(lhs == rhs);
  }

private:
  int x;
  int y;
}; // Point

std::array<geom::Point, 4> geom::Point::neighbors() const {
  // We base the neighboring points on the graphics Cartesian Coordinate system
  // with the origin starting in the top left corner [0, 0].
  // x increases horizontally to the right, y increases vertically down.
  // Neighbours:       [x  , y-1] (Top)
  // (Left) [x-1, y  ] [x  , y  ] [x+1, y  ] (Right)
  //                   [x  , y+1] (Bottom)
  //
  Point top{x, y - 1};
  Point right{x + 1, y};
  Point bottom{x, y + 1};
  Point left{x - 1, y};

  return std::array<Point, 4>{top, right, bottom, left};
}

class Rect {
public:
  constexpr explicit Rect(Point p) noexcept
      : min_x{p.get_x()}, max_x{p.get_x()}, min_y{p.get_y()}, max_y{
                                                                  p.get_y()} {};

  constexpr Rect(int min_x, int max_x, int min_y, int max_y) noexcept
      : min_x{min_x}, max_x{max_x}, min_y{min_y}, max_y{max_y} {};

  [[nodiscard]] int get_min_x() const { return min_x; }
  [[nodiscard]] int get_max_x() const { return max_x; }
  [[nodiscard]] int get_min_y() const { return min_y; }
  [[nodiscard]] int get_max_y() const { return max_y; }

  [[nodiscard]] constexpr int width() const { return max_x - min_x; }
  [[nodiscard]] constexpr int height() const { return max_y - min_y; }

  [[nodiscard]] PerimeterIterator perimeter() const;

  [[nodiscard]] RectIterator begin() const;
  [[nodiscard]] RectIterator end() const;

  [[nodiscard]] constexpr Point center() const {
    return Point{(max_x + min_x) / 2, (max_y + min_y) / 2};
  }

  [[nodiscard]] constexpr bool is_fully_enclosed_by(Rect const &other) const {
    return this->min_x > other.min_x &&
           this->max_x<other.max_x &&this->min_y> other.min_y &&
           this->max_y < other.max_y;
  }

  void expand_to_include(Point const &c);

private:
  int min_x;
  int max_x;
  int min_y;
  int max_y;
}; // Rect

void geom::Rect::expand_to_include(Point const &c) {
  min_x = std::min(min_x, c.get_x());
  max_x = std::max(max_x, c.get_x());
  min_y = std::min(min_y, c.get_y());
  max_y = std::max(max_y, c.get_y());
}

class RectIterator {
public:
  RectIterator(Rect const &rect, Point starting_point) noexcept
      : rect{rect}, current{starting_point} {};

  [[nodiscard]] Point const &operator*() const { return current; };

  RectIterator operator++();

  friend bool operator!=(RectIterator const &lhs, RectIterator const &rhs) {
    return lhs.current != rhs.current;
  }

  friend Rect;

private:
  Rect rect;
  Point current = Point{rect.get_min_x(), rect.get_min_y()};
}; // RectIterator

geom::RectIterator geom::RectIterator::operator++() {
  if (current.get_x() < rect.get_max_x()) {
    current = Point{current.get_x() + 1, current.get_y()};
  } else {
    current = Point{rect.get_min_x(), current.get_y() + 1};
  }

  return *this;
}

geom::RectIterator geom::Rect::begin() const {
  return RectIterator{*this, Point{min_x, min_y}};
}

geom::RectIterator geom::Rect::end() const {
  return RectIterator{*this, Point{min_x, max_y + 1}};
}

class PerimeterIterator {
public:
  constexpr PerimeterIterator(Rect const &rect, Point starting_point) noexcept
      : rect{rect}, current{starting_point} {};

  [[nodiscard]] constexpr Point const &operator*() const { return current; };

  PerimeterIterator operator++();

  friend bool operator!=(PerimeterIterator const &lhs,
                         PerimeterIterator const &rhs) {
    return lhs.current != rhs.current;
  }

  [[nodiscard]] PerimeterIterator begin() const;
  [[nodiscard]] PerimeterIterator end() const;

private:
  Rect rect;
  Point current;
};

geom::PerimeterIterator geom::PerimeterIterator::begin() const {
  return PerimeterIterator{rect, Point{rect.get_min_x(), rect.get_min_y()}};
}

geom::PerimeterIterator geom::PerimeterIterator::end() const {
  return PerimeterIterator{rect, Point{rect.get_min_x(), rect.get_max_y() + 1}};
}

geom::PerimeterIterator geom::PerimeterIterator::operator++() {
  // Top or bottom edges

  if (current.get_y() == rect.get_min_y() ||
      current.get_y() == rect.get_max_y()) {
    if (current.get_x() < rect.get_max_x()) {
      current = Point{current.get_x() + 1, current.get_y()};
    } else {
      current = Point{rect.get_min_x(), current.get_y() + 1};
    }
  } else {
    // Flip flop between vertical edges
    if (current.get_x() == rect.get_min_x()) {
      current = Point{rect.get_max_x(), current.get_y()};
    } else if (current.get_x() == rect.get_max_x()) {
      current = Point{rect.get_min_x(), current.get_y() + 1};
    }
  }

  return *this;
}

geom::PerimeterIterator geom::Rect::perimeter() const {
  return PerimeterIterator{*this, Point{this->min_x, this->min_y}};
}

class Circle {
public:
  constexpr Circle(Point o, int r) noexcept : origin{o}, radius{r} {};

  [[nodiscard]] Point get_origin() const { return origin; }
  [[nodiscard]] int get_radius() const { return radius; }

  [[nodiscard]] CircumferenceIterator circumference() const;
  [[nodiscard]] constexpr Rect bounding_box() const {
    return Rect{origin.get_x() - radius, origin.get_x() + radius,
                origin.get_y() - radius, origin.get_y() + radius};
  }

private:
  const Point origin;
  const int radius;
}; // Circle

class CircumferenceIterator {
public:
  // Include the usual iterator tags for compatability with STL algorithms
  using iterator_category = std::forward_iterator_tag;
  using difference_type = int;
  using value_type = Point;
  using pointer = Point *;
  using reference = Point &;

  constexpr CircumferenceIterator(Circle const &c, int dx) noexcept
      : circle{c}, dx{dx} {};

  [[nodiscard]] value_type operator*() const;
  CircumferenceIterator operator++();

  friend bool operator==(CircumferenceIterator const &lhs,
                         CircumferenceIterator const &rhs) {
    return lhs.dx == rhs.dx;
  }

  friend bool operator!=(CircumferenceIterator const &lhs,
                         CircumferenceIterator const &rhs) {
    return !(lhs == rhs);
  }

  [[nodiscard]] CircumferenceIterator begin() const;
  [[nodiscard]] CircumferenceIterator end() const;

private:
  Circle const &circle;
  int dx = 0;
  int octant = 0;
}; // CircumferenceIterator

geom::CircumferenceIterator geom::CircumferenceIterator::begin() const {
  return CircumferenceIterator{circle, 0};
}

geom::CircumferenceIterator geom::CircumferenceIterator::end() const {
  const int end_dx = static_cast<int>(circle.get_radius() / sqrt(2) + 1);
  return CircumferenceIterator{circle, end_dx};
}

geom::Point geom::CircumferenceIterator::operator*() const {
  const int r = circle.get_radius();
  const int dy = (int)sqrt(pow(r, 2) - pow(dx, 2));

  geom::Point const &origin = circle.get_origin();
  switch (octant) {
  case 0:
    return Point{origin.get_x() + dx, origin.get_y() + dy};
  case 1:
    return Point{origin.get_x() + dx, origin.get_y() - dy};
  case 2:
    return Point{origin.get_x() - dx, origin.get_y() + dy};
  case 3:
    return Point{origin.get_x() - dx, origin.get_y() - dy};
  case 4:
    return Point{origin.get_x() + dy, origin.get_y() + dx};
  case 5:
    return Point{origin.get_x() + dy, origin.get_y() - dx};
  case 6:
    return Point{origin.get_x() - dy, origin.get_y() + dx};
  case 7:
    return Point{origin.get_x() - dy, origin.get_y() - dx};
  default:
    assert(false);
  }
}

geom::CircumferenceIterator geom::CircumferenceIterator::operator++() {
  if ((++octant %= 8) == 0) {
    ++dx;
  }

  return *this;
}

geom::CircumferenceIterator geom::Circle::circumference() const {
  return CircumferenceIterator{*this, 0};
}

class Color {
public:
  constexpr Color(uint8_t r, uint8_t g, uint8_t b) noexcept
      : R{r}, G{g}, B{b} {};

  const uint8_t R;
  const uint8_t G;
  const uint8_t B;

  constexpr static Color Red() { return Color{255, 0, 0}; }
  constexpr static Color EmeraldGreen() { return Color{0, 204, 102}; }
  constexpr static Color AzureBlue() { return Color{0, 127, 255}; }
}; // Color

} // namespace geom

using PointPredicate = std::function<bool(geom::Point const &)>;
using OptionalPointVecRef =
    std::optional<std::reference_wrapper<std::vector<geom::Point>>>;

/* =============================================================================
 *   img (namespace)
 *   Contains the classes & functions that work primarily to load, alter, &
 *   save the image.
 * =============================================================================
 */
namespace img {
// ⚠️ WARNING ⚠️
// This class is part of the assignment starter code, so can't be altered.
class pixel_class {
private:
  int red, green, blue;
  bool exclude; // if true, do not check this pixel
public:
  void loaddata(int v1, int v2, int v3);
  void datatofile(std::fstream &ppmfile);
  int getR() const { return red; }
  int getG() const { return green; }
  int getB() const { return blue; }
  void setexclude(bool ex) { exclude = ex; }
  bool getexclude() { return exclude; }
};

void img::pixel_class::loaddata(int v1, int v2, int v3) {
  red = v1;
  green = v2;
  blue = v3;
}

void img::pixel_class::datatofile(std::fstream &ppmfile) {
  // write the data for one pixel to the ppm file
  ppmfile << red << " " << green;
  ppmfile << " " << blue << "  ";
}

// ⚠️ WARNING ⚠️
// This global variable is part of the assignment starter code, so can't be
// altered.
pixel_class picture[600][600];

// ⚠️ WARNING ⚠️
// This function is part of the assignment starter code, so can't be altered.
// This function breaks the usual control flow & may exit the program, instead
// of throwing an exception!
void loadButtons() {
  // load the picture from Buttons.ppm
  int x, y, R, G, B;
  std::fstream infile;
  std::string infilename, line;
  infilename = "Buttons.ppm";
  infile.open(infilename.c_str(), std::fstream::in);
  if (infile.is_open() == false) {
    std::cout << "ERROR: not able to open " << infilename << std::endl;
    std::exit(2);
  }
  std::getline(infile, line);   // this line is "P3"
  std::getline(infile, line);   // this line is "# filename"
  infile >> screenx >> screeny; // this line is the size
  infile >> maxcolours;         // this line is 256
  for (y = 0; y < screeny; y++) {
    for (x = 0; x < screenx; x++) {
      infile >> R >> G >> B;
      picture[y][x].loaddata(R, G, B);
      picture[y][x].setexclude(false);
    }
  }
  infile.close();
}

void saveButtons(std::string const &output_filename) {
  std::fstream output_file;

  std::cout << "Writing to " << output_filename << std::endl;
  output_file.open(output_filename.c_str(), std::fstream::out);
  if (!output_file.is_open()) {
    throw std::runtime_error("Unable to write to " + output_filename);
  }

  // Needed for .ppm file formatting
  output_file << "P3" << std::endl;
  output_file << "# " << output_filename << std::endl;
  output_file << screenx << " " << screeny << std::endl;
  output_file << maxcolours << std::endl;

  // pixel rgb values
  for (int y = 0; y < screeny; ++y) {
    for (int x = 0; x < screenx; ++x) {
      picture[y][x].datatofile(output_file);
    }
    output_file << std::endl;
  }

  output_file.close();
}

img::pixel_class *get_pixel(geom::Point const &p) {
  return (p.get_x() >= 0 && p.get_x() < screenx && p.get_y() >= 0 &&
          p.get_y() < screeny)
             ? &picture[p.get_y()][p.get_x()]
             : nullptr;
}

bool is_part_of_button(geom::Point const &point) {
  auto px = get_pixel(point);
  if (px != nullptr) {
    return px->getR() > 128;
  }

  return false;
}

void draw_point(geom::Point const &p, geom::Color const &color) {
  auto px = get_pixel(p);
  if (px != nullptr) {
    px->loaddata(color.R, color.G, color.B);
  }
}

} // namespace img

constexpr int kNumRequiredButtonHoles = 4;

/* =============================================================================
 *   Namespace alg
 *   Contains the algorithms that discover & categorize buttons (broken or not)
 * =============================================================================
 */
namespace alg {

/**
 * Discovers the extent of points that are deemed connected to the given point.
 * @param[in] point The point to start discovering from.
 * @param[in, out] discovered_extent A Rect which will be grown to fit all the
 * connected points as they are discovered.
 * @param[in] pred_fn A predicate function which points must pass to be
 * considered part of the discovered extent.
 * @param[out] discovered_points An optional vector which, if provided, will
 * be filled with all discovered points.
 */
void discover_extent_of_connected_points(
    geom::Point const &point, geom::Rect &discovered_extent,
    PointPredicate const &pred_fn,
    OptionalPointVecRef discovered_points = std::nullopt) {
  auto px = img::get_pixel(point);
  if (!px || px->getexclude() || !pred_fn(point)) {
    return;
  }

  // Tracking discovered points is optional so points are only appended to the
  // vector if a vector is provided
  if (discovered_points) {
    discovered_points->get().emplace_back(point);
  }

  px->setexclude(true);
  discovered_extent.expand_to_include(point);

  for (auto const &p : point.neighbors()) {
    discover_extent_of_connected_points(p, discovered_extent, pred_fn,
                                        discovered_points);
  }
}

/**
 * Explores the area within the bounds (which is expected to be the bounds of a
 * button) to determine the number of button holes the button has.
 * @param bounds
 * @return The number of enclosed button holes the button has
 */
int discover_num_button_holes(geom::Rect const &bounds) {
  int num_btn_holes = 0;

  // Iterate over the pixels within the bounding box of the button & flip
  // their exclude status. Then the pixels are in a "clean" slate.
  for (auto const &point : bounds) {
    img::get_pixel(point)->setexclude(false);
  }

  for (auto const &point : bounds) {
    auto px = img::get_pixel(point);
    if (!px) {
      continue;
    }

    const bool did_discover_new_empty_area =
        !img::is_part_of_button(point) && !px->getexclude();

    if (did_discover_new_empty_area) {
#if DEBUG_VISUALIZATIONS
      std::vector<geom::Point> discovered_points{};
#endif
      geom::Rect discovered_extent = geom::Rect{point};

      discover_extent_of_connected_points(
          point, discovered_extent,
          [](geom::Point const &p) { return !img::is_part_of_button(p); }
#if DEBUG_VISUALIZATIONS
          ,
          discovered_points
#endif
      );

      // If the connected pixels touch the bounds, then the empty area
      // discovered isn't a fully enclosed buttonhole. Conversely, if it
      // was then we have found a buttonhole.
      if (discovered_extent.is_fully_enclosed_by(bounds)) {
        num_btn_holes++;

#if DEBUG_VISUALIZATIONS
        for (auto const &p : discovered_points) {
          img::draw_point(p, geom::Color::AzureBlue());
        }
#endif
      }
    }

    px->setexclude(true);
  }

  return num_btn_holes;
}

/**
 * Discovers all the bounding boxes for the buttons. It does not categorize
 * the buttons as broken or not broken.
 * @return A vector containing the bounds of all the buttons in the image.
 */
std::vector<geom::Rect> discover_all_button_bounds() {
  std::vector<geom::Rect> bounds_of_buttons;
  const geom::Rect image_rect = geom::Rect{0, screenx - 1, 0, screeny - 1};

  for (auto const &point : image_rect) {
    auto px = img::get_pixel(point);

    const bool did_discover_new_button =
        img::is_part_of_button(point) && !px->getexclude();

    if (did_discover_new_button) {
      // Initialize our bounds to a 0-by-0 box which discover_bounds expands
      geom::Rect discovered_extent{point};
      alg::discover_extent_of_connected_points(
          point, discovered_extent, [](geom::Point const &point) {
            return img::is_part_of_button(point);
          });

      bounds_of_buttons.emplace_back(discovered_extent);
    }

    px->setexclude(true);
  }

  return bounds_of_buttons;
}

/**
 * The primary function which will discover all buttons,
 * categorize them as broken or not broken, & output a new
 * image. The image will contain the buttons with red boxes
 * to indicate broken buttons, or otherwise green for OK.
 *
 * Set DEBUG_VISUALIZATIONS to true to enable debug visualizations and see
 * what the algorithms have discovered/determined about each button.
 */
void process_image() {
  for (auto const &bounds : alg::discover_all_button_bounds()) {
    bool is_broken = false;

    // Draw two concentric circles & require that the pixelated edge of the
    // button image falls between them.
    const int radius =
        static_cast<int>(std::max(bounds.width(), bounds.height()) / 2.0);

    const geom::Circle outer{bounds.center(), static_cast<int>(radius * 1.2)};
    const geom::Circle inner{bounds.center(), static_cast<int>(radius * 0.9)};

    auto outer_circumference = outer.circumference();
    auto inner_circumference = inner.circumference();

    is_broken |= std::any_of(outer_circumference.begin(),
                             outer_circumference.end(), img::is_part_of_button);

    is_broken |=
        std::any_of(inner_circumference.begin(), inner_circumference.end(),
                    [](auto p) { return !img::is_part_of_button(p); });

    is_broken |= alg::discover_num_button_holes(inner.bounding_box()) !=
                 kNumRequiredButtonHoles;

#if DEBUG_VISUALIZATIONS
    for (auto const &point : outer_circumference) {
      img::draw_point(point, geom::Color::AzureBlue());
    }
    for (auto const &point : inner_circumference) {
      img::draw_point(point, geom::Color::AzureBlue());
    }
#endif

    geom::Color status_color =
        is_broken ? geom::Color::Red() : geom::Color::EmeraldGreen();
    for (auto const &point : bounds.perimeter()) {
      img::draw_point(point, status_color);
    }
  }
}

} // namespace alg

const std::string kOutputFilename = "Buttons_processed.ppm";

int main() {
  img::loadButtons();
  alg::process_image();
  img::saveButtons(kOutputFilename);

  return EXIT_SUCCESS;
}
