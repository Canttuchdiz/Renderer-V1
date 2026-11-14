#include "vec3.h"
#include "cam.h"

const double pi = std::acos(-1.0);

double degrees_to_radians(double degrees) { return degrees * (pi / 180.0); }

Camera::Camera(int width, double aspect_ratio, double fov, Point3 position) : image_width_{width},
                                                                              horizontal_fov_{fov},
                                                                              aspect_ratio_{aspect_ratio},
                                                                              position_{position},
                                                                              forward_{Vector3(0, 0, 1)},
                                                                              up_{Vector3(0, 1, 0)},
                                                                              right_{Vector3(1, 0, 0)} {}

Point3 Camera::position() const { return position_; }

Point3 Camera::pixel_position(int x, int y) const
{
    Point3 plane_position = position_ + (forward_ * (1 / std::tan(degrees_to_radians(horizontal_fov_ / 2))) + (up_ / aspect_ratio_) - right_) * (image_width_ / 2.0);
    Point3 pixel_x = plane_position + (right_ * ((2 * x + 1)/2.0));
    Point3 pixel_pos = pixel_x - (up_ * ((2 * y + 1)/2.0));
    
    return pixel_pos;
}