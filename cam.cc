#include <random>
#include "vec3.h"
#include "cam.h"
#include "constants.h"

std::random_device rd_cam;
std::mt19937 gen_cam(rd_cam());
std::uniform_real_distribution<double> dis_cam(0.0, 1.0);

double degrees_to_radians(double degrees) { return degrees * (pi / 180.0); }

Camera::Camera(int width, double aspect_ratio, double fov, Point3 position) : image_width_{width},
                                                                              aspect_ratio_{aspect_ratio},
                                                                              horizontal_fov_{fov},
                                                                              position_{position},
                                                                              forward_{Vector3(0, 0, 1)},
                                                                              up_{Vector3(0, 1, 0)},
                                                                              right_{Vector3(1, 0, 0)} {}

Point3 Camera::position() const { return position_; }

Point3 Camera::plane_origin() const {
        Point3 plane_position = position_ + (forward_ * (1 / std::tan(degrees_to_radians(horizontal_fov_ / 2))) + (up_ / aspect_ratio_) - right_) * (image_width_ / 2.0);
        return plane_position;
}

Point3 Camera::pixel_center(int x, int y) const {

    Point3 pixel_x = plane_origin() + (right_ * (x + 0.5));
    Point3 pixel_pos = pixel_x - (up_ * (y + 0.5));
    return pixel_pos;
}

Point3 Camera::pixel_random(int x, int y) const {
    Point3 pixel_x = plane_origin() + (right_ * (x + dis_cam(gen_cam)));
    Point3 pixel_pos = pixel_x - (up_ * (y + dis_cam(gen_cam)));
    return pixel_pos;
}